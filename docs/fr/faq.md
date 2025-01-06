# Foire aux questions (FAQ)

---

## Mes paramètres seront-ils conservés lors de la mise à jour de BSB-LAN ?
- Cela dépend. Les mises à jour mineures n'affectent aucun paramètre, mais il est parfois inévitable que des modifications dans le code affectent également les paramètres. Dans ce cas, cela est mentionné dans le fichier `CHANGELOG.md` et BSB-LAN réécrit les paramètres dans l'EEPROM en fonction des paramètres dans `BSB_LAN_config.h`. C'est pourquoi il est préférable de toujours apporter des modifications importantes aux paramètres également dans ce fichier.
Les mises à jour n'affectent jamais aucun paramètre du système de chauffage.

---

## Mon chauffage a une connexion OpenTherm/eBus/BridgeNet/L-Bus/R-Bus, puis-je utiliser BSB-LAN ?
- Non, ces contrôleurs ne sont pas compatibles avec BSB-LAN. **Ne tiens pas** de connecter l'adaptateur à ton système de chauffage !  
Si tu possedes l'un de ces systèmes de chauffage, il existe d'autres projets pour le [R-Bus](https://github.com/pepijndevos/R-Bus) de Remeha (également utilisé dans les systèmes de chauffage Brötje plus récents), le [bus BridgeNet](https://github.com/wrongisthenewright/ebusd-configuration-ariston-bridgenet) (en fait une sorte de [eBus](https://adapter.ebusd.eu/) utilisé par les systèmes de chauffage Elco/Ariston/Chaffoteaux) et [OpenTherm](https://otgw.tclcode.com/index.html).  
Ces projets **ne sont pas** liés au BSB-LAN de quelque manière que ce soit, et **aucun support** ne peut être fourni ici.

---

## Il me manque la fonction *XYZ*
- BSB-LAN offre la possibilité de créer ses propres fonctions à l'aide des fichiers `BSB_LAN_custom_global.h`, `BSB_LAN_custom_setup.h` et `BSB_LAN_custom.h`. Pour plus de détails et d'exemples, veuillez consulter le dossier `custom_functions` dans le repo Github. N'hésitez pas à partager vos solutions avec nous !
