Ondřej Mach (xmacho12)  
Rostislav Lán (xlanro00)  

# ICP projekt

Projekt do kurzu ICP 2021/2022, VUT FIT.


## Hlavní okno

Hlavní okno programu se skládá z menu, volby nástrojů a zobrazení diagramů.

Menu umožňuje provádět operace se soubory (záložka `File`).
Tyto operace jsou všechny implementované a plně funkční.
Ve složce testFiles jsou přiloženy soubory pro demonstraci.
Tyto soubory jsou ve formátu XML s vlastními prvky.
V jednom souboru je vždy uložen právě jeden class diagram a 0..N sekenčních diagramů.

V záložce `Edit` jsou dostupné operace `Undo` a `Redo`.
Pro rychlejší použití je vhodné používat běžné zkratky `Ctrl+Z` a `Ctrl+Shift+Z`.

Uprostřed hlavního okna se nachází kreslící plocha.
Ta může být ve dvou režimech, na kreslení class diagramů a na kreslení sequence diagramů.
Mezi režimy se přepíná pomocí tabů nahoře, class diagram je vždy první a sekvenční diagramy následují.
Na konci všech tabů se nachází `New Sequence`, kterým lze přidat nový sekvenční diagram.

Po levé straně se nachází nástroje, které jsou různé pro oba typy diagramů.

## Editor class diagramů

V editoru class diagramů lze používat nástroje `Myš`, `Přidat třídu`,`Přidat vazbu` (více druhů) a `Odstranit`.

Nástroj přidat třídu je snadný na použití, při kliknutí umístí novou třídu.
Ta má předvyplněné údaje, které lze editovat pravým tlačítkem a kliknutím na `Edit`.
Tím se zobrazí dialog, ve kterém lze přepsat jmémo třídy, její atributy a metody.
Pokud políčko metody nebo atributy yůstane nevyplněné, nebude uložena do modelu.

Nástroj přidání vazby se používá 'natažením' nové vazby mezi dvěma třídami. 
Kurzorem myši njedeme na jednu třídu a striskneme levé tlačítko. 
Stále držíme tlačítko a dotáhneme kurozor až nad druhou třídu. 
Pustíme tlačítko myši a položíme tím vazbu.
Mezi dvěma třídami může existovat pouze jedna vazba, v případě přidání nové bude původní přepsána.

Nástroj `Odstranit` smaže vazby i třídy při kliknutí nebo přejetí myší.

Nástroj `Myš` se používá k přesouvání tříd.


## Editor sekvenčních diagramů

Pro demonstraci veškerých možností tohoto editoru je třeba načíst z přiloženého testovacího souboru.
Program totiž umí zobrazit mnoho věcí, ale ne všechny z nich umí nakreslit.
