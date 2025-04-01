#include <bits/stdc++.h>
using namespace std;
//Search through every element in the array to find the element x
int linearSearchWithSetinel(int* arr, int n, int x){
    //Put the element x at the end of the array
    arr[n] = x;
    int i = 0;
    //Search through the array until the element x is found
    while(arr[i] != x){
        i++;
    }
    //If the index i equal to n, then the element x is not in the original array
    if(i < n){
        return i;
    }
    return -1;
}
int main(){
    int n;
    cin >> n;
    int* arr = new int[n + 1];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int x;
    cin >> x;
    cout << linearSearchWithSetinel(arr, n, x) << endl;
    return 0;
}