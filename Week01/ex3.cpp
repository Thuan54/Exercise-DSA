#include <iostream>
using namespace std;

// Generate all binary strings of length n
void generateBinaryString(int n, string& s){
    // If the length of the string is n, print it
    if(s.size() == n){
        cout << s << endl;
        return;
    }
    // Append '0' to the string
    s.push_back('0');
    // Generate all binary strings of length n-1
    generateBinaryString(n, s);
    // Remove the '0' just added
    s.pop_back();
    // Append '1' to the string
    s.push_back('1');
    // Generate all binary strings of length n-1
    generateBinaryString(n, s);
    // Remove the '1' just added
    s.pop_back();
}
int main(){
    int n;
    cin >> n;
    string s;
    generateBinaryString(n, s);
    return 0;   
}