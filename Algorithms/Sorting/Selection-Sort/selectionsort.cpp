#include <iostream>
#include <vector>

using namespace std;

void swapElements(int first, int second, vector<int> &cont){
    int tmp = cont[first];
    cont[first] = cont[second];
    cont[second] = tmp;
}

void selectionSort(vector<int> &cont){
    int minEl = cont[0];
    int minIdx = 0;
    
    for(int i=0; i < cont.size()-1; i++){
        minEl = cont[i];
        minIdx = i;
        for (int j=i+1; j < cont.size(); j++){
            if (minEl > cont[j]){
                minEl = cont[j];
                minIdx = j;
            }
        }
        swapElements(i, minIdx, cont);
    }
}

int main(){

	int n, x; 
    cout << "Enter the number of elements: ";
    cin >> n;
    vector<int> arr;
    
    for(int i = 0; i < n; ++i){
		cin >> x;
        arr.push_back(x);
    }

    cout << "Array: ";
    for(int i = 0; i < n; ++i)
		cout << arr[i] << " ";
    
    selectionSort(arr);

    cout << endl <<"After sort " << endl;
    for(int i = 0; i < n; ++i)
		cout << arr[i] << " ";
	
	return 0;
}
