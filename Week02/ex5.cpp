#include <bits/stdc++.h>
using namespace std;
//Find the minimum length of a contiguous subarray of which the sum is greater than or equal to the target
int minimumLength(int* arr,int n,int target){
    int left = 0, right = 0, sum = 0;
    //The minimum length should be at most the size of the array
    int minLength = n+1;

    while(right < n){
        //Add the element to the sum
        sum += arr[right];
        //Move the left pointer to the right until the sum is less than the target
        while(sum >= target){
            minLength = min(minLength, right - left+1);
            sum -= arr[left++];
        }
        right++;
    }
    //If the minLength is still the initial value, that's mean the target is not reachable
    //Return 0
    return minLength > n ? 0 : minLength;
}

int main(){
    int n, target;
    cin >> n;
    int* nums = new int[n];
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    cin >> target;
    cout << minimumLength(nums, n, target) << endl;
    delete[] nums;
    return 0;
}