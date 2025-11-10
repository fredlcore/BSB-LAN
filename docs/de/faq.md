# Häufig gestellte Fragen (FAQ)

---

## Hat ein Update Auswirkungen auf die Einstellungen von BSB-LAN?
- Das kommt darauf an. Kleinere Updates haben keine Auswirkungen auf die Einstellungen, aber manchmal lässt es sich nicht verhindern, dass Änderungen im Code Auswirkungen auf die Einstellungen haben. Dies ist dann in der Datei `CHANGELOG.md` erwähnt. In diesem Fall schreibt BSB-LAN die Einstellungen neu ins EEPROM, basierend auf den Einstellungen in `BSB_LAN_config.h`. Deshalb ist es am besten, größere Änderungen an den Einstellungen immer auch in dieser Datei vorzunehmen.
Updates haben niemals Auswirkungen auf Parameter im Heizsystem.

---

## Meine Heizung hat einen OpenTherm/eBus/BridgeNet/L-Bus/R-Bus Anschluss, kann ich damit BSB-LAN benutzen?
- Nein, diese Regler sind nicht mit BSB-LAN kompatibel. Bitte **auf keinen Fall** versuchen, den Adapter mit diesen Systemen zu verbinden!  
Wenn Du eines dieser Heizungssysteme besitzt, gibt es hierfür einige andere Projekte, z.B. für Remehas [R-Bus](https://github.com/pepijndevos/R-Bus) (kommt in neueren Brötje Heizungen zum Einsatz), den [BridgeNet Bus](https://github.com/wrongisthenewright/ebusd-configuration-ariston-bridgenet) (eine Art [eBus](https://adapter.ebusd.eu/), der bei manchen Elco/Ariston/Chaffoteaux Heizungen zum Einsatz kommt) und [OpenTherm](https://otgw.tclcode.com/index.html).  
Diese Projekte stehen **nicht** in Verbindung mit BSB-LAN und **kein Support** kann hier dafür geleistet werden.

---

## Bei meiner Atlantic-Heizung werden die in BSB-LAN vorgenommenen Änderungen nicht auf dem Display angezeigt!

– Einige Atlantic-Heizungen verfügen über ein Display, das die Parameter nicht automatisch mit der Siemens-Steuerung synchronisiert und Änderungen nur dann sendet, wenn diese direkt auf dem Display der Heizung vorgenommen werden. Daher werden Änderungen, die über BSB-LAN vorgenommen wurden, nicht auf dem Display der Heizung angezeigt. Sie sind jedoch aktiv, und die von BSB-LAN eingestellten und abgefragten Parameter sind die „echten“. Das ist verwirrend, lässt sich aber leider nicht beheben.
Falls deine Heizung betroffen ist, teile uns bitte die verwendeten Geräte mit, damit wir eine entsprechende Liste erstellen können.

---

## Ich vermisse Parameter XYZ, ein Bekannter mit der gleichen Heizung hat diesen Parameter!
- Das mag sein, aber das gleiche Modell einer Heizung bedeutet nicht den gleichen Regler zu haben, und selbst wenn der Regler das gleiche Modell ist, kann es je nach Firmware-Stand des Reglers Dutzende unterschiedliche Parameter geben. Über die gerätespezifische Parameterliste gibt der Regler bekannt, welche Parameter er unterstützt. Das ist das, was BSB-LAN anbieten kann, nicht mehr und nicht weniger.  
Wer dennoch selbst Parameter hinzufügen möchte, z.B. aus der user-erstellten Version 2.2, der findet [hier im Wiki](https://github.com/fredlcore/BSB-LAN/wiki/Adding-selected-parameters-from-release-version-2.2) die nötigen Hintergrundinformationen. Von unserer Seite gibt es hierfür jedoch keinen weiteren Support!

---

## Ich vermisse die Funktion *XYZ*
- BSB-LAN ermöglicht es, eigene Funktionen hinzuzufügen, dafür gibt es die Dateien `BSB_LAN_custom_global.h`, `BSB_LAN_custom_setup.h` und `BSB_LAN_custom.h`. Bitte schau' Dir das Verzeichnis `custom_functions` im Repository an, um weitere Details und Beispiele zu bekommen. Wir freuen uns über weitere Beiträge!
