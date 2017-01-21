<H2>My heating system has parameters that are not supported in the software yet, can I help adding these parameters?</H2>

Yes, you can :)! All you need is to connect your Arduino to a Laptop/PC while it is connected to your heating system and follow these steps:

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
The first four lines are from the parameter you switched forward to, the last four lines are from the parameter you want to analyze (doing the switching back and forth only makes sure that the last message on the bus is really the parameter you are looking for).
Each data telegram has the following structure:<BR><BR>
1st byte: always 0xDC (start of telegram)<br>
2nd byte: source (0x00 = heating system, 0x06 = room device 1, 0x07 = room device 2, 0x0A = display, 0x7F = all)<BR>
3rd byte: destination (same values as source)<BR>
4th byte: telegram length (start-of-telegram byte (0xDC) is not counted)<BR>
5th byte: message type (0x02 = info, 0x03 = set, 0x04 = ack, 0x05 = nack, 0x06 = query, 0x07 = answer, 0x08 = error)<BR>
Byte 6-9: Command ID (that's what we're interested in!)<BR>
Byte 10...: Return values (only in type "answer")<BR>
Last two bytes: CRC checksum<BR><BR>
5. The last four lines above have the command ID 0x113D3063. Please note that the first two bytes of the command ID are switched in message type "query" (0x06), so make sure you look at the right telegram (last line in this example).
6. Look up the "global command table" section in file BSB_lan_defs.h and check whether an entry for this command already exists (search for STRxxxx where xxxx is the parameter number). If it does exist, go on to step 6b.
6a. If your parameter is not yet listed in the "global command table", you have to add an entry in the "menu strings" section like this:
<pre>const char STRxxxx[] PROGMEM = "Parameter_Name_or_Function";</pre>
Now copy a line from the "global command table" section where your new parameter would fit numerically. Proceed with step 6b but rather than replacing CMD_UNKNOW you have to replace the command ID and value type of the copied line of course.
6b. Replace the CMD_UNKNOWN with the command ID you just found. If the return value type (column 3) is VT_UNKNOWN try and find out which parameter type from the list at the beginning of the file works. For example, if the parameter should return a temperature value, you can try VT_TEMP, VT_TEMP_SHORT, VT_TEMP_SHORT5 or VT_TEMP_WORD. For parameters which offer multiple options, you have to add a corresponding line in the "ENUM tables" section. 
6c. If the web interface gives you the same value as is displayed on the heating system, you have found the right value type and the parameter is now fully functional (i.e. querying and setting the value will work). Congratulations!
7. When you are done, double check that the new command ID is not used somewehere else in the definition file (i.e. search for the command id - only one location should come up). It's possible that command IDs exist for different parameters with different heating systems because the protocol is not standardized and manufacuters don't seem to bother how other manufacturers use the command IDs, at least with less general parameters. If it occurs that a command ID is now existing twice in the BSB_lan_defs.h file, please mark it clearly when sending us the update and state which heating system you are using. We will then add a conditional compile flag so that heatingy system X will compile differently than system Y so that in the end both will use the ambiguous command ID for the right parameter.
8. Please send only the new/updated lines to bsb (ät) code-it.de - if you use a diff-file, please make sure that you download the most recent BSB_lan_defs.h from the repository before making the diff because sometimes the file gets updated without an actual new version being released.
