# Foire aux questions (FAQ)

---

## Mes paramètres seront-ils conservés lors de la mise à jour de BSB-LAN ?
- Cela dépend. Les mises à jour mineures n'affectent aucun paramètre, mais il est parfois inévitable que des modifications dans le code affectent également les paramètres. Dans ce cas, cela est mentionné dans le fichier `CHANGELOG.md` et BSB-LAN réécrit les paramètres dans l'EEPROM en fonction des paramètres dans `BSB_LAN_config.h`. C'est pourquoi il est préférable de toujours apporter des modifications importantes aux paramètres également dans ce fichier.
Les mises à jour n'affectent jamais aucun paramètre du système de chauffage.

---

## Mon chauffage a une connexion OpenTherm/eBus/L-Bus/R-Bus, puis-je utiliser BSB-LAN ?
- Non, ces contrôleurs ne sont pas compatibles avec BSB-LAN. Ne tentez **pas** de connecter l'adaptateur à votre système de chauffage !

---

## Il me manque la fonction *XYZ*
- BSB-LAN offre la possibilité de créer ses propres fonctions à l'aide des fichiers `BSB_LAN_custom_global.h`, `BSB_LAN_custom_setup.h` et `BSB_LAN_custom.h`. Pour plus de détails et d'exemples, veuillez consulter le dossier `custom_functions` dans le repo Github. N'hésitez pas à partager vos solutions avec nous !
