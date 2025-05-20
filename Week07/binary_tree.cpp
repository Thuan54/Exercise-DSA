#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

NODE* createNode(int data){
    NODE* node = new NODE;
    node->key = data;
    node->p_left = nullptr;
    node->p_right = nullptr;
    return node;
}

vector<int> NLR(NODE* pRoot){
    stack<NODE*> s;
    vector<int> res;
    if(pRoot) s.push(pRoot);
    while(!s.empty()){
        NODE* node = s.top();
        s.pop();
        res.push_back(node->key);
        if(node->p_right) s.push(node->p_right);
        if(node->p_left) s.push(node->p_left);
    }
    return res;
}

vector<int> LNR(NODE* pRoot){
    stack<NODE*> s;
    vector<int> res;
    NODE* curr = pRoot;
    while(!s.empty() || curr){
        while(curr){
            s.push(curr);
            curr = curr->p_left;
        }
        curr = s.top();
        s.pop();
        res.push_back(curr->key);
        curr = curr->p_right;
    }
    return res;
}

vector<int> LRN(NODE* pRoot){
    stack<NODE*> s;
    vector<int> res;
    NODE* curr = pRoot;
    while(!s.empty() || curr){
        while(curr){
            s.push(curr);
            s.push(curr);
            curr = curr->p_left;
        }
        if(s.empty()) break;
        curr = s.top();
        s.pop();
        if(!s.empty()&&curr == s.top()){
            curr = curr->p_right;
        }
        else{
            res.push_back(curr->key);
            curr = nullptr;
        }

    }
    return res;
}

vector<vector<int>> LevelOrder(NODE* pRoot){
    queue<NODE*> q;
    vector<vector<int>> res;
    if(pRoot) q.push(pRoot);
    while(!q.empty()){
        int size = q.size();
        vector<int> v;
        for(int i = 0; i < size;i++){
            NODE* node = q.front();
            q.pop();
            if(node->p_left) q.push(node->p_left);
            if(node->p_right) q.push(node->p_right);
            v.push_back(node->key);
        }
        res.push_back(v);
    }
    return res;
}

int countNode(NODE* pRoot){
    if(!pRoot) return 0;
    int left = countNode(pRoot->p_left);
    int right = countNode(pRoot->p_right);
    return left + right + 1;
}

int sumNode(NODE* pRoot){
    if(!pRoot) return 0;
    int left = sumNode(pRoot->p_left);
    int right = sumNode(pRoot->p_right);
    return left + right + pRoot->key;
}

int heightNode(NODE* pRoot, int value){
    int height = -1;
    queue<NODE*> q;
    if(pRoot) q.push(pRoot);
    while(!q.empty()){
        int size = q.size();
        for(int i= 0;i <size;i++){
            NODE* node = q.front();
            q.pop();
            if(node->p_left) q.push(node->p_left);
            if(node->p_right) q.push(node->p_right);
            if(node->key == value) height = 0;
        }
        if(height != -1) height++;
    }
    return height != -1 ? height -1:-1;
}

int Level(NODE* pRoot, NODE* p){
    int level = -1;
    bool found = false;
    queue<NODE*> q;
    if(pRoot) q.push(pRoot);
    while (!q.empty())
    {
        int size = q.size();
        for(int i = 0; i < size; i++){
            NODE* node = q.front();
            q.pop();
            if(node->p_left) q.push(node->p_left);
            if(node->p_right) q.push(node->p_right);
            if(node->key == p->key){
                while(!q.empty()) q.pop();
                found = true;
                break;
            }
        }
        level++;
    }
    return !found ? -1: level;
}

int countLeaf(NODE* pRoot){
    if(!pRoot) return 0;
    int left = countLeaf(pRoot->p_left);
    int right = countLeaf(pRoot->p_right);
    if(left == 0 && right == 0) return 1;
    return left + right;
}