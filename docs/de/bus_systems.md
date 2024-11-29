# Der BSB/LPB/PPS-Bus

Entwickelt am Ende des letzten Jahrtausends auf Basis des BatiBUS (weitere Informationen finden sich [hier](https://2007.blog.dest-unreach.be/wp-content/uploads/2012/12/Interface-module-I-O-OPEN-ALBATROS-PTM59-20V1_19957_hq-en.pdf) und [hier](https://2007.blog.dest-unreach.be/wp-content/uploads/2012/12/BatiBus_v1.4.pdf)), verwenden viele Siemens-Heizungssteuerungen immer noch den gleichen physischen Bus, um mit Raumgeräten und anderen Heizgeräten zu "kommunizieren". Auch wenn eine Busgeschwindigkeit von nur 4800 Bit pro Sekunde heute anachronistisch erscheinen mag, bietet sie dennoch ein stabiles und robustes Übertragungsprotokoll, das auch heute noch völlig ausreichend ist, wenn es darum geht, kurze Nachrichten von einigen Dutzend Bytes über Leitungen zu übertragen, die manchmal bis zu einem Kilometer lang sind.

Die Bus-Topologie ermöglicht es außerdem, BSB-LAN an jedem beliebigen Punkt anzuschließen: am Raumgerät, an der Heizungsanlage oder überall dort, wo die Busleitungen verfügbar sind. Sie können sogar die beiden Drähte für BSB-LAN in einem bereits "belegten" Steckplatz hinzufügen, ohne dass dies dem anderen Gerät schadet (vorausgesetzt, die Installation ist ordnungsgemäß).

Auf derselben physischen Ebene bieten drei Bussysteme, BSB, LPB und PPS, Lösungen für unterschiedliche Aufgaben, wobei BSB und LPB immer dann vorgezogen werden sollten, wenn sie verfügbar sind, während PPS dennoch eine Reihe von Parametern bietet, die für den durchschnittlichen Benutzer in der Regel völlig ausreichend sind.

BSB-LAN kann auf jedem dieser Busse betrieben werden, und der Wechsel zwischen ihnen ist nur eine Frage der Änderung weniger Einstellungen.

---

[](){#BSB}
## Der Heizungsbus (BSB)

BSB ist das am häufigsten verwendete Bussystem in Siemens-Steuerungen der letzten 10-15 Jahre. Es ist der Nachfolger des PPS-Systems, mit dem es sich die gleichen physikalischen Parameter teilt, aber es ist viel vielseitiger: Anstatt nur einige Dutzend Parameter kann es auf Hunderte von Parametern zugreifen und diese in verschiedene Kategorien einteilen, um die Navigation zu erleichtern. Es handelt sich um ein transaktionsbasiertes Protokoll, bei dem die meisten Nachrichten von einem Gerät an ein anderes gesendet werden und der Empfänger eine Art von Feedback zurücksendet, z. B. ob die Aufgabe abgeschlossen werden konnte oder ob sie ungültige Daten enthielt.

Obwohl BSB in der Lage ist, mehrere Geräte auf dem Bus anzusprechen, wird es nicht in Systemen mit mehr als einem Heizgerät verwendet. Das Heizgerät hat immer die ID `0`, die Anzeigeeinheit an der Heizungsanlage hat die ID `10` (oder `0x0A` in hexadezimal) und die Standard-Raumgerät hat die ID `6`. BSB-LAN hat die ID `66` oder `0x42` in hexadezimal. Raumgeräte, die "BSB sprechen", sind z. B. das QAA55 und das QAA75.

---

[](){#LPB}
## Der lokale Prozessbus (LPB)

LPB wurde ungefähr zur gleichen Zeit wie PPS eingeführt, das es in Bezug auf die Kommunikation mit anderen Heizgeräten ergänzte: Während PPS zur Kommunikation mit dem Raumgerät verwendet wurde, wurde LPB verwendet, um Befehle von einem Haupt-Heizgerät an ein oder mehrere Hilf-Heizgeräte zu senden, z. B. in einer Kaskaden-Konfiguration. Zu dieser Zeit bezogen sich die meisten über LPB übertragenen Informationen auf die internen Abläufe der Heizungsanlage (wie Sensordaten oder interne Solltemperaturen), während die für den Benutzer relevanten Parameter (wie z. B. die Komfort-Soll-Raumtemperatur) nur über PPS verfügbar waren. Heutzutage bieten Heizgeräte, die sowohl LPB als auch BSB unterstützen, auf beiden Bussystemen die gleichen Parameterinformationen an.

LPB verwendet ein spezifisches Adressierungsschema mit Segmenten und Geräten. Jedes Segment von 0 bis 15 kann bis zu 15 Geräte (von 1 bis 15) enthalten. Beim Schreiben dieser Adressen werden Segment und Gerät durch einen Doppelpunkt getrennt: `00:01` oder `04:03`.

Um die segmentbasierte Adresse in die für BSB-LAN erforderliche Ziel-ID umzuwandeln, lautet die Formel wie folgt:
`SEGMENT` multipliziert mit 16 plus `GERÄT` minus eins.
Beispiel: Gerät 3 im Segment 4 entspricht `4 * 16 + 3 - 1` = 66.
Die Haupt-Heizungsanlage ist per Definition `00:01`, was einer Ziel-ID 0 entspricht.
Weitere Informationen zum LPB-System und seiner Implementierung finden Sie in diesen beiden Dokumenten aus den späten 1990er Jahren, die eines die [grundlegenden Systemdaten](https://sid.siemens.com/v/u/20138) abdeckt, die die Konzeptionierung eines LPB-Netzwerks umfassen, und das andere sich mit den [grundlegenden technischen Daten](https://sid.siemens.com/v/u/20140) befasst und Details zu Kabellängen und -durchmessern usw. enthält.

Mit Ausnahme einiger Weishaut-Heizgeräte sind Raumgeräte nicht über LPB mit der Heizungsanlage verbunden. Neuere Modelle verwenden für diese Aufgabe BSB, während ältere Modelle entweder PPS oder in einigen Fällen auch OpenTherm verwenden.

---

[](){#PPS}
## Die Punkt-zu-Punkt-Schnittstelle (PPS)

Die Punkt-zu-Punkt-Schnittstelle (PPS, abgeleitet vom deutschen Begriff "Punkt-zu-Punkt-Schnittstelle") ist auf der physischen Ebene mit den anderen Systemen kompatibel, aber nicht in der Art und Weise, wie Nachrichten-Telegramme ausgetauscht werden. Während BSB und LPB miteinander kommunizieren, indem sie Telegramme senden und deren Empfang bestätigen, wird PPS vom Heizgerät dominiert. Das Heizgerät sendet ständig seine Daten an das Raumgerät und teilt diesem mit, wann und welche Art von Informationen es senden soll. Daher kann es einige Minuten dauern, bis ein in BSB-LAN eingestellter Wert tatsächlich vom Heizsystem angefordert und dort angezeigt wird.

Es handelt sich außerdem um ein sehr zeitkritisches Protokoll, sodass lange andere Aufgaben, die BSB-LAN erledigen soll, zu einer vorübergehenden Unterbrechung und möglicherweise zu einer Fehlermeldung auf der Heizungsanlage führen. Allerdings sollte sich dies nach kurzer Zeit von selbst erledigen, wenn die beiden Komponenten wieder miteinander "kommunizieren".

Im Gegensatz zu BSB und LPB werden Änderungen, die in BSB-LAN vorgenommen werden, nicht sofort wirksam. Änderungen von Werten, beispielsweise der Soll-Raumtemperatur, werden zunächst intern in BSB-LAN gespeichert und erst an das Heizsystem gesendet, wenn dieses das Raumgerät (d. h. BSB-LAN) auffordert, dies zu tun. Dies kann bis zu einer Minute oder sogar länger dauern, sodass man nicht verwirrt sein sollte, wenn Einstellungen nicht sofort auf dem Heizgerät angezeigt werden, wie es bei BSB und LPB der Fall ist.

Mit PPS kann BSB-LAN in zwei Modi betrieben werden: entweder passives Abhören oder als Raumgerät. Im Passivmodus kann BSB-LAN nur den Datenaustausch zwischen dem Raumgerät und dem Heizgerät mithören. Es ist nicht möglich, eigene Daten zu senden, da diese sofort von den gleichen Daten überschrieben würden, die vom Raumgerät kommen.

Um Parameterdaten an das Heizsystem zu senden, muss BSB-LAN im "Raumgerät"-Modus ausgeführt werden, was bedeutet, dass alle Raumgeräte vom Heizsystem entfernt werden müssen. In diesem Fall ist es besonders wichtig, regelmäßig einen Raumtemperaturwert an BSB-LAN zu senden, der diesen Wert wiederum an das Heizgerät weiterleitet. Nur wenn der Heizkörper ausschließlich auf der Grundlage der Außentemperatur arbeitet, kann dieser Wert ignoriert werden.

BSB-LAN speichert einige Werte in seinem nicht flüchtigen EEPROM, aber einige Werte müssen nach einem Neustart neu eingestellt werden, wie z. B. die Soll-Raumtemperatur. Dies soll verhindern, dass ein ungültig gewordener Parameterwert gespeichert und gesendet wird, nur weil er im EEPROM gespeichert ist.

Raumgeräte, die häufig mit Heizsystemen verwendet werden, die PPS unterstützen, sind das QAA50 und das QAA70.