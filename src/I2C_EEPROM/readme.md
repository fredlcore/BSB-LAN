<html>
 <head>
  <meta http-equiv="content-type" content="text/html; charset=utf-8">
  <title>I2C EEProm </title>
 </head>
 <body>
<h1>Eine recht universelle I2C EEProm Library</h1>
<p>Version 0.3 vom 06.01.2016 12:52:30</p>
<p>Einsetzbar mit der Arduino IDE. Die Lib basiert auf Wire.</p>
<br>


<h2>Download</h2>
<a href="http://combie.de/Arduino/I2C_EEPROM/I2C_EEPROM.zip">I2C EEProm Library für Arduino</a>, evtl. in einer neueren Fassung
<br>
<a href="http://combie.de/Arduino/I2C_EEPROM/readme.html">Dieses Dokument</a>, evtl. in einer neueren Fassung
<br>


<h2>Features</h2>
<ol type="1">
 <li>Größtenteils aufrufkompatibel mit der Arduino EEPROM Lib</li>
 <li>Unterstützung vieler I2C EEProms</li>
 <li>Relativ einfache Erstellung von User definierten EEProms</li>
 <li>Geringer RAM Verbrauch</li>
</ol>
<br>

<h2>Unterstützte EEProms</h2>
Hinzufügen weiterer EEProms ist jederzeit möglich.
<table width="760" align="center" border="1" cellspacing="0" cellpadding="7" style="border-collapse: collapse">
 <tr>
  <td valign="top" colspan="4">
  Atmel
  </td>
 </tr>
 
  <tr>
    <td>Classname</td>
    <td>Size</td>
    <td>Page Size</td>
    <td>Adressmode</td>
 </tr>
  <tr>
    <td>AT24C01</td>
    <td>128</td>
    <td>8</td>
    <td>1</td>
 </tr>
 
  <tr>
    <td>AT24C02</td>
    <td>256</td>
    <td>8</td>
    <td>1</td>
 </tr>
  <tr>
    <td>AT24C04</td>
    <td>512</td>
    <td>16</td>
    <td>1</td>
 </tr>
   <tr>
    <td>AT24C08</td>
    <td>1024</td>
    <td>16</td>
    <td>1</td>
 </tr>
   <tr>
    <td>AT24C16</td>
    <td>2048</td>
    <td>16</td>
    <td>1</td>
 </tr>
  <tr>
    <td>AT24C32</td>
    <td>4096</td>
    <td>32</td>
    <td>2</td>
 </tr>
  <tr>
    <td>AT24C64</td>
    <td>8192</td>
    <td>64</td>
    <td>2</td>
 </tr>
  <tr>
    <td>AT24C128</td>
    <td>16384</td>
    <td>64</td>
    <td>2</td>
 </tr>
 
  <tr>
    <td>AT24C256</td>
    <td>32768</td>
    <td>64</td>
    <td>2</td>
 </tr>
  <tr>
    <td>AT24C512</td>
    <td>65536</td>
    <td>128</td>
    <td>2</td>
 </tr>
</table>
<br>
<table width="760" align="center" border="1" cellspacing="0" cellpadding="7" style="border-collapse: collapse">
 <tr>
  <td valign="top" colspan="4">
  STMicroelectronics
  </td>
 </tr>
 
  <tr>
    <td>Classname</td>
    <td>Size</td>
    <td>Page Size</td>
    <td>Adressmode</td>
 </tr>
 
  <tr>
    <td>M24C01</td>
    <td>128</td>
    <td>16</td>
    <td>1</td>
 </tr>
  <tr>
    <td>ST24C01</td>
    <td>128</td>
    <td>8</td>
    <td>1</td>
 </tr>
  <tr>
    <td>M24C02</td>
    <td>256</td>
    <td>16</td>
    <td>1</td>
 </tr>
  <tr>
    <td>ST24C02</td>
    <td>256</td>
    <td>8</td>
    <td>1</td>
 </tr>
  <tr>
    <td>M24C04</td>
    <td>512</td>
    <td>16</td>
    <td>1</td>
 </tr>
  <tr>
    <td>ST24C04</td>
    <td>512</td>
    <td>8</td>
    <td>1</td>
 </tr>
  <tr>
    <td>M24C08</td>
    <td>1024</td>
    <td>16</td>
    <td>1</td>
 </tr>
  <tr>
    <td>ST24C08</td>
    <td>1024</td>
    <td>16</td>
    <td>1</td>
 </tr>
  <tr>
    <td>M24C16</td>
    <td>2048</td>
    <td>16</td>
    <td>1</td>
 </tr>
 
  <tr>
    <td>M24C32</td>
    <td>4096</td>
    <td>32</td>
    <td>2</td>
 </tr>
  <tr>
    <td>M24C64</td>
    <td>8192</td>
    <td>32</td>
    <td>2</td>
 </tr>
 
  <tr>
    <td>M24128</td>
    <td>16384</td>
    <td>64</td>
    <td>2</td>
 </tr>
  <tr>
    <td>M24256</td>
    <td>32768</td>
    <td>64</td>
    <td>2</td>
 </tr>
  <tr>
    <td>M24512</td>
    <td>65536</td>
    <td>64</td>
    <td>2</td>
 </tr>
 </table>
