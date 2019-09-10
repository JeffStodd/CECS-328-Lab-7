/*
Jeffrey Stoddard
CECS 328
Lab 7
*/

#include <iostream>
#include <algorithm>
#include <cmath>
#include <chrono>

int *arr;
long int size = 0; //n
int k = 0;

//Initializes array with size from user input
void InitArray()
{
	std::cout << "Please enter a positive integer for the array size: ";
	std::cin >> size;
	arr = new int[size];
}

//Prints array
void printArray(int arr[])
{
	for (int i = 0; i < size; i++)
	{
		std::cout << i << "[" << arr[i] << "] ";
	}
	std::cout << std::endl;
}

//generates -5000 through 5000 in arr
void populateArray()
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 41 - 20;
	}
}

//Swap utility function for integers
void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

//quick sort implementation
void quickSort(int a[], int left = 0, int right = size, bool ascending = true)
{
	//base case
	if ((right - left) <= 1)
		return;

	int pivot = a[right - 1]; //pivot = last element

	int lower = left - 1; //counter of elements less than pivot
	//iterate from left to element just before pointer
	for (int i = left; i < right - 1; i++)
	{
		if (ascending == true) //sort the list ascending
		{
			if (a[i] <= pivot)
			{
				//swap current selection with first element after lower elements
				lower++;
				int temp = a[i];
				a[i] = a[lower];
				a[lower] = temp;
			}
		}
		else //sort the list descending
		{
			if (a[i] >= pivot)
			{
				//swap current selection with first element after lower elements
				lower++;
				int temp = a[i];
				a[i] = a[lower];
				a[lower] = temp;
			}
		}
	}
	//swap last element (pivot) with the first element larger than the pivot
	lower++;
	int temp = a[right - 1];
	a[right - 1] = a[lower];
	a[lower] = temp;

	quickSort(a, left, lower, ascending); //q sort from left pointer to lower pointer
	quickSort(a, lower, right, ascending); //q sort from lower to right pointer
}

int MPSS(int a[], int left = 0, int right = size)
{
	
	if (right - left <= 1)
	{
		int r = a[left];
		if (r <= 0)
			return INT_MAX;
		else return r;
	}

	int middle = (right + left) / 2;

	std::cout << left << " | " << middle << " | " << right << std::endl;
	/*
	int lsum = 0;
	int rsum = 0;

	for (int i = 0; i < right; i++)
	{
		if (i < middle)
			lsum += a[i];
		else rsum += a[i];
	}
	*/

	quickSort(a, left, middle);
	quickSort(a, middle, right, false);

	printArray(a);
	//system("pause");

	int i = left;
	int j = middle;

	int min = INT_MAX;

	while ((i < middle) && (j < right))
	{
		int s = a[i] + a[j];
		if (s <= 0)
		{
			i++;
		}
		else if (s < min)
		{
			min = s;
			j++;
		}
		else
		{
			j++;
		}
	}

	int MPSS_mid = min;

	//int localMin = std::min(std::min(lsum, rsum), MPSS_mid);
	return std::min(std::min(MPSS(a, left, middle), MPSS_mid), MPSS(a, middle, right));
}

int main()
{
	//seed from clock
	srand(time(NULL));

	InitArray();
	populateArray();

	printArray(arr);

	std::cout << std::endl<< MPSS(arr) << std::endl;
	system("pause");
	return 0;
}