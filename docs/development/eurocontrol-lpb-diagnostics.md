# Legacy Eurocontrol K/M diagnostic findings

This report records findings through 2026-11-10 for one installation with a
Eurocontrol K (family 22, variant 254) and M/RVA46 (family 23, variant 254).
The K controls a direct radiator circuit, boiler and domestic hot water; the M
controls a separate mixed floor-heating circuit. These functions and destination
addresses are installation-specific. LPB destinations are not modern HC1/HC2
program numbers.

The firmware additions, parser fixes and offline description reader are in
this branch. Later diagnostic interpretation, history, pump events, schedule
editing, ioBroker integration and observation-only learning are implemented in
the separate [SmartHome dashboard](https://github.com/zonfacter/SmartHome_py/tree/codex/heating-dashboard).
The dashboard reads raw LPB objects through BSB-LAN; it is not firmware running
inside the ESP32. The object index below is a candidate/reference list for
future firmware work, not a claim that 133 new programs have been added here.

## Evidence levels

1. Exact device-description handlers establish field positions and encodings.
   They do not prove that a device answers a query or accepts a write.
2. Payload-free TYPE_QUR 06 / TYPE_ANS 07 reads verify the responding controller,
   object, byte layout and frame checksum. An invalid scalar is still an answer;
   it is not a real temperature and must not be replaced with 20 C.
3. Controlled physical comparisons establish observed changes, with other
   controllers left unchanged. The M mode sequence now includes a return to Auto.
4. Manufacturer descriptions of later LPB generations are used only for matching
   object/layout combinations. They do not establish every effect of the old K/M.
5. A protocol indication and a time correlation do not prove the unique physical
   reason for a stopped pump. Contact state is not a water-flow measurement.

Private network configuration, credentials, household schedules, recorder
databases, photos, vendor binaries and the complete extracted vendor catalogs
are excluded. The checked-in fixtures are selected self-recorded protocol data;
the index and notes are self-authored. Vendor documents are linked, not bundled.

## Read-only object inventory

[eurocontrol-readonly-object-index.json](eurocontrol-readonly-object-index.json)
lists all 133 fields used by the external collector, grouped into 123
controller/object pairs. Each field records its decoder kind, unit, polling
group and one sample's quality, without publishing the live configuration.
Multiple fields can share one object. A `valid` transport/field sample does not
establish calibrated sensor accuracy, and `unavailable` does not mean the
object itself is unsupported.

Notable configuration objects, read on K unless marked K/M:

| CoID | Meaning | Encoding / restriction |
| --- | --- | --- |
| `0500071E` | DHW request source | Legacy boolean: valid `00 00` sensor, `00 FF` thermostat |
| `05000727` | DHW separation setting | Cascade separation; not circulation-pump shutdown |
| `05000930` | Burner configuration | Valid `00 00` single-stage, `00 FF` two-stage; does not prove wiring or stage power |
| `0500092D` | OEM boiler minimum | Scalar temperature, signed 16-bit /64 |
| `05000932`, `05000933` | Second-stage release/reset integral | Scalar K min, not a temperature or a fixed time delay |
| `05000924` | Boiler mode setting | Legacy valid `00 00` continuous, `00 FF` automatic; distinct from room-heating mode |
| `05000925` | Chimney-sweep state | Read only; do not enable to provoke status bits |
| `05000602` (K/M) | Startup room-setpoint boost | Scalar temperature difference, K |
| `0500060D`, `0500060E` (K/M) | Adaptation sensitivities ZAF1/ZAF2 | Signed byte after scalar state |
| `05000067` (K/M) | Plant type code | Keep raw controller code; no invented hydraulic topology |
| `0500006D` (K/M) | Clock source | Own clock / LPB without remote setting / LPB with remote setting / master |
| `05000082` (K/M) | Outside-temperature source | Two block fields: segment, device; no scalar validity prefix |

Burner hours were identified only in the K's nine-byte `11000209` producer
block, bytes 5..8 as a signed seconds counter. Do not apply that interpretation
to M's superficially similar producer block. Burner relay indication, flame
operation, nameplate input/output and an empirical gas-meter calibration are
different measurements.

## Request, lock, force and producer-status objects

The reference is [Brötje ISR MODBM 7715040-06, 2019-07-24, pp. 34-35](https://polo.broetje.de/pdf/7715040%3D6%3Dpdf_%28bdr_a4_manual%29%3Dde-de_ma_modbm.pdf).
The retained local source SHA-256 is
`84bc5e6043d481b06ca5872ff83aeec8d6e9a174e1c64da89c0ac4c9a41414be`.
Use the source's object scope, not a generic rule that bit 0 always means valid.

| CoID | LPB object | Supported interpretation | Still open |
| --- | --- | --- | --- |
| `210001F4`, `250001F4`, `190001F4` | 500 | Four bytes: signed temperature /64, then 16-bit attributes | Unique physical pump-switching cause |
| `150001F5` | 501 | Five-byte field layout only | Do not copy the four-byte request mask here |
| `110001F7` | 503 | Two raw bytes retained | Attribute semantics and old-controller effects |
| `150001F8` | 504 | Signed percent byte, attribute byte | Actual reduction at each consumer |
| `190001F9` | 505 | Two raw bytes retained | No mask inferred from object 504 |
| `110001FA` | 506 | Two raw bytes retained | No mask inferred from object 507 |
| `150001FB` | 507 | Signed percent byte, attribute byte | Actual consumer action |
| `11000209` | 521 | Raw producer block; bounded K counter above | Do not copy object 522 status mask here |
| `1500020A` | 522 | Five bytes, leading 16-bit attributes | Remaining power/auxiliary fields |
| `2D00020B` | 523 | M first byte 0/1/2 observed frost/reduced/comfort | Second byte and other values |

For the matching four-byte object-500 requests, attribute bit 0 is validity,
bit 1 requests a transport pump, bits 2/3 indicate absolute/shifting DHW
priority. Priority flags are interpreted only when validity is set. A transport
pump request is not automatically the local Q1 contact. Unknown bits are retained.
For example, `08 40 00 02` has a 33 C temperature field but no valid request;
it must not be shown as active heat demand. `0A 00 00 03` carries a valid 40 C
request; on the tested M, the local mixed-flow target was separately 30 C.

For object 504, bit 0 marks a valid reduction; bit 1 marks mandatory reduction.
A percent field alone does not establish a pump stop. For object 507, bit 0
marks validity and bit 1 distinguishes force to all consumers from afterrun
only. With bit 1 clear, a retained 50 percent byte is not a command to force
every consumer to 50 percent.

For object 522, bit 0 instead means **producer present**. Documented bits
1,2,3,4,5,8 indicate ECO/outdoor limit, producer fault, chimney sweep, manual
producer lock, unavailable for space heating due to DHW charging, and manual
mode. When producer presence is not confirmed, the other flags are not treated
as active conditions. Other bits remain unassigned.

## Observed pump context and timing limits

During natural DHW charging, K pump-off observations coincided with Q3 on and
`64 01` in object 504. M could keep its pump on with that same reduction value,
consistent with restricting a mixed circuit through its valve. These are
correlations, not independent controlled proof of all priority effects.

The external collector groups each controller's related reads. Diagnosis
requires valid samples, age no more than 90 s and a combined timestamp span no
more than 30 s for the fields actually used. It abstains for missing or skewed
data. It reports demand, afterrun, DHW reduction and producer-status indications
as compatible contexts; the unique physical cause remains unresolved. It does
not infer an off motor from a cached or missing relay sample.

The [M mode fixture](eurocontrol-mode-test-20261110.json) covers
Auto -> continuous -> standby -> Auto. It independently distinguishes normal
continuous mode from emergency manual operation and reproduces levels 1 -> 2
-> 0 -> 1. The return restored the original reduced setpoint, inactive local
heat demand and off pump contact. The unresolved lock/force bytes did not
acquire a new semantic meaning from that experiment.

The M candidate `0500065E`, present in later device descriptions as lock-signal
gain, returned TYPE_ERR 07 on the tested M. It is excluded from periodic reads.
This bounded negative result does not prove the whole function is inaccessible.

## Remaining verification work

- Repeat the explicit normal-continuous versus emergency-manual distinction on
  K before changing its historical code-4 translation.
- Observe naturally occurring DHW priority and boiler startup/afterrun phases;
  make one authorized controller change at a time, retain before/after reads,
  verify restoration, and compare actual device indications.
- Do not force overheating, sensor failures, frost, relay tests or disabled
  protections to manufacture signal changes.
- Keep unresolved objects 503/505/506 and level attributes raw until exact
  documentation or controlled comparisons establish them.
- Propose independently reviewed firmware program numbers and access flags for
  additional objects. Readability never establishes writability.

## Reproducing the offline checks

From this repository root:

```sh
python -m unittest discover -s tests -p 'test_*.py' -v
python -m unittest discover -s tests/host -v
```

The first command checks the offline description reader and retained frame
evidence without vendor files or hardware. The second compiles production
firmware sections with a host C++ compiler, including device-specific lookup,
independent K/M mode enums, decoder failures and bounded SET behavior. Neither
command sends bus traffic. A complete embedded build remains a separate check.
