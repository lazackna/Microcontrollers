# Opgave B.5: Coding LCD module (easy/intermediate)

Ontwerp een LCD ‘C module’ (dus een *.c en een *.h file, bijvoorbeeld lcd.c en lcd.h). 
Realiseer in de header de volgende prototypes:
```java
void init();
void display_text(char *str);
void set_cursor(int position);
```

Ontwerp en implementeer in de *.c file de implementatie van bovenstaande functies. 
Welke ontwerpbeslissingen maak je? Met behulp van de simulator (deel A) heb je geleerd hoe het LCD werkt. 
Verwerk deze in de body van bovenstaande functies.

Implementeer (in een aparte file) een test programma om bovenstaande te testen.

Als alles goed werkt heb je nu een generieke module gemaakt die je in al je projecten kunt gebruiken.