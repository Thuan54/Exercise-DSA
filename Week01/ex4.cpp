#include <iostream>
using namespace std;

// Calculate the number of moves required to solve the Tower of Hanoi problem
int towerOfHanoi(int n){
    //If there is only one or zero disk, return 1 or 0
    if(n < 2) return n;
    //Move the n-1 disks to the auxiliary rod
    //Move the last disk to the destination rod
    //Move the n-1 disks from the auxiliary rod to the destination rod
    //f(n) = f(n-1) + 1 + f(n-1)
    return 2*towerOfHanoi(n-1)+1;
}
int main(){
    int n;
    cin >> n;
    cout << towerOfHanoi(n);
    return 0;
}