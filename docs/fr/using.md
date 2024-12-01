# Utilisation de BSB-LAN

## Contrôle du système de chauffage via l'interface web

Dans un premier temps, ou si vous souhaitez simplement allumer ou éteindre votre système de chauffage, vous pouvez ouvrir l'interface web de BSB-LAN et accéder au menu *Paramètres*. Cela affichera une liste de catégories de votre contrôleur de chauffage.

Vous pouvez cliquer sur chaque catégorie pour obtenir une liste des paramètres correspondants. Si vous voyez un bouton `Set`, cela signifie que le paramètre peut être modifié, et en cliquant sur le bouton, la nouvelle valeur sera envoyée au chauffage. Si le bouton `Set` n'est pas présent, le paramètre est en lecture seule et ne peut pas être modifié.

<img src="../images/Web-Interface.png">

---

## Utilisation des commandes URL de BSB-LAN

La plupart des fonctionnalités de BSB-LAN peuvent être contrôlées à l'aide de commandes URL. Ces commandes sont utiles, voire nécessaires, lorsque vous connectez BSB-LAN à un [système de domotique](homeautomation.md). Elles permettent également d'accéder à des fonctions qui ne sont pas directement accessibles via l'interface web.

Les commandes URL sont appelées juste après le nom d'hôte de BSB-LAN et une clé de passe (facultative). Par exemple, pour obtenir une liste de catégories, vous devez ouvrir l'URL `http://bsb-lan.local/K` (ou `http://bsb-lan.local/1234/K` si la clé de passe `1234` est utilisée).

### Interrogation et définition de paramètres

<style>
table th:first-of-type {
    width: 20%;
}
table th:nth-of-type(2) {
    width: 80%;
}
</style>

| Commande URL | Fonctionnalité |
|:----------|:------------|
| `/<x>` | Interroger le paramètre `<x>` |
| `/<x>!<addr>` | Interroger le paramètre `<x>` du contrôleur à l'adresse de destination `<addr>` |
| `/<x>/<y>/<z>` | Interroger les paramètres `<x>`, `<y>` et `<z>`. Les paramètres peuvent inclure `!` pour adresser différents contrôleurs. |
| `/<x>-<y>` | Interroger les paramètres de `<x>` à `<y>` |
| `/<x>!<addr>-<y>` | Interroger les paramètres de `<x>` à `<y>` du contrôleur à l'adresse de destination `<addr>` |
| `/K` | Lister toutes les catégories de paramètres du contrôleur à l'adresse de destination par défaut |
| `/K!<addr>` | Lister toutes les catégories de paramètres du contrôleur à l'adresse de destination `<addr>` |
| `/K<x>` | Interroger tous les paramètres de la catégorie `<x>` du contrôleur à l'adresse de destination par défaut |
| `/K<x>!<addr>` | Interroger tous les paramètres de la catégorie `<x>` du contrôleur à l'adresse de destination `<addr>` |
| `/S<x>=<y>` | Définir le paramètre `<x>` du contrôleur à l'adresse de destination par défaut sur la valeur `<y>`. Pour définir un paramètre sur `---` (off/désactivé), envoyez simplement une valeur vide : `S<x>=` |
| `/S<x>!<addy>=<y>` | Définir le paramètre `<x>` du contrôleur à l'adresse de destination `<addr>` sur la valeur `<y>` |
| `/I<x>=<y>` | Envoyer la valeur `y` en tant que télégramme INF au paramètre `<x>`. Cela n'est nécessaire que pour la définition de la température de la pièce (paramètres 10000 ff.). |

### Configuration

| Commande URL | Fonctionnalité |
|:----------|:------------|
| `/C` | Configuration |
| `/CO` | Afficher la configuration de BSB-LAN |
| `/P<x>,<y>,<z>` | Définir temporairement le type de bus sur `<x>`, l'adresse propre sur `<y>` et l'adresse cible sur `<z>` |
| `/V<x>` | Activer (`1`) ou désactiver (`0`) le mode de sortie détaillé. Il doit rester activé sauf instruction contraire. |

### Journalisation

