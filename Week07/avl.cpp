#include <vector>
#include <stack>
using namespace std;
struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};

NODE* createNode(int data){
    NODE* node = new NODE;
    node->key = data;
    node->height = 1;
    node->p_left = nullptr;
    node->p_right = nullptr;
    return node;
}
int height(NODE* node){
    if(!node) return 0;
    return node->height;
}
NODE* rightRotation(NODE* node){
    if(!node || !node->p_left) return node;
    NODE* left = node->p_left;

    node->p_left = left->p_right;
    left->p_right = node;

    node->height = 1 + max(height(node->p_left), height(node->p_right));
    left->height = 1 + max(height(left->p_left), height(left->p_right));
    return left;
}
NODE* leftRotation(NODE* node){
    if(!node || !node->p_right) return node;
    NODE* right = node->p_right;
    
    node->p_right = right->p_left;
    right->p_left = node;

    node->height = 1 + max(height(node->p_left), height(node->p_right));
    right->height = 1 + max(height(right->p_left), height(right->p_right));
    return right;
}
int getBal(NODE* node){
    if(!node) return 0;
    return height(node->p_left) - height(node->p_right);
}
void Insert(NODE*& pRoot, int x){
    if(!pRoot){
        NODE* node = createNode(x);
        pRoot = node;
        return;
    }
    if(pRoot->key < x) Insert(pRoot->p_right,x);
    else if(pRoot->key > x) Insert(pRoot->p_left,x);
    else return;

    pRoot->height = 1 + max(height(pRoot->p_left), height(pRoot->p_right));
    int bal = getBal(pRoot);
    
    if(bal > 1 && pRoot->p_left->key > x){
        pRoot = rightRotation(pRoot);
    }
    else if(bal > 1 && pRoot->p_left->key < x){
        pRoot->p_left = leftRotation(pRoot->p_left);
        pRoot = rightRotation(pRoot);
    }
    else if(bal < -1 && pRoot->p_right->key < x){
        pRoot = leftRotation(pRoot);
    }
    else if(bal < -1 && pRoot->p_right->key > x){
        pRoot->p_right = rightRotation(pRoot->p_right);
        pRoot = leftRotation(pRoot);
    }
    return;
}

void Remove(NODE*& pRoot, int x){
    if(!pRoot) return;
    if(pRoot->key < x) {
        Remove(pRoot->p_right,x);
    }
    else if(pRoot->key > x){
        Remove(pRoot->p_left,x);
    }
    else{
        if(!pRoot->p_left && !pRoot->p_right){
            delete pRoot;
            pRoot = nullptr;
        }
        else if(!pRoot->p_right){
            NODE* temp = pRoot;
            pRoot = pRoot->p_left;
            delete temp;
        }
        else{
            NODE* leftMost = pRoot->p_right;
            while(leftMost->p_left) leftMost = leftMost->p_left;
            pRoot->key = leftMost->key;
            Remove(pRoot->p_right,leftMost->key);
        }
    }

    if(!pRoot) return;
    pRoot->height = 1 + max(height(pRoot->p_left),height(pRoot->p_right));
    int bal = getBal(pRoot);
    int leftBal = getBal(pRoot->p_left);
    int rightBal = getBal(pRoot->p_right);
    if(bal > 1 && leftBal >=0){
        pRoot = rightRotation(pRoot);
    }
    else if(bal > 1 && leftBal < 0){
        pRoot->p_left = leftRotation(pRoot->p_left);
        pRoot = rightRotation(pRoot);
    }
    else if(bal < -1 && rightBal <= 0){
        pRoot = leftRotation(pRoot);
    }
    else if(bal < -1 && rightBal > 0){
        pRoot->p_right = rightRotation(pRoot->p_right);
        pRoot = leftRotation(pRoot);
    }
}

bool isAVL(NODE* pRoot){
    stack<NODE*> s;
    NODE* curr = pRoot;
    vector<int> inorder;
    while(!s.empty() || curr){
        while(curr){
            s.push(curr);
            curr = curr->p_left;
        }
        curr = s.top();
        s.pop();
        if(!inorder.empty() && curr->key < inorder.back()) return false;
        int bal = height(curr->p_left)-height(curr->p_right);
        if(bal > 1 || bal < -1) return false;
        inorder.push_back(curr->key);
        curr = curr->p_right;
    }
    return true;
}