BSB-LAN-Adapter

ACHTUNG:  
      Es gibt KEINE GARANTIE (oder Gewährleistung jeglicher Art), dass dieser Adapter dein Heizungssystem NICHT beschädigt!

Autor:	Gero Schumacher (gero.schumacher@gmail.com)  
      Basierend auf dem Code und der Arbeit von vielen anderen Entwicklern (s. Info-Abschnitt weiter unten). Vielen Dank!

Übersetzung EN-DE: Ulf Dieckmann (nach bestem Wissen und Gewissen ;) )

Lizenz:
	Es steht dir frei, diese Software auf dein eigenes Risiko hin zu benutzen. Bitte beachte die Lizenzbedingungen der genutzten Bibliotheken und Software.

Info:  
      http://www.mikrocontroller.net/topic/218643  
      http://blog.dest-unreach.be/2012/12/14/reverse-engineering-the-elco-heating-protocol  
      http://forum.fhem.de/index.php/topic,29762.0.html  
      systemhandbuch_isr.pdf

Host System:  
Die Software wurde entwickelt, um auf einem Arduino-Mega2560-Board samt Ethernet-Shield zu laufen. Da es unterschiedliche Pinbelegungen bei den verschiedenen Ethernet-Shields gibt, ist es u.U. nötig, den BSB-Adapter an andere Pins anzuschließen und die entsprechenden Änderungen bzgl. der Pinbelegung in der Software anzupassen.  
Die Software wurde mit folgenden Komponenten getestet:        
- SainSmart MEGA2560 R3 Development Board  
- SainSmart Ethernet Schild für Arduino UNO MEGA Duemilanove Neu Version W5100  
- BSB-Interface (see BSB_adapter.pdf)  
Für diese Konfiguration wird Pin A14 (68) als RX, und Pin A15 (69) als TX genutzt:

`BSB bus(68,69);`
      
Zielsystem:  
      Getestet mit: Elco Straton Ölbrenner
	Die Kommunikation sollte prinzipiell mit allen Systemen möglich sein, die einen BSB aufweisen.
	Fehlende Befehls-IDs müssen in der cmdtbl hinzugefügt werden.
	Bisher ist mir nicht klar, worin der Unterschied zwischen den LPB- und den BSB-Protokollen besteht. Die technischen Spezifikationen sind die gleichen. Möglicherweise gibt es Unterschiede auf der Protokoll-Ebene. Bisher habe ich den Adapter nur an den BSB angeschlossen.
    
VOR DEM KOMPILIEREN der Software müssen einige Parameter in der Datei "BSB_lan_config.h" angepasst werden:  
- Die MAC-Adresse des Ethernet-Shields. Üblicherweise (jedoch nicht immer) befindet sie sich auf einem Aufkleber auf dem Ethernet-Shield:  
  `byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEA };`  
- Ethernet-Adresse:  
  `IPAddress ip(192,168,178,88);`  
- Ethernet-Port:  
  `EthernetServer server(80);`  
- Pinbelegung des BSB-Adapters:  
  `BSB bus(68,69);`  
- (optional) Man kann die Funktion eines Sicherheitsschlüssels (PASSKEY) aktivieren (s. unten):  
  `#define PASSKEY  "1234"`  
- (optional) BSB-Adresse (voreingestellt ist 0x06=RGT1, dies kann jedoch bei der Bus-Initialisierung überschrieben werden):  
  `BSB bus(68,69,<my_addr>);`
  Um den BSB-LAN-Adapter (bei einem bereits vorhandenem Raumgerät RGT1) als RGT2 anzumelden, gib Folgendes ein:
  `BSB bus(68,69,7);`  
