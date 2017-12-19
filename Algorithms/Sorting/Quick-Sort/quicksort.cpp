#include <iostream>
#include <random>

using namespace std;

int partition(int *arr, int beg, int end){

	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(beg, end);

	int pivot_index = dist(gen);
	int pivot = arr[pivot_index];

	int lil, big, temp;

	arr[pivot_index] = arr[beg];
	arr[beg] = pivot;

	lil = beg + 1;
	big = end;

	while(lil != big){
		if(arr[lil] < pivot){
			++lil;
		}
		else{
			temp = arr[lil];
			arr[lil] = arr[big];
			arr[big] = temp;
			--big;
		}
	}
	if(arr[lil] > pivot){
		--big;
		--lil;
	}
	arr[beg] = arr[lil];
	arr[lil] = pivot;
	return lil;
}

void qckSort(int *arr, int beg, int end){
	if(beg < end){
		int pivot_index = partition(arr, beg, end);
		qckSort(arr, beg, pivot_index - 1);
		qckSort(arr, pivot_index + 1, end);
	}
}

int main(){

	mt19937 gen;
	gen.seed(random_device()());
	uniform_int_distribution<mt19937::result_type> dist(0,99999);

	int lenght;
	cin >> lenght;

	int *array = new int[lenght];

	for(int i = 0; i < lenght; ++i)
		array[i] = dist(gen);;

	qckSort(array, 0, lenght - 1);

	for(int i = 0; i < lenght; ++i)
		cout << array[i] << endl;

	return 0;
}