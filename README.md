# PROIECT1_SD

 -> Scopul acestui proiect este compararea performantei a 5 algoritmi (Mergesort, Heapsort, Radixsort, Insertionsort, Shellsort) intre ei, dar si cu algoritmul nativ al limbajului c++(sort).
 
 -> Am generat vectorii utilizand mt19937_64 si uniform_int_distribution.
 
 -> Observarea timpilor de executie a fiecarei sortari este realizata cu ajutorul librariei chrono, iar rezultatul este afisat in secunde.
 
 -> COMPLEXITATI:
       Radixsort: O(p*n), unde p este numarul de cifre ale fiecarui numar;
       Mergesort: O(nlogn);
       Shellsort: best case: O(nlogn),
                  worst case: O(n^2);
       Heapsort: O(nlongn);
       Insertionsort: O(n^2);
       
 ->CONCLUZIE:
    Incercand sa creez un clasament in functie de performanta fiecarei sortari, am observat ca nu se poate gasi un algoritm de sortare genral optim, eficienta fiecaruia depinzand de setul de date de intrare.
 