- (optional) Man kann den Zugriff auf den Adapter auf Lesen beschränken, ein Setzen bzw. Verändern von Parametern der Heizungssteuerung per Adapter ist dann nicht mehr möglich. Dazu muss in der betreffenden Zeile (#define DEFAULT_FLAG 0) das Flag auf FL_RONLY gesetzt werden:  
  `#define DEFAULT_FLAG FL_RONLY;`
- (optional) Man kann die Sprache des Webinterfaces des Adapters auf deutsch einstellen, indem man das entsprechende Definement aktiviert:  
  `#define LANG_DE;`
        
Adapter:  
      Eine einfache Syntaxbeschreibung wird auf der Webseite angezeigt, wenn ohne weitere Parameter auf die URL des Servers zugegriffen wird.  
      Bspw. `http://<ip-of-server>`  
      Um das System vor einem ungewollten Zugriff von aussen zu schützen, kann die Funktion des Sicherheitsschlüssels (PASSKEY) aktiviert werden (sehr einfach und nicht wirklich sicher!).  
      Falls die PASSKEY-Funktion aktiviert ist (s. unten), muss die URL den definierten Schlüssel als erstes Element enthalten,
      bspw. `http://<ip-of-server>/<passkey>/`    - um die Hilfeseite zu sehen  
      Die URLs in den folgenden Beispielen müssen um die PASSKEY-Definition erweitert werden, falls die Funktion aktiviert wurde.  
      Alle Parameter werden anhand ihrer Zeilennummern abgefragt. Eine nahezu vollständige Übersicht findet sich im Systemhandbuch der ISR ("systemhandbuch_isr.pdf").  
      Einige Zeilen sind 'virtuell' und wurden bspw. hinzugefügt, um den Zugang zu komplexen Einstellungen wie den Tagesprogrammen zu erleichtern.  
      Die Parameter sind in Kategorien unterteilt, die den im Display dargestellten Untermenükategorien entsprechen, wenn auf das Heizungssystem vom integrierten Regler aus zugegriffen wird.  

      Alle Kategorien auflisten:
      http://<ip-of-server>/K
        Bei diesem Befehl kommuniziert der Adapter nicht mit dem Heizungssystem. Es ist eine softwareseitige, interne Funktion.

      Alle enum-Werte für Parameter x auflisten:
      http://<ip-of-server>/E<x>
        Bei diesem Befehl kommuniziert der Adapter nicht mit dem Heizungssystem. Es ist eine softwareseitige, interne Funktion.
        Dieser Befehl ist nur für Parameter des Typs VT_ENUM verfügbar.

      Alle Werte von Kategorie x abfragen: 
        http://<ip-of-server>/K<x>

      Alle Werte von Zeile x abfragen:
        http://<ip-of-server>/<x>

      Alle Werte eines Zeilenbereichs abfragen (von Zeile x bis Zeile y):
        http://<ip-of-server>/<x>-<y>

      Mehrere Abfragen können miteinander verkettet werden:
        e.g. http://<ip-of-server>/K11/8000/8003/8005/8300/8301/8730-8732/8820

      Frage den Reset-Wert für Parameter x ab:
        http://<ip-of-server>/R<x>
        Im Display der integrierten Heizungssteuerung gibt es für einige Parameter eine Reset-Option. Ein Reset wird vorgenommen, indem das System nach dem Reset-Wert gefragt wird und dieser anschließend gesetzt wird.

      Setze Wert v (value) für den Parameter x
        http://<ip-of-server>/S<x>=<v>
        ACHTUNG: Dies Funktion ist nicht ausgiebig getestet! Bitte sei vorsichtig mit dieser Funktion und nutze sie ausschließlich auf dein eigenes Risiko hin. Das Format des Wertes hängt von seinem Typ ab. Einige Parameter können abgeschaltet werden. 
        Um einen Parameter auf 'abgeschaltet/deaktiviert' zu setzen, muss einfach ein leerer Wert eingefügt werden.
        http://<ip-of-server>/S<x>=
        Die Beschreibung der Werteformatierungen wird hier hinzugefügt. Bis dahin sieh dir den Quellcode an (Funktion 'set').
         
      Sende eine INF Nachricht für den Parameter x mit dem Wert v
        http://<ip-of-server>/I<x>=<v>
        Einige Werte können nicht direkt gesetzt werden. Das Heizungssystem wird mit einer TYPE_INF-Nachricht informiert, bspw. die Raumtemperatur:
        http://<ip-of-server>/I10000=19.5  // Raumtemperatur beträgt 19.5°C

      Setze den Verbositäts-Level auf n
        http://<ip-of-server>/V<n>
        Der voreingestellte Verbositäts-Level ist 0. Wenn er auf 1 gesetzt wird, werden der Bus überwacht und alle Daten zusätzlich im Raw-Hex-Format dargestellt.
        Der Verbositäts-Level betrifft sowohl die serielle Konsole des Arduino Mega2560 als auch (optional) das Loggen der Bus-Daten auf die microSD-Karte, so dass die Karte u.U. sehr schnell voll wird! Die html-Ausgabe bleibt unverändert.

      Bus-Monitor aktivieren:
        http://<ip-of-server>/M<n>
        Wenn er auf 1 gesetzt wird, werden alle Bytes auf dem Bus überwacht. Telegramme werden durch Umbruchzeichen (Anm. d. Übers.: ? - original:"break character condition") als solche erkannt. Jedes Telegramm wird im Hex-Format auf der seriellen Konsole mit einem Zeitstempel in Milisekunden dargestellt.
        Die Ausgabe der Überwachung betrifft nur die serielle Konsole des Arduino Mega2560. Die html-Ausgabe bleibt unverändert.
        
      Setzen/Abfragen der GPIO Pins
        http://<ip-of-server>/G<xx>[=<y>]
        Gibt den momentanen Status von GPIO Pin xx zurück (0 oder 1). Kann ebenfalls benutzt werden, um den Pin auf 0 (LOW) oder 1 (HIGH) zu setzen. 
        Reservierte Pins, die nicht gesetzt werden dürfen, können in der BSB_lan_config.h unter dem Parameter GPIO_exclude gesperrt werden.
      
      24h Durchschnittswerte von ausgewählten Parametern anzeigen
        http://<ip-of-server>/A[=parameter1,...,parameter20]
        Zeigt rollierende 24h Durchschnittswerte ausgewählter Parameter an. Initiale Festlegung dieser Parameter in BSB_lan_config.h in der Variable avg_parameters.
        Während der Laufzeit kann "/A=[parameter1],...,[parameter20]" verwendet werden, um (bis zu 20) neue Parameter zu definieren.
      
      Abfrage von DS18B20 Temperatursensoren
        http://<ip-of-server>/T
        Gibt die Temperaturwerte von optional angeschlossenen DS18B20-Sensoren aus.
        
      Abfrage von DHT22 Feuchtigkeits-/Temperatursensoren
        http://<ip-of-server>/H
        Gibt die Feuchtigkeits-/Temperaturwerte von optional angeschlossenen DHT22-Sensoren aus.
      
      Akkumulierte Brennerlaufzeit
        http://<ip-of-server>/B
        Fragt die akkumulierte Brennerlaufzeit (in Sekunden) ab, die von den Broadcast Nachrichten ermittelt wurden. /B0 setzt den Zähler zurück.

      Aktivieren/Deaktivieren des Loggens auf die microSD-Karte
      	Prinzipiell erfolgt das Aktivieren/Deaktivieren der Log-Funktion durch das entsprechende Definement in der config_h vor dem Flashen. Während des Betriebes kann jedoch das Loggen deaktiviert werden, indem man folgende Parameter definiert:
	http://<ip-of-server>/L=0,0
	Zum Aktivieren können dann einfach wieder das Intervall und die gewünschten Parameter eingetragen werden (s. Konfiguration des Logfiles).

      Konfiguration des Logfiles
      	http://<ip-of-server>/L=<x>[,<parameter1>,<...>,<parameter20>]
      	Setzt während der Laufzeit das Logging-Intervall auf x Sekunden und (optional) die Logging-Parameter auf [parameter1], [parameter2] etc. Das Logging muss durch das Definement #define LOGGING in der Datei BSB_lan_config.h aktiviert werden und kann initial anhand der Variablen log_parameters und log_interval konfiguriert werden.

      Konfiguration des Loggens von Bus-Telegrammen
      	http://<ip-of-server>/LU=<x>
      	Wenn Bus-Telegramme geloggt werden (Parameter 30000 als einzigen Parameter loggen), logge nur die unbekannten command IDs (x=1) oder alle (x=0) Telegramme.

      Darstellung des Logfiles
        http://<ip-of-server>/D
        Zeigt den Inhalt der Datei datalog.txt, die sich auf der microSD-Karte im Slot des Ethernet-Shields befindet. 
        Mittels /D0 kann die Datei datalog.txt zurückgesetzt werden, ebenso wird eine korrekte CSV-Header-Datei generiert (dieser Schritt wird für die erste Benutzung empfohlen, bevor das Loggen startet).

Offene Punkte
- Mehr Befehle (command ID) hinzufügen.
          Nur die bekannten Befehle aus der o.g. Forendiskussion und dem getesteten Heizungssystem (ELCO) sind Bestandteil des Programms.
          Jeder Nutzer eines anderen Heizungssystems kann den Verbositäts-Level auf 1 setzen und die fehlenden Befehle dekodieren, indem er sie einfach über die integrierte Steuerung aufruft.
          Unser Ziel ist es, eine generell lauffähiges System zu entwickeln, das herstellerübergreifend mit allen Heizungssystemen verwendet werden kann, die einen BSB aufweisen. Jede Hilfe und jede Rückmeldung ist willkommen!
          
- Testen und Vervollständigen der Funktionalität
          Mit der gegenwärtigen Implementierung können bereits viele Werte gesetzt werden. Jedoch sind noch immer Tests nötig und einige Parameter müssen hinzgefügt werden.

- Zulässige Wertebereiche für Parameter einführen
          Um den Zugriff sicherer zu machen, wenn Werte für Parameter gesetzt werden, sollten zulässige Wertebereiche zum command table hinzugefügt werden.

- Testen und möglicherweise das System so erweitern, dass es mit dem LPB anstelle des BSB genutzt werden kann.

- Dekodieren der DE-Telegramme. Möglicherweise beinhalten sie Statusinformationen, die ohne Abfragen genutzt werden können.

- Unterstützung der vom Heizungssystem aus gesendeten Fehlerberichte hinzufügen
