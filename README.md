# zadanie_projekt_artur_tamm

Aby skompilować plik należy posiadać: 
-wxWidgets https://www.wxwidgets.org/
-Visual Studio 2019
-opcja "enable intrinsic functions" (C++/Optimization w Visual Studio) ustawieniach oraz procesor kompatybilny z SSE (instrukcja POPCNT)

poradnik jak zainstalować wxwidgets w visual studio:
https://www.youtube.com/watch?v=EI2taYkErRg

Jako że to jest dosyć kłopotliwe i może zająć dużo czasu, w folderze "release" znajduje się gotowy skompilowany (wxChess1.exe) który można normalnie uruchomić
Wszystkie pliki grafik oraz pliki .dll biblioteki wxwidgets muszą znajdować się w tej samej lokacji co plik wykonywalny .exe.

Szczegóły implementacji:
Od ostatnich zajęć nie udało mi się nic dodać, a więc implementacja dalej jest bardzo prymitywna. Można ruszać figurami (przeciągając
figury, jednakże żadne zasady gry nie zostały dodane). Było to w moich planach, jednakże trzeba było też zrobić zadania z grafiki i 
moim priorytetem jednak był egzamin w środę. 

Udało mi się zaimplementować następujące klasy z diagramu klas:
-Move (prosta klasa zapisująca ruchy, częściowo)
-Bitboard (prosta klasa zapisująca pozycje)
-IPC (kompletnie nie działa)
-board (podzielona na "GameLogic" i "board"), GameLogic to pozostałość po moich kombinacjach z GUI ucząc się wxWidgets, miało zostać usunięte ale nie starczyło czasu
Klasa ta zawiera różne losowe próby implementacji, jednakże nie skończyło mi czasu na nic sensownego.
-GUIPlayfield nazwane PlayfieldWindow, ogólna klasa implementująca GUI

Cały kod implementacji jest chaotyczny, chciałem aby cokolwiek w ogóle działało ale wyszło że prawie nic nie działa, istnieje wiele zalążków
różnych prób implementacji rzeczy, wiele kodu który nic nie robi.