| Commande URL | Fonctionnalité |
|:----------|:------------|
| `/DG` | Affichage graphique (tracé) d'un fichier journal actif |
| `/D` ou `/DD` | Afficher le fichier journal `datalog.txt` du stockage. Contient les paramètres enregistrés et leurs valeurs lorsque la journalisation sur carte SD est active. |
| `/D<n>` | Afficher les `<n>` derniers jours du calendrier du fichier journal |
| `/D<a>,<b>` | Afficher les données du fichier journal entre `<a>` et `<b>`. `<a>` et `<b>` doivent être au format aaaa-mm-jj (par exemple `/D2024-04-01,2024-04-30`) |
| `/D0` | Réinitialiser les fichiers journaux `datalog.txt` et `journal.txt` et créer de nouveaux en-têtes. Doit être exécuté avant la première journalisation. |
| `/DK<n>` | Supprimer les données plus anciennes que `<n>` jours du fichier journal |
| `/LN` | Forcer la journalisation indépendamment de l'intervalle actuelle et redémarrer l'intervalle configuré à ce moment-là |
| `/L=<x>,<y>,<z>` | Définir l'intervalle de journalisation sur `<x>` secondes et (facultativement) réinitialiser les paramètres de journalisation sur `<y>`, `<z>`, etc. jusqu'au redémarrage |
| `/L=0,0` | Désactiver la journalisation sur le stockage jusqu'au redémarrage |
| `/LB=<x>` | Journaliser uniquement les télégrammes de diffusion (`1`) ou tous les télégrammes (`0`). Le paramètre est actif jusqu'au redémarrage. |
| `/LU=<x>` | Journaliser uniquement les télégrammes de bus inconnus (`1`) ou tous les télégrammes (`0`). Le paramètre est actif jusqu'au redémarrage. |
| `/A=0` | Désactiver le calcul de la moyenne sur 24 heures jusqu'au redémarrage |
| `/A=<x>,<y>,<z>` | Changer le calcul de la moyenne sur 24 heures pour les paramètres `<x>`, `<y>` et `<z>` jusqu'au redémarrage |
| `/B0` | Réinitialiser les statistiques de temps de fonctionnement et de cycles du brûleur |
| `/DD0` | Supprimer uniquement le fichier journal `datalog.txt` |
| `/DJ` | Afficher le fichier journal `journal.txt` du stockage |
| `/DJ0` | Supprimer uniquement le fichier journal `journal.txt` |
| `/LD` | Désactiver la journalisation des télégrammes dans `journal.txt` jusqu'au redémarrage |
| `/LE` | Activer la journalisation des télégrammes dans `journal.txt` |

### Informations sur les paramètres

| Commande URL | Fonctionnalité |
|:----------|:------------|
| `/E<x>` | Afficher les options du paramètre `<x>`. Disponible uniquement pour les paramètres de type option, tels que les types de données `VT_ENUM`, `VT_CUSTOM_ENUM`, `VT_BITS` et `VT_CUSTOM_BITS`. |
| `/R<x>` | Interroger la valeur par défaut du paramètre `<x>` |

### Contrôle GPIO

| Commande URL | Fonctionnalité |
|:----------|:------------|
| `/G<x>` | Afficher l'état actuel de la broche GPIO `<x>` |
| `/G<x>=<y>` | Définir la broche GPIO `<x>` sur HIGH (`<y>` = `1`) ou LOW (`<y>` = `0`) |

### Interface JSON

**Pour une structure complète de l'API JSON, voir [ici dans la documentation OpenAPI](https://editor.swagger.io/?url=https://raw.githubusercontent.com/fredlcore/bsb_lan/master/openapi.yaml).**

