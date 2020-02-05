# Aide-mémoire commandes URL #

| URL-command           | Effect                                                                   					|
|:----------------------|:--------------------------------------------------------------------------------------------------------------|
|  /\<x\>               | Demande la valeur / le réglage du paramètre \<x\>   									|
|  /\<x\>/\<y\>/\<z\>   | Affichage des valeurs / réglages des paramètres \<x\>, \<y\> et \<z\>   							|
|  /\<x\>-\<y\>         | Affichage des valeurs / réglages des paramètres \<x\> à \<y\>  								|
|  /A                   | Affichage des moyennes sur 24h											|
|  /A=\<x\>,\<y\>       | Change le calcul des valeurs moyennes sur 24h des paramètres \<x\>, \<y\>  						|
|  /A=0			| Disable 24h average calculation temporarily  
|  /B                   | Affichage des temps de fonctionnement cumulés du brûleur (en sec.) (y compris eau chaude sanitaire)  						|
|  /B0                  | Remise à zéro du temps de fonctionnement du brûleur 										|
|  /C                   | Affichage de la configuration de BSB_lan  										|
|  /D                   | Affichage du fichier journal (log) de la carte micro SD  									|
|  /DG                  | Affichage sous forme de graphique du fichier journal (log) de la carte micro SD  								|
|  /D0                  | Remise à zéro du fichier journal (log) et regénération de entêtes  										|
|  /E\<x\>              | Affichage des valeurs ENUM du paramètre \<x\>  									|
|  /G\<x\>              | GPIO (entrées/sorties): interroge l'état de la pin \<x\>  											|
|  /G\<x\>,\<y\>        | GPIO (entrées/sorties): définit la pin \<x\> à l'état haut (\<y\> = 1) ou à l'état bas (\<y\> = 0)  							|
|  /G\<x\>,I            | GPIO (entrées/sorties): interroge l'état de la pin \<x\> en la définissant en tant qu'entrée (INPUT)  								|
|  /I\<x\>=\<y\>        | Envoi d'un message INF au paramètre \<x\> avec la valeur \<y\>  							|
|  /JK=\<x\>        	| JSON: énumère les paramètres disponibles de la catégorie \<x\>  								|
|  /JK=ALL        	| JSON: énumère toutes les catégories y compris les paramètres associés avec leur numéro   						|
|  /JQ=\<x\>,\<y\>,\<z\>| JSON: interroge les paramètres \<x\>, \<y\> et \<z\>  								|
|  /JQ  /JS  		| → sous forme de structure JSON (voir le [manuel](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#824-retrieving-and-controlling-via-json)) via une requête de type HTTP-POST : interrogation et réglage des paramètres  				|
|  /K                   | Liste toutes les catégories  												|
|  /K\<x\>              | Interrogation des valeurs / réglages de la catégorie \<x\>  								|
|  /L=0,0               | Désactive temporairement l'enregistrement sur la carte micro SD  								|
|  /L=\<x\>,\<y1\>,\<y2\>,\<y3\>       | Définit l'intervalle d'enregistrement (log) à \<x\> secondes et les paramètres (facultatifs) \<y1\>,\<y2\>,\<y3\>  	|
|  /LB=\<x\>            | Configure l'enregistrement des télégrammes du bus: messages émis seulement (\<x\>=1) ou tout (\<x\>=0)  				|
|  /LU=\<x\>            | Configure l'enregistrement des télégrammes du bus: messages inconnus seulement (\<x\>=1) ou tout (\<x\>=0)  					|
|  /M\<x\>              | Active (\<x\> = 1) ou désactive (\<x\> = 0) la supervision du bus sur le port série  						|
|  /N                   | Réinitialise et redémmare l'Arduino (nécessite environ 15 sec.)  								|
|  /NE                  | Réinitialise et redémmare l'Arduino (nécessite environ 15 sec.) et efface la mémoire EEPROM 						|
|  /P\<x\>              | Change temporairement le type de bus ou protocole : \<x\> = 0 → BSB | 1 → LPB | 2 → PPS  				|
|  /P\<x\>,\<s\>,\<d\>  | Change temporairement le type de bus ou protocole \<x\>, adresse propre \<s\>, adresse de destination \<d\>  				|
|  /Q                   | Test des paramètres non répertoriés spécifiques au contrôleur  								|
|  /R\<x\>              | Demande la valeur par défaut du paramètre \<x\>  									|
|  /S\<x\>=\<y\>        | Envoie la valeur <y> au paramètre \<x\>  										|
|  /T                   | Interroge les capteurs des type DS18B20 et DHT22 (facultatifs)  										|
|  /V\<x\>              | Active (\<x\> = 1) ou désactive (\<x\> = 0) l'affichage détaillé sur le port série  						|
|  /X                   | Interroge les thermostats de type MAX! (facultatifs)   										|


[Aide-mémoire en PDF](https://github.com/1coderookie/BSB-LPB-LAN_EN/raw/master/commandref/Cheatsheet_URL-commands_FR.pdf)



