#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* Search(NODE* pRoot, int x){
    NODE* curr = pRoot;
    while(curr){
        if(curr->key == x) return curr;
        if(curr->key < x) curr = curr->p_right;
        else curr = curr->p_left;
    }
    return curr;
}

void Insert(NODE*& pRoot, int x){
    if(!pRoot){
        NODE* node = new NODE;
        node->key = x;
        node->p_left = nullptr;
        node->p_right = nullptr;
        pRoot = node;
        return;
    }
    if(pRoot->key < x){
        Insert(pRoot->p_right,x);
    }
    else if(pRoot->key > x){
        Insert(pRoot->p_left,x);
    }
}

void Remove(NODE*& pRoot, int x){
    NODE*& curr = pRoot;
    if(!curr) return;
    if(curr->key < x)
        Remove(curr->p_right,x);
    else if(curr->key > x)
        Remove(curr->p_left,x);
    else{
        if(!curr->p_left && !curr->p_right){
            delete curr;
            curr = nullptr;
        }
        else if(!curr->p_right){
            NODE* temp = curr;
            curr = curr->p_left;
        }
        else{
            NODE* leftMost = curr->p_right;
            while(leftMost->p_left){
                leftMost = leftMost->p_left;
            }
            curr->key = leftMost->key;
            Remove(curr->p_right,leftMost->key);
        }
    }
}

NODE* createTree(int a[], int n){
    NODE* root = nullptr;
    for(int i = 0; i < n; i++){
        Insert(root,a[i]);
    }
    return root;
}

void removeTree(NODE*& pRoot){
    if(!pRoot) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

int Height(NODE* pRoot){
    if(!pRoot) return -1;
    int left = Height(pRoot->p_left);
    int right = Height(pRoot->p_right);
    return max(left,right) + 1;
}

int countLess(NODE* pRoot, int x){
    if(!pRoot) return 0;
    int res = countLess(pRoot->p_left,x);

    if(pRoot->key < x){
        res += countLess(pRoot->p_right,x);
    }

    if(pRoot->key < x) res += 1;
    return res;
}

int countGreater(NODE* pRoot, int x){
    if(!pRoot) return 0;
    int res = countGreater(pRoot->p_right,x);
    
    if(pRoot->key > x){
        res += countGreater(pRoot->p_left,x);
    }
    
    if(pRoot->key > x) res += 1;
    return res;
}

bool isBST(NODE* pRoot){
    stack<NODE*> s;
    vector<int> v;
    NODE* curr = pRoot;
    while(!s.empty()||curr){
        while (curr){
            s.push(curr);
            curr = curr->p_left;
        }
        curr = s.top();
        s.pop();
        if(!v.empty() && v.back() >= curr->key) return false;
        v.push_back(curr->key);
        curr = curr->p_right;
    }
    return true;
}

bool isFullBST(NODE* pRoot){
    if(!isBST(pRoot)) return false;
    queue<NODE*> q;
    if(pRoot) q.push(pRoot);
    while(!q.empty()){
        int size = q.size();
        for(int i = 0; i < size; i++){
            NODE* node = q.front();
            q.pop();
            if(node->p_left && node->p_right){
                q.push(node->p_left);
                q.push(node->p_right);
            }
            else if(!node->p_left && !node->p_right){
                continue;
            }
            else return false;
        }
    }
    return true;
}