<br>
<table width="760" align="center" border="1" cellspacing="0" cellpadding="7" style="border-collapse: collapse">
 <tr>
  <td valign="top" colspan="4">
  Microchip
  </td>
 </tr>
 
  <tr>
    <td>Classname</td>
    <td>Size</td>
    <td>Page Size</td>
    <td>Adressmode</td>
 </tr>
 
  <tr>
    <td>MC24C01C</td>
    <td>128</td>
    <td>16</td>
    <td>1</td>
 </tr>
 
  <tr>
    <td>MC24AA02E48</td>
    <td>256</td>
    <td>8</td>
    <td>1</td>
 </tr>
  <tr>
    <td>MC24AA025E48</td>
    <td>256</td>
    <td>16</td>
    <td>1</td>
 </tr>
 </table>


<h2> Grund zur Erstellung</h2>
<p>Für eine Menueführung wollten viele Strings verwaltet werden. Selbst das F() Macro war nur bedingt hilfreich, es wurde knapp mit dem Flash Speicher. Das im AVR eingebaute EEPROM hat am Anfang Linderung gebracht, aber mit zunehmender Größe des Projektes reichte es auch nicht mehr. Und sowieso sind die EEProms des AVR eher klein.</p>


<p>Abhilfe versprach das sowieso schon auf der verwendeten RTC verbaute Atmel AT24C32 I2C EEProm. Bei der Suche nach brauchbaren Libs ist mir einiges Gutes unter gekommen. Aber auch viele gruselige Dinge. Was aber allen gemeinsam war, sie decken nur wenige Typen ab. Und jede Lib hat ihre eigenen Methoden, welche wenig Ähnlichkeiten mit den Methoden der original Arduino EEProm Lib haben.</p>

<h2>Installation</h2>
<p>Diese Library liegt als Zip Datei vor. Im Library Manager der Arduino IDE, die Zip Datei auswählen und installieren.
<br>
Hauptmenu -> Sketch -> Include Library -> Add .ZIP Library<br>
</p>

<h2>Abhängigkeiten</h2>
<p> Diese Lib basiert auf Wire. In der setup() Funktion muss ein Wire.begin() gemacht werden. Die verwendeten EEProms müssen das "ACKNOWLEDGE POLLING" beherrschen. </p>

</p>Hier die status.ino aus den examples/Beispielen der Library</p>
<pre>
<font color="#000000">#include</font> <font color="#434f54">&lt;</font><font color="#d35400">Wire</font><font color="#434f54">.</font><font color="#000000">h</font><font color="#434f54">&gt;</font>
<font color="#000000">#include</font> <font color="#434f54">&lt;</font><font color="#000000">I2C_EEPROM</font><font color="#434f54">.</font><font color="#000000">h</font><font color="#434f54">&gt;</font>




<font color="#000000">AT24C32</font><font color="#434f54">&lt;</font><font color="#434f54">&gt;</font> <font color="#000000">eep</font><font color="#000000">;</font> <font color="#434f54">// Das EEProm auf der china üblichen RTC, default Adresse 0x50 (80)</font>

