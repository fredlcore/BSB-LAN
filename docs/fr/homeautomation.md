# Connexion de BSB-LAN aux systèmes de domotique

BSB-LAN fournit quatre façons de se connecter aux systèmes de domotique :

1. Utilisation de modules pris en charge pour des systèmes de domotique spécifiques
1. Échange de données via MQTT
1. Échange de données via JSON
1. Échange de données via des commandes URL et la récupération de données à l'écran

---

## Utilisation de modules pris en charge pour des systèmes de domotique spécifiques

Pour certains systèmes, des modules spécifiques existent et peuvent être utilisés pour accéder à BSB-LAN de manière transparente :

### Home Assistant

Même si le plugin officiel ne fonctionne plus, l'approche MQTT (voir ci-dessous) marche bien avec Home Assistant, y compris la fonctionnalité de découverte automatique.  
Voici un lien vers une [vidéo sur la chaîne YouTube de BSB-LAN](https://youtu.be/DbHEiWm5nBs) qui montre comment configurer BSB-LAN dans Home Assistant en utilisant cette fonctionnalité.

Pour plus de détails sur la mise en œuvre, tu peux aussi consulter ces tutoriels :

- L'utilisateur GitHub @ryann72 a écrit des instructions détaillées pour [BSB-LAN et HomeAssistant/Mosquitto](https://github.com/ryann72/Home-assistant-tutoriel/blob/main/BSB-LAN/tutoriel%20BSB-LAN%20English.md). Il est aussi disponible en [français](https://github.com/ryann72/Home-assistant-tutoriel/blob/main/BSB-LAN/tutoriel%20BSB-LAN.md).
- L'utilisateur YouTube @StoneTime a créé deux vidéos (en allemand) dans lesquelles il montre l'[installation de BSB-LAN](https://www.youtube.com/watch?v=n-5I-TUzXuk) ainsi que sa [configuration dans Home Assistant](https://www.youtube.com/watch?v=R2Q-_flTPvk). Merci !
- L'utilisateur YouTube @ArminasTV a créé deux vidéos (en français) dans lesquelles il montre l'[installation de BSB-LAN](https://www.youtube.com/watch?v=5lNgNYlZ7M0&t=0s) ainsi que sa configuration avec [Home Assistant et MQTT](https://www.youtube.com/watch?v=WtmKPo1xMio&t=411s). Merci !

### Homebridge

L'utilisateur de BSB-LAN, Michael, a écrit un [plugin pour Homebridge](https://www.npmjs.com/package/@bsblan/homebridge-bsblan-thermostat). Merci !

### ioBroker

L'utilisateur GitHub @hacki11 a développé [un adaptateur pour ioBroker](https://github.com/hacki11/ioBroker.bsblan). Merci !

### Jeedom

L'utilisateur GitHub @bernard-dandrea a écrit un [plugin pour Jeedom](https://bernard-dandrea.github.io/jeedom-BSBLAN/fr_FR/) (avec une description en français). Merci !

### Node-RED

L'utilisateur GitHub @konne a écrit un [module pour Node-RED](https://github.com/node-red-contrib/node-red-contrib-bsb-lan). Merci !

### FHEM

L'utilisateur du forum FHEM, Luposoft, a écrit une explication concise de la [configuration pour utiliser FHEM via MQTT](https://forum.fhem.de/index.php/topic,29762.msg1129702.html#msg1129702). Merci !

### openHAB

Depuis la version 2.5.4, il existe une [liaison](https://www.openhab.org/addons/bindings/bsblan/) qui fait officiellement partie d'OpenHAB.

### Homematic

L'utilisateur du forum FHEM, PaulM, a [écrit quelques scripts](https://forum.fhem.de/index.php?topic=29762.1830) pour illustrer l'intégration de BSB-LAN dans Homematic. Merci !

### SmartHomeNG

L'utilisateur GitHub @thensty a écrit un [plugin pour SmartHomeNG](https://github.com/smarthomeNG/plugins/tree/develop/bsblan). Merci !

### Volkszaehler

L'utilisateur GitHub @lapixo a contribué à un [script pour le projet Volkszaehler](https://github.com/lapixo/volkszaehler_bsb-lan/tree/main). Merci !

### Script Bash

L'utilisateur GitHub @khfm a écrit des [scripts Bash](https://github.com/khfm/bsb-lan-readout) pour interroger les données et les afficher à l'aide de gnuplot. Merci !

---

## Échange de données via MQTT

C'est la méthode recommandée pour connecter BSB-LAN aux systèmes de domotique car elle permet un échange de données fluide.  
Tu auras besoin d'un courtier MQTT ([mosquitto](https://mosquitto.org)), soit local, soit via un service public. Certains systèmes comme Home Assistant intègrent mosquitto.

**Attention** : Actuellement, le courtier mosquitto semble avoir un problème avec la gestion d'un grand nombre de messages à partir des versions 2.0.16 et ultérieures ([voir ce rapport de bogue](https://github.com/eclipse-mosquitto/mosquitto/issues/2887)). Si tu rencontres le problème que tes entités BSB-LAN deviennent « indisponibles », en particulier après avoir utilisé la fonctionnalité de découverte automatique ci-dessous, rétrograde vers la version 2.0.15 de mosquitto. Cependant, sois conscient que cette version a des problèmes de sécurité, donc assure-toi que ton courtier s'exécute dans un environnement protégé par un pare-feu.

Dans BSB-LAN, tu dois effectuer ou activer au moins les configurations suivantes :

- Définis le **mode de journalisation** (en plus) sur **Envoyer au courtier MQTT**.
- Définis l'**intervalle de journalisation** sur le temps (en secondes) pendant lequel tu veux que les paramètres de journalisation soient publiés.
- Sélectionne jusqu'à 20 **paramètres de journalisation** que tu souhaites envoyer à ton système de domotique.
- Définis l'**utilisation de MQTT** sur **texte brut**.
- Définis le **serveur du courtier MQTT** sur le nom d'hôte de ton courtier MQTT (tel que le serveur mosquitto).

Si ton système de domotique prend en charge la découverte automatique MQTT (comme c'est le cas avec Home Assistant), tu peux appeler la commande URL `/M1!<x>` et BSB-LAN enverra des messages de découverte automatique pour **tous les paramètres disponibles** à partir de l'ID d'appareil `<x>` au courtier MQTT et donc au système de domotique. Note que si tu n’actives pas les paramètres en écriture dans BSB-LAN, tous les paramètres seront considérés comme en lecture seule dans Home Assistant. Si tu changes ce réglage plus tard dans BSB-LAN, tu devras relancer le processus de découverte automatique.  
Tu devras peut-être effectuer un nettoyage par la suite ou envoyer un message de suppression pour tous ces paramètres à l'aide de la commande URL `/M0!<x>` si tu ne veux plus utiliser cette fonctionnalité.

Sinon, si tu veux configurer tes propres détails de connexion, la structure de sujet de BSB-LAN est la suivante :  
`<BSB-LAN MQTT Topic>/<device ID>/<category no.>/<parameter no.>`  

où :

- `<BSB-LAN MQTT Topic>` est défini dans les paramètres de BSB-LAN (par défaut `BSB-LAN`),
- `<device ID>` est l'ID du régulateur de chauffage (généralement `0` pour le contrôleur principal),
- `<category no.>` est le numéro de catégorie tel qu'il est utilisé avec la commande URL `/K`,
- `<parameter no.>` est le numéro de paramètre, tel que `501.1`.

Cette structure est suivie de l'un de ces sujets qui déterminent l'action à effectuer :

- `/status` - contient la valeur du paramètre dans la charge utile MQTT.
- `/set` - utilisé pour définir un paramètre avec la valeur contenue dans la charge utile MQTT publiée à l'aide du télégramme SET (méthode par défaut de définition des paramètres).
- `/inf` - identique à `/set`, mais utilise le télégramme INF (utilisé pour envoyer le paramètre de température ambiante 10000, par exemple).
- `/poll` - ignore la valeur publiée et force BSB-LAN à mettre à jour immédiatement `/status` du même paramètre avec une valeur de paramètre nouvellement récupérée. `/poll` peut également être accessible directement sous le sujet principal (par exemple `BSB-LAN/poll`) où il accepte une liste de paramètres séparés par des virgules. Ces paramètres auront ensuite leurs sujets `/status` respectifs mis à jour en une seule fois. L'adressage des paramètres peut être effectué soit dans le style de sujet (avec une barre oblique de début), soit de manière similaire à la liste des paramètres de journalisation dans les paramètres de BSB-LAN (voir les exemples ci-dessous).

Dans le même temps, la méthode héritée d'envoi de commandes URL via MQTT directement au sujet principal (tel que défini dans les paramètres, par défaut `BSB-LAN`), est toujours prise en charge pour des raisons de compatibilité, mais est déconseillée. Les réponses seront toujours écrites dans `/status` de la structure de sujet ci-dessus.

Le sujet `/status` est mis à jour de quatre manières :

- via les paramètres de journalisation vers MQTT comme expliqué ci-dessus,
- chaque fois qu'une requête URL est effectuée sur BSB-LAN (peut être désactivé en **activant** `Only send log parameters to MQTT` dans la configuration),
- chaque fois qu'un paramètre est modifié via le module de commande (peut être désactivé en **activant** `Only send log parameters to MQTT` dans la configuration),
- chaque fois que le paramètre est mis à jour via le sujet `/poll` comme expliqué ci-dessus.

Dans ces cas, les valeurs respectives des paramètres concernés seront envoyées au courtier MQTT, de sorte que même les modifications apportées en dehors de BSB-LAN sont envoyées au système de domotique, c'est pourquoi l'approche MQTT est la méthode recommandée pour se connecter à un système de domotique. Cela signifie également que, comme alternative à la fonctionnalité de journalisation intégrée de BSB-LAN, tu peux aussi appeler périodiquement une URL avec les paramètres que tu veux voir mis à jour. Étant donné que ces paramètres seront également envoyés au courtier MQTT, ton système de domotique les recevra aussi.  
Par exemple, si tu appelles périodiquement l'URL `http://bsb-lan.local/700/8700`, le mode de fonctionnement du circuit de chauffage 1 (paramètre 700) ainsi que la température extérieure actuelle (paramètre 8700) seront envoyés au courtier MQTT.

### Exemples d'interrogation ou de définition de paramètres via MQTT à l'aide de mosquitto ###
Interroger la température extérieure (ID d'appareil 0, numéro de catégorie 51, paramètre 8700) :  
`mosquitto_sub -h my.mosquitto-broker.local -u USER -P PASSWORD -t BSB-LAN/0/51/8700/status`

Définir le point de consigne de température de confort (ID d'appareil 0, numéro de catégorie 16, paramètre 710) à 20 degrés :  
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "20" -t BSB-LAN/0/16/710/set`

Forcer la mise à jour immédiate de la température extérieure (ID d'appareil 0, numéro de catégorie 51, paramètre 8700) :  
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "" -t BSB-LAN/0/51/8700/poll`

Forcer la mise à jour immédiate des paramètres 700 et 8700 à partir de l'appareil par défaut ainsi que du paramètre 8326 à partir de l'ID d'appareil 1 :  
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "700,8700,8326!1" -t BSB-LAN/poll`  
ou  
`mosquitto_pub -h my.mosquitto-broker.local -u USER -P PASSWORD -m "/0/16/700,/0/51/8700,/1/50/8326" -t BSB-LAN/poll`

**Attention :** Note que le numéro de catégorie diffère d'un système à l'autre et doit être comparé avec ton système en premier !

---

## Échange de données via JSON

BSB-LAN permet d'interroger et de définir des paramètres via des structures JSON et fournit également de nombreuses informations sur les paramètres et les structures de catégories de cette manière. L'API JSON est accessible via des [commandes URL](using.md) et le fichier `openapi.yaml` fourni dans ce référentiel peut être utilisé avec [Swagger](https://editor.swagger.io/?url=https://raw.githubusercontent.com/fredlcore/bsb_lan/master/openapi.yaml) pour explorer ses possibilités et ses fonctionnalités.

---

## Échange de données via des commandes URL et la récupération de données à l'écran

Pour des solutions plus simples, l'[utilisation de commandes URL](using.md) pour interroger et définir des paramètres peut être utilisée pour contrôler BSB-LAN à partir d'autres systèmes. La récupération de données à l'écran est possible car le projet tente de ne pas rompre certaines façons d'afficher les données, de sorte que l'analyse avec des expressions régulières reste réalisable. Néanmoins, pour la plupart des scénarios, l'une des autres options sera probablement préférable.