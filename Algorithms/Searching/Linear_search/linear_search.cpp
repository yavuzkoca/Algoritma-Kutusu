#include <iostream>
using namespace std;

int linearSearch(int *array, int size, int key)
{
	for(int i=0; i < size; i++)
		if(array[i] == key)
			return i;
	return -1;
}


int main(){

}
