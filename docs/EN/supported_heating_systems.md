# Supported heating systems
BSB-LAN supports heating systems that communicate using either the [BSB (Boiler System Bus)](bus_systems.md#BSB), the [LPB (Local Process Bus)](bus_systems.md#LPB) or the [PPS (Punkt-zu-Punkt-Schnittstelle)](bus_systems.md#PPS). These controllers are usually manufactured by Siemens, older controllers might still bear the company name "Landis & Stafea" or "Landis & Gyr".

We have compiled a [list of working models](supported_models.md) from various heating system manufacturers who have been confirmed working with BSB-LAN, although there is no 100% guarantee that the manufacturers keep the model name but change the controller to a different system. So always make sure to double-check that the right connectors are available.

Here are a few examples from heating controllers and the connectors that are used to connect to BSB-LAN. Some connectors have three pins, some have two pins. If there are three pins, **make sure you choose the correct two (CL+ and CL-)** as the third von (G+) is to provide background lighting for the room unit. It won't harm BSB-LAN, but it might be misleading because BSB-LAN's LED will be on even though it's not connected to the right pin.  
By the way: If you only have one connector and it is already occupied with a room unit, it's no problem to add BSB-LAN to the same connector. Just be careful when adding the wires for BSB-LAN.  

|Controller|Image|Remarks|
|:--------:|:---:|:------|
|[](){#LMS14}**LMS14**<br>**LMS15**|<img src="../images/LMS14.jpeg">|BSB connection:<br>**+** = Left<br>**-** = Center|
|**LMS14**<br>**LMS15**|<img src="../images/LMS14-2.jpeg">|BSB connection: CL+/CL-|
|**LMS14**<br>**LMS15**<br>Baxi Luna Platinum,<br>Chappee Klista|<img src="../images/LMS15 Baxi Platinum.jpeg"><img src="../images/LMS15 Chappee Klista.jpeg"><img src="../images/LMS15 Baxi Platinum Mainboard.jpeg">|BSB connection:<br>Terminal block M2<br>Pin 2: CL-<br>Pin 3: CL+<br>See detailed instructions here for <a href="https://github.com/fredlcore/BSB-LAN/wiki/Special-instructions-for-special-heating-systems#js-repo-pjax-container">Baxi Luna Platinum</a>.|
|[](){#LMU64}**LMU54**<br>**LMU64** |<img src="../images/LMU64.jpeg">|LPB connection:<br>via additional OCI420 plugin, see [details below][OCI420].|
|[](){#LMU74}**LMU74**<br>**LMU75** |<img src="../images/LMU74.jpeg">|BSB connection:<br>**+** = Top<br>**-** = Center<br>LPB connection:<br>via additional OCI420 plugin|
|[](){#RVA53}**RVA53** |<img src="../images/RVA53.jpeg">|PPS connection: A6/MD|
|[](){#RVA63}**RVA63** |<img src="../images/RVA63.jpeg">|LPB connection: MB/DB<br>PPS connection: A6/MD|
|[](){#RVP54}**RVP54** |<img src="../images/RVP54.jpeg">|PPS connection: A6/M|
|[](){#RVS13}**RVS13** |<img src="../images/RVS13.jpeg">|BSB connection: CL+/CL-|
|[](){#RVS21}**RVS21** |<img src="../images/RVS21.jpeg">|BSB connection via connector X86<br>**+** = rightmost pin<BR>**-** = second pin from right|
|[](){#RVS21-AVS55}**RVS21 with AVS55** |<img src="../images/RVS21-AVS55.jpeg">|AVS55 extension module, sitting on top of RVS21.<br>BSB connection either via connector X86:<br>**+** = rightmost pin<BR>**-** = second pin from right<br>or via connector X150:<br>**+** = topmost pin<BR>**-** = second pin from top|
|[](){#RVS23}**RVS23** |<img src="../images/RVS23.jpeg">|LPB connection: LPB/M|
|[](){#RVS41}**RVS41** |<img src="../images/RVS41.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS43}**RVS43<br>LOGON B**|<img src="../images/RVS43.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS43-ZR1}**RVS46<br>ISR-ZR1** |<img src="../images/RVS46-ISR-ZR1.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS46}**RVS46** |<img src="../images/RVS46.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS51}**RVS51** |<img src="../images/RVS51.jpeg">|BSB connection: CL+/CL-|
|[](){#RVS53}**RVS53** |<img src="../images/RVS53.jpeg">|BSB connection: CL+/CL-|
|[](){#RVS61}**RVS61** |<img src="../images/RVS61.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS63}**RVS63** |<img src="../images/RVS63.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS65}**RVS65** |<img src="../images/RVS65.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|

[](){#OCI420}
## Configuration settings for OCI420 ##

Getting the OCI420 to work properly can be a bit challenging if it is not already part of an existing LPB network. If you connect the OCI420 for the first time to your heater and have no other LPB heating device, you will most likely get "error 81" which indicates that there is a bus error. But don't worry, most likely it's just a matter of configuring a few parameters to get it going. For the LMU64, the corresponding parameter is 604 (_LPBKonfig0_). It needs to be set as follows for using BSB-LAN as the only device connected to the OCI420:  
```
604.0 = 0  
604.1 = 1 
604.2 = 1 
604.3 = 1 
604.4 = 1 
604.5 = 0 
604.6 = 0 
604.7 = 0 
```

Then you need to set the LPB address of the OCI420 in parameters 605 (needs to be set to 1) and 606 (needs to be set to 0). Afterwards, there should be no more error message and the red LED of the OCI420 should blink in regular intervals and you are ready to connect and use BSB-LAN.  
**Attention:** If the OCI420 is already connected to another LPB device, **do not make any changes here** and rather connect BSB-LAN to the other LPB device. It should work without any adjustments.

## List of working controller models

There are a many more controllers that are likely to work with BSB-LAN. Look out for these Siemens controller models in your heating system: 

--8<-- "docs/en/list_of_controllers.md"