<font color="#00979c">void</font> <font color="#5e6d03">setup</font><font color="#000000">(</font><font color="#000000">)</font> 
<font color="#000000">{</font>
 &nbsp;&nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">begin</font><font color="#000000">(</font><font color="#000000">9600</font><font color="#000000">)</font><font color="#000000">;</font> 
 &nbsp;&nbsp;<font color="#d35400">Wire</font><font color="#434f54">.</font><font color="#d35400">begin</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">;</font>
 
 &nbsp;&nbsp;<font color="#434f54">// die Speichergröße des EEProm wird in der Klasse gespeichert</font>
 &nbsp;&nbsp;<font color="#434f54">// kann also ausgelesen werden, ohne dass das EEProm wirlich</font>
 &nbsp;&nbsp;<font color="#434f54">// bereit ist </font>
 &nbsp;&nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">print</font><font color="#000000">(</font><font color="#00979c">"EE Prom lenth: "</font><font color="#000000">)</font><font color="#000000">;</font> 
 &nbsp;&nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">println</font><font color="#000000">(</font><font color="#000000">eep</font><font color="#434f54">.</font><font color="#d35400">length</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">)</font><font color="#000000">;</font> 

 &nbsp;&nbsp;<font color="#5e6d03">if</font><font color="#000000">(</font><font color="#000000">eep</font><font color="#434f54">.</font><font color="#d35400">ready</font><font color="#000000">(</font><font color="#000000">)</font><font color="#000000">)</font> <font color="#434f54">// eeprom bereit ?</font>
 &nbsp;&nbsp;<font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#434f54">// eeprom wurde gefunden, und ist bereit</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">println</font> <font color="#000000">(</font><font color="#00979c">"EEProm ist bereit!"</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;<font color="#000000">}</font><font color="#5e6d03">else</font>
 &nbsp;&nbsp;<font color="#000000">{</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#434f54">// eeprom hat nicht geantwortet</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<font color="#434f54">// Auch direkt nach dem schreiben blockiert das eeprom ein paar ms</font>
 &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<b><font color="#d35400">Serial</font></b><font color="#434f54">.</font><font color="#d35400">println</font><font color="#000000">(</font><font color="#00979c">"EEProm ist nicht bereit, Verkabelung prüfen "</font><font color="#000000">)</font><font color="#000000">;</font>
 &nbsp;&nbsp;<font color="#000000">}</font>
<font color="#000000">}</font>

<font color="#00979c">void</font> <font color="#5e6d03">loop</font><font color="#000000">(</font><font color="#000000">)</font> 
<font color="#000000">{</font>

<font color="#000000">}</font>
</pre>

<h2>Kompatibilität zu EEPROM</h2>

<h3>void begin()</h3>
<p>Eine Methode begin() gibt es nicht. Es besteht hier keine Notwendigkeit für eine solche Methode.</p>
<br>
<h3>uint16_t length()</h3>
<p>Length gibt die größe des EEProms zurück.</p>
<br>
<h3>uint8_t read(unit16_t address)</h3>
<p>Read liest 1 Byte von der angegebenen Adresse</p>
<br>
<h3>void write(unit16_t address,uint8_t value)</h3>
<p>Write schreibt 1 Byte an die angegebenen Adresse</p>
<br>
<h3>void update(unit16_t address,uint8_t value)</h3>
<p>Update nutzt intern read() und write(). Es wird nur geschrieben wenn sich die Daten unterscheiden.</p>
<br>
<h3>void put(unit16_t address,  customvar)</h3>
<p>Put schreibt einen beliebigen Variableninhalt an gegebenen Adresse. Die notwendige Länge wird selbst berechnet. put() ruft intern update() auf.</p>
<br>
<h3>void get(unit16_t address,  customvar)</h3>
<p>Get liest einen beliebigen Variableninhalt von der gegebenen Adresse. Die notwendige Länge wird selbst berechnet.</p>

<h3>Array Access Interface</h3>
<p>Nicht implementiert.</p>



<h2>Eigene, zusätzliche Methoden</h2>

<h3>bool ready()</h3>
<p>Ready liefert true, wenn der Baustein bereit ist.</p>
<br>
<h3>void fastBlockWrite(uint16_t address,void * start, uint16_t length)</h3>
<p>fastBlockWrite schreibt einen beliebigen Datenblock an die angegebene EEProm Addresse. Das Paging wird intern abgehandelt.</p>
<br>
<h3>void fastBlockRead(uint16_t address,void * start, uint16_t length)</h3>
<p>fastBlockRead liest einen beliebigen Datenblock von der angegebenen EEProm Addresse. Das Paging wird intern abgehandelt.</p>
<br>
<p>fastBlockRead() und fastBlockWrite() sind deutlich fixer (ca 6 mal), als put() und get(). Der Geschwindigkeitsvorteil wird erkauft durch den Verzicht auf das vorherige prüfen, ob sich die Daten unterscheiden. Desweiteren wird das Page schreiben/lesen der Bausteine unterstützt.  </p>

<br>

<h3>void onWaiting( void (*callback)())</h3>
<p>Nach Schreibvorgängen braucht das EEProm etwas Zeit um den Vorgang abzuschließen. Hier kann eine Callback Funktion aufgerufen werden um diese Zeit zu nutzen. Es ist nicht ratsam, in der Callback Funktion, weitere EEProm Aufrufe zu tätigen. </p>


<p></p>
<p></p>
<p></p>
<p></p>



  
 </body>
</html>