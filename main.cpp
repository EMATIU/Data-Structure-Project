#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;
ifstream f("teste.in");
vector <long long>  L, M;

int verif_sort(vector <long long> &arr, int n)
{
    int i;
    bool ok=1;
    for(i=1;i<n&&ok;i++)
        if(arr[i-1]>arr[i]) ok=0;
    return ok;
}
void generate_vector(vector<long long> &arr, long long maxim)
{ mt19937_64 gen(time(NULL));
  uniform_int_distribution<long long> random(0, maxim);
  for(auto i = arr.begin(); i!=arr.end(); i++){ *i = random(gen); }
 }


// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(vector <long long> &arr, int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = arr[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = arr[mid + 1 + j];

	auto indexOfSubArrayOne = 0, // Initial index of first sub-array
		indexOfSubArrayTwo = 0; // Initial index of second sub-array
	int indexOfMergedArray = left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		arr[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		arr[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(vector <long long> &arr, int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(arr, begin, mid);
	mergeSort(arr, mid + 1, end);
	merge(arr, begin, mid, end);
}


void shellSort(vector <long long> &arr)
{
    // Start with a big gap, then reduce the gap
    for (int gap = arr.size()/2; gap > 0; gap /= 2)
    {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < arr.size(); i += 1)
        {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }

}

void heapify(vector <long long> &arr, int n, int i)
{
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// main function to do heap sort
void heapSort(vector <long long> &arr, int n)
{
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void insertionSort(vector <long long> &arr, int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// A utility function to get maximum value in arr[]
int getMax(vector <long long> &arr, int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(vector <long long> &arr, int n, int exp)
{
    int output[n]; // output array
    int i, count[10] = { 0 };

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixSort(vector <long long> &arr, int n, int base)
{
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 2^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= base)
        countSort(arr, n, exp);
}

void printArray(vector <long long> arr) {
  for (int i = 0; i < arr.size(); i++)
     cout << arr[i] << " ";
    cout << endl;
}

int main() {
  srand(time(0));
  int start,stop,j;
  int nr_teste,nr ,m;
  f>>nr_teste;
  cout<<"Algoritmii de sortare sunt testati pe urmatoarele "<<nr_teste<<" teste: "<<'\n';
 //cout<<"N=100000 MAXIM=1000000"<<'\n';
 for(j=1;j<=nr_teste;j++)
  {
      f>>nr>>m;
      cout<<"N = "<<nr<<" " <<"Maxim = "<<m<<'\n';
      vector <long long> arr(nr), arr1(nr);
      int n=nr;
      generate_vector(arr1, m);
      arr=arr1;
      //cout << "Unsorted array: \n";
     //printArray(arr);
      start = clock();
      sort(arr.begin(),arr.end());
      stop = clock();
      //cout << "Sorted array: \n";
     //printArray(arr);
      if(verif_sort(arr,n)) cout<<"Sort functioneaza"<<'\n';
      else cout<<"Sort NU functioneaza pe acest exemplu"<<'\n';
       cout <<"Execusion time SORT: "<<double(stop-start) / CLOCKS_PER_SEC <<"s"<<'\n';

  ///MERGESORT
  arr=arr1;
  //cout << "Unsorted array: \n";
  //printArray(arr);
   start = clock();
  mergeSort(arr, 0, arr.size() - 1);
   stop = clock();
  //cout << "Sorted array: \n";
  //printArray(arr);
  if(verif_sort(arr,n)) cout<<"Mergesort functioneaza"<<'\n';
  else cout<<"Mergesort NU functioneaza pe acest exemplu"<<'\n';
    cout <<"Execusion time MERGESORT: "<<double(stop-start) / CLOCKS_PER_SEC <<"s"<<'\n';

  ///SHELLSORT
  arr=arr1;
  //cout << "Unsorted array: \n";
  //printArray(arr);
   start = clock();
  shellSort(arr);
   stop = clock();
  //cout << "Sorted array: \n";
  //printArray(arr);
  if(verif_sort(arr,n)) cout<<"Shellsort functioneaza"<<'\n';
  else cout<<"Shellsort NU functioneaza pe acest exemplu"<<'\n';
  cout <<"Execusion time SHELLSORT: "<<double(stop-start) / CLOCKS_PER_SEC <<"s"<<'\n';

  ///HEAPSORT
  arr=arr1;
  //cout << "Unsorted array: \n";
  //printArray(arr);
  start = clock();
  heapSort(arr,n);
  stop = clock();
  //cout << "Sorted array: \n";
  //printArray(arr);
  if(verif_sort(arr,n)) cout<<"Heapsort functioneaza"<<'\n';
  else cout<<"Heapsort NU functioneaza pe acest exemplu"<<'\n';
  cout <<"Execusion time HEAPSORT: "<<double(stop-start) / CLOCKS_PER_SEC <<"s"<<'\n';

  ///RADIXSORT
  arr=arr1;
  //cout << "Unsorted array: \n";
  //printArray(arr);

  int start_b10 = clock();
  radixSort(arr,n,10);
  int stop_b10 = clock();
  int start_b2 = clock();
  radixSort(arr,n,2);
  int stop_b2 = clock();
  if(verif_sort(arr,n)) cout<<"Radixsort cu baza 2 functioneaza"<<'\n';
  else cout<<"Radixsort cu baza 2 NU functioneaza pe acest exemplu"<<'\n';
  //cout << "Sorted array: \n";
 // printArray(arr);
  if(verif_sort(arr,n)) cout<<"Radixsort cu baza 10 functioneaza"<<'\n';
  else cout<<"Radixsort cu baza 10 NU functioneaza pe acest exemplu"<<'\n';
  cout <<"Execusion time RADIXSORT base 2: "<<double(stop_b2-start_b2) / CLOCKS_PER_SEC <<"s"<<'\n';
  cout <<"Execusion time RADIXSORT base 10: "<<double(stop_b10-start_b10) / CLOCKS_PER_SEC <<"s"<<'\n';

  ///INSERTIONSORT
  arr=arr1;
  //cout << "Unsorted array: \n";
  //printArray(arr);
   start = clock();
  insertionSort(arr,n);
   stop = clock();
  //cout << "Sorted array: \n";
 // printArray(arr);
 if(verif_sort(arr,n)) cout<<"Insertionsort functioneaza"<<'\n';
 else cout<<"Insertionsort NU functioneaza pe acest exemplu"<<'\n';
  cout <<"Execusion time INSERTIONSORT: "<<double(stop-start) / CLOCKS_PER_SEC <<"s"<<'\n';

  cout<<endl;}

  return 0;


}
