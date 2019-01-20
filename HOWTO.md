<H1>BSB Boiler-System-Bus LAN Interface</H1>

<B>ATTENTION:</B>  
      There is no waranty that this system will not damage your heating system!

<B>Authors:</B>  
Gero Schumacher (gero.schumacher ät gmail.com) (up to version 0.16)  
Frederik Holst (bsb ät code-it.de) (from version 0.17 onwards)  
Based on the code and work from many other developers. Many thanks!

<B>Host System:</B>  
The software is designed to run on an arduino mega2560 board with ethernet shield.
Because there are different pin assignments for different ethernet shields, you
may have to connect the BSB-LPB adapter to different pins and to change the pin assigment
in the software.  
The software is tested with the following components:        
- SainSmart MEGA2560 R3 Development Board  
- SainSmart Ethernet Schild für Arduino UNO MEGA Duemilanove Neu Version W5100  
- BSB-Interface (see BSB_adapter.pdf)  
For this configuration, pin A14 (68) is used as RX and pin A15 (69) is used as TX (see setting parameters below).

The interface board may also be used with an Raspberry Pi 2, but a completely different software (bsb_gateway) would have to be used which can be found <A HREF="https://github.com/loehnertj/bsbgateway">here</A>. Please note that you would have to contact the author of bsb_gateway for any support related to that software. All further information on this website relate to the Arduino version only!
      
<B>Target System:</B>  
      Tested with various Elco and Brötje heating systems (see README).
      Communication should be possible with all systems that support the BSB interface. 

<B>Getting started:</B>
* Connect the CL+ and CL- connectors of the interface to the corresponding port of your heating system (look out for port names like BSB, FB, CL+/CL-, remote control). For LPB, connect with DB/MB (connect DB(+) to CL+ and MB(-) to CL-).
* Download and install the most recent version of the Arduino IDE from https://www.arduino.cc/en/Main/Software (Windows, Mac and Linux are available).
* <del>Copy the contents of the BSB_lan libraries folder into your local Arduino libraries folder (My Documents\Arduino\libraries\ on Windows, ~/Documents/Arduino/libraries on Mac).</del> No longer necessary from version 0.34 onwards.
* Download the current version of BSB-LAN from https://github.com/fredlcore/bsb_lan and unzip the downloaded file „bsb_lan-master.zip“. Rename the created folder <code>bsb_lan-master</code> to <code>BSB_lan</code>.
* Rename the default <code>BSB_lan_config.h.default</code> to <code>BSB_lan_config.h</code>
* Open the BSB_lan sketch by double-clicking on the BSB_lan.ino file in the BSB_lan folder. The corresponding BSB_lan_config.h and BSB_lan_defs.h files will be automatically loaded as well.
* Configure the IP-address in BSB_lan_config.h according to your network (default 192.168.178.88 will work with standard Fritz!Box routers, but check for address collision).
* Select "Arduino/Genuino Mega or Mega 2560" under Tools/Board.
* Select "ATmega 2560" under Tools/Processor.
* Select "AVRISP mkII" under Tools/Programmer.
* Select the corresponding USB/serial port under Tools/Port.
* Upload the sketch to the Arduino under Sketch/Upload.
* Open `http://<ip address from config>/` (or `http://<ip address from config>/<passkey>/` when using the passkey function, see below) to see if everything was compiled and uploaded correctly. A simple web-interface should appear.

Optionally configure the following parameters in BSB_lan_config.h:  
- Heating system configuration  
  `int fixed_device_id = 0;`  
  Set this to 0 to turn on auto-detection at startup of the Arduino or enter value of parameter 6225 here.
  A fixed value will ensure that BSB_LAN works correctly even if the heating system was turned on after the Arduino (in which case of course BSB_LAN cannot detect the heating system).
- MAC address of your ethernet shield. It can be normally found on a label at the shield:  
  `byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEA };`  
  You only need to change the default MAC-address when using more than one interface in the same network.
- IP-Address  
  `define #IPAddr 192,168,178,88`  
  Note: Use commas instead of dots!  
- Ethernet port  
  `#define Port 80`  
- Ethernet2 shield (W5500)  
  `#define ETHERNET_W5500`  
  Additionally, unzip the Ethernet2.zip archive in the "src" subdirectory
