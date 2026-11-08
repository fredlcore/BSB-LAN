"""Exercise the production JSON URL preparation and raw telegram parser."""
import re
import unittest

from source_harness import ROOT, between, compile_and_run


class JsonRawUrlRegression(unittest.TestCase):
    def test_raw_payload_and_destination_survive_json_preparation(self):
        sketch = (ROOT / "BSB_LAN/BSB_LAN.ino").read_text(encoding="utf-8")
        preparation = between(sketch, "uint8_t opening_brackets = 0;", "{//local variable scope")
        raw_branch = between(sketch, "if (p[2] == 'Y') {  // raw data query", "if (change_dest_success == true)")
        parsing = "uint8_t type =" + raw_branch.split("uint8_t type =", 1)[1]
        maximum = re.search(r"#define MAX_PARAM_LEN (\d+)", sketch).group(1)
        compile_and_run(r'''
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <vector>

#define CHECK(condition) do { if (!(condition)) { fprintf(stderr, "line %d: %s\n", __LINE__, #condition); return 1; } } while (0)
static uint8_t destination_changed_to = 255;
static bool set_temp_destination(uint8_t address) { destination_changed_to = address; return true; }
static uint8_t char2int(char c) {
    if (c >= '0' && c <= '9') return static_cast<uint8_t>(c - '0');
    if (c >= 'A' && c <= 'F') return static_cast<uint8_t>(c - 'A' + 10);
    return static_cast<uint8_t>(c - 'a' + 10);
}
struct Parsed { uint8_t type; uint32_t command; std::vector<uint8_t> payload; uint8_t destination; bool changed; std::string url; };
static Parsed parse_raw(const char *url) {
    std::vector<char> storage(url, url + strlen(url) + 1);
    char *p = storage.data();
    ''' + preparation + r'''
    (void)json_token;
    uint8_t tempDestAddr = 5;
    ''' + "const unsigned MAX_PARAM_LEN = " + maximum + ";\n" + parsing + r'''
    (void)return_value;
    return {type, c, std::vector<uint8_t>(param, param + param_len), tempDestAddr,
            change_dest_success, std::string(p)};
}
static std::vector<std::string> normal_json_tokens(const char *url) {
    std::vector<char> storage(url, url + strlen(url) + 1);
    char *p = storage.data();
    ''' + preparation + r'''
    std::vector<std::string> tokens;
    while (json_token != NULL) {
        tokens.push_back(json_token);
        json_token = strtok(NULL, ",");
    }
    return tokens;
}
int main() {
    const char *set_url = "/JY03,0500060F,000040!0";
    Parsed set = parse_raw(set_url);
    CHECK(set.url == set_url);
    CHECK(set.type == 3 && set.command == 0x0500060F);
    CHECK(set.payload == std::vector<uint8_t>({0x00, 0x00, 0x40}));
    CHECK(set.destination == 0 && destination_changed_to == 0 && set.changed);

    const char *query_url = "/JY06,05000488!1";
    Parsed query = parse_raw(query_url);
    CHECK(query.url == query_url);
    CHECK(query.type == 6 && query.command == 0x05000488 && query.payload.empty());
    CHECK(query.destination == 1 && destination_changed_to == 1);

    destination_changed_to = 255;
    Parsed info = parse_raw("/JY02,2D3D0215,000500");
    CHECK(info.type == 2 && info.command == 0x2D3D0215);
    CHECK(info.payload == std::vector<uint8_t>({0x00, 0x05, 0x00}));
    CHECK(info.destination == 5 && destination_changed_to == 255);

    Parsed maximum = parse_raw("/JY03,0500060F,000102030405060708090A0B0C0D0E0F101112131415!66");
    CHECK(maximum.payload.size() == 22 && maximum.destination == 66);
    for (uint8_t i = 0; i < maximum.payload.size(); ++i) CHECK(maximum.payload[i] == i);

    CHECK(normal_json_tokens("/JQ=6224!1,6225!0") == std::vector<std::string>({"6224!1", "6225!0"}));
    CHECK(normal_json_tokens("/JC,750") == std::vector<std::string>({"750"}));
    CHECK(normal_json_tokens("/JI").empty());
    return 0;
}
''')


if __name__ == "__main__":
    unittest.main()
