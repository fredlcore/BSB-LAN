# Der BSB/LPB/PPS-Bus

Entwickelt Ende des letzten Jahrtausends auf Basis des BatiBUS (weitere Informationen findest du [hier](https://2007.blog.dest-unreach.be/wp-content/uploads/2012/12/Interface-module-I-O-OPEN-ALBATROS-PTM59-20V1_19957_hq-en.pdf) und [hier](https://2007.blog.dest-unreach.be/wp-content/uploads/2012/12/BatiBus_v1.4.pdf)), verwenden viele Siemens-Heizungssteuerungen immer noch den gleichen physischen Bus, um mit Raumgeräten und anderen Heizgeräten zu "kommunizieren". Auch wenn eine Busgeschwindigkeit von nur 4800 Bit pro Sekunde heute anachronistisch erscheinen mag, bietet sie immer noch ein stabiles und robustes Übertragungsprotokoll, das auch heute noch völlig ausreichend ist, wenn es darum geht, kurze Nachrichten von einigen Dutzend Bytes über Leitungen zu senden, die manchmal bis zu einem Kilometer lang sind.

Die Bus-Topologie ermöglicht es dir außerdem, BSB-LAN an jedem beliebigen Punkt anzuschließen: Am Raumgerät, an der Heizungsanlage oder überall dort, wo die Busleitungen verfügbar sind. Du kannst sogar die beiden Drähte für BSB-LAN in einem bereits "besetzten" Steckplatz hinzufügen, ohne das andere Gerät zu beschädigen (vorausgesetzt, die Installation ist ordnungsgemäß).

Auf derselben physischen Ebene bieten drei Bussysteme, BSB, LPB und PPS, Lösungen für unterschiedliche Aufgaben, wobei BSB und LPB immer vorgezogen werden sollten, wenn sie verfügbar sind. PPS bietet jedoch in der Regel eine ausreichende Anzahl an Parametern für den durchschnittlichen Benutzer. BSB-LAN kann auf jedem dieser Busse ausgeführt werden und der Wechsel zwischen ihnen ist einfach durch Ändern einiger Einstellungen möglich.

---

[](){#BSB}
## Der Boiler System Bus (BSB)

BSB ist das am häufigsten verwendete Bussystem in Siemens-Steuerungen der letzten 10-15 Jahre. Es ist der Nachfolger des PPS-Systems, mit dem es die gleichen physikalischen Parameter teilt, aber viel vielseitiger ist: Anstatt nur einige Dutzend Parameter kann es auf Hunderte von Parametern zugreifen und diese in verschiedene Kategorien einteilen, um die Navigation zu erleichtern. Es handelt sich um ein transaktionsbasiertes Protokoll, bei dem die meisten Nachrichten von einem Gerät an ein anderes gesendet werden und der Empfänger eine Art Feedback gibt, z. B. ob die Aufgabe abgeschlossen werden konnte oder ob sie ungültige Daten enthielt.

Obwohl BSB in der Lage ist, mehrere Geräte auf dem Bus anzusprechen, wird es nicht in Systemen mit mehr als einem Heizgerät verwendet. Das Heizgerät hat immer die ID `0`, die Anzeigeeinheit an der Heizungsanlage hat die ID `10` (oder `0x0A` in hexadezimal) und die Standard-Raumgerät hat die ID `6`. BSB-LAN hat die ID `66` oder `0x42` in hexadezimal. Raumgeräte, die "BSB sprechen", sind zum Beispiel QAA55 und QAA75.

---

[](){#LPB}
## Der lokale Prozessbus (LPB)

LPB wurde ungefähr zur gleichen Zeit wie PPS eingeführt, das es in Bezug auf die Kommunikation mit anderen Heizgeräten ergänzte: Während PPS zur Kommunikation mit dem Raumgerät verwendet wurde, wurde LPB verwendet, um Befehle von einem Haupt-Heizgerät an ein oder mehrere Hilf-Heizgeräte zu senden, beispielsweise in einer Kaskaden-Konfiguration. Zu dieser Zeit bezogen sich die meisten über LPB übertragenen Informationen auf die internen Abläufe der Heizungsanlage (wie Sensordaten oder interne Solltemperaturen), während die für den Benutzer relevanten Parameter (wie z. B. die Komfort-Soll-Raumtemperatur) nur über PPS verfügbar waren. Heutzutage bieten Heizgeräte, die sowohl LPB als auch BSB unterstützen, die gleichen Parameter-Daten auf beiden Bussystemen an.

LPB verwendet ein spezifisches Adressierungsschema mit Segmenten und Geräten. Jedes Segment von 0 bis 15 kann bis zu 15 Geräte (von 1 bis 15) enthalten. Beim Schreiben dieser Adressen werden Segment und Gerät durch einen Doppelpunkt getrennt: `00:01` oder `04:03`.

Um die segmentbasierte Adresse in die für BSB-LAN erforderliche Ziel-ID umzuwandeln, wird folgende Formel verwendet:
`SEGMENT` mal 16 plus `GERÄT` minus eins.
Beispiel: Gerät 3 im Segment 4 entspricht `4 * 16 + 3 - 1` = 66.
Die Haupt-Heizungsanlage ist per Definition `00:01`, was einer Ziel-ID 0 entspricht.

Um mehr über das LPB-System und seine Implementierung zu erfahren, kannst du auf diese beiden Dokumente aus den späten 1990er Jahren zurückgreifen: Eines behandelt die [grundlegenden Systemdaten](https://sid.siemens.com/v/u/20138) und die Konzeptionierung eines LPB-Netzwerks, das andere befasst sich mit den [grundlegenden technischen Daten](https://sid.siemens.com/v/u/20140) und enthält Details zu Kabellängen und -durchmessern usw.

Mit Ausnahme einiger Weishaut-Heizgeräte sind Raumgeräte nicht über LPB mit der Heizungsanlage verbunden. Neuere Modelle verwenden für diese Aufgabe BSB, während ältere Modelle entweder PPS oder in einigen Fällen auch OpenTherm verwenden.

---

[](){#PPS}
## Die Punkt-zu-Punkt-Schnittstelle (PPS)

Die Punkt-zu-Punkt-Schnittstelle (PPS, abgeleitet vom deutschen Begriff "Punkt-zu-Punkt-Schnittstelle") ist auf der physischen Ebene mit den anderen Systemen kompatibel, aber nicht in der Art und Weise, wie Nachrichten-Telegramme ausgetauscht werden. Während BSB und LPB miteinander kommunizieren, indem sie Telegramme senden und deren Empfang bestätigen, wird PPS vom Heizgerät dominiert. Das Heizgerät sendet kontinuierlich seine Daten an das Raumgerät und teilt diesem mit, wann und welche Art von Informationen es senden soll. Es kann also bis zu einigen Minuten dauern, bis ein in BSB-LAN eingestellter Wert tatsächlich vom Heizsystem angefordert und dort angezeigt wird.

Es handelt sich außerdem um ein sehr zeitkritisches Protokoll, sodass andere Aufgaben, die BSB-LAN erledigen soll, zu einer vorübergehenden Unterbrechung und möglicherweise zu einer Fehlermeldung auf der Heizungsanlage führen können. Allerdings sollte sich dies nach kurzer Zeit von selbst beheben, wenn die beiden Komponenten wieder miteinander "kommunizieren".

Im Gegensatz zu BSB und LPB werden Änderungen, die in BSB-LAN vorgenommen werden, nicht sofort wirksam. Änderungen von Werten, beispielsweise der Komfort-Soll-Raumtemperatur, werden zunächst intern in BSB-LAN gespeichert und erst an die Heizungsanlage gesendet, wenn diese das Raumgerät (d. h. BSB-LAN) dazu auffordert. Dies kann bis zu einer Minute dauern, daher sollte man nicht verwirrt sein, wenn Einstellungen nicht sofort auf dem Heizgerät erscheinen, wie es bei BSB und LPB der Fall ist.

Mit PPS kann BSB-LAN in zwei Modi betrieben werden: entweder passives Abhören oder als Raumgerät. Im Passivmodus kann BSB-LAN nur den Datenaustausch zwischen dem Raumgerät und dem Heizgerät mithören. Es ist nicht möglich, eigene Daten zu senden, da diese sofort von den gleichen Daten überschrieben würden, die vom Raumgerät kommen.

Um Parameterdaten an die Heizungsanlage zu senden, muss BSB-LAN im "Raumgerät"-Modus ausgeführt werden, was bedeutet, dass alle Raumgeräte von der Heizungsanlage entfernt werden müssen. In diesem Fall ist es besonders wichtig, regelmäßig einen Raumtemperaturwert an BSB-LAN zu senden, der diesen Wert dann an das Heizgerät weiterleitet. Nur wenn der Heizkörper ausschließlich auf der Außentemperatur basiert, kann dieser Wert ignoriert werden.

BSB-LAN speichert einige Werte in seinem nicht-flüchtigen EEPROM, aber einige Werte müssen nach einem Neustart neu eingestellt werden, wie z. B. die Raumtemperatur-Soll-Einstellung. Dies verhindert, dass ein ungültig gewordener Parameterwert gespeichert und gesendet wird, nur weil er im EEPROM gespeichert ist.

Raumgeräte, die häufig mit Heizungsanlagen verwendet werden, die PPS unterstützen, sind QAA50 und QAA70.

## Welchen Bus soll ich verwenden?
**Achtung:** Triff unbedingt zuerst die Entscheidung, wo Du den BSB-LAN-Adapter anschließen möchtest, **bevor** Du die gerätespezifische Parameterliste erstellst!
### Wenn der Heizungsregler sowohl BSB als auch LPB hat
BSB und LPB bieten im Großen und Ganzen Zugriff auf die gleichen Parametersätze, sodass es keinen großen Unterschied macht, welchen Bus man verwendet.  
Bei nur **einem einzigen Heizungsregler**, der BSB und LPB zur Verfügung stellt, solltest Du BSB wählen. Der Vorteil der Verwendung von BSB besteht darin, dass einige Statustelegramme, wie z. B. Brenneraktivität, nur über BSB gepusht werden. Daher kann man beispielsweise auf die Parameter 20000 bis 20005 nur über BSB zugreifen.  
Wenn es bereits **mehrere Heizungsregler** gibt und diese über LPB in einem Verbund miteinander sind, dann sollten man BSB-LAN auch über LPB anschließen, um mit nur einem einzigen BSB-LAN-Adapter über LPB auf alle Geräte zugreifen zu können.  
Wenn Du das „Beste aus beiden Welten“ möchtest, also sowohl Zugriff auf die (wenigen zusätzlichen) Statusparameter haben möchtest, die nur über BSB verfügbar sind (wie etwa Parameter 20000 bis 20005), als auch gleichzeitig auf mehr als ein Gerät auf dem LPB-Bus zugreifen willst, benötigst Du zwei Adapter, einen für den Anschluss an BSB und einen für LPB.
### Wenn der Heizungsregler über PPS und LPB verfügt
Dies ist normalerweise nur bei älteren Heizungsreglern der Fall. In diesem Fall hat man Zugriff auf die Funktionen eines Raumgeräts, wenn man BSB-LAN per PPS anschließt, und auf die systematischeren Parameter, wenn man BSB-LAN per LPB anschließt. Je nach Heizungsregler hat man über LPB aber möglicherweise auch Zugriff auf die Funktionen, die über PPS verfügbar sind - umgekehrt jedoch nicht. Wenn es einen Unterschied in der Funktionalität gibt und Du jeden verfügbaren Parameter nutzen willst, benötigst Du zwei BSB-LAN-Adapter, einen für den Anschluss über PPS und einen für den Anschluss über LPB.
