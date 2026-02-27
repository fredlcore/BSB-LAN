# The BSB/LPB/PPS Bus

Developed at the end of the last millenium based on the BatiBUS (more information can be found [here](https://2007.blog.dest-unreach.be/wp-content/uploads/2012/12/Interface-module-I-O-OPEN-ALBATROS-PTM59-20V1_19957_hq-en.pdf) and [here](https://2007.blog.dest-unreach.be/wp-content/uploads/2012/12/BatiBus_v1.4.pdf)), many Siemens heating system controllers still use the same kind of physical bus to "talk" to room units as well as other heating devices. While a bus speed of a mere 4800 bits per second might sound anachronistic these days, it still provides for a stable and robust transmission protocol that is even today perfectly sufficient when it comes to transmitting short messages of a few dozen bytes over lines sometimes as long as one kilometer.

The bus topology also allows you to connect BSB-LAN at any point: At the room unit, at the heating system or anywhere where the bus lines are available. You can even add the two wires for BSB-LAN in an already "occupied" slot, and it won't harm the other device (proper installation assumed).

On top of the same physical layer, three bus systems, BSB, LPB and PPS, cater for different tasks, and while BSB and LPB should always be preferred if available, PPS nevertheless provides a set of parameters that is usually quite enough for the average user.  
BSB-LAN runs on any of these busses and swapping between them is just changing a few settings away.

---

[](){#BSB}
## The Boiler System Bus (BSB)
BSB is the most common bus system in Siemens controllers for the last 10-15 years. It is the successor of the PPS system with which it shares the same physical parameters, but is much more versatile: Instead of just a few dozen parameters, it can access hundreds of parameters and group them into various categories for easier navigation. It is a transaction-based protocol where most messages are being sent from one device to another and the recipient returning some kind of feedback, for example whether the task could be completed or whether it contained invalid data.

While BSB is capable of addressing multiple devices on the bus, it is not used in systems with more than one heating device. The heating device always has the ID `0`, the display unit on the heating system has the ID `10` (or `0x0A` in hexadecimal) and the standard room unit has the ID `6`. BSB-LAN has the ID `66` or `0x42` in hexadecimal.   
Room units that "speak" BSB are, for example, the QAA55 and the QAA75.

---

[](){#LPB}
## The Local Process Bus (LPB)
LPB was introduced more or less around the same time as PPS which it complemented in terms of communication with other heating devices: While PPS was used to communicate with the room unit, LPB was used to send commands from one main heating device to one or more auxilliary heating devices, for example in a cascade setup. At that time, most of the information transmitted via LPB was related to the internals of the heating system (such as sensor data or internal setpoint temperatures), whereas the parameters relevant for the user (such as comfort temperature setpoint etc.) were only available via PPS. Nowadays, heating devices that offer both LPB and BSB have the same kind of parameter data available on both bus systems.

LPB uses a specific addressing scheme with segments and devices. Each segment from 0 to 15 can contain up to 15 devices (from 1 to 15). When writing these addresses, segment and device are separated by a colon: `00:01` or `04:03`.  
To convert the segment-based address into the destination ID required for BSB-LAN, the formula is as this:
`SEGMENT` multiplied by 16 plus `DEVICE` minus one.  
Example: Device 3 in segment 4 equals to `4 * 16 + 3 - 1` = 66.  
The main heating unit is by definition `00:01`, so this equals to a destination ID 0.
To learn more about the LPB system and how it should be deployed, you may refer to these two documents from the end of the 1990s, one covers the [basic system data](https://sid.siemens.com/v/u/20138) that covers the conceptualization of an LPB network, and the other one deals with the [basic engineering data](https://sid.siemens.com/v/u/20140) and provides details about cable lengths and diameters etc.

Except for some Weishaut heaters, room units are not connected to the heating system via LPB. Newer models use BSB for this task while older models use either PPS or in some cases also OpenTherm.

---

[](){#PPS}
## The Point-to-Point Interface (PPS)
The Point-to-Point Interface (PPS deriving from the German term "Punkt-zu-Punkt Schnittstelle") is compatible to the other systems on a physical layer, but not in the way message telegrams are being exchanged. While BSB and LPB talk to each other by sending telegrams and acknowledging their receipt respectively, PPS is dominated by the heating unit. The heating unit constantly sends its data to the room unit and tells the room unit when and what kind of information it should send. So it may take up to a few minutes until a value that is set in BSB-LAN is actually requested by the heating system and shown there.  
It is also a very timing sensitive protocol, therefore long other tasks that BSB-LAN is told to do will lead to a temporary interruption and possible error message on the heating system. However, after a short while, this should be clearing by itself when the two components "talk" to each other again.  

Other than BSB and LPB, changes made in BSB-LAN do not take immediate effect. Changing values, for example like the room temperature comfort setpoint, will be stored internally in BSB-LAN first to be sent out to the heating system once it tells the room unit (i.e. BSB-LAN) to do so. This may take up to a minute or so, so one should not be confused that settings do not show up on the heater immediately, as is the case with BSB and LPB.

With PPS, BSB-LAN can run in two modes: either listening passively or as a room unit. In passive mode, BSB-LAN can just listen to the data exchanged between the room unit and the heating device. It is not possible to send one's own data, for the simple fact that it would be overwritten in no time by the same type of data coming from the room unit.  
In order to send parameter data to the heating system, BSB-LAN mus run in "room unit" mode, and this means that any room unit will have to be removed from the heating system. In this case, it is especially important to regularly send a room temperature value to BSB-LAN which in turn will send this value to the heating device. Only if the heater runs solely on outside temperature then this value can be ignored.  
BSB-LAN stores some values in its non-volatile EEPROM, but some values need to be set anew after a reboot, such as the room temperature setpoint. This is to prevent to store a parameter value that has become invalid but is still sent as it is stored in the EEPROM.

Room units commonly used with heating systems that support PPS are the QAA50 and the QAA70.

## Which bus should I use?
**Attention:** Make sure that you make the decision where you want to connect your BSB-LAN adapter **before** you create the device-specific parameter list!
### If your heating controller has both BSB and LPB
Overall, BSB and LPB provide access to the same parameter sets, so it doesn't make much of a difference which one you choose.  
If you only have **one single heating controller** and you have the option to choose between BSB and LPB then you should choose BSB. The advantage of using BSB is that a few status telegrams, such as burner activity, are pushed only via BSB. Therefore, you can, for example, access parameters 20000 to 20005 only via BSB.
If you already have **more than one heating controller** and these are connected via LPB, then you should also connect BSB-LAN via LPB in oder to have access to all devices using just a single BSB-LAN adapter via LPB.  
If you want the "best of both worlds", i.e. also having access to the (few) status parameters that are only available via BSB (such as parameters 20000 to 20005) as well as accessing more than one device on your LPB bus, you will need to get two adapters, one connected to BSB and one to LPB.  
### If your heating controller has PPS and LPB
This is usually only the case for older heating controllers. In this case, you will have access to the functions of a room unit when connecting BSB-LAN to PPS, and the more systematic parameters when connecting BSB-LAN to LPB. Depending on the heating controller, you may also have access to the functions available via PPS when connecting via LPB. If there is a difference in functionality, and you want to use every last available parameter, then you need two BSB-LAN adapters, one to connect via PPS and another one to connect via LPB.