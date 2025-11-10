# Frequently Asked Questions (FAQ)

---

## Will my settings remain when updating BSB-LAN?
- That depends. Minor updates will not affect any settings, but sometimes it is unavoidable that changes in the code also affect the settings. In that case, it is mentioned in the file `CHANGELOG.md`, and BSB-LAN rewrites the settings in the EEPROM based on the settings in `BSB_LAN_config.h`. That's why it's best to always make significant changes in the settings also in that file.  
Updates never affect any parameters in the heating system.

---

## My heater has a OpenTherm/eBus/BridgeNet/L-Bus/R-Bus connector, can I use BSB-LAN?
- No, these controllers are not compatible with BSB-LAN. Do **not** try and connect the adapter to your heating system!  
If you own any of these heating systems, there are some other projects for Remeha's [R-Bus](https://github.com/pepijndevos/R-Bus) (also used in newer Brötje heating systems), [BridgeNet bus](https://github.com/wrongisthenewright/ebusd-configuration-ariston-bridgenet) (actually some sort of [eBus](https://adapter.ebusd.eu/) used by Elco/Ariston/Chaffoteaux heating systems), and [OpenTherm](https://otgw.tclcode.com/index.html).  
These projects are **not** related to BSB-LAN in any way, and **no support** can be provided here.

---

## On my Atlantic heater, the changes I made in BSB-LAN do not show on the heater's display!
- Some Atlantic heaters have a display that does not sync the parameters with the Siemens controller automatically and only sends parameter changes when changed on the heater's display. Therefore, changes made via BSB-LAN are not shown on the heater's display. They are, however, active, and the parameters set and queried by BSB-LAN are the "real" ones. This is confusing, but nothing can be done about it.  
If you have an affected heater, please let us know the devices that you are using, so we can compile a list.

---

## I'm missing parameter XYZ, a friend with the same heating system has this parameter!
- That may be the case, but having the same heating system doesn't mean that these use the same controller, and even if the controller is the same, different firmware versions can result in dozens of different parameters. With the device-specific parameter list, the controller tells us what parameters it supports. This is what BSB-LAN can offer, no more, no less.  
If you still want to add parameters on your own, e.g. from the user-created parameter list that we used until version 2.2, then you can find background information on this process [here in the wiki](https://github.com/fredlcore/BSB-LAN/wiki/Adding-selected-parameters-from-release-version-2.2). But please take note: There is no support from our end for this!

---

## I'm missing function *XYZ*
- BSB-LAN offers the possibility to create own functions using the files `BSB_LAN_custom_global.h`, `BSB_LAN_custom_setup.h` and `BSB_LAN_custom.h`. Please see the folder `custom_functions` in the repository for more details and examples. Feel free to contribute your solutions to the public!
