#include <iostream>
#include<algorithm>

struct Job{
    char id;
    int dead;
    int profit;
};

bool comparision(Job a, Job b){
    return a.profit > b.profit;
}

void findBestJobs(Job *arr, int n);
bool slot[10000];
int result[10000];

int main(){
    int n,b,c;
    char a;
    std::cin >> n;
    Job arr[n];
    for(int i=0; i<n; i++){
        std::cin >> a >> b >> c;
        arr[i].id = a;
        arr[i].dead = b;
        arr[i].profit = c;
    }

    findBestJobs(arr, n);


    return 0;
}

void findBestJobs(Job *arr, int n){
    std::sort(arr, arr+n, comparision);
    int totalProfit = 0;
    for(int i=0; i<n; i++){
        for(int j=std::min(n, arr[i].dead)-1; j>=0 ; j--){
            if(!slot[j]){
                result[j] = i;
                slot[j] = true;
                totalProfit += arr[i].profit;
                break;
            }
        }
    }
    std::cout << "Total profit: " << totalProfit << std::endl;
    for(int i=0; i<n; i++){
        if(slot[i]){
            std::cout << arr[result[i]].id << " ";
        }
    }

}