| Commande URL | Fonctionnalité |
|:----------|:------------|
|`/JQ=<x>,<y>,<z>`|Interroger les paramètres `<x>`, `<y>` et `<z>` et renvoyer une structure JSON.|
|`/JQ`      |Interroger les paramètres en fonction d'une structure JSON reçue via HTTP POST.|
|`/JS`      |Définir les paramètres en fonction d'une structure JSON reçue via HTTP POST.|
|`/JR<x>`   |Interroger la valeur par défaut du paramètre `<x>` et renvoyer une structure JSON.|
|`/JK=ALL`  |Afficher les plages de toutes les catégories disponibles en tant que structure JSON.|
|`/JK=<x>`  |Afficher la structure des paramètres pour tous les paramètres de la catégorie `<x>`.|
|`/JC=<x>,<y>,<z>`|Afficher les valeurs possibles pour les paramètres `<x>`, `<y>` et `<z>` pour les paramètres de type option. Même structure JSON que `/JK=<x>`.|
|`/JC      `|Afficher les valeurs possibles pour les paramètres en fonction d'une structure JSON reçue via HTTP POST. Même structure JSON que `/JK=<x>`.|
|`/JB`      |Sauvegarder tous les paramètres modifiables dans une structure JSON qui peut être utilisée pour les réécrire avec `/JS` |
|`/JB!<addr>`|Sauvegarder tous les paramètres modifiables du contrôleur à l'adresse de destination `<addr>` dans une structure JSON qui peut être utilisée pour les réécrire avec `/JS` |
|`/JL`      |Créer une structure JSON des paramètres de configuration de BSB-LAN |
|`/JW`      |Écrire les paramètres de configuration en fonction d'une structure JSON créée par `/JL` |
|`/JI`      |Afficher les informations d'exécution de BSB-LAN en tant que structure JSON |
|`/JV`      |Renvoyer la version de l'API JSON de BSB-LAN en tant que structure JSON |

### Divers

| Commande URL | Fonctionnalité |
|:----------|:------------|
| `/M<x>!<y>` | Envoyer (`<x>=1`) ou révoquer (`<x>=0`) les messages de découverte automatique MQTT pour tous les paramètres du contrôleur à l'adresse de destination `<y>`. |
| `/N` | Réinitialiser et redémarrer le microcontrôleur (environ 15 secondes) |
| `/NE` | Effacer l'EEPROM et redémarrer le microcontrôleur. Tous les paramètres de configuration seront ensuite lus à partir du fichier de configuration jusqu'à ce qu'ils soient définis et enregistrés à nouveau dans l'interface web pour être écrits dans l'EEPROM. |
| `/QD` | Afficher la structure des paramètres du système de chauffage |
| `/W` | Avec `/W` précédant les commandes URL `C`, `S` et `Q`, les données sont renvoyées sans en-tête et pied de page HTML (par exemple : `/WC` ou `/WS<x>=<y!z>`). |

---

## Utilisation de la fonctionnalité de tracé graphique

<img src="../images/Web-Interface2.png">

Si des données journalisées sont disponibles sur le stockage (carte SD ou mémoire flash interne), l'option **Afficher le fichier journal** devient cliquable. Par défaut, elle affichera les données journalisées dans le navigateur.

Pour accéder aux données journalisées elles-mêmes (dans le fichier `datalog.txt`), utilisez la commande URL `/D` mentionnée ci-dessus.

Par défaut, "Afficher le fichier journal" affiche les données de journalisation des `n` derniers jours (`n=DEFAULT_DAYS_TO_PLOT`, configurable dans `BSB_LAN_config.h`). Ensuite, vous pouvez utiliser les contrôles de la page web pour sélectionner une autre plage, en fonction des données contenues dans le fichier journal.

Les actions de survol, de clic et de roulette de la souris dans l'affichage graphique offrent diverses options de contrôle :

- Meilleure lisibilité des numéros de valeur lorsque les tracés sont proches les uns des autres (survol du tracé)
- Les utilisateurs peuvent mettre en surbrillance les tracés de manière interactive pour une meilleure vue d'ensemble (survol des entrées de légende)
- Les utilisateurs peuvent désactiver les tracés de manière interactive pour une meilleure vue d'ensemble et un meilleur ajustement vertical (clic sur les entrées de légende)
- Zoom (roulette de la souris/pinch sur le tracé) et capacité de panoramique (déplacement du tracé zoomé)

Pour une analyse plus approfondie, vous pouvez utiliser ce [script Python](https://github.com/DE-cr/BSB-LAN/tree/BSB-LAN_evaluate_datalogs/BSB_LAN/scripts/BSB-LAN_evaluate_datalogs) qui prend la sortie du journal de BSB-LAN pour créer des fichiers CSV pivotés qui peuvent être utilisés pour des diagrammes plus informatifs.
