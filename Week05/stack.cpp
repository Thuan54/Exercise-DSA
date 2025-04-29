#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Node
{
    int data;
    Node* next;
    Node(int data):data(data),next(nullptr){}
};
struct Stack
{
    int size;
    Node* top;
    Stack():size(0),top(nullptr){}
    void push(int data){
        Node* node = new Node(data);
        node->next = this->top;
        this->top = node;
        size++;
    }
    int pop(){
        if(this->size == 0) return INT_MIN;
        int temp = this->top->data;
        Node* temp2 = this->top;
        this->top = this->top->next;
        delete temp2;
        size--;
        return temp;
    }
    bool isEmpty(){
        return this->size == 0;
    }
    ~Stack(){
        while(this->top){
            this->pop();
        }
    }
};
void tolower(string& word){
    for(int i=0; i<word.size();i++){
        word[i] = tolower(word[i]);
    }
}
int main(){
    string inputFileName = "input.txt";
    string outputFileName = "output.txt";
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    
    if(!inputFile.is_open() || !outputFile.is_open()){
        cerr<<"Error opening file!"<<endl;
        return -1;
    }
    Stack* stack = nullptr;
    while(!inputFile.eof()){
        string word;
        inputFile>>word;
        tolower(word);
        bool isCorrectWord = false;
        if(word == "init" || !stack){
            stack = new Stack;
            isCorrectWord = true;
        }
        else if(word == "push"){
            int data;
            inputFile>>data;
            stack->push(data);
            isCorrectWord = true;
        }
        else if(word == "pop"){
            stack->pop();
            isCorrectWord = true;
        }
        else if(word == "size"){
            isCorrectWord = true;
        }
        else if(word == "isempty"){
            stack->isEmpty();
            isCorrectWord = true;
        }
        if(isCorrectWord&&stack->isEmpty()){
            outputFile<<"EMPTY"<<endl;
        }
        else if(isCorrectWord){
            Stack s;
            Node* curr = stack->top;
            while(curr){
                s.push(curr->data);
                curr = curr->next;
            }
            curr = s.top;
            while(curr){
                outputFile<<curr->data<<" ";
                curr = curr->next;
            }
            outputFile<<endl;
        }
    }

    if(stack) delete stack;
    inputFile.close();
    outputFile.close();
}