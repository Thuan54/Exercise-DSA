#include <iostream>
using namespace std;

// Calculate the factorial of n
int factorial(int n){
    //0! = 1
    if(n == 0) return 1;
    //n! = n*(n-1)!
    return n*factorial(n-1);
}
int main(){
    int n;
    cin >> n;
    cout << factorial(n);
    return 0;
}