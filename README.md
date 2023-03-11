# Data Structure Project

-> The purpose of this project is to compare the performance of 5 algorithms (Mergesort, Heapsort, Radixsort, Insertionsort, Shellsort) among themselves, as well as with the native C++ algorithm (sort).

-> The vectors were generated using mt19937_64 and uniform_int_distribution.

-> The execution times of each sorting algorithm are measured using the chrono library, and the results are displayed in seconds.

-> COMPLEXITIES:
Radixsort: O(p*n), where p is the number of digits in each number;
Mergesort: O(nlogn);
Shellsort: best case: O(nlogn),
worst case: O(n^2);
Heapsort: O(nlogn);
Insertionsort: O(n^2);

-> CONCLUSION:
Trying to create a ranking based on the performance of each sorting algorithm, it was observed that there is no universally optimal sorting algorithm, as the efficiency of each depends on the input dataset.

