"""Validate recorded read-only protocol evidence without a live heating system."""
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


def packet(text):
    data = bytes.fromhex(text)
    if len(data) < 15 or data[0] != 0x78 or data[1] != len(data) - 1:
        raise ValueError('Invalid LPB packet length/header')
    length = len(data) - 1
    checksum = ((257 - length) * 256 + length - 2 + sum(data[:length - 1])) & 0xffff
    if checksum != int.from_bytes(data[-2:], 'big'):
        raise ValueError('Invalid LPB checksum')
    return data


class EurocontrolEvidence(unittest.TestCase):
    def setUp(self):
        self.evidence = json.loads((ROOT / 'docs/development/eurocontrol-mode-test-20261110.json').read_text())

    def test_every_retained_frame_is_the_claimed_payload_free_read_and_answer(self):
        self.assertTrue(self.evidence['frames'])
        for frame in self.evidence['frames']:
            with self.subTest(phase=frame['phase'], coid=frame['coid'], family=frame['target_family']):
                tx, rx = packet(frame['tx_hex']), packet(frame['rx_hex'])
                command = bytes.fromhex(frame['coid'])
                target = {22: 0, 23: 1}[frame['target_family']]
                self.assertEqual((len(tx), tx[8], rx[8]), (15, 6, 7))
                self.assertEqual(tx[2:4], bytes([target, 66]))
                self.assertEqual(rx[2:4], bytes([66, target]))
                self.assertEqual(tx[9:13], bytes([command[1], command[0], command[2], command[3]]))
                self.assertEqual(rx[9:13], command)
                self.assertEqual(rx[13:-2], bytes.fromhex(frame['payload_hex']))

    def test_recorded_M_modes_and_levels_cover_both_changes_and_auto_return(self):
        frames = {(f['phase'], f['coid']): bytes.fromhex(f['payload_hex'])
                  for f in self.evidence['frames'] if f['target_family'] == 23}
        for phase, mode, level, setpoint, pump in [
                ('continuous', 4, 2, 20.5, 255),
                ('standby', 0, 0, 6, 0),
                ('auto_return', 1, 1, 8, 0)]:
            self.assertEqual(frames[phase, '05000074'], bytes([0, mode]))
            self.assertEqual(frames[phase, '2D00020B'], bytes([level, 1]))
            self.assertEqual(int.from_bytes(frames[phase, '05000593'][1:], 'big', signed=True) / 64, setpoint)
            self.assertEqual(frames[phase, '05000488'][2], pump)
        # A retained request temperature without G must not become heat demand.
        for phase in ('standby', 'auto_return'):
            attributes = int.from_bytes(frames[phase, '210001F4'][2:], 'big')
            self.assertFalse(attributes & 1)


if __name__ == '__main__':
    unittest.main()
