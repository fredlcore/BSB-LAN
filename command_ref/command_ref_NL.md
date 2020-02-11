# Cheatsheet van URL-commando's #

| URL-commando          | Resultaat                                                                     |
|:----------------------|:------------------------------------------------------------------------------|
|  /\<x\>               | Opvragen van waarde/instelling van parameter \<x\>
|  /\<x\>/\<y\>/\<z\>   | Opvragen van waardes/waardes van parameters \<x\>, \<y\> and \<z\>   
|  /\<x\>-\<y\>         | Opvragen van waardes/waardes van parameters \<x\> to \<y\>  
|  /A                   | Opvragen van 24uurs-gemiddelde waardes  
|  /A=\<x\>,\<y\>       | Verander het 24uurs-gemiddelde waarde berekening van parameters \<x\>, \<y\>  
|  /A=0			| Disable 24h average calculation temporarily  
|  /B                   | Opvragen van geaccumuleerde brander-looptijd (in secondes) en -cycli (inbegrepen SWW)  
|  /B0                  | Reset teller van brander-looptijd and -cycli  
|  /C                   | Weergave configuratie van BSB-LAN 
|  /D                   | Toon logbestand van de microSD-kaart 
|  /DG                  | Grafische weergave van het logbestand van microSD-kaart  
|  /D0                  | Reset logfile en maak een nieuwe header 
|  /E\<x\>              | Toon ENUM-waardes van parameter \<x\>  
|  /G\<x\>              | GPIO: Opvragen van pin \<x\>  
|  /G\<x\>=\<y\>        | GPIO: Set pin \<x\> naar hoog (\<y\> = 1) of laag (\<y\> = 0)  
|  /G\<x\>,I            | GPIO: Opvragen van pin \<x\> tijdens het instellen op INPUT 
|  /I\<x\>=\<y\>        | Stuur INF-message naar parameter \<x\> met waarde \<y\>  
|  /JK=\<x\>        	| JSON: Opvragen van alle parameters van categorie \<x\>  
|  /JK=ALL          	| JSON: Maak een lijst van alle categorieën met bijbehorende parameternummers  
|  /JQ=\<x\>,\<y\>,\<z\>      | JSON: Opvragen van parameters \<x\>, \<y\> en \<z\>  
|  /JQ                  | *→ met JSON-structure (bekijk [manual](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#824-retrieving-and-controlling-via-json)) via HTTP-POST request:* Opvragen van parameters
|  /JS                  | *→ met JSON-structure (bekijk [manual](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#824-retrieving-and-controlling-via-json)) via HTTP-POST request:* Parameters instellen
|  /K                   | Maak een lijst van alle categorieën  
|  /K\<x\>              | Vraag alle parameters en waardes van categorie \<x\>  
|  /L=0,0               | Deactiveer het loggen tijdelijk naar een microSD-kaart  
|  /L=\<x\>,\<y1\>,\<y2\>,\<y3\>       | Stel registratie-interval in op \<x\> seconden met (optionele) logging-parameter \<y1\>,\<y2\>,\<y3\>  
|  /LB=\<x\>            | Logging van bustelegrammen configureren: alleen uitzendingen (\<x\>=1) or all (\<x\>=0)  
|  /LU=\<x\>            | Logging van bustelegrammen configureren: alleen onbekend (\<x\>=1) or all (\<x\>=0)  
|  /M\<x\>              | Activeer (\<x\> = 1) of deactiveer (\<x\> = 0) busmonitor-modus 
|  /N                   | Reset & reboot arduino (duurt ongeveer 15 seconden)
|  /NE                  | Reset & reboot arduino (duurt ongeveer 15 seconden) en wis EEPROM
|  /P\<x\>              | Busprotocol / bustype instellen (tijdelijk): \<x\> = 0 → BSB | 1 → LPB | 2 → PPS  
|  /P\<x\>,\<s\>,\<d\>  | Stel busprotocol/-type \<x\>, eigen adres \<s\>, doeladres \<d\> in (tijdelijk)  
|  /Q                   | Controleer op niet-vrijgegeven controller-specifieke parameter  
|  /R\<x\>              | Opvragen van de reset-waarde van de parameter \<x\>  
|  /S\<x\>=\<y\>        | Stel de waarde <y> in voor de parameter \<x\>  
|  /T                   | Opvragen van optionele sensors (DS18B20/DHT22)  
|  /U                   | Displays the user-defined variables if used in `BSB_lan_custom.h`  
|  /V\<x\>              | Activeren (\<x\> = 1) of deactiveren (\<x\> = 0) uitgebreide uitvoer modus 
|  /X                   | Opvragen van optionele MAX! -Thermostaten  

       
[Cheatsheet as PDF](https://github.com/1coderookie/BSB-LPB-LAN_EN/raw/master/commandref/Cheatsheet_URL-commands_NL.pdf)

    
