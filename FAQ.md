<H2>Is there a simple way to log parameters?</H2>

Yes, there is!
Run this command periodically (e.g. via a cron job):
<pre>
DATE=`date +%Y%m%d%H%M%S`; wget -qO- http://192.168.1.50/1234/8310/720/710 | egrep "(8310|720|710)" | sed "s/^/$DATE /" >> log.txt
</pre>
The resulting log.txt file of this example contains the logged values for parameters 8310, 720 and 710. Just change these parameter numbers in the http-request as well as the egrep command (and of course the IP address and the passcode) and you are set. 
Later on, you can sort the log file based on parameter numbers with the sort command:
<pre>
sort -k2 log.txt
</pre>

<H2>I'm using FHEM and want to process the data from my heating system. How can I do this?</H2>

Please note that FHEM is a complex software and this is not the place to provide basic introductions or instructions. But if you have already configured other devices for FHEM, this will hopefully help you:

To access the web interface of the device, you can use FHEM's HTTPMOD module. Here's an example configuration which you can easily adapt to your own needs and parameters. Of course you need to change the IP address as well as the passcode, too.
This code polls parameters 8700, 8743 and 8314 every 300 seconds and assigns these to the device "THISION" (the name of my heating system) to the readings "Aussentemperatur", "Vorlauftemperatur" and "Ruecklauftemperatur". It furthermore provides a reading "Istwert" that can be set via FHEM to provide the current room temperature to the heating system (parameter 10000). Finally, it calculates the difference between "Vorlauftemperatur" and "Ruecklauftemperatur" and assigns this difference to the reading "Spreizung".

<pre>
define THISION HTTPMOD http://192.168.1.50/1234/8700/8743/8314 300
attr THISION userattr reading0Name reading0Regex reading1Name reading1Regex reading2Name reading2Regex readingOExpr set0Name set0URL
attr THISION event-on-change-reading .*
attr THISION reading0Name Aussentemperatur
attr THISION reading0Regex 8700 .*:[ \t]+([-]?[\d\.]+)
attr THISION reading1Name Vorlauftemperatur
attr THISION reading1Regex 8743 .*:[ \t]+([-]?[\d\.]+)
attr THISION reading2Name Ruecklauftemperatur
attr THISION reading2Regex 8314 .*:[ \t]+([-]?[\d\.]+)
attr THISION readingOExpr $val=~s/[\r\n]//g;;$val
attr THISION set0Name Istwert
attr THISION set0URL http://192.168.1.50/1234/I10000=$val
attr THISION timeout 5
attr THISION userReadings Spreizung { sprintf("%.1f",ReadingsVal("THISION","Vorlauftemperatur",0)-ReadingsVal("THISION","Ruecklauftemperatur",0));; }
</pre>

<H2>My heating system has parameters that are not supported in the software yet, can I help adding these parameters?</H2>

Yes, you can :)! All you need is to connect your Arduino to a Laptop/PC via USB while it is connected to your heating system and follow these steps:

1. Start the Arduino IDE and turn on the serial monitor
2. Enable logging to the serial console and turn on verbose output with the URL-Parameters /M1 and /V1 respectively on the Arduino, e.g. http://192.168.1.50/1234/M1 and http://192.168.1.50/1234/V1
3. On the heating system, switch to the parameter you want to analyze (using the command wheel, arrows or whatever input mode your heating system has).
4. Wait for "silence" on the bus and then switch forward one parameter and then back again to the parameter you want. You should now have something like this on the log:
<pre>
DISP->HEIZ QUR      113D305F
DC 8A 00 0B 06 3D 11 30 5F AB EC
HEIZ->DISP ANS      113D305F 00 00
DC 80 0A 0D 07 11 3D 30 5F 00 00 03 A1 
DISP->HEIZ QUR      113D3063
DC 8A 00 0B 06 3D 11 30 63 5C 33
HEIZ->DISP ANS      113D3063 00 00 16
DC 80 0A 0E 07 11 3D 30 63 00 00 16 AD 0B 
</pre>
The first four lines are from the parameter you switched forward to, the last four lines are from the parameter you want to analyze (doing the switching back and forth only makes sure that the last message on the bus is really the parameter you are looking for). Instead of DISP you might see RGT1, depending on what device you are using to select the parameter.
Each data telegram has the following structure:<BR><BR>
Byte 1: always 0xDC (start of telegram)<br>
Byte 2: source device (0x00 = heating system, 0x06 = room device 1, 0x07 = room device 2, 0x0A = display, 0x7F = all) plus 0x80<BR>
Byte 3: destination device (same values as source)<BR>
Byte 4: telegram length (start-of-telegram byte (0xDC) is not counted)<BR>
Byte 5: message type (0x02 = info, 0x03 = set, 0x04 = ack, 0x05 = nack, 0x06 = query, 0x07 = answer, 0x08 = error)<BR>
Byte 6-9: Command ID (that's what we're interested in!)<BR>
Byte 10...: Payload data (optional)<BR>
Last two bytes: CRC checksum<BR><BR>
5. The lower data telegram above has the command ID 0x113D3063. Please note that the first two bytes of the command ID are switched in message type "query" (0x06), so make sure you look at the right telegram (type "answer" (0x07), last line in this example).
6. Look up the "global command table" section in file BSB_lan_defs.h and check whether an entry for this command already exists (search for STRxxxx where xxxx is the parameter number). If it does exist, go on to step 8.
7. If your parameter is not yet listed in the "global command table", you have to add an entry in the "menu strings" section like this:
<pre>const char STRxxxx[] PROGMEM = "Parameter_Name_or_Function";</pre>
Now copy a line from the "global command table" section where your new parameter would fit numerically. Proceed with step 6b but rather than replacing CMD_UNKNOW you have to replace the command ID and value type of the copied line of course.
8. Replace the CMD_UNKNOWN with the command ID you just found. If the return value type (column 3) is VT_UNKNOWN try and find out which parameter type from the list at the beginning of the file works. For example, if the parameter should return a temperature value, you can try VT_TEMP, VT_TEMP_SHORT, VT_TEMP_SHORT5 or VT_TEMP_WORD. For parameters which offer multiple options, you have to add a corresponding line in the "ENUM tables" section. 
9. If the web interface gives you the same value as is displayed on the heating system, you have found the right value type and the parameter is now fully functional (i.e. querying and setting the value will work). Congratulations!
10. When you are done, double check that the new command ID is not used somewehere else in the definition file (i.e. search for the command id - only one location should come up). It's possible that command IDs exist for different parameters with different heating systems because the protocol is not standardized and manufacuters don't seem to bother how other manufacturers use the command IDs, at least with less general parameters. If it occurs that a command ID is now existing twice in the BSB_lan_defs.h file, please mark it clearly when sending us the update and state which heating system you are using. We will then add a conditional compile flag so that heatingy system X will compile differently than system Y so that in the end both will use the ambiguous command ID for the right parameter.
11. Please send only the new/updated lines to bsb (ät) code-it.de - if you use a diff-file, please make sure that you download the most recent BSB_lan_defs.h from the repository before making the diff because sometimes the file gets updated without an actual new version being released immediately.
