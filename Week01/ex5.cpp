#include <iostream>
using namespace std;

// Check if the array is sorted in ascending order
bool isSorted(int* arr, int n, int i){
    // If the last element is reached, return true
    if(i == n-1) return true;
    // If the current element is greater than the next element, return false
    if(arr[i] > arr[i+1]) return false;
    // Check the next element
    return isSorted(arr, n, i+1);
}
int main(){
    int n;
    cin >> n;
    int* arr = new int[n];
    for(int i=0; i<n; i++){
        cin >> arr[i];
    }

    if(n == 0){
        cout << "No need to check on an empty array";
        return 0;
    }
    if(isSorted(arr,n,0)){
        cout << "YES";
    }else{
        cout << "NO";
    }

    delete[] arr;
    return 0;
}