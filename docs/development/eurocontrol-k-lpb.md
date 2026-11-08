# Eurocontrol K: verified legacy LPB behavior

This note records observations from one Eurocontrol K (legacy RVA43, LPB device
family 22) and its associated RVA46 mixing controller (family 23). It separates
manufacturer-description candidates from successful reads, acknowledged writes,
and a controlled change at the physical controller. It is a starting point for
family-specific BSB-LAN support, not a claim that every RVA variant is identical.

The original manufacturer archive, extracted descriptions, full translation
catalog, private configuration, and operational captures are kept outside this
repository. The optional [offline reader](siemens-sysdef-research.md) lets a
developer inspect their own copy. Compact evidence is in
[rva43-verified-facts.json](rva43-verified-facts.json).

## Confirmed objects

CoIDs below use BSB-LAN's eight-hex-digit representation. The destination is the
actual K controller, rather than an emulated room unit. Panel numbers are the
numbers in the exact Eurocontrol K manual; they are not BSB-LAN program numbers.

| K panel line / function | LPB CoID | Confirmed interpretation |
| --- | --- | --- |
| 65: room influence enable | `05000603` | The validity/enable state of the KORR scalar, not a separate numeric boolean. See controlled comparison below. |
| OEM gain KORR | `05000603` | The numeric component is the gain; it stayed `04` when panel 65 changed. |
| 67: room switching differential | `0500060F` | Signed 16-bit scalar, slope 1/64; active range 0.5 to 4.0 K. |
| 71: heating-curve adaptation | `0500060B` | Boolean scalar; valid `00 FF` is enabled, valid `00 00` is disabled. |
| Pump output contact Q1 | `05000488` | Raw eight-byte contact block; Q1 is at zero-based byte offset 2. |
| 51: relay test | `05000073` | Read value 0 matched normal control rather than an output test. |
| 72: pump function | `05000BCE` | Read value 1 matched the configured boiler/heating-circuit pump function. |
| Heating operating mode | `05000074` | Code 4 matched manual operation at the actual controller. |

Other successful scalar reads included the room knob setpoint (`05000458`),
current room setpoint (`05000593`), curve slope (`050005F7`), DHW actual
temperature (`05000462`), and boiler actual temperature (`05000468`). Treat
these as object-identification evidence, not as independently calibrated sensors.

The older `0500021D` object is described as the system/main flow process signal.
It must not automatically be equated to the boiler's local sensor just because
both temperatures happened to be similar. For a local boiler measurement,
the description supplies `05000468`.

## Panel 65 is the scalar's state, not its gain value

A read of `05000603` returned `00 04` before a controlled panel change. The
operator then changed only panel 65 from 1 to 0. The same read returned `01 04`:

| Physical panel 65 | Scalar read payload | Interpretation |
| --- | --- | --- |
| 1 | `00 04` | Room influence enabled, gain 4. |
| 0 | `01 04` | Room influence disabled, retained gain 4. |

This establishes the relationship between panel 65 and the scalar state on the
tested controller. Looking only at the value `04` misses the enable/disable
change. Conversely, displaying `4` as the boolean panel setting is incorrect.
The remote SET representation for panel 65 was **not** tested. Do not infer it
from the successful writes to other objects.

## Read validity and write control bytes differ

The following writes were explicitly requested and acknowledged on the tested
controller. An ACK was followed by independent readback; an attempted write
alone was never treated as success.

| Object | Operation | Payload | Observed result |
| --- | --- | --- | --- |
| `0500060F` | Read active differential | `00 00 40` | Valid 1.0 K. |
| `0500060F` | SET same active value | `01 00 40` | ACK; read remained `00 00 40`. |
| `0500060F` | SET disabled, retain numeric component | `05 00 40` | ACK; read returned `01 00 40` (`---`). |
| `0500060B` | SET adaptation off | `01 00` | ACK; read returned `00 00`. |

The ordinary disabled prefix `00` was rejected for the room differential, both
with a zero numeric component and with the retained `0040` component. The
documented BSB-LAN `VT_TEMP_N` disable prefix `05` worked. Although that type's
normal active prefix is `06`, this investigation only verified active prefix
`01`; it does not establish whether `06` is accepted by this controller.

