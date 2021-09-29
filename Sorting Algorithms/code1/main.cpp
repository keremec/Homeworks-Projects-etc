#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Array {
private:
	int capacity;
	int size;
	int* arr;
	
	// useful functions
	void deleteitem(int index) {
		for (int i = index; i <= size - 2; i++) {
			arr[i] = arr[i + 1];
		}
		size--;
	}
	int findit(int number, int start = 0) {
		for (; start <= size - 1; start++) {
			if (arr[start] == number) {
				return start;
			}
		}
		return -1;
	}
	void reallocate() {
		int* temparr = new int[capacity];
		for (int i = 0; i <= size - 1; i++) {
			temparr[i] = arr[i];
		}
		delete[]arr;
		arr = temparr;
	}

public:
	//Array Operations
	Array(int cap) {
		capacity = cap;
		arr = new int[capacity];
		//cout << "new int array created with capacity " << capacity << endl << endl;
	}
	void cleaner() {
		delete[]arr;
	}
	void addItem(int a) {
		if (size + 1 > capacity) {
			capacity *= 2;
			reallocate();
		}
		arr[size] = a;
		size++;
	}
	void removeIndexItem(int a) {
		if (a <= size - 1 && a >= 0) {
			deleteitem(a);
			//cout << "Item is succesfully deleted" << endl << endl;
		}
		else {
			//cout << "ERROR No item at the index " << a << endl << endl;
		}
	}
	void removeItem(int a) {
		int control = 0;
		int counter = 0;
		while (control != -1) {
			control = findit(a, control);
			if (control != -1) {
				deleteitem(control);;
				counter++;
			}
		}

		cout << counter << " items (" << a << ") are deleted from the Array" << endl << endl;
	}
	void printItems(int stats = 0) {
		for (int i = 0; i < size; i++) {
			cout << arr[i] << "-";
		}
		cout << endl;
		if (stats == 1) {
			cout << "capacity=" << capacity << " size=" << size << endl;
		}
		cout <<endl;
	}
	void fillrandomnums(int max = 100) {
		srand(time(NULL));
		for (int i = 0; i <= capacity - 1; i++) {
			int num = rand() % 100;
			addItem(num);
		}
	}

	//Sort Algorithms
private:
	void swap(int a, int b) {
		int temp;
		temp = arr[a];
		arr[a] = arr[b];
		arr[b] = temp;
	}
	int partition(int min, int max) {
		int pivot = arr[max];
		int i = (min - 1);
		for (int j = min; j <= max - 1; j++) {
			if (arr[j] < pivot) { i++; swap(i, j); }
		}
		swap(i + 1, max);
		return (i + 1);
	}
	int merge(int l, int m, int r) {
		int i, j, k; int ctr = 0;
		int n1 = m - l + 1; int n2 = r - m;
		Array L(n1); Array R(n2);
		for (i = 0; i < n1; i++) {
			L.arr[i] = arr[l + i];
		}
		for (j = 0; j < n2; j++) {
			R.arr[j] = arr[m + 1 + j];
		}
		i = 0;
		j = 0;
		k = l;
		while (i < n1 && j < n2) {
			if (L.arr[i] <= R.arr[j]) {
				arr[k] = L.arr[i];
				i++;
			}
			else {
				arr[k] = R.arr[j];
				j++;
			}
			k++; ctr++;
		}
		while (i < n1) {
			arr[k] = L.arr[i];
			i++;
			k++;
		}
		while (j < n2) {
			arr[k] = R.arr[j];
			j++;
			k++;
		}
		delete[] L.arr;
		delete[] R.arr;
		return ctr;
	}
	int heapify(int n, int i) {
		int ctr = 0;
		int largest = i; int l = 2 * i + 1; int r = 2 * i + 2;
		if (l < n) { if (arr[l] > arr[largest]) { largest = l; ctr++; } }
		if (r < n) { if (arr[r] > arr[largest]) { largest = r; ctr++; } }
		if (largest != i) {
			swap(i, largest);
			ctr += heapify(n, largest);
		}
		return ctr;
	}
public:
	//quick sort "quickSort(0, n-1)"
	int quickSort(int min, int max) {
		int ctr = 0;
		if (min < max) {
			ctr += max - min;
			int pi = partition(min, max);
			ctr += quickSort(min, pi - 1);
			ctr += quickSort(pi + 1, max);
		}
		return ctr;
	}
	//merge sort "mergeSort(0, n-1)"
	int mergeSort(int l, int r) {
		int ctr = 0;
		if (l < r) {
			int m = l + (r - l) / 2;
			ctr += mergeSort(l, m);
			ctr += mergeSort(m + 1, r);
			ctr += merge(l, m, r);
		}
		return ctr;
	}
	// heap sort "heapSort(n)"
	int heapSort(int n) {
		int ctr = 0;
		for (int i = n / 2 - 1; i >= 0; i--) {
			ctr += heapify(n, i);
		}
		for (int i = n - 1; i >= 0; i--) {
			swap(0, i);
			ctr += heapify(i, 0);
		}
		return ctr;
	}
};

int main() {
	int n; int m;
	cout << "Please enter lenght of array: ";	cin >> n;
	Array a(n);
	a.fillrandomnums();
	cout << endl; a.printItems(0);
	cout << "Please select the sort algorithm:" << endl << "1.Quick Sort\n2.Merge Sort\n3.Heap Sort\n\n";

Start:
	cout << ">"; cin >> m;
	switch (m) {
	case 1: cout << a.quickSort(0, n - 1) << " comparisons made" << endl; a.printItems();
		break;
	case 2: cout << a.mergeSort(0, n - 1) << " comparisons made"<< endl; a.printItems();
		break;
	case 3: cout << a.heapSort(n) << " comparisons made" << endl; a.printItems();
		break;
	default: cout << "Wrong input, try again\n";
		goto Start;
	}

	a.cleaner();
	return 0;
}