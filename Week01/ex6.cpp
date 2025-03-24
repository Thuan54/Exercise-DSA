#include <iostream>
using namespace std;

// Find all solutions
int findSol(int r,int n, bool* cols, bool* posDiag, bool* negDiag){
    // If all the queens are placed, save the solution
    if(r == n){
        return 1;
    }
    int sols = 0;
    // Place the queen in the current row and column if it is safe
    for(int i=0; i < n; i++){
        // Check if the column, positive diagonal, and negative diagonal are occupied
        if(cols[i] || posDiag[r+i] || negDiag[r-i+n-1]){
            continue;
        }
        // Mark the column, positive diagonal, and negative diagonal as occupied
        cols[i] = true;
        posDiag[r+i] = true;
        negDiag[r-i+n-1] = true;
        // Move to the next row
        sols += findSol(r+1,n,cols,posDiag,negDiag);
        // Unmark the column, positive diagonal, and negative diagonal as occupied
        cols[i] = false;
        posDiag[r+i] = false;
        negDiag[r-i+n-1] = false;
    }
    return sols;
}
// Find all solutions of the N-Queen
int N_Queen(int n){

    // Initialize the columns, positive diagonals, and negative diagonals
    // Save to check if they are occupied
    bool* cols = new bool[n];
    bool* posDiag = new bool[2*n-1];
    bool* negDiag = new bool[2*n-1];

    for(int i=0; i<n; i++){
        cols[i] = false;
    }

    for(int i = 0; i< 2*n-1; i++){
        posDiag[i] = false;
        negDiag[i] = false;
    }
   
    // Find all solutions
    return findSol(0,n,cols,posDiag,negDiag);

    delete[] cols;
    delete[] posDiag;
    delete[] negDiag;
}
int main(){
    int n;
    cin >> n;

    int sols = N_Queen(n);
    cout << sols << endl;
    return 0;
}