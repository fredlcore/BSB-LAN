# Le bus BSB/LPB/PPS

Développé à la fin du dernier millénaire sur la base du BatiBUS (plus d'informations sont disponibles [ici](https://2007.blog.dest-unreach.be/wp-content/uploads/2012/12/Interface-module-I-O-OPEN-ALBATROS-PTM59-20V1_19957_hq-en.pdf) et [ici](https://2007.blog.dest-unreach.be/wp-content/uploads/2012/12/BatiBus_v1.4.pdf)), de nombreux contrôleurs de systèmes de chauffage Siemens utilisent toujours le même type de bus physique pour communiquer avec les modules de commande des pièces et d'autres appareils de chauffage. Bien qu'une vitesse de bus de seulement 4800 bits par seconde puisse sembler anachronique de nos jours, elle fournit toujours un protocole de transmission stable et robuste qui est encore aujourd'hui parfaitement suffisant pour transmettre de courts messages de quelques dizaines d'octets sur des lignes pouvant atteindre un kilomètre de long.

Cette topologie de bus permet également de connecter BSB-LAN à n'importe endroit: au module de commande, au système de chauffage ou à tout endroit où les 2 fils de bus sont disponibles. Vous pouvez même ajouter les deux fils pour BSB-LAN dans un emplacement déjà "occupé" et cela n'endommagera pas l'autre appareil (en supposant une installation correcte).

En plus de la même couche physique, trois systèmes de bus, BSB, LPB et PPS, s'occupent de différentes tâches et, bien que BSB et LPB doivent toujours être préférés lorsqu'ils sont disponibles, PPS fournit néanmoins un ensemble de paramètres qui est généralement tout à fait suffisant pour l'utilisateur moyen.
BSB-LAN fonctionne sur l'un de ces bus et le passage de l'un à l'autre nécessite simplement de modifier quelques paramètres.

---

[](){#BSB}
## Boiler System Bus (BSB)

BSB est le système de bus le plus courant dans les contrôleurs Siemens depuis 10 à 15 ans. Il s'agit du successeur du système PPS, avec lequel il partage les mêmes paramètres physiques, mais il est beaucoup plus polyvalent: au lieu de quelques dizaines de paramètres, il peut en gérer des centaines et les regrouper en différentes catégories pour faciliter la navigation. Il s'agit d'un protocole basé sur les transactions, dans lequel la plupart des messages sont envoyés d'un appareil à un autre, et le destinataire renvoie un type de retour, par exemple si la tâche a pu être effectuée ou si elle contenait des données non valides.

Bien que BSB soit capable d'adresser plusieurs appareils sur le bus, il n'est pas utilisé dans les systèmes avec plus d'un appareil de chauffage. L'appareil de chauffage a toujours l'ID `0`, l'unité d'affichage sur le système de chauffage a l'ID `10` (ou `0x0A` en hexadécimal) et le module de commande standard a l'ID `6`. BSB-LAN a l'ID `66` ou `0x42` en hexadécimal.
Les modules de commande qui "parlent" BSB sont, par exemple, les QAA55 et les QAA75.

---

[](){#LPB}
## Local Process Bus (LPB)

LPB a été introduit plus ou moins en même temps que PPS, qu'il complétait en termes de communication avec d'autres appareils de chauffage: alors que PPS était utilisé pour communiquer avec le module de commande, LPB était utilisé pour envoyer des commandes d'un appareil de chauffage principal à un ou plusieurs appareils de chauffage auxiliaires, par exemple dans une configuration en cascade. À l'époque, la plupart des informations transmises via LPB étaient liées aux composants internes du système de chauffage (telles que les données des capteurs ou les températures de consigne internes), tandis que les paramètres pertinents pour l'utilisateur (tels que la température de confort) n'étaient disponibles que via PPS. De nos jours, les appareils de chauffage qui offrent à la fois LPB et BSB ont le même type de paramètres disponibles sur les deux bus.

LPB utilise un schéma d'adressage spécifique avec des segments et des appareils. Chaque segment de 0 à 15 peut contenir jusqu'à 15 appareils (de 1 à 15). Lors de l'écriture de ces adresses, le segment et l'appareil sont séparés par un deux-points: `00:01` ou `04:03`.
Pour convertir l'adresse basée sur le segment en ID de destination requis pour BSB-LAN, la formule est la suivante:
`SEGMENT` multiplié par 16 plus `APPAREIL` moins un.
Exemple: l'appareil 3 du segment 4 est égal à `4 * 16 + 3 - 1` = 66.
L'unité de chauffage principale est par définition `00:01`, ce qui correspond à un ID de destination 0.
Pour en savoir plus sur le système LPB et son déploiement, vous pouvez consulter ces deux documents de la fin des années 1990, l'un couvre les [données système de base](https://sid.siemens.com/v/u/20138) qui couvrent la conceptualisation d'un réseau LPB, et l'autre traite des [données d'ingénierie de base](https://sid.siemens.com/v/u/20140) et fournit des détails sur les longueurs et diamètres de câble, etc.

À l'exception de certains radiateurs Weishaut, les modules de commande ne sont pas connectées au système de chauffage via LPB. Les modèles plus récents utilisent BSB pour cette tâche, tandis que les modèles plus anciens utilisent soit PPS, soit dans certains cas OpenTherm.

---

[](){#PPS}
## Point-to-Point Interface (PPS)

L'interface point à point (PPS, pour "Punkt-zu-Punkt Schnittstelle" en allemand) est compatible avec les autres systèmes au niveau physique, mais pas au niveau du protocole de communication. Alors que BSB et LPB communiquent en envoyant des messages et en accusant leur réception, PPS est asservi à l'unité de chauffage. L'unité de chauffage envoie constamment ses données au module de commande et lui indique quand et quel type d'informations il lui renvoyer. Il peut donc falloir jusqu'à quelques minutes avant qu'une valeur définie dans BSB-LAN ne soit réellement demandée par le système de chauffage et affiché.
Il s'agit également d'un protocole très sensible à la temporisation, de sorte que l'exécution d'autres tâches longues par BSB-LAN entraînera une interruption temporaire et un éventuel message d'erreur sur le système de chauffage. Cependant, après un court moment, cela devrait se résoudre de lui-même lorsque les deux composants "communiquent" à nouveau.

Contrairement à BSB et LPB, les modifications apportées dans BSB-LAN n'ont pas d'effet immédiat. La modification de valeurs, par exemple comme la température de consigne de confort de la pièce, sera tout d'abord stockée en interne dans BSB-LAN, puis envoyée au système de chauffage une fois que celui-ci aura demandé au module de commande (c'est-à-dire BSB-LAN) de le faire. Cela peut prendre jusqu'à une minute ou plus, il ne faut donc pas être confus si les paramètres ne s'affichent pas immédiatement sur l'unite de chauffage, comme c'est le cas avec BSB et LPB.

Avec PPS, BSB-LAN peut fonctionner dans deux modes: écoute passive ou en tant que module de commande. En mode passif, BSB-LAN peut simplement écouter les données échangées entre le module de commande et l'appareil de chauffage. Il n'est pas possible d'envoyer ses propres données, tout simplement parce qu'elles seraient écrasées en un rien de temps par le même type de données provenant du module de commande d'ambiance.
Pour envoyer des données de paramètres au système de chauffage, BSB-LAN doit fonctionner en mode "module de commande", ce qui signifie que tout autre module de commande doit être retirée du système de chauffage. Dans ce cas, il est particulièrement important d'envoyer régulièrement une valeur de température de pièce à BSB-LAN, qui à son tour enverra cette valeur à l'appareil de chauffage. Seule une valeur de température extérieure peut être ignorée si le radiateur fonctionne uniquement sur la température extérieure.
BSB-LAN stocke certaines valeurs dans sa mémoire EEPROM non volatile, mais certaines valeurs doivent être réinitialisées après un redémarrage, telles que la température de consigne de la pièce. Il s'agit d'éviter de stocker une valeur de paramètre qui est devenue non valide mais qui est toujours envoyée car elle est stockée dans l'EEPROM.

Les module de commande couramment utilisées avec les systèmes de chauffage qui prennent en charge PPS sont les QAA50 et les QAA70.
