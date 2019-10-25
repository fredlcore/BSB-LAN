# Cheatsheet URL-commands #

| URL-command           | Effect                                                                    |
|:----------------------|:------------------------------------------------------------------------------|
|  /\<x\>               | Query value/setting of parameter \<x\>
|  /\<x\>,\<y\>,\<z\>   | Query values/settings of parameters \<x\>, \<y\> and \<z\>   
|  /\<x\>-\<y\>         | Query values/settings of parameters \<x\> to \<y\>  
|  /A                   | Query 24h-average values  
|  /A=\<x\>,\<y\>       | Change 24h-average value calculation of parameters \<x\>, \<y\>  
|  /B                   | Query accumulated burner-runtimes (in seconds) and -cycles (including DHW)  
|  /B0                  | Reset counter of burner-runtime and -cycles  
|  /C                   | Display configuration of BSB-LAN  
|  /D                   | Display logfile from the microSD-card  
|  /DG                  | Graphical display of the logfile from microSD-card  
|  /D0                  | Reset logfile & create new header  
|  /E\<x\>              | Display ENUM-values of parameter \<x\>  
|  /G\<x\>              | GPIO: Query pin \<x\>  
|  /G\<x\>,\<y\>        | GPIO: Set pin \<x\> to high (\<y\> = 1) or low (\<y\> = 0)  
|  /G\<x\>,I            | GPIO: Query pin \<x\> while setting to INPUT  
|  /I\<x\>=\<y\>        | Send INF-message to parameter \<x\> with value \<y\>  
|  /JK=\<x\>        	| JSON: Query all parameters of category \<x\>  
|  /JK=ALL          	| JSON: List all categories with corresponding parameter numbers  
|  /JQ=\<x\>,\<y\>,\<z\>      | JSON: Query parameters \<x\>, \<y\> und \<z\>  
|  /JQ                  | *→ with JSON-structure (see [manual](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#824-abrufen-und-steuern-mittels-json)) via HTTP-POST request:* Query parameters
|  /JS                  | *→ with JSON-structure (see [manual](https://1coderookie.github.io/BSB-LPB-LAN/kap08.html#824-abrufen-und-steuern-mittels-json)) via HTTP-POST request:* Set parameters
|  /K                   | List all categories  
|  /K\<x\>              | Query all parameters and values of category \<x\>  
|  /L=0,0               | Deactivate logging to microSD-card temporary  
|  /L=\<x\>,\<y1\>,\<y2\>,\<y3\>       | Set logging interval to \<x\> seconds with (optional) logging parameter \<y1\>,\<y2\>,\<y3\>  
|  /LB=\<x\>            | Configure logging of bus-telegrams: only broadcasts (\<x\>=1) or all (\<x\>=0)  
|  /LU=\<x\>            | Configure logging of bus-telegrams: only unknown (\<x\>=1) or all (\<x\>=0)  
|  /M\<x\>              | Activate (\<x\> = 1) or deactivate (\<x\> = 0) bus monitor mode  
|  /N                   | Reset & reboot arduino (takes approx. 15 seconds)  
|  /NE                  | Reset & reboot arduino (takes approx. 15 seconds) and erase EEPROM 
|  /P\<x\>              | Set busprotocol / bustype (temporarily): \<x\> = 0 → BSB | 1 → LPB | 2 → PPS  
|  /P\<x\>,\<s\>,\<d\>  | Set busprotocol/-type \<x\>, own address \<s\>, target-address \<d\> (temporarily)  
|  /Q                   | Check for unreleased controller-specific parameter  
|  /R\<x\>              | Query reset-value of parameter \<x\>  
|  /S\<x\>=\<y\>        | Set value <y> for parameter \<x\>  
|  /T                   | Query optional sensors (DS18B20/DHT22)  
|  /V\<x\>              | Activate (\<x\> = 1) or deactivate (\<x\> = 0) verbose output mode  
|  /X                   | Query optional MAX!-thermostats  

       
[Cheatsheet as PDF](https://github.com/1coderookie/BSB-LPB-LAN/raw/master/commandref/Cheatsheet_URL-commands_EN.pdf)

    