Keep the numeric component within its valid range when changing the optional
state. Do not generalize this one object's behavior to every nullable scalar
in an extracted description, or turn all static candidates into writable
firmware definitions automatically.

## Q1 is a block field, not a scalar with a validity prefix

`05000488` returned `00 00 FF 00 00 00 00 00`. The description identifies the
third byte as contact Q1; the operator independently confirmed that the pump
was running at that time. The raw block declares eight data bytes. Do not skip
its first byte as if it were a scalar validity flag, which would shift Q1 to
the wrong field.

A controller's contact indication is not a measurement of motor rotation or
water flow. The earlier stopped-pump observation preceded this successful
mapping, so the reason for that earlier stop has not been proven.

## Family-specific operating mode

The manufacturer description's mode range is 0 through 4, with 0 = standby,
1 = automatic, and 4 = manual; its entries for 2 and 3 are placeholders. Code 4
was confirmed against the controller's physical display. Do not decode this
object with a modern four-state `ENUM700` or invent meanings for the placeholder
values. The companion RVA46 returned code 1, but its display was not checked
independently in the same comparison.

After the operator switched the K from manual to automatic, the same object
changed from `00 04` to `00 01`. Automatic mode is therefore also confirmed
against a physical mode change on the K. Room influence remained disabled,
the differential remained `---`, and adaptation remained off.

## Firmware support in this branch

The default command table now includes these entries, restricted to the tested
LPB family 22 / variant 254:

| BSB-LAN program | Display / API meaning | Access |
| --- | --- | --- |
| `700` | Legacy mode: 0 standby, 1 automatic, 4 manual | Read only |
| `726` | Curve adaptation, controller line 71 | Standard write protection applies; SET accepts only 0 or 1 |
| `750` | Retained OEM gain KORR | Read only |
| `750.1` | Room influence enabled, controller line 65 | Read only; normalized 0 or 1 |
| `760` | Room switching differential, controller line 67 | Standard write protection applies; 0.5 to 4.0 K or `---` |
| `8730` | Pump relay contact Q1 | Read only; normalized 0 or 1 |

For example, `/JQ=700,726,750,750.1,760,8730` queries these programs on the
configured destination. Select the actual controller destination when using
several LPB devices. A disabled influence value is exported as 0, while 750
still reports the retained gain. A disabled differential uses the existing
`---` representation, never a measured zero kelvin. The web UI, JSON and MQTT
share the decoded values.

Program 760 uses active SET prefix `01` and the independently verified disable
prefix `05`, preserving the numeric component from a fresh read. Invalid and
nonfinite input, out-of-range temperatures, and unverified INF writes for the
two writable objects are rejected before sending a telegram.

Malformed scalar flags and truncated relay blocks produce a decoding error
rather than a plausible off state. Existing type numbers are unchanged; the
two read-only decoder types are appended to the type table. The new disable
flag affects only entries that explicitly request it.

For a build with a private/generated `BSB_LAN_custom_defs.h`, merge the six
`DEV_022_254` entries from the updated default into its sorted command table,
or regenerate a reviewed profile. Do not overwrite a different controller's
custom definitions. Global write protection remains in force; this extension
does not send commands during boot or enable writes globally.

## Implementation and review plan

1. Preserve the independently useful `/JY` parsing and string-decoder fixes as
   separate commits. Raw requests must retain their payload and target suffix;
   decoding must not change the original frame or checksum.
2. Add reviewed family-specific definitions rather than replacing `DEV_ALL`
   modern addresses or forcing a controller to another family/variant.
3. Represent panel 65's enable state separately from the retained KORR number.
   Preserve the disabled-state flag when exposing optional values in JSON/MQTT.
4. Cover scalar validity, raw block offsets, mode enums, and disabled SET bytes
   with regression tests before exposing writes in a general UI.
5. Keep complete local source hashes/offsets and negative-query records. A query
   rejection at one candidate does not prove the whole feature is inaccessible.

The existing PPS findings remain useful but are a separate protocol scope:
QAA70-emulation settings are not LPB installer parameters, and an emulated
room temperature must be distinguished from a controller measurement. A fixed
placeholder value is not a real room sensor. An EG room sensor also need not be
a representative reference for an independently controlled OG circuit.
