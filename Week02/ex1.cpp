#include <bits/stdc++.h>
using namespace std;

//Search through every element in the array to find the element x
//Return the index of the element if found, otherwise return -1
int linearSearch(int* arr, int n, int x){
    for(int i = 0; i < n; i++){
        if(arr[i] == x){
            return i;
        }
    }
    return -1;
}
int main(){
    int n;
    cin >> n;
    int* arr = new int[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    int x;
    cin >> x;
    cout << linearSearch(arr, n, x) << endl;
    delete[] arr;
    return 0;
}