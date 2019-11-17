# Istruzioni dei comandi URL #

| URL-command           | Effect                                                                    |
|:----------------------|:------------------------------------------------------------------------------|
|  /\<x\>               | Interroga il valore del parametro \<x\>
|  /\<x\>,\<y\>,\<z\>   | Interroga i valori dei parametri \<x\>, \<y\> and \<z\>
|  /\<x\>-\<y\>         | Interroga i valori dei parametri da \<x\> a \<y\>
|  /A                   | Interroga i valori medi su 24h dei parametri impostati
|  /A=\<x\>,\<y\>       | Imposta i parametri per il calcolo medio su 24h \<x\>, \<y\>
|  /B                   | Interroga i tempi (in secondi) e i cicli di funzionamento del bruciatore (incluso ACS)
|  /B0                  | Azzera il contatore dei tempi e dei cicli di funzionamento del bruciatore
|  /C                   | Visualizza la configurazione di BSB-LAN
|  /D                   | Visualizza il file di registro dalla scheda microSD
|  /DG                  | Visualizza graficamente il file di registro dalla scheda microSDG
|  /D0                  | Cancella il file di registro e ne crea una nuovo vuoto
|  /E\<x\>              | Visualizza i valori ENUM del parametro \ <x \>
|  /G\<x\>              | GPIO: Interroga il pin \<x\>
|  /G\<x\>,\<y\>        | GPIO: Imposta il pin \<x\> a HIGH (\<y\> = 1) oppure a LOW (\<y\> = 0)
|  /G\<x\>,I            | GPIO: Interroga il pin \<x\> mentre lo imposta a INPUT
|  /I\<x\>=\<y\>        | Invia un messaggio INF al parametro \<x\> con valore \<y\>
|  /JK=\<x\>        	| JSON: Interroga una categoria specifica \<x\>
|  /JK=ALL          	| JSON: Interroga tutte le categorie definite
|  /JQ=\<x\>,\<y\>,\<z\>      | JSON: Interroga le categorie specifiche \<x\>, \<y\> e \<z\>
|  /JQ                  | *→ con struttura JSON (vedi [manuale](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#824-retrieving-and-controlling-via-json)) tramite richiesta HTTP-POST:* Interroga i parametri
|  /JS                  |  *→ con struttura JSON (vedi [manuale](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#824-retrieving-and-controlling-via-json)) tramite richiesta HTTP-POST:* Imposta i parametri
|  /K                   | Elenca tutte le categories di parametri
|  /K\<x\>              | Interroga tutti i parametri e i valori della categoria \<x\>
|  /L=0,0               | Disattiva temporaneamente il logging su microSD-card 
|  /L=\<x\>,\<y1\>,\<y2\>,\<y3\>       | Imposta l'intervallo di logging a \<x\> secondi per i parametri (facoltativo) \<y1\>,\<y2\>,\<y3\>
|  /LB=\<x\>            | Configura il logging delle comunicazioni sul bus: solo messaggi broadcast (\<x\>=1) oppure tutti (\<x\>=0)
|  /LU=\<x\>            | Configura il logging delle comunicazioni sul bus: solo sconosciuti (\<x\>=1) oppure tutti (\<x\>=0)
|  /M\<x\>              | Attiva (\<x\> = 1) oppure disattiva (\<x\> = 0) il monitoraggio delle comunicazioni sul bus 
|  /N                   | Reset & riavvio di arduino (impiega circa 15 secondi)
|  /NE                  | Reset & riavvio di arduino (impiega circa 15 secondi) e cancellazione della EEPROM
|  /P\<x\>              | Imposta il tipo di protocollo del bus (temporaneamente): \<x\> = 0 → BSB | 1 → LPB | 2 → PPS
|  /P\<x\>,\<s\>,\<d\>  | Imposta il tipo di protocollo del bus \<x\>, il proprio indirizzo \<s\>, l'indirizzo di destinazione \<d\> (temporaneamente)
|  /Q                   | Interroga parametri specifici del controller non censiti
|  /R\<x\>              | Ripristina il valore del parametro \<x\> 
|  /S\<x\>=\<y\>        | Imposta il valore \<y\> per il parametro \<x\>
|  /T                   | Interroga i sensori opzionali (DS18B20/DHT22)
|  /V\<x\>              | Attiva (\<x\> = 1) oppure disattiva (\<x\> = 0) la modalità verbose di output
|  /X                   | Interroga i termoatati MAX! opzionali


[Istruzioni in PDF](https://github.com/1coderookie/BSB-LPB-LAN_EN/raw/master/Cheatsheet_URL-commands_IT.pdf)


