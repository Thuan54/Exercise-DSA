#include <bits/stdc++.h>
using namespace std;

//Find the minimum element in a sorted rotated array
int findMinInSortedRotatedArray(int* arr, int n){

    int left = 0, right = n - 1;

    while(left < right){
        //If the array from left to right is already sorted, return the left element
        if(arr[left] < arr[right]){
            return arr[left];
        }

        int mid = (left+right) / 2;
        //If the mid element is less than or equal the right element, that's mean array from mid to right already sorted
        //right = mid mean the minimun could be the mid
        if(arr[mid] <= arr[right]){
            right = mid;
        } 
        //left = mid + 1 mean the minimum is in from mid + 1 to right
        else{
            left = mid + 1;
        }
    }
    return arr[left];
}
int main(){
    int n;
    cin >> n;
    int* arr = new int[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    cout << findMinInSortedRotatedArray(arr, n) << endl;
    delete[] arr;
    return 0;
}