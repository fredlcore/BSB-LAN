"""Keep LPB frames intact while executing the production string decoder."""
import re
import unittest

from source_harness import ROOT, between, compile_and_run


class StringTelegramRegression(unittest.TestCase):
    def test_string_decoding_preserves_frame_and_checksum(self):
        sketch = (ROOT / "BSB_LAN/BSB_LAN.ino").read_text(encoding="utf-8")
        printing = (ROOT / "BSB_LAN/include/print_telegram.h").read_text(encoding="utf-8")
        bus_source = (ROOT / "BSB_LAN/src/BSB/bsb.cpp").read_text(encoding="utf-8")
        decoder = between(printing, "case VT_STRING: // string", "case VT_PPS_TIME:")
        remove_char = "void remove_char(" + between(sketch, "void remove_char(", "void replace_char(")
        crc = "uint16_t crc_lpb(" + between(bus_source, "uint16_t BSB::CRC_LPB (", "// Generates CRC for PPS")
        capacity = re.search(r"char value\[(\d+)\];", sketch).group(1)
        compile_and_run(r'''
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>

#define CHECK(condition) do { if (!(condition)) { fprintf(stderr, "line %d: %s\n", __LINE__, #condition); return 1; } } while (0)
typedef uint8_t byte;
struct BusStub { uint8_t getPl_start() const { return 13; } } bus_stub;
static BusStub *bus = &bus_stub;
struct Decoded {
    char value[''' + capacity + r'''];
    uint16_t error;
    uint8_t guard[8];
} decodedTelegram;
static std::string debug;
static void printToDebug(const char *text) { debug += text; }
static void prepareToPrintHumanReadableTelegram(byte *, int, uint8_t) {}
''' + remove_char + crc + r'''
static void decode(byte *msg, int data_len) {
    switch (0) {
        case 0:
        ''' + decoder + r'''
    }
}
static void reset() {
    memset(&decodedTelegram, 0, sizeof(decodedTelegram));
    memset(decodedTelegram.guard, 0xA5, sizeof(decodedTelegram.guard));
    debug.clear();
}
static std::vector<byte> frame(const std::vector<byte> &payload) {
    std::vector<byte> msg(15 + payload.size(), 0);
    msg[0] = 0x78;
    msg[1] = static_cast<byte>(msg.size() - 1);
    msg[2] = 0x42;
    msg[4] = 0x0C;
    msg[5] = 0x02;
    msg[7] = 0x14;
    msg[8] = 0x07;
    msg[9] = 0x05;
    msg[12] = 0x01;
    memcpy(msg.data() + 13, payload.data(), payload.size());
    uint16_t crc_value = crc_lpb(msg.data(), msg[1]);
    msg[msg.size() - 2] = static_cast<byte>(crc_value >> 8);
    msg[msg.size() - 1] = static_cast<byte>(crc_value & 0xFF);
    return msg;
}
static bool crc_valid(std::vector<byte> &msg) {
    return crc_lpb(msg.data(), msg[1]) ==
        static_cast<uint16_t>((msg[msg.size() - 2] << 8) | msg.back());
}
int main() {
    // A real-shaped LPB device identity, filling its payload without a NUL.
    const std::string identity = "RVA43.223/500";
    std::vector<byte> msg = frame(std::vector<byte>(identity.begin(), identity.end()));
    const std::vector<byte> original = msg;
    CHECK(crc_valid(msg) && msg[msg.size() - 2] != 0);
    reset();
    decode(msg.data(), static_cast<int>(identity.size()));
    CHECK(std::string(decodedTelegram.value) == identity && debug == identity);
    CHECK(msg == original && crc_valid(msg));

    // Existing text behavior: stop at an embedded NUL, strip apostrophes only
    // from the decoded value, and leave the source/debug text unchanged.
    const byte quoted_payload[] = {'R', '\'', 'V', 'A', 0, 'x', 'y'};
    msg = frame(std::vector<byte>(quoted_payload, quoted_payload + sizeof(quoted_payload)));
    const std::vector<byte> quoted_original = msg;
    reset();
    decode(msg.data(), sizeof(quoted_payload));
    CHECK(std::string(decodedTelegram.value) == "RVA" && debug == "R'VA");
    CHECK(msg == quoted_original && crc_valid(msg));

    // Bounds are independent of a sender's payload length. Both the decoded
    // value and its debug representation fit, and neighboring state survives.
    std::vector<byte> long_payload(sizeof(decodedTelegram.value) + 10, 'A');
    msg = frame(long_payload);
    const std::vector<byte> long_original = msg;
    reset();
    decode(msg.data(), static_cast<int>(long_payload.size()));
    CHECK(strlen(decodedTelegram.value) == sizeof(decodedTelegram.value) - 1);
    CHECK(debug == std::string(sizeof(decodedTelegram.value) - 1, 'A'));
    CHECK(decodedTelegram.error == 0);
    for (unsigned i = 0; i < sizeof(decodedTelegram.guard); ++i) CHECK(decodedTelegram.guard[i] == 0xA5);
    CHECK(msg == long_original && crc_valid(msg));

    msg = frame(std::vector<byte>({0, 'x', 'y'}));
    const std::vector<byte> disabled_original = msg;
    reset();
    decode(msg.data(), 3);
    CHECK(std::string(decodedTelegram.value) == "-" && debug.empty());
    CHECK(msg == disabled_original && crc_valid(msg));

    reset();
    decode(msg.data(), 0);
    CHECK(decodedTelegram.error == 256 && msg == disabled_original);
    return 0;
}
''')


if __name__ == "__main__":
    unittest.main()
