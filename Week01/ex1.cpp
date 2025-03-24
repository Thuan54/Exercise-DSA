#include <iostream>
using namespace std;

// Calculate the n-th Fibonacci number
int fibonacci(int n, int* cache){
    //fibonacci(0) = 0
    //fibonacci(1) = 1
    if(n<=1) return n;
    // If the value of fibonacci(n) is already calculated, return it
    if(cache[n]!=-1) return cache[n];
    //fibonacci(n) = fibonacci(n-1) + fibonacci(n-2)
    cache[n] = fibonacci(n-1, cache)+fibonacci(n-2, cache);
    return cache[n];
}
int main(){
    int n;
    cin >> n;
    int* cache = new int[n+1];
    for(int i=0; i<n; i++) cache[i] = -1;
    cache[0] = 0;
    cache[1] = 1;
    fibonacci(n-1, cache);
    // Print the values of the cache array
    for(int i=0; i<n; i++){
        cout << cache[i] << " ";
    }
    
    delete[] cache;
    return 0;
}