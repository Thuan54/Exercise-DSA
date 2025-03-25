#include <iostream>
using namespace std;

// Generate all binary strings of length n
void generateBinaryString(string& s,int i){
    // If the length of the string is n, print it
    if(i == s.size()){
        cout << s << endl;
        return;
    }
    // Choose '0' to the string
    s[i] = '0';
    // Generate all binary strings of length n-1
    generateBinaryString(s,i+1);
    // Choose '1' to the string
    s[i] = '1';
    // Generate all binary strings of length n-1
    generateBinaryString(s,i+1);
}
int main(){
    int n;
    cin >> n;
    
    string s(n,'0');
    generateBinaryString(s,0);
    return 0;   
}