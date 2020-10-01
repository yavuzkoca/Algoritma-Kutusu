#include <iostream>
using namespace std;

int binarySearch(int arr[], int l, int r, int x) {
    if (r >= l) {
        int mid = l + (r - l)/2;

        if (arr[mid] == x) return mid;

        if (arr[mid] > x) return binarySearch(arr, l, mid-1, x);

        return binarySearch(arr, mid+1, r, x);
    }

    return -1;
}

int binarySearch(int arr[], int n, int x) {
    return binarySearch(arr, 0, n-1, x); 
}

int main(){

}
