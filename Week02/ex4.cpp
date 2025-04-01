#include <bits/stdc++.h>
using namespace std;
//Find the minimum capacity of a ship to carry all the weights within D days
int leastCapacity(int* weights, int n, int D){
    //Find the maximum weight and the total weight
    //The minimum capacity should be at least the maximum weight
    //The maximum capacity should be at most the total weight
    int left = -1, right = 0;
    for(int i = 0; i < n; i++){
        left = max(left, weights[i]);
        right += weights[i];
    }
    //Binary search the minimum capacity
    while(left < right){
        
        int mid = (left + right)/2;
        int days = 1, sum = 0;

        for(int i = 0; i < n; i++){
            //If can't carry the next package, increase the days and reset the sum
            if(sum + weights[i] > mid){
                days++;
                sum = 0;
            }
            //Carry the package
            sum += weights[i];
        }
        //If the days exceed the limit, that's mean the capacity is too small
        if(days > D) left = mid + 1;
        //Otherwise, the capacity is too big or just right
        else right = mid;
    }
    return left;
}

int main(){
    int n, D;
    cin >> n;
    int* weights = new int[n];
    for(int i = 0; i < n; i++){
        cin >> weights[i];
    }
    cin >> D;
    cout << leastCapacity(weights, n, D) << endl;
    delete[] weights;
    return 0;
}