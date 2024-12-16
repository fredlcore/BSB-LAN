# Frequently Asked Questions (FAQ)

---

## Will my settings remain when updating BSB-LAN?
- That depends. Minor updates will not affect any settings, but sometimes it is unavoidable that changes in the code also affect the settings. In that case, it is mentioned in the file `CHANGELOG.md`, and BSB-LAN rewrites the settings in the EEPROM based on the settings in `BSB_LAN_config.h`. That's why it's best to always make significant changes in the settings also in that file.  
Updates never affect any parameters in the heating system.

---

## My heater has a OpenTherm/eBus/L-Bus/R-Bus connector, can I use BSB-LAN?
- No, these controllers are not compatible with BSB-LAN. Do **not** try and connect the adapter to your heating system!

---
## I'm missing function *XYZ*
- BSB-LAN offers the possibility to create own functions using the files `BSB_LAN_custom_global.h`, `BSB_LAN_custom_setup.h` and `BSB_LAN_custom.h`. Please see the folder `custom_functions` in the repository for more details and examples. Feel free to contribute your solutions to the public!
