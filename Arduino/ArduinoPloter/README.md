# Ploter 

## Cel

System jako argumenty przyjmuje ((plik G-code z obiektem do narysowania) , (kartke paapieru)), resultatem dzialania systemu jest kartka z narysowanym obiektem zdefiniowanym w G-codedzie.

## Realizacja

Główne elementy systemu:
- Na komputerze PC: program parsujacy G-Code i wysylajacy za posrednictwem portu szeregowego kolejne współrzędne polozenia końcówki rysującej plotera
- port szeregowy umożliwiajacy komunikacje Arduino <-> PC
- Kontroler Arduino: odbiera zadane polozenie i generuje sygnal sterujacy dla serwomechanizmów, aby przesunać płynnym ruchem w lini prostej koncówke rysującą w nową wskazaną pozycję, po czym wysyła sygmał do PC z proźbą o kolejne położenie
- Ramie z końcówką rysującą poruszane serwomechanizmami o 3 stopniach swobody 

## Sposob uzycia

Część systemu działajacą na komputerze należy zbudować za pomocą CMake.
W kodzie ręcznie należy ustawić docelowy port komunikacji.
Jako argument do programu nalezy podac scieżkę do pliku z G-Code

System dzialający na arduino należy wgrać za pomocą Arduino IDE.
