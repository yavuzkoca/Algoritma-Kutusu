#include <iostream>
#include "Tree.h"

using namespace std;

Tree t;

int main(){
    int arr[] = {1,2,3,4,5,6,7,99};
    int n = sizeof(arr)/ sizeof(int);
    node* root = t.add_node(arr, root, 0, n);
    // t.print_post_order(root);

    cout << t.findMax(root) << endl;
    // cout << t.findMin(root) << endl;
    // cout << t.findNumNode(root) << endl;
    // cout << t.calculateAverage(root,n) << endl;

    root = t.remove(root);
    // t.print_post_order(root);

    return 0;
}