Problem komiwojażera
====================

*Kompilacja:*
mpiCC BF.cpp Graph.cpp main.cpp -o tsp

*Uruchomienie:*
mpirun -np "liczba procesów" -host "hosty" ./tsp

Program wczytuje dane z pliku input.txt


Liczby pierwsze
===============

*Kompilacja:*
mpicc MPITest.cpp -o MPITest

"Uruchomienie:"
mpirun -np "liczba procesów" ./MPITest "Początek zakresu" "Koniec zakresu"
