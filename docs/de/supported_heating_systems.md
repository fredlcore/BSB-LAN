# Unterstützte Heizsysteme

BSB-LAN unterstützt Heizsysteme, die entweder über den [BSB (Boiler System Bus)](bus_systems.md#BSB), den [LPB (Local Process Bus)](bus_systems.md#LPB) oder die [PPS (Punkt-zu-Punkt-Schnittstelle)](bus_systems.md#PPS) kommunizieren. Diese Steuergeräte werden normalerweise von Siemens hergestellt, ältere Geräte können aber noch den Firmenamen "Landis & Stafea" oder "Landis & Gyr" tragen.

Wir haben eine [Liste mit funktionierenden Modellen](supported_models.md) verschiedener Heizsystemhersteller zusammengestellt, die mit BSB-LAN kompatibel sind, obwohl es keine 100%ige Garantie gibt, dass die Hersteller den Modellnamen beibehalten, aber den Controller zu einem anderen System wechseln. Stellen Sie also immer sicher, dass Sie doppelt überprüfen, ob die richtigen Anschlüsse verfügbar sind.

Hier sind einige Beispiele für Heizungssteuerungen und die Anschlüsse, die zum Verbinden mit BSB-LAN verwendet werden. Einige Anschlüsse haben drei Pole, einige haben zwei Pole. Wenn es drei Pole gibt, **stellen Sie sicher, dass Sie die richtigen zwei auswählen (CL+ und CL-)**, da der dritte Pol (G+) für die Hintergrundbeleuchtung der Raumeinheit dient. Es wird BSB-LAN nicht beschädigen, kann aber irreführend sein, da die LED von BSB-LAN leuchtet, obwohl sie nicht mit dem richtigen Pol verbunden ist.

Übrigens: Wenn Sie nur über einen Anschluss verfügen und dieser bereits mit einer Raumeinheit belegt ist, ist es kein Problem, BSB-LAN am gleichen Anschluss hinzuzufügen. Seien Sie nur vorsichtig, wenn Sie die Drähte für BSB-LAN hinzufügen.

| Controller | Bild | Bemerkungen |
|:--------:|:---:|:------|
| [](){#LMS14}**LMS14**<br>**LMS15** | <img src="../images/LMS14.jpeg"> | BSB-Verbindung:<br>**+** = Links<br>**-** = Mitte |
| **LMS14**<br>**LMS15** | <img src="../images/LMS14-2.jpeg"> | BSB-Verbindung: CL+/CL- |
| **LMS14**<br>**LMS15**<br>Baxi Luna Platinum,<br>Chappee Klista | <img src="../images/LMS15 Baxi Platinum.jpeg"><img src="../images/LMS15 Chappee Klista.jpeg"><img src="../images/LMS15 Baxi Platinum Mainboard.jpeg"> | BSB-Verbindung:<br>Anschlussklemme M2<br>Pin 2: CL-<br>Pin 3: CL+<br>Detaillierte Anweisungen finden Sie hier für <a href="https://github.com/fredlcore/BSB-LAN/wiki/Special-instructions-for-special-heating-systems#js-repo-pjax-container">Baxi Luna Platinum</a>. |
| [](){#LMU64}**LMU54**<br>**LMU64** | <img src="../images/LMU64.jpeg"> | LPB-Verbindung:<br>über zusätzliches OCI420-Plugin, siehe [Details unten][OCI420]. |
| [](){#LMU74}**LMU74**<br>**LMU75** | <img src="../images/LMU74.jpeg"> | BSB-Verbindung:<br>**+** = Oben<br>**-** = Mitte<br>LPB-Verbindung:<br>über zusätzliches OCI420-Plugin |
| [](){#RVA53}**RVA53** | <img src="../images/RVA53.jpeg"> | PPS-Verbindung: A6/MD |
| [](){#RVA63}**RVA63** | <img src="../images/RVA63.jpeg"> | LPB-Verbindung: MB/DB<br>PPS-Verbindung: A6/MD |
| [](){#RVP54}**RVP54** | <img src="../images/RVP54.jpeg"> | PPS-Verbindung: A6/M |
| [](){#RVS13}**RVS13** | <img src="../images/RVS13.jpeg"> | BSB-Verbindung: CL+/CL- |
| [](){#RVS21}**RVS21** | <img src="../images/RVS21.jpeg"> | BSB-Verbindung über Anschluss X86<br>**+** = rechtester Pin<BR>**-** = zweiter Pin von rechts |
| [](){#RVS21-AVS55}**RVS21 mit AVS55** | <img src="../images/RVS21-AVS55.jpeg"> | AVS55-Erweiterungsmodul, auf RVS21 sitzend.<br>BSB-Verbindung entweder über Anschluss X86:<br>**+** = rechtester Pin<BR>**-** = zweiter Pin von rechts<br>oder über Anschluss X150:<br>**+** = oberster Pin<BR>**-** = zweiter Pin von oben |
| [](){#RVS23}**RVS23** | <img src="../images/RVS23.jpeg"> | LPB-Verbindung: LPB/M |
| [](){#RVS41}**RVS41** | <img src="../images/RVS41.jpeg"> | BSB-Verbindung: CL+/CL-<br>LPB-Verbindung: MB/DB |
| [](){#RVS43}**RVS43<br>LOGON B** | <img src="../images/RVS43.jpeg"> | BSB-Verbindung: CL+/CL-<br>LPB-Verbindung: MB/DB |
| [](){#RVS43-ZR1}**RVS46<br>ISR-ZR1** | <img src="../images/RVS46-ISR-ZR1.jpeg"> | BSB-Verbindung: CL+/CL-<br>LPB-Verbindung: MB/DB |
| [](){#RVS46}**RVS46** | <img src="../images/RVS46.jpeg"> | BSB-Verbindung: CL+/CL-<br>LPB-Verbindung: MB/DB |
| [](){#RVS51}**RVS51** | <img src="../images/RVS51.jpeg"> | BSB-Verbindung: CL+/CL- |
| [](){#RVS53}**RVS53** | <img src="../images/RVS53.jpeg"> | BSB-Verbindung: CL+/CL- |
| [](){#RVS61}**RVS61** | <img src="../images/RVS61.jpeg"> | BSB-Verbindung: CL+/CL-<br>LPB-Verbindung: MB/DB |
| [](){#RVS63}**RVS63** | <img src="../images/RVS63.jpeg"> | BSB-Verbindung: CL+/CL-<br>LPB-Verbindung: MB/DB |
| [](){#RVS65}**RVS65** | <img src="../images/RVS65.jpeg"> | BSB-Verbindung: CL+/CL-<br>LPB-Verbindung: MB/DB |

[](){#OCI420}
## Konfigurationseinstellungen für OCI420 ##

Es kann etwas schwierig sein, das OCI420 ordnungsgemäß zum Laufen zu bringen, wenn es nicht bereits Teil eines bestehenden LPB-Netzwerks ist. Wenn Sie das OCI420 zum ersten Mal an Ihre Heizung anschließen und über kein anderes LPB-Heizgerät verfügen, erhalten Sie wahrscheinlich "Fehler 81", was darauf hinweist, dass ein Busfehler vorliegt. Aber machen Sie sich keine Sorgen, es ist wahrscheinlich nur eine Frage der Konfiguration einiger Parameter, um es zum Laufen zu bringen. Für den LMU64 ist der entsprechende Parameter 604 (_LPBKonfig0_). Er muss wie folgt für die Verwendung von BSB-LAN als einziges an das OCI420 angeschlossenes Gerät eingestellt werden:
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

Dann müssen Sie die LPB-Adresse des OCI420 in den Parametern 605 (muss auf 1 gesetzt werden) und 606 (muss auf 0 gesetzt werden) einstellen. Anschließend sollte keine Fehlermeldung mehr angezeigt werden und die rote LED des OCI420 sollte in regelmäßigen Abständen blinken, und Sie können BSB-LAN anschließen und verwenden.

**Achtung:** Wenn das OCI420 bereits mit einem anderen LPB-Gerät verbunden ist, **nehmen Sie hier keine Änderungen vor**, sondern verbinden Sie BSB-LAN mit dem anderen LPB-Gerät. Es sollte ohne Einstellungen funktionieren.

## Liste der funktionierenden Controllermodelle

Es gibt noch viele weitere Controller, die wahrscheinlich mit BSB-LAN funktionieren. Achten Sie auf diese Siemens-Controllermodelle in Ihrem Heizsystem:

--8<-- "docs/de/list_of_controllers.md"