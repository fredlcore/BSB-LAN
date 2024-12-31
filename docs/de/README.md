# Was ist BSB-LAN?

<div style="float:left"><svg class='logo' viewBox='0 0 400 400' xmlns='http://www.w3.org/2000/svg' height=100% width=100%><path id='b' d='m98 47-63 1c-6 0-12 4-11 11v88c1 5 3 10 10 11l79-1c25-1 24-53 4-61 11-5 18-49-19-49zM48 72h52c1 10-2 18-11 19l-38 1v22l43-1c14 0 14 11 14 20H48Z'/><use href='#b' x='246'/><path d='m268 350 1-100c2-14 14-16 29-1l56 59v-69h25l-1 99c1 12-12 17-22 7l-63-64v69Zm-65-173c-112 90-67 155-34 173-4-11-7-23-6-38h60c0 29-4 31-8 40 57-35 42-86 15-112-21-21-32-40-27-63zm-10 81c13 10 18 20 24 30h-48c5-9 8-18 24-30zM21 239h25v86h77v25l-90-1s-11 1-11-12z M246 47v25h-68c-10 1-11 18 1 18l47 1c41 3 37 63 2 66l-82 1v-25h77c11 0 12-18 0-18h-48c-42-5-37-67 0-67z'/></svg></div>
[BSB-LAN ist eine Software](https://www.bsb-lan.de) / Hardware-Lösung für den Zugriff auf den ["Boiler-System-Bus" (BSB)][BSB], den ["Local-Process-Bus (LPB)"][LPB] und die ["Punkt-zu-Punkt-Schnittstelle" (PPS)][PPS]. Die BSB-LAN-Hardware ist für verschiedene *ESP32*-basierte Mikrocontroller (ESP32 NodeMCU, Olimex EVB, Olimex POE-ISO) sowie für einen *Arduino Due* mit Ethernet-Shield erhältlich. Es ermöglicht den Zugriff auf Heizsysteme von Atlantic, Brötje, Elco und vielen anderen Herstellern über LAN/WLAN, sofern sie einen der unten aufgeführten Siemens-Controller verwenden.

BSB-LAN ermöglicht es dir, das Heizsystem zu überwachen und zu steuern und beliebige Werte zu protokollieren. Dieses Projekt unterstützt fast alle Parameter, die in Heizsystemen verfügbar sind, und kann eine umfassendere und kostengünstigere Alternative zu OZW 672, OCI 700 oder Remocon Net B sein.

Eine optionale [Integration in bestehende Smart-Home-Systeme](homeautomation.md) wie [Home Assistant][HomeAssistant], [ioBroker][ioBroker], [openHAB][openHAB], [Node-RED][NodeRED], [Homebridge][Homebridge], [Jeedom][Jeedom], [SmartHomeNG][SmartHomeNG], [Volkszähler][Volkszaehler], [FHEM][FHEM], [HomeMatic][Homematic], Loxone, IP-Symcon oder EDOMI ist über [MQTT][MQTT], [JSON][JSON] oder [HTTP-Zugriff][using] möglich.

Der Adapter kann auch als eigenständiger Logger ohne LAN- oder Internetverbindung verwendet werden, wenn du eine microSD-Karte verwendest.

Temperatur- und Feuchtigkeitssensoren können ebenfalls angeschlossen und deren Daten protokolliert und analysiert werden. Die Möglichkeit, deinen eigenen Code in die BSB-LAN-Software zu integrieren, bietet außerdem eine Vielzahl von Erweiterungsmöglichkeiten.

# Wo und wie fange ich an?

- Wenn du ein erfahrener Benutzer bist, kannst du direkt zur [Schnellstart](quickstart.md)- oder [Update](install.md#updates)-Anleitung gehen. Wenn nicht (oder wenn du auf Probleme stößt), lies bitte weiter!
- Wird mein Heizsystem von BSB-LAN unterstützt? Bitte gehe zur [Liste der unterstützten Heizsysteme](supported_heating_systems.md).
- Wenn du bereits weißt, dass dein System unterstützt wird, erfahre mehr über den [BSB-LAN-Adapter](bsb-lan_adapter.md) und wo du ihn bekommen kannst.
- Wenn du den Adapter bereits hast, möchtest du vielleicht wissen, [wie du den Adapter installierst](install.md).
- Wenn du den Adapter installiert hast, musst du [BSB-LAN konfigurieren](configure.md).
- Sobald alles eingerichtet ist, findest du heraus, [wie du BSB-LAN verwendest](using.md) oder mehr über die Möglichkeiten erfährst, BSB-LAN in [Home-Automation-Systeme zu integrieren](homeautomation.md).
- Wenn du BSB-LAN aktualisieren möchtest und wissen möchtest, was sich seit deiner letzten Installation geändert hat, solltest du das [ChangeLog](CHANGELOG.md) überprüfen.
- Unsere [Wiki-Seiten](https://github.com/fredlcore/BSB-LAN/wiki) wachsen kontinuierlich und bieten Hintergrundwissen sowie spezielle Themen zu BSB-LAN und Heizsystemen im Allgemeinen.
- Wenn du auf Probleme stößt, wirf einen Blick auf die [Seite zur Fehlerbehebung](troubleshooting.md).
- Und bevor du jemand anderem irgendwelche Fragen stellst, schau dir zuerst unsere [Häufig gestellten Fragen (FAQ)](faq.md) an!