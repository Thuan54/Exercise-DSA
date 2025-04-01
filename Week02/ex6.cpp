#include <bits/stdc++.h>
using namespace std;
//Check if there are two elements in the array that sum up to the target
//The array is sorted
bool isContainTwoSum(int* arr, int n, int target){
    //Two pointers
    int l = 0;
    int r = n -1;

    while(l < r){
        //If the sum of the two elements is equal to the target, return true
        if(arr[l] + arr[r] == target){
            return true;
        }
        //If the sum is less than the target, move the left pointer to the right
        else if(arr[l] + arr[r] < target){
            l++;
        }
        //If the sum is greater than the target, move the right pointer to the left
        else{
            r--;
        }
    }
    return false;
}
int main(){
    int n, target;
    cin >> n;
    int* arr = new int[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    //Sort the array
    for(int i = 0; i < n;i++){
        for(int j = i+1;j<n;j++){
            if(arr[i]>arr[j]){
                int temp = arr[i];
                arr[i ]= arr[j];
                arr[j] = temp;
            }
        }
    }
    cin >> target;
    if(isContainTwoSum(arr, n, target)){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
    delete[] arr;    
    return 0;
}