- Adapter configuration  
  `BSB bus(68,69,<my_addr>,<dest_addr>);`  
  RX-Pin, TX-Pin, own bus address (defaults to 0x06=RGT1), destination bus address (defaults to 0x00=heating system)
  If you already have an RGT1 installed, you can type in the following to address the adapter as RGT2:  
  `BSB bus(68,69,7);`
  
- Bus protocol  
  `uint8_t bus_type = bus.setBusType(<type>);`  
  Default is 0 for BSB, change here to 1 for LPB or use URL command /P0 and /P1 to temporarily switch accordingly.  
- Activate the usage of the passkey functionality (see below)  
  `#define PASSKEY  "1234"`  
- You can restrict access to the adapter to read-only, so that you can not set or change certain parameters of the heater itself by accessing it via the adapter. To achieve this, you have to set the flag in the concerning line (#define DEFAULT_FLAG 0) to FL_RONLY:  
  `#define DEFAULT_FLAG FL_RONLY;`
- You can set the language of the webinterface of the adapter to english by deactivating the concerning definement:
  `//#define LANG_DE;`
        
<B>Web-Interface:</B>  
A simple website is displayed when the server is accessed by its simple URL without any parameters.  
e.g. `http://<ip-of-server>`  
To protect the system from unwanted access you can enable the passkey feature (very simple and not really secure!).  
If the passkey feature is enabled (see below), the URL has to contain the defined passkey as first element
e.g. `http://<ip-of-server>/<passkey>/`    - to see the help. Don't forget the trailing slash after the passkey! 
The urls in the below examples have to be exented, if the passeky feature is turned on.  

In addition to the web-interface, all functions can also be directly accessed via URL commands, this is especially useful when 
using the device in home automation systems such as FHEM.
      
All heating system parameters are accessed by line numbers. A nearly complete description can be found in the "Brötje Systemhandbuch ISR".  
Some lines are 'virtual', i.e. they were added to simplify the access to complex settings like time programms.  
The parameters are grouped in categories according to the submenu items when accessing your boiler system from the display.  

* List all categories:  
`http://<ip-of-server>/K`  
This command does not communicate with the boiler system. It is a software internal feature.

* List all enum values for parameter x  
`http://<ip-of-server>/E<x>`  
This command does not communicate with the boiler system. It is a software internal feature. The command is only available for parameters of the type VT_ENUM.

* Query all values from category x:  
`http://<ip-of-server>/K<x>`  

* Query value for line x  
`http://<ip-of-server>/<x>`  

* Query value for a range of lines (from line x up to line y)  
 `http://<ip-of-server>/<x>-<y>`  

* Multiple queries can be concatenated  
e.g. `http://<ip-of-server>/K11/8000/8003/8005/8300/8301/8730-8732/8820`  

* Query for the reset value of parameter x  
`http://<ip-of-server>/R<x>`  
In the display there is a reset option for some parameters. A reset is performed by asking the boiler for the reset value and setting it afterwards.

* Set value v for parameter x  
`http://<ip-of-server>/S<x>=<v>`  
Attention: This feature is not extensively tested. So be careful what are you doing and do it on your own risk. The format of the value depends on its type. Some parameters can be disabled. 
To set a parameter to 'disable', just send an empty value  
`http://<ip-of-server>/S<x>=`  
The description of the value formats will be added here. Until then have a look at the source code (function set).
         
* Send INF message for parameter x with value v  
`http://<ip-of-server>/I<x>=<v>`  
Some values cannot be set directly. The heating system is informed by a TYPE_INF message, e.g. the room temp:
`http://<ip-of-server>/I10000=19.5`  // room temperature is 19.5 degree.
        
* Activate verbose output  
`http://<ip-of-server>/V<n>`  
Set to 1 to print all data additionally in raw hex format. Set to 0 to turn verbose output off.  
The verbose output affects both the serial console of the mega2560 as well as (optional) logging bus data to SD card, so this can fill up your card pretty fast! The html output is kept unchanged.

* Activate bus monitor  
`http://<ip-of-server>/M<n>`  
When setting it to 1 all bytes on the bus monitored. Telegrams are recognized by a character break condition. Every Telegramm is printed in hex format to serial output with a timestamp in milliseconds.  
The monitor output only affects the serial console of the mega2560. The html output is kept unchanged.
        
* Set/query GPIO pins  
`http://<ip-of-server>/G<xx>[,I][=<y>]`  
Returns the current status of GPIO pin xx (0 or 1). Can be used to set the pin to 0 (LOW) or 1 (HIGH).  
Reserved pins which are not allowed to be written can be defined in BSB_lan_config.h in variable GPIO_exclude.  
By default, pins are set to output mode. To set to input mode, add `,I` after the pin you want to turn to input, e.g. `/G06,I`.
      
* Show 24h averages of selected parameters  
`http://<ip-of-server>/A[=parameter1,...,parameter20]`  
Initially define parameters you want to generate rolling 24h averages from in BSB_lan_config.h in variable avg_parameters.
During runtime, you can use `/A=[parameter1],...,[parameter20]` to set (up to 20) new parameters.
      
* Query values of ds18b20 temperature sensors  
`http://<ip-of-server>/T`  
Returns temperature of optionally connected ds18b20 temperature sensors.
        
* Query values of DHT22 temperature sensors  
`http://<ip-of-server>/H`  
Returns temperature of optionally connected DHT22 temperature/humidity sensors.
      
* Query temperatures of MAX! heating/wall thermostats  
`http://<ip-of-server>/X`  
Returns temperature of optional MAX! heating/wall thermostats defined in BSB_lan_config.h.
      
* Accumulated duration of burner  
`http://<ip-of-server>/B`   
Query accumulated duration of burner on status (in seconds) captured from broadcast messages. Use /B0 to reset.

* Activate/deactivate logging to microSD-card  
In general, the activation/deactivation of the logging founds place by the definement in the BSB_lan_config.h-file.  
If the function is active, you can deactivate the function during runtime by using the following parameters: 
`http://<ip-of-server>/L=0,0`  
For activation, you can just set a new interval and the desired parameters (see configure log file).
        
* Configure log file  
`http://<ip-of-server>/L=<x>[,<parameter1>,<...>,<parameter20>]`  
Set logging interval to x seconds and (optionally) set logging parameters to [parameter1], [parameter2] etc. during runtime. Logging parameters needs to be activated by uncommenting the LOGGER directive in BSB_lan_config.h and can be configured initially with variables log_parameters and log_interval.
        
* Configure logging of bus telegrams  
`http://<ip-of-server>/LU=<x>`  
When logging bus telegrams (logging parameter 30000), log only unknown command IDs (x=1) or all (x=0) telegrams.  
`http://<ip-of-server>/LB=<x>`  
When logging bus telegrams (logging parameter 30000), log only broadcast (x=1) or all (x=0) telegrams.

* Display log file  
`http://<ip-of-server>/D`  
Shows the content of datalog.txt file on the Ethernet shield's micro SD card slot.  
Use /D0 to reset datalog.txt including writing a proper CSV file header (recommended on first use before logging starts).

* Set bus type (temporarily)  
`http://<ip-of-server>/Px`  
Switches between BSB (x=0), LPB (x=1) and PPS bus (x=2). Use setBusType config option in BSB_lan_config.h to set bus type permanently.

* Reset Arduino  
`http://<ip-of-server>/N`  
Resets the Arduino after pausing for 8 seconds (#define RESET in BSB_lan_config.h).

<B>Open issues</B>  
- Add more command ids to the table.
          Only the known command ids from the threads listed above and the tested boiler systems are contents of the table.
          Any user with a different boiler system can set the verbosity to 1 and decode the missing command ids simply by accessing the 
          sytem via
          the display.
          Cause we want to provide a general working system for all boiler configurations working with BSB. Any help and feedback is 
          appreciated!
          
- Test and complete the set funcionality
          With the current implementation a lot of values can be already set. But there is still some testing needed and some parameter 
          types have to be added.

- Decode DE telegrams. Maybe they contain some status information and we can use them without querying.

- Add further support of error messages sent by the boiler system

<B>Further Info:</B>  
      http://www.mikrocontroller.net/topic/218643  
      http://blog.dest-unreach.be/2012/12/14/reverse-engineering-the-elco-heating-protocol  
      http://forum.fhem.de/index.php/topic,29762.0.html  
      Brötje "Systemhandbuch ISR"
