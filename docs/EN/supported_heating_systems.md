# Supported heating systems
BSB-LAN supports heating systems that communicate using either the [BSB (Boiler System Bus)](bus_systems.md#BSB), the [LPB (Local Process Bus)](bus_systems.md#LPB) or the [PPS (Punkt-zu-Punkt-Schnittstelle)](bus_systems.md#PPS). These controllers are usually manufactured by Siemens, older controllers might still bear the company name "Landis & Stafea" or "Landis & Gyr".

We have compiled a [list of working models](supported_models.md) from various heating system manufacturers who have been confirmed working with BSB-LAN, although there is no 100% guarantee that the manufacturers keep the model name but change the controller to a different system. So always make sure to double-check that the right connectors are available.

Here are a few examples from heating controllers and the connectors that are used to connect to BSB-LAN. Some connectors have three pins, some have two pins. If there are three pins, **make sure you choose the correct two (CL+ and CL-)** as the third von (G+) is to provide background lighting for the room unit. It won't harm BSB-LAN, but it might be misleading because BSB-LAN's LED will be on even though it's not connected to the right pin.

|Controller|Image|Remarks|
|:--------:|:---:|:------|
|[](){#LMS14}**LMS14**<br>**LMS15**|<img src="../images/LMS14.jpeg">|BSB connection:<br>**+** = Left<br>**-** = Center|
|**LMS14**<br>**LMS15**|<img src="../images/LMS14-2.jpeg">|BSB connection: CL+/CL-|
|[](){#LMU64}**LMU54**<br>**LMU64** |<img src="../images/LMU64.jpeg">|LPB connection:<br>via additional OCI420 plugin|
|[](){#LMU74}**LMU74**<br>**LMU75** |<img src="../images/LMU74.jpeg">|BSB connection:<br>**+** = Top<br>**-** = Center<br>LPB connection:<br>via additional OCI420 plugin|
|[](){#RVA53}**RVA53** |<img src="../images/RVA53.jpeg">|PPS connection: A6/MD|
|[](){#RVA63}**RVA63** |<img src="../images/RVA63.jpeg">|LPB connection: MB/DB<br>PPS connection: A6/MD|
|[](){#RVP54}**RVP54** |<img src="../images/RVP54.jpeg">|PPS connection: A6/M|
|[](){#RVS21}**RVS21** |<img src="../images/RVS21.jpeg">|BSB connection via connector X86<br>**+** = rightmost pin<BR>**-** = second pin from right|
|[](){#RVS21-AVS55}**RVS21 with AVS55** |<img src="../images/RVS21-AVS55.jpeg">|AVS55 extension module, sitting on top of RVS21.<br>BSB connection via connector X86:<br>**+** = rightmost pin<BR>**-** = second pin from right|
|[](){#RVS41}**RVS41** |<img src="../images/RVS41.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS43}**RVS43<br>LOGON B**|<img src="../images/RVS43.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS43-ZR1}**RVS46<br>ISR-ZR1** |<img src="../images/RVS46-ISR-ZR1.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS46}**RVS46** |<img src="../images/RVS46.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS51}**RVS51** |<img src="../images/RVS51.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS61}**RVS61** |<img src="../images/RVS61.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|
|[](){#RVS63}**RVS63** |<img src="../images/RVS63.jpeg">|BSB connection: CL+/CL-<br>LPB connection: MB/DB|

## List of working controller models

There are a many more controllers that are likely to work with BSB-LAN. Look out for these Siemens controller models in your heating system: 

--8<-- "docs/en/list_of_controllers.md"
