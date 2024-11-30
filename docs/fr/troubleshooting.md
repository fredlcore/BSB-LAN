# Dépannage

BSB-LAN s'efforce de rendre l'accès à votre système de chauffage aussi simple que possible, mais il y a toujours des choses qui peuvent mal tourner. Si vous rencontrez encore des problèmes après avoir lu ce document ainsi que la [FAQ](faq.md), veuillez [ouvrir un rapport de bogue](https://github.com/fredlcore/BSB-LAN/issues/new?assignees=&labels=&projects=&template=bug_report.md&title=%5BBUG%5D) sur la page GitHub du projet et assurez-vous de nous fournir tous les fichiers journaux nécessaires et les autres détails requis, en particulier à partir du moniteur série (ou *SerMo* en abrégé).

Avant de le faire, cependant, assurez-vous d'installer la version la plus récente de BSB-LAN à partir du référentiel maître (et non la version de publication), même si la vôtre n'est vieille que de "quelques" jours. Beaucoup de choses auraient pu se passer depuis lors : !

### Utilisation du moniteur série
- Accédez au moniteur série en allant dans ***Outils/Moniteur série*** dans l'IDE Arduino.
- Définissez la vitesse de transmission sur 115200 dans le coin supérieur droit de la fenêtre du moniteur série.
- Assurez-vous de copier les messages à partir du moment où votre microcontrôleur démarre (indiqué par le message `READY`) jusqu'au moment où vous rencontrez le problème.
- Veuillez ne pas envoyer de captures d'écran, uniquement des fichiers texte brut.

Le moniteur série dans l'IDE Arduino présente actuellement un bogue qui vous permet de ne copier que les parties des messages du moniteur série qui s'affichent à l'écran. Bien que cela signifie que la copie de grandes parties des messages du journal est fastidieuse, vous devez tout de même fournir le journal complet pour obtenir de l'aide. Augmenter la taille de la fenêtre du moniteur série aide un peu.

---

## La compilation échoue : "Croquis trop grand"
- [Sélectionnez le schéma de partition *Minimal SPIFFS*][SPIFFS] dans l'IDE Arduino sous ***Outils/Schéma de partition***.
**Attention :** Ce paramètre est réinitialisé par défaut lors de la mise à jour du framework ESP32 !
Si vous utilisez des mises à jour par-dessus l'air, vous devez flasher le logiciel une fois via USB après avoir modifié le schéma de partition avant que les mises à jour OTA ne fonctionnent à nouveau.

---

## Plus d'accès à l'interface Web
Si vous avez modifié les paramètres de sorte que vous ne pouvez plus accéder à l'interface Web, il existe deux façons de restaurer le système :

- **Si vous pouvez flasher l'appareil :**
    1. Configurez `BSB_LAN_config.h` avec des paramètres corrects et fonctionnels.
    2. Définissez `UseEEPROM` sur `0`.
    3. Flasher BSB-LAN sur le microcontrôleur.
    4. Vous pouvez maintenant accéder à BSB-LAN. Accédez à "Paramètres" et enregistrez les paramètres. Cela stockera les paramètres de travail dans l'EEPROM.
    5. Maintenant, modifiez `BSB_LAN_config.h` *à nouveau* ! et définissez `UseEEPROM` sur `1` et flasher à nouveau BSB-LAN sur le microcontrôleur.
    6. Ce n'est qu'à ce moment-là que BSB-LAN lira et utilisera les paramètres de l'EEPROM, vous pourrez donc apporter d'autres modifications dans l'interface Web.
- **Si vous ne pouvez pas flasher l'appareil :**
    1. Si vous ne pouvez pas flasher l'appareil sur place, vous pouvez réinitialiser BSB-LAN sur le dernier paramètre `BSB_LAN_config.h` en connectant deux broches *avant et pendant le démarrage du microcontrôleur* :
        - ESP32-Olimex : connecter les broches 34 et 3V3.
        - ESP32-NodeMCU : connecter les broches 21 et 3V3.
        - Arduino Due : connecter les broches 31 et 33.
    2. Si les broches ont été connectées avec succès, la LED intégrée du microcontrôleur clignotera lentement pendant quatre secondes.
    3. Ensuite, ouvrez la configuration dans l'interface Web, vérifiez tous les paramètres de la configuration et enregistrez-les. Cela stockera les paramètres de travail dans l'EEPROM.
- **Point d'accès temporaire sur un microcontrôleur basé sur ESP32**
    - Sur un microcontrôleur basé sur ESP32, BSB-LAN configurera son propre point d'accès sans fil nommé `BSB-LAN` s'il ne peut pas se connecter à un réseau. Dans ce cas, vous pouvez vous connecter à ce point d'accès avec le mot de passe `BSB-LPB-PPS-LAN` et accéder à BSB-LAN via l'adresse IP `http://192.168.4.1` et voir si vous pouvez corriger la configuration de cette manière. Gardez à l'esprit que si vous avez défini une clé de passe ou un nom d'utilisateur et un mot de passe HTTP, ils sont toujours requis si ces détails sont stockés dans l'EEPROM ou `BSB_LAN_config.h`.

---

## Je ne peux accéder qu'à très peu de paramètres via BSB/LPB !
- Initialement, BSB-LAN n'est fourni qu'avec un petit ensemble de paramètres qui fonctionnent sur (presque) tous les systèmes de chauffage. Vous devez obtenir une [liste de paramètres spécifique à l'appareil](install.md#generating-the-device-specific-parameter-list).

---

## La liste des catégories est soudainement très petite
- BSB-LAN a besoin de détecter le contrôleur du système de chauffage pour déterminer les catégories à afficher. Si BSB-LAN n'est pas connecté au contrôleur ou si la détection échoue, seules quelques catégories universelles sont affichées.

---

## Impossible de lire les paramètres / la famille d'appareils est `0`
- Type de bus incorrect (BSB au lieu de LPB ou vice versa).
- Si la LED rouge de l'adaptateur n'est pas allumée (et idéalement clignote légèrement), il y a un problème de câblage entre l'adaptateur et le système de chauffage. La LED rouge s'allumera une fois l'adaptateur correctement connecté, même si l'adaptateur BSB-LAN n'est même pas connecté au microcontrôleur !

---

## Pas de données même si la LED rouge de l'adaptateur est allumée
- Assurez-vous que l'adaptateur est connecté à CL+/CL- et non à la troisième broche (G+) : G+ alimentera la LED, mais ce n'est pas une ligne de données.
- [Assurez-vous d'avoir allumé le microcontrôleur][PowerSupply]. Vous pouvez penser que le système de chauffage alimente le microcontrôleur car la LED sur l'adaptateur BSB-LAN est allumée, mais ce n'est pas le cas. Vous devez l'alimenter séparément.
- Avec l'adaptateur pour les microcontrôleurs Olimex : Assurez-vous que la carte adaptatrice BSB-LAN est **exactement** centrée sur le connecteur UEXT. Il s'insérera toujours, s'il est décalé d'une broche vers la gauche ou la droite, mais il ne fonctionnera pas.
- Assurez-vous que les broches RX/TX sont correctement définies/détectées. La séquence de démarrage dans le moniteur série vous montrera quelles broches sont utilisées ou ont été détectées automatiquement.

---

## Pas de connexion réseau ou connexion non fiable
- Essayez d'alimenter le microcontrôleur via USB à partir d'un ordinateur portable. Nous avons eu de nombreux cas où les alimentations étaient peu fiables malgré des spécifications suffisantes.
- Consultez le journal du moniteur série pour vérifier si le microcontrôleur a pu acquérir une adresse IP. Si ce n'est pas le cas, vos paramètres réseau ou votre connexion physique peuvent être défectueux.

---

## Aucune connexion au réseau Wi-Fi masqué possible
- Oui, il s'agit d'une restriction connue. La seule façon de le faire est de [définir explicitement le BSSID][BSSID] dans `BSB_LAN_config.h`.

---

## La température de la pièce (ou tout autre paramètre) ne peut pas être définie
- Vérifiez les paramètres de BSB-LAN et assurez-vous que [l'accès en écriture est activé][WriteAccess] et défini sur *standard* ou *complet*.

---

## L'interface Web se fige lors de l'établissement d'une nouvelle connexion
- BSB-LAN n'est pas un système multitâche. Cela signifie qu'il peut s'occuper d'une tâche à la fois. Donc, même si une commande URL est arrêtée (en fermant la fenêtre du navigateur), BSB-LAN risque de ne pas le détecter et de ne commencer à traiter les nouvelles demandes qu'une fois la précédente terminée.

---

## Le moniteur série n'affiche pas de données lisibles
- Assurez-vous que la vitesse est correctement définie sur 115200 bps.
- Assurez-vous que le bon port est sélectionné.