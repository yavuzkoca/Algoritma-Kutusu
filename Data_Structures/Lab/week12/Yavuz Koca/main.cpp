#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Tree.h"

using namespace std;

Tree t;

int main(){
    srand(time(NULL));
    int n = rand() % 10+1;
    int arr[n];
    for(int i=0; i<n; i++)
        arr[i] = rand() % 100+1;
    for(int i=0; i<n; i++)
        cout << arr[i] << " ";
    cout << endl;
    // int n = sizeof(arr)/ sizeof(int);
    node* root = t.add_node(arr, root, 0, n);
    cout << "POST ORDER\n";
    t.print_post_order(root);
    cout << "PRE ORDER\n";
    t.print_pre_order(root);
    cout << "IN ORDER\n";
    t.print_in_order(root);

    cout << "max" << endl;
    cout << t.findMax(root) << endl;
    cout << "min" << endl;
    cout << t.findMin(root) << endl;
    cout << "number of nodes" << endl;
    cout << t.findNumNode(root) << endl;
    cout << "average" << endl;
    cout << t.calculateAverage(root,n) << endl;
    cout << "leaf number" << endl;
    cout << t.findNumLeaf(root) << endl;
    cout << endl;
    cout << t.calculateDepth(root);
//    cout << t.calculateDepth(root);
//    cout << endl;


    root = t.remove(root);
    // t.print_post_order(root);

    return 0;
}