# Skrócona lista komend URL-a #

| Polecenie URL           | Efekt                                                                    |
|:----------------------|:------------------------------------------------------------------------------|
|  /\<x\>               | Wyświetlenie/ustawienie wartośći parametru \<x\>
|  /\<x\>/\<y\>/\<z\>   | Wyświetlenie/ustawienie wartośći parametrów \<x\>, \<y\> i \<z\>   
|  /\<x\>-\<y\>         | Wyświetlenie/ustawienie wartośći parametrów \<x\> do \<y\>  
|  /A                   | Wyświetlenie wartości średnich z 24h  
|  /A=\<x\>,\<y\>       | Zmiana obliczanie wartości średniej 24-godzinnej dla parametrów \<x\>, \<y\>  
|  /A=0			| Disable 24h average calculation temporarily  
|  /B                   | Wyświetl skumulowany czasy pracy palnika (w sekundach) (w tym cwu)  
|  /B0                  | Reset licznik czasu pracy palnika  
|  /C                   | Wyświetl konfigurację BSB-LAN  
|  /D                   | Wyświetl plik log z karty microSD  
|  /DG                  | Wykres z pliku log z karty microSD  
|  /D0                  | Zresetuj plik log i utwórz nowy nagłówek  
|  /E\<x\>              | Wyświetl liste możliwych wartości tekstu parametru \<x\>  
|  /G\<x\>              | GPIO: Wyświetl stan pinu \<x\>  
|  /G\<x\>=\<y\>        | GPIO: Ustaw stan pinu \<x\> na wysoki (\<y\> = 1) lub niski (\<y\> = 0)  
|  /G\<x\>,I            | GPIO: Wyświetl stan pinu \<x\> i zmień typ na weściowy  
|  /I\<x\>=\<y\>        | Wyślij komunikat INF do parametru \<x\> z wartością \<y\>  
|  /JK=\<x\>        	| JSON: Zapytanie o wszystkie parametry kategorii \<x\>  
|  /JK=ALL          	| JSON: Lista wszystkich kategorii z odpowiednimi numerami parametrów  
|  /JQ=\<x\>,\<y\>,\<z\>      | JSON: Parametry zapytania \<x\>, \<y\> i \<z\>  
|  /JQ i /JS                 | *→ ze strukturą JSON ([patrz podręcznik](https://1coderookie.github.io/BSB-LPB-LAN_EN/chap08.html#824-retrieving-and-controlling-via-json)) za pośrednictwem żądania HTTP-POST: Zapytanie i ustawienie parametrów
|  /K                   | Wyświetl wszystkie kategorie  
|  /K\<x\>              | Zapytanie o wszystkie parametry i wartości kategorii \<x\>  
|  /L=0,0               | Tymczasowo wyłącz rejestrowanie na karcie microSD  
|  /L=\<x\>,\<y1\>,\<y2\>,\<y3\>       | Ustaw interwał logowania na \<x\> sekund, opcjonalnie ustaw rejestrowanie parametrów \<y1\>,\<y2\>,\<y3\>  
|  /LB=\<x\>            | Skonfiguruj rejestrowanie telegramów magistrali: tylko transmisje (\<x\>=1) lub wszystkie (\<x\>=0)  
|  /LU=\<x\>            | Skonfiguruj rejestrowanie telegramów magistrali: tylko nieznane (\<x\>=1) lub wszystkie (\<x\>=0)  
|  /M\<x\>              | Aktywuj (\<x\> = 1) lub wyłącz (\<x\> = 0) tryb monitorowania magistrali  
|  /N                   | Zresetuj i uruchom ponownie arduino (trwa około 15 sekund)  
|  /NE                  | Zresetuj i uruchom ponownie arduino (trwa około 15 sekund) i skasuj EEPROM 
|  /P\<x\>              | Ustaw protokół / typ magistrali (tymczasowo): \<x\> = 0 → BSB | 1 → LPB | 2 → PPS  
|  /P\<x\>,\<s\>,\<d\>  | Ustaw protokół / typ magistrali \<x\>, własny adres \<s\>, adres docelowy \<d\> (tymczasowo)  
|  /Q                   | Przetestuj nieznane parametry sterownika (tylko BSB/LPB)  
|  /R\<x\>              | Wyświetl i zrestetuj parametr \<x\>  
|  /S\<x\>=\<y\>        | Ustaw wartość <y> dla parametru \<x\>  
|  /T                   | Wyświetl opcjonalne czujniki (DS18B20/DHT22)  
|  /U                   | Displays the user-defined variables if used in `BSB_lan_custom.h`  
|  /V\<x\>              | Aktywuj (\<x\> = 1) lub dezaktywuj (\<x\> = 0) tryb przekazywania dodatkowych informacji na interfejs szeregowy Arduino  
|  /X                   | Wyświetl opcjonalne termostaty MAX!  

       
[Pobierz skróconą listę komend URL jako plik PDF](https://github.com/1coderookie/BSB-LPB-LAN_EN/raw/master/commandref/Cheatsheet_URL-commands_PL.pdf)
    
