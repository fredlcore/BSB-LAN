# Cheatsheet URL-commands #

| URL-command           | Effect                                                                    |
|:----------------------|:------------------------------------------------------------------------------|
|  /\<x\>               | Query value/setting of parameter \<x\>
|  /\<x\>,\<y\>,\<z\>   | Query values/settings of parameters \<x\>, \<y\> and \<z\>   
|  /\<x\>-\<y\>         | Query values/settings of parameters \<x\> to \<y\>  
|  /A                   | Query 24h-average values  
|  /A=\<x\>,\<y\>       | Change 24h-average value calculation of parameters \<x\>, \<y\>  
|  /B                   | Query accumulated burner-runtimes (in seconds) (including DHW)  
|  /B0                  | Reset counter of burner-runtime  
|  /C                   | Display configuration of BSB-LAN  
|  /D                   | Display logfile from the microSD-card  
|  /DG                  | Graphical display of the logfile from microSD-card  
|  /D0                  | Reset logfile & create new header  
|  /E\<x\>              | Display ENUM-values of parameter \<x\>  
|  /G\<x\>              | GPIO: query pin \<x\>  
|  /G\<x\>,\<y\>        | GPIO: set pin \<x\> to high (\<y\> = 1) or low (\<y\> = 0)  
|  /G\<x\>,I            | GPIO: query pin \<x\> while setting to INPUT  
|  /H                   | Query optional DHT22-sensors  
|  /I\<x\>=\<y\>        | Send INF-message to parameter \<x\> with value \<y\>  
|  /JK=\<x\>        	| JSON: query category \<x\>  
|  /JK=ALL        	| JSON: query all categories (including min. and max.)  
|  /JQ=\<x\>,\<y\>,\<z\>      | JSON: query parameter \<x\>, \<y\> and \<z\>  
|  /JS=\<x\>,\<y\>,\<z\>      | JSON: set parameter \<x\> with value \<y\> by send-type \<z\><br>(
For this: \<y\> = numeric: ON = 1, OFF = 0; Temp. 20°C = 20;<br>if more than one option is available: respective option = respective number;<br>\<z\> = 0 (for INF) or 1 (for SET))  
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
|  /T                   | Query optional DS18B20-sensors  
|  /V\<x\>              | Activate (\<x\> = 1) or deactivate (\<x\> = 0) verbose output mode  
|  /X                   | Query optional MAX!-thermostats  

       
[Cheatsheet as PDF](https://github.com/1coderookie/BSB-LPB-LAN/raw/master/Cheatsheet%20URL-commands_EN.pdf)
    
