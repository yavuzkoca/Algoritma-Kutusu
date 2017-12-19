// Vahit Bugra Yesilkaynak @2017

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000000

void merge(int *, int, int, int, int);

void mrgsort(int *arr, int beg, int end){
	int mid;
	if(beg < end){
		mid = (beg + end) / 2;
		mrgsort(arr, beg, mid);
		mrgsort(arr, mid+1, end);
		merge(arr, beg, mid, mid+1, end);
	}
}

void merge(int *arr, int beg, int mid1, int mid2, int end){
	int first_counter = beg;
	int second_counter = mid2;
	int global_counter = 0;
	int *temp = (int *)malloc(sizeof(int) * (end - beg + 1));
	while( first_counter <= mid1 && second_counter <= end){
		if( *(arr + first_counter) > *(arr + second_counter) ){
			*(temp + global_counter) = *(arr + first_counter);
			++first_counter;
		}
		else{
			*(temp + global_counter) = *(arr + second_counter);
			++second_counter;
		}
		++global_counter;
	}
	if(first_counter == mid2){
		for(int i = beg; i < second_counter; ++i){
			*(arr + i) = *(temp + i - beg);
		}
	}
	else{
		for(int i = first_counter; i <= mid1; ++i){
			*(temp + global_counter + i - first_counter) = *(arr + i);
		}
		for(int i = beg; i <= end; ++i){
			*(arr + i) = *(temp + i - beg);
		}
	}
}

int main(){
	srand(time(NULL));   // should only be called once
	int r = rand(); 
	int *array = (int *)malloc(sizeof(int) * SIZE);
	for(int i = 0; i < SIZE; ++i) *(array + i) = rand() % 1000;
	mrgsort(array, 0, SIZE - 1);
	for(int i = 0; i < SIZE; ++i) printf("%d. %d\n", i + 1, *(array + i));
}
