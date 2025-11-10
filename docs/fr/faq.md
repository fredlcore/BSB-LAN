# Foire aux questions (FAQ)

---

## Mes paramètres seront-ils conservés lors de la mise à jour de BSB-LAN ?
- Cela dépend. Les mises à jour mineures n'affectent aucun paramètre, mais il est parfois inévitable que des modifications dans le code affectent également les paramètres. Dans ce cas, cela est mentionné dans le fichier `CHANGELOG.md` et BSB-LAN réécrit les paramètres dans l'EEPROM en fonction des paramètres dans `BSB_LAN_config.h`. C'est pourquoi il est préférable de toujours apporter des modifications importantes aux paramètres également dans ce fichier.
Les mises à jour n'affectent jamais aucun paramètre du système de chauffage.

---

## Mon chauffage a une connexion OpenTherm/eBus/BridgeNet/L-Bus/R-Bus, puis-je utiliser BSB-LAN ?
- Non, ces contrôleurs ne sont pas compatibles avec BSB-LAN. **Ne tiens pas** de connecter l'adaptateur à ton système de chauffage !  
Si tu possèdes l'un de ces systèmes de chauffage, il existe d'autres projets pour le [R-Bus](https://github.com/pepijndevos/R-Bus) de Remeha (également utilisé dans les systèmes de chauffage Brötje plus récents), le [bus BridgeNet](https://github.com/wrongisthenewright/ebusd-configuration-ariston-bridgenet) (en fait une sorte de [eBus](https://adapter.ebusd.eu/) utilisé par les systèmes de chauffage Elco/Ariston/Chaffoteaux) et [OpenTherm](https://otgw.tclcode.com/index.html).  
Ces projets **ne sont pas** liés au BSB-LAN de quelque manière que ce soit, et **aucun support** ne peut être fourni ici.

---

## Sur mon chauffage Atlantic, les changements faits via BSB-LAN n’apparaissent pas sur l’écran du chauffage !

- Certains chauffages Atlantic ont un écran qui ne synchronise pas automatiquement les paramètres avec le contrôleur Siemens. Il envoie seulement les changements quand ils sont faits directement sur l’écran du chauffage. Donc, les modifications faites via BSB-LAN ne s’affichent pas sur l’écran, même si elles sont bien prises en compte. Les paramètres lus et modifiés par BSB-LAN sont les "vrais" paramètres actifs. C’est un peu déroutant, mais on ne peut rien y faire.  
Si ton chauffage est concerné, merci de nous dire quels appareils tu utilises, pour qu’on puisse établir une liste.

---

## Il me manque le paramètre XYZ, un autre utilisateur ayant le même système de chauffage a ce paramètre !
- C'est possible, mais avoir le même système de chauffage ne signifie pas forcément que le contrôleur est identique, et même si c'est le cas, différentes versions du firmware peuvent entraîner des dizaines de paramètres différents. Avec la liste des paramètres spécifiques à l'appareil, le contrôleur nous indique quels paramètres il prend en charge. BSB-LAN ne peut offrir que cela, ni plus ni moins.  
Si tu veux quand même ajouter des paramètres toi-même, par exemple à partir de la liste de paramètres créée par les utilisateurs que nous utilisions jusqu'à la version 2.2, tu peux trouver des informations sur ce processus [ici dans le wiki](https://github.com/fredlcore/BSB-LAN/wiki/Adding-selected-parameters-from-release-version-2.2). Mais attention : nous n’offrons aucun support à ce sujet !

---

## Il me manque la fonction *XYZ*
- BSB-LAN offre la possibilité de créer ses propres fonctions à l'aide des fichiers `BSB_LAN_custom_global.h`, `BSB_LAN_custom_setup.h` et `BSB_LAN_custom.h`. Pour plus de détails et d'exemples, veuillez consulter le dossier `custom_functions` dans le repo Github. N'hésite pas à partager tes solutions avec nous !