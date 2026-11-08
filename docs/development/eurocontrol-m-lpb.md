# Eurocontrol M: observed legacy LPB read profile

This branch adds 23 read-only programs for the observed RVA46.531/500,
LPB family 23 / variant 254. The installation uses this controller for an EG
floor-heating circuit and a separate Eurocontrol K for the OG radiators.
The controllers are separate LPB destinations; their local circuit is not
automatically equivalent to modern BSB-LAN's HC1/HC2 numbering.

All M entries use `FL_RONLY`, including settings that could potentially become
writable later. No successful K write is generalized to the M. Existing K
definitions and global write protection are unchanged. No commands are sent at
boot by this extension.

## Programs

| BSB-LAN program | LPB CoID | Read meaning |
| --- | --- | --- |
| 700 | 05000074 | Legacy operating mode, manufacturer enum |
| 710 | 05000458 | Nominal room setpoint at the setting knob |
| 712 | 05000590 | Reduced room setpoint |
| 714 | 05000592 | Frost-protection room setpoint |
| 720 | 050005F7 | Curve slope on the legacy controller scale |
| 721 | 05000610 | Curve parallel displacement |
| 726 | 0500060B | Curve adaptation enabled |
| 730 | 050005FD | Summer/winter changeover temperature |
| 740 | 05000663 | Minimum flow-temperature limitation |
| 741 | 05000662 | Maximum flow-temperature limitation |
| 750 | 05000603 | Retained room-influence gain KORR |
| 750.1 | 05000603 | Room-influence scalar enabled |
| 760 | 0500060F | Room switching differential |
| 830 | 0500065D | Mixing-circuit temperature boost |
| 830.1 | 05000BCC | Pump overrun time in minutes |
| 8700 | 05000521 | Controller's outside-temperature value |
| 8730 | 05000488, byte 2 | Pump relay contact |
| 8731 | 05000488, byte 0 | Mixing-valve opening relay Y1 |
| 8732 | 05000488, byte 1 | Mixing-valve closing relay Y2 |
| 8740 | 0500051E | Actual room temperature, or disabled/invalid |
| 8741 | 05000593 | Current room setpoint |
| 8743 | 05000464 | Actual flow temperature |
| 8744 | 05000667 | Resulting flow setpoint |

`750.1`, `830.1`, `8731` and `8732` are branch-specific extensions. These are
BSB-LAN identifiers, not panel line numbers. In particular, `830.1` is placed
beside the mixing-circuit setting within the default heating-circuit category;
it does not label the M pump as a boiler pump.

The observed installation addresses the M as destination 1. For example,
`/JQ=710!1,8730!1,8731!1,8732!1,8740!1,8743!1,8744!1` requests these programs
using the existing per-parameter destination syntax. Verify actual destination
assignments for another installation. MQTT/logging parameter identifiers can
likewise distinguish `!0` and `!1` through the existing destination handling.

The default command table must be merged into a private/generated
`BSB_LAN_custom_defs.h` when one is used. Keep entries sorted and preserve
other controllers' rows. This source support is not automatically installed
on a running adapter.

## Decoding and observed values

The read-only probe sent 28 explicit, payload-free TYPE_QUR requests and
received 25 TYPE_ANS responses with verified LPB checksums. Family 23 and
variant 254 were read directly. Compact samples and provenance are in
[rva46-verified-facts.json](rva46-verified-facts.json).

Three-byte temperatures use a validity byte followed by a signed 16-bit
value divided by 64. Observed examples include flow `00 07 09` = 28.1 C,
flow setpoint `00 07 80` = 30 C, and minimum `00 05 C0` = 23 C.
The room-temperature response `01 00 00` is invalid/disabled, not a measured
zero or a replacement 20 C. It remains `---` in the existing decoder.
Room influence and adaptation were reported enabled at the same time; this
observation does not establish how this model handles a missing room sensor.

Curve `00 1C` is 28 / 2 = 14.0 on the old controller scale, not a modern
slope of 1.4. Pump overrun `00 06` means 6 minutes: catalog UnitID 16 is
`Time_Min_3D` (minute), slope 1. Numeric gain and scalar enable state remain
separate programs, as for the K.

## Pump and mixing-valve contacts

The manufacturer profile `D0017684.apw` identifies OV 200.6, matching the
observed M's reported OV version. Its eight-byte `05000488` block assigns
Y1 to offset 0, Y2 to offset 1, and the pump to offset 2. There is no leading
scalar validity byte. `00` is off and `FF` is on. Other boolean values and
truncated blocks produce a decode error in the shared reader.

The user reported the EG pump running and the mixer off. Three subsequent
reads all returned `00 00 FF 00 00 00 00 00`, agreeing with pump on and both
mixing-valve contacts off. The direction names come from manufacturer data;
neither an actual opening movement nor a closing movement has yet been
correlated with a physical observation. Synthetic direction tests check only
the decoder and are not presented as live observations.

Older OV-200.6 data calls the pump contact Q1, while the model-specific relay
test catalog and some later profiles call it Q2. The UI therefore uses the
neutral label "Pump relay contact". A contact state does not measure rotation,
flow, valve position, or a percentage opening.

Across all 98 family-23 profiles in the supplied corpus, 70 contain this relay
block: Y1/Y2 always occupy offsets 0/1, and the pump always occupies offset 2.
The pump is named Q1 in 56 profiles and Q2 in 14. Matching an OV version is
not an exact proof of a `/500` / variant-254 product profile; this implementation
is restricted to the family/variant actually queried, with physical validation
limits stated above.

## Bounded negative results and validation

Individual Monday period-start/end candidates `05000A28` and `05000A29`, and
mixing-valve neutral-zone candidate `0500065B`, returned TYPE_ERR with code 07.
They are omitted from the firmware table. This does not rule out another
supported representation of the weekly schedule.

Host regressions execute the production lookup and readers with recorded
payloads, check invalid room-temperature handling and independent relay fields,
and verify that every M row is read-only and cannot replace another family's
definitions. The ESP32-EVB firmware build also succeeds. No firmware upload or
M write was performed during this implementation.
