#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Node
{
    int data;
    Node* next;
    Node(int data):data(data),next(nullptr){}
};

struct Queue{
    int size;
    Node* front;
    Node* back;
    Queue():size(0),front(nullptr),back(nullptr){}
    void enqueue(int data){
        Node* node = new Node(data);
        if(!this->front){
            this->front = node;
            this->back = node;
        }
        else{
            this->back->next = node;
            this->back = node;
        }
        size++;
    }
    int dequeue(){
        if(size == 0) return INT_MIN;
        if(size == 1) this->back = nullptr;
        int temp = this->front->data;
        Node* temp2 = this->front;
        this->front = this->front->next;
        delete temp2;
        size--;
        return temp;
    }
    int isEmpty(){
        return this->size == 0;
    }
    ~Queue(){
        while(this->front){
            this->dequeue();
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
    Queue* queue = nullptr;
    while(!inputFile.eof()){
        string word;
        inputFile>>word;
        tolower(word);
        bool isCorrectWord = false;
        if(word == "init" || !queue){
            queue = new Queue;
            isCorrectWord = true;
        }
        else if(word == "enqueue"){
            int data;
            inputFile>>data;
            queue->enqueue(data);
            isCorrectWord = true;
        }
        else if(word == "dequeue"){
            queue->dequeue();
            isCorrectWord = true;
        }
        else if(word == "size"){
            isCorrectWord = true;
        }
        else if(word == "isempty"){
            queue->isEmpty();
            isCorrectWord = true;
        }
        if(isCorrectWord&&queue->isEmpty()){
            outputFile<<"EMPTY"<<endl;
        }
        else if(isCorrectWord){
            Node* curr = queue->front;
            while(curr){
                outputFile<<curr->data<<" ";
                curr = curr->next;
            }
            outputFile<<endl;
        }
    }

    if(queue) delete queue;
    inputFile.close();
    outputFile.close();
}