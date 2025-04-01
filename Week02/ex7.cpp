#include <bits/stdc++.h>
using namespace std;
//Return all unique triplets that sum up to 0
vector<vector<int>> ThreeSum(int* arr, int n){
    //Store the result
    vector<vector<int>> res;
    //Choose the first element
    //n-2 mean the second element and the third element
    for(int i = 0; i < n-2;i++){
        //Skip the duplicate element
        //If the first element is the same could result in the same result
        if(i > 0 && arr[i] == arr[i-1]) continue;
        //Choose the second element and the third element
        int l = i+1, r = n-1;
        
        while(l<r){
            int sum = arr[i] + arr[l] + arr[r];
            //If the sum is less than 0, increase the left pointer
            if(sum < 0) l++;
            //If the sum is greater than 0, decrease the right pointer
            else if(sum > 0) r--;
            //If the sum is equal to 0, store the result
            else{
                res.push_back({arr[i], arr[l], arr[r]});
                l++;
                r--;
                //Skip the duplicate element
                //We could skip l or r, but if we skip r, could lead to out of bounds
                while(l < r && arr[l] == arr[l-1]) l++;
            }
        }
    }
    return res;
}

int main(){
    int n;
    cin>>n;
    int* arr = new int[n];
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    //Sort the array
    for(int i = 0; i < n; i++){
        for(int j = i+1; j <n ;j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    vector<vector<int>> result = ThreeSum(arr, n);
    for(int i = 0; i < result.size(); i++){
        cout<<'[';
        for(int j = 0; j < result[0].size();j++){
            cout<<result[i][j]<<" ";
        }
        cout<<"] ";
    }

    delete[] arr;
    return 0;
}