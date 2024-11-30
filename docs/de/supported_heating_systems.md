# Unterstützte Heizungssysteme

BSB-LAN unterstützt Heizungssysteme, die entweder mit dem [BSB (Boiler System Bus)](bus_systems.md#BSB), dem [LPB (Local Process Bus)](bus_systems.md#LPB) oder der [PPS (Punkt-zu-Punkt-Schnittstelle)](bus_systems.md#PPS) kommunizieren. Diese Steuergeräte werden normalerweise von Siemens hergestellt, bei älteren Geräten kann aber auch noch der Firmenname "Landis & Stafea" oder "Landis & Gyr" auftauchen.

Wir haben eine [Liste mit funktionierenden Modellen](supported_models.md) von verschiedenen Herstellern von Heizungssystemen zusammengestellt, die mit BSB-LAN getestet wurden. Allerdings kann es vorkommen, dass die Hersteller den Modellnamen beibehalten, aber die Steuerung auf ein anderes System umstellen, daher solltest du immer doppelt überprüfen, ob die richtigen Anschlüsse vorhanden sind.

Hier sind ein paar Beispiele von Heizungssteuerungen und den entsprechenden Anschlüssen, die für die Verbindung mit BSB-LAN verwendet werden. Einige Anschlüsse haben drei Pins, andere nur zwei. Wenn drei Pins vorhanden sind, **stelle bitte sicher, dass du die richtigen zwei auswählst (CL+ und CL-)**, da der dritte Pin (G+) für die Hintergrundbeleuchtung der Raumeinheit zuständig ist. Er wird BSB-LAN nicht beschädigen, kann aber verwirrend sein, da die LED von BSB-LAN leuchtet, obwohl es nicht richtig angeschlossen ist.

Übrigens: Wenn du nur einen Anschluss hast und dieser bereits von einer Raumeinheit belegt ist, kannst du BSB-LAN ohne Probleme an den gleichen Anschluss anschließen. Sei nur vorsichtig, wenn du die Drähte für BSB-LAN hinzufügst.

| Steuergerät | Bild | Bemerkungen |
|:--------:|:---:|:------|
| [](){#LMS14}**LMS14**<br>**LMS15** | <img src="../images/LMS14.jpeg"> | BSB-Anschluss:<br>**+** = Links<br>**-** = Mitte |
| **LMS14**<br>**LMS15** | <img src="../images/LMS14-2.jpeg"> | BSB-Anschluss: CL+/CL- |
| **LMS14**<br>**LMS15**<br>Baxi Luna Platinum,<br>Chappee Klista | <img src="../images/LMS15 Baxi Platinum.jpeg"><img src="../images/LMS15 Chappee Klista.jpeg"><img src="../images/LMS15 Baxi Platinum Mainboard.jpeg"> | BSB-Anschluss:<br>Anschlussklemme M2<br>Pin 2: CL-<br>Pin 3: CL+<br>Ausführliche Anweisungen findest du hier für <a href="https://github.com/fredlcore/BSB-LAN/wiki/Special-instructions-for-special-heating-systems#js-repo-pjax-container">Baxi Luna Platinum</a>. |
| [](){#LMU64}**LMU54**<br>**LMU64** | <img src="../images/LMU64.jpeg"> | LPB-Anschluss:<br>über zusätzliches OCI420-Plugin, siehe [Details unten][OCI420]. |
| [](){#LMU74}**LMU74**<br>**LMU75** | <img src="../images/LMU74.jpeg"> | BSB-Anschluss:<br>**+** = Oben<br>**-** = Mitte<br>LPB-Anschluss:<br>über zusätzliches OCI420-Plugin |
| [](){#RVA53}**RVA53** | <img src="../images/RVA53.jpeg"> | PPS-Anschluss: A6/MD |
| [](){#RVA63}**RVA63** | <img src="../images/RVA63.jpeg"> | LPB-Anschluss: MB/DB<br>PPS-Anschluss: A6/MD |
| [](){#RVP54}**RVP54** | <img src="../images/RVP54.jpeg"> | PPS-Anschluss: A6/M |
| [](){#RVS13}**RVS13** | <img src="../images/RVS13.jpeg"> | BSB-Anschluss: CL+/CL- |
| [](){#RVS21}**RVS21** | <img src="../images/RVS21.jpeg"> | BSB-Anschluss über Stecker X86<br>**+** = rechtester Pin<br>**-** = zweiter Pin von rechts |
| [](){#RVS21-AVS55}**RVS21 mit AVS55** | <img src="../images/RVS21-AVS55.jpeg"> | AVS55-Erweiterungsmodul, auf RVS21 aufgesetzt.<br>BSB-Anschluss entweder über Stecker X86:<br>**+** = rechtester Pin<br>**-** = zweiter Pin von rechts<br>oder über Stecker X150:<br>**+** = oberster Pin<br>**-** = zweiter Pin von oben |
| [](){#RVS23}**RVS23** | <img src="../images/RVS23.jpeg"> | LPB-Anschluss: LPB/M |
| [](){#RVS41}**RVS41** | <img src="../images/RVS41.jpeg"> | BSB-Anschluss: CL+/CL-<br>LPB-Anschluss: MB/DB |
| [](){#RVS43}**RVS43<br>LOGON B** | <img src="../images/RVS43.jpeg"> | BSB-Anschluss: CL+/CL-<br>LPB-Anschluss: MB/DB |
| [](){#RVS43-ZR1}**RVS46<br>ISR-ZR1** | <img src="../images/RVS46-ISR-ZR1.jpeg"> | BSB-Anschluss: CL+/CL-<br>LPB-Anschluss: MB/DB |
| [](){#RVS46}**RVS46** | <img src="../images/RVS46.jpeg"> | BSB-Anschluss: CL+/CL-<br>LPB-Anschluss: MB/DB |
| [](){#RVS51}**RVS51** | <img src="../images/RVS51.jpeg"> | BSB-Anschluss: CL+/CL- |
| [](){#RVS53}**RVS53** | <img src="../images/RVS53.jpeg"> | BSB-Anschluss: CL+/CL- |
| [](){#RVS61}**RVS61** | <img src="../images/RVS61.jpeg"> | BSB-Anschluss: CL+/CL-<br>LPB-Anschluss: MB/DB |
| [](){#RVS63}**RVS63** | <img src="../images/RVS63.jpeg"> | BSB-Anschluss: CL+/CL-<br>LPB-Anschluss: MB/DB |
| [](){#RVS65}**RVS65** | <img src="../images/RVS65.jpeg"> | BSB-Anschluss: CL+/CL-<br>LPB-Anschluss: MB/DB |

[](){#OCI420}
## Konfigurationseinstellungen für OCI420 ##

Es kann etwas knifflig sein, das OCI420 zum Laufen zu bringen, wenn es nicht bereits Teil eines bestehenden LPB-Netzwerks ist. Wenn du das OCI420 zum ersten Mal an deine Heizung anschließt und kein anderes LPB-Heizgerät hast, wirst du wahrscheinlich "Fehler 81" erhalten, was auf einen Busfehler hinweist. Mach dir aber keine Sorgen, es ist wahrscheinlich nur eine Frage der Konfiguration einiger Parameter. Für den LMU64 ist der entsprechende Parameter 604 (_LPBKonfig0_). Er muss wie folgt eingestellt werden, um BSB-LAN als einziges an das OCI420 angeschlossenes Gerät zu verwenden:
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

Dann musst du die LPB-Adresse des OCI420 in den Parametern 605 (muss auf 1 gesetzt werden) und 606 (muss auf 0 gesetzt werden) einstellen. Danach sollte keine Fehlermeldung mehr erscheinen und die rote LED des OCI420 sollte in regelmäßigen Abständen blinken, und du bist bereit, BSB-LAN anzuschließen und zu verwenden.

**Achtung:** Wenn das OCI420 bereits mit einem anderen LPB-Gerät verbunden ist, **nimm hier keine Änderungen vor** und verbinde BSB-LAN stattdessen mit dem anderen LPB-Gerät. Es sollte ohne Anpassungen funktionieren.

## Liste der funktionierenden Steuergerätemodelle

Es gibt noch viele weitere Steuergeräte, die wahrscheinlich mit BSB-LAN funktionieren. Achte auf diese Siemens-Steuergerätemodelle in deinem Heizungssystem:

--8<-- "docs/en/list_of_controllers.md"
