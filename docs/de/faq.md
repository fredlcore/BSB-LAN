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

## Ich vermisse die Funktion *XYZ*
- BSB-LAN ermöglicht es, eigene Funktionen hinzuzufügen, dafür gibt es die Dateien `BSB_LAN_custom_global.h`, `BSB_LAN_custom_setup.h` und `BSB_LAN_custom.h`. Bitte schau' Dir das Verzeichnis `custom_functions` im Repository an, um weitere Details und Beispiele zu bekommen. Wir freuen uns über weitere Beiträge!
