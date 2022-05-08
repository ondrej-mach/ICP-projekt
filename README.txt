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

Pro třídní i sekvenční diagramy jsou v záložce `Edit` jsou dostupné operace `Undo` a `Redo`.
Pro rychlejší použití je vhodné používat běžné zkratky `Ctrl+Z` a `Ctrl+Shift+Z`.

Uprostřed hlavního okna se nachází kreslící plocha.
Ta může být ve dvou režimech, na kreslení class diagramů a na kreslení sequence diagramů.
Mezi režimy se přepíná pomocí tabů nahoře, class diagram je vždy první a sekvenční diagramy následují.

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

Pro demonstraci veškerých možností tohoto editoru je třeba načíst z přiložených testovacích souborů.
Program totiž umí načíst kompletní reprezentaci ze souboru, ale ne všechny prvky z nich umí také nakreslit.
Do editoru se lze dostat kliknutím na tlačítko `New sequence`, které se nachází na konci všech tabů.

Po otevření je vytvořen prázdný sekvenční diagram. Do něj je poté možné nástrojem `New entity` přidat novou entitu.
Ta je umístěna na předem definované místo, za všechny ostatní entity a nelze s ní hýbat. Kliknutím pravým tlačítkem ji lze přejmenovat, smazat ji lze nástrojem `Delete`.
Pokud v třídním diagramu neexistuje objekt se stejným názvem, je entita vyznačena červeně.
Při přejmenování stejnojmenné třídy v třídním diagramu jsou stejnojmenné entity ve všech sekvenčních diagramech automaticky přejmenovány na odpovídající název.

Po přidání alespoň dvou entit je možné natahovat mezi jejich osami, které se samy prodlužují s celkovým počtem interakcí, zprávy.
Nově vytvořené zprávy se umístí pod všechny ostatní a jsou typů vytvářející(`Create`),
synchronní(`Sync`), asynchronní(`Async`), návratové(`Return`) a mazací(`Destroy`).
Nad zprávu se umístí příslušný popis, který v momentální implementaci nelze editovat, je však možné jej správně načíst a vykreslit z xml souboru.
Zprávy create a destroy nelze natáhnout do jedné entity vícekrát, ostatní zprávy nejsou nijak omezeny.
Mazání zpráv je možné provést nástrojem (`Delete`), po jehož zvolení stačí na zprávu kliknout levým tlačítkem myši.

Nástroje `Activate` a `Deactivate` pro editaci aktivit entit nebyly implementovány. Program je však umí správně načíst a vykreslit z xml souboru.

Nástroj `Myš` se používá k označení entit pro přejmenování.
