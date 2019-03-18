# Cheatsheet URL-commands #

| URL-command           | effect                                                                    |
|:----------------------|:------------------------------------------------------------------------------|
|  /\<x\>               | query value/setting of parameter \<x\>
|  /\<x\>,\<y\>,\<z\>   | query values/settings of parameters \<x\>, \<y\> and \<z\>   
|  /\<x\>-\<y\>         | query values/settings of parameters \<x\> to \<y\>  
|  /A                   | query 24h-average values  
|  /A=\<x\>,\<y\>       | change 24h-average value calculation of parameters \<x\>, \<y\>  
|  /B                   | query accumulated burner-runtimes (in seconds) (including DHW)  
|  /B0                  | reset counter of burner-runtime  
|  /C                   | display configuration of BSB-LAN  
|  /D                   | display logfile from the microSD-card  
|  /DG                  | graphical display of the logfile from microSD-card  
|  /D0                  | reset logfile & create new header  
|  /E\<x\>              | display ENUM-values of parameter \<x\>  
|  /G\<x\>              | GPIO: query pin \<x\>  
|  /G\<x\>,\<y\>        | GPIO: set pin \<x\> to high (\<y\> = 1) or low (\<y\> = 0)  
|  /G\<x\>,I            | GPIO: query pin \<x\> while setting to INPUT  
|  /H                   | query optional DHT22-sensors  
|  /I\<x\>=\<y\>        | send INF-message to parameter \<x\> with value \<y\>  
|  /JK=\<x\>        	| JSON: query category \<x\>  
|  /JK=ALL        	| JSON: query all categories (including min. & max.)  
|  /JQ=\<x\>,\<y\>,\<z\>      | JSON: query parameter \<x\>, \<y\> and \<z\>  
|  /JS=\<x\>,\<y\>,\<z\>      | JSON: set parameter \<x\> with value \<y\> by send-type \<z\><br>(Herefore: \<y\> = numeric: ON = 1, OFF = 0; Temp. 20°C = 20;<br>if more than one option is available: respective option = respective number;<br>\<z\> = 0 (for INF) or 1 (for SET))  
|  /K                   | list all categories  
|  /K\<x\>              | query all parameters and values of category \<x\>  
|  /L=0,0               | deactivate logging to microSD-card temporary  
|  /L=\<x\>,\<y\>       | set logging interval to \<x\> seconds with (optional) logging parameter \<y\>  
|  /LB=\<x\>            | configure logging of bus-telegrams: only broadcasts (\<x\>=1) or all (\<x\>=0)  
|  /LU=\<x\>            | configure logging of bus-telegrams: only unknown (\<x\>=1) or all (\<x\>=0)  
|  /M\<x\>              | activate (\<x\> = 1) or deactivate (\<x\> = 0) bus monitor mode  
|  /N                   | reset & reboot arduino (takes approx. 15 seconds)  
|  /NE                  | reset & reboot arduino (takes approx. 15 seconds) and erase EEPROM 
|  /O                   | display URL-commands  
|  /P\<x\>              | set busprotocol / bustype (temporarily): \<x\> = 0 → BSB | 1 → LPB | 2 → PPS  
|  /P\<x\>,\<s\>,\<d\>  | set busprotocol/-type \<x\>, own address \<s\>, target-address \<d\> (temporarily)  
|  /Q                   | check for unreleased controller-specific parameter  
|  /R\<x\>              | query reset-value of parameter \<x\>  
|  /S\<x\>=\<y\>        | set value <y> for parameter \<x\>  
|  /T                   | query optional DS18B20-sensors  
|  /V\<x\>              | activate (\<x\> = 1) or deactivate (\<x\> = 0) verbose output mode  
|  /X                   | query optional MAX!-thermostats  

       
[Cheatsheet as PDF](https://github.com/1coderookie/BSB-LPB-LAN/raw/master/Cheatsheet%20URL-commands_EN.pdf)
    
