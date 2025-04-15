#include <iostream>
#include <cassert>
using namespace std;

struct d_NODE {
    int key;
    d_NODE* pNext;
    d_NODE* pPrev;
};

struct d_List {
    d_NODE* pHead;
    d_NODE* pTail;
    d_List(d_NODE* head = nullptr, d_NODE* tail = nullptr) : pHead(head), pTail(tail) {}
};

// Function prototypes
void removeNode(d_NODE* node);
d_NODE* createNode(int data);
d_List* createList(d_NODE* pNode);
d_List* createListFromArray(int arr[], int size);

bool addHead(d_List*& L, int data);
bool removeHead(d_List*& L);

bool addTail(d_List*& L, int data);
bool removeTail(d_List*& L);

bool addAfter(d_List*& L, int data, int val);
void removeAfter(d_List *&L, int val);

bool addBefore(d_List*& L, int data, int val);
void removeBefore(d_List *&L, int val);

bool addPos(d_List *&L, int data, int pos);
void removePos(d_List *&L, int data, int pos);

void removeAll(d_List*& L);
bool removeElement(d_List*& L, int key);
void removeDuplicate(d_List*& L);

int countElements(d_List* L);
void printList(d_List* L);

d_List* reverseList(d_List* L);

// Function implementations
d_NODE* createNode(int data) {
    d_NODE* node = new d_NODE;
    node->key = data;
    node->pNext = nullptr;
    node->pPrev = nullptr;
    return node;
}

d_List* createList(d_NODE* pNode) {
    d_List* list = new d_List;
    list->pHead = pNode;
    list->pTail = pNode;
    return list;
}

bool addHead(d_List*& L, int data) {
    d_NODE* newNode = createNode(data);
    if (!L->pHead) {
        L->pHead = L->pTail = newNode;
        return true;
    }
    newNode->pNext = L->pHead;
    L->pHead->pPrev = newNode;
    L->pHead = newNode;
    return true;
}

bool addTail(d_List*& L, int data) {
    d_NODE* newNode = createNode(data);
    if (!L->pTail) {
        L->pHead = L->pTail = newNode;
        return true;
    }
    newNode->pPrev = L->pTail;
    L->pTail->pNext = newNode;
    L->pTail = newNode;
    return true;
}

bool removeHead(d_List*& L) {
    if (!L->pHead) return false;
    if(L->pTail == L->pHead) L->pTail = nullptr;

    d_NODE* temp = L->pHead;
    L->pHead = L->pHead->pNext;
    if(L->pHead) L->pHead->pPrev = nullptr;
    delete temp;
    return true;
}

bool removeTail(d_List*& L) {
    if (!L->pTail) return false;
    if(L->pHead == L->pTail) L->pHead = nullptr;

    d_NODE* temp = L->pTail;
    L->pTail = L->pTail->pPrev;
    if(L->pTail) L->pTail->pNext = nullptr;
    delete temp;
    return true;
}

void removeAll(d_List*& L) {
    while (removeHead(L));
}

void removeBefore(d_List *&L, int val){
    if(!L->pHead || !L->pHead->pNext) return;
    d_NODE* curr = L->pHead;
    while(curr){
        if(curr->key == val){
            if(curr == L->pHead) removeHead(L);
            else{
                d_NODE* prev = curr->pPrev;
                curr->pPrev = prev->pPrev;
                prev->pPrev->pNext = curr;
                delete prev;
            }
            return;
        }
        curr = curr->pNext;
    }
}
void removeAfter(d_List *&L, int val){
    if(!L->pHead || !L->pHead->pNext) return;
    d_NODE* curr = L->pHead;
    while(curr){
        if(curr->key == val){
            if(curr->pNext == L->pTail) removeTail(L);
            removeNode(curr->pNext);
            return;
        }
        curr = curr->pNext;
    }
}
bool addAfter(d_NODE *node, int val){
    if(!node) return false;
    d_NODE* newNode = createNode(val);

    newNode->pNext = node->pNext;
    newNode->pPrev = node;

    if(node->pNext) node->pNext->pPrev = newNode;
    node->pNext = newNode;
    return true;
}
bool addAfter(d_List*& L, int data, int val) {
    d_NODE* curr = L->pHead;
    while (curr) {
        if (curr->key == val) {
            if(!curr->pNext) addTail(L,data);
            else addAfter(curr,data);
            return true;
        }
        curr = curr->pNext;
    }
    return false;
}
void addBefore(d_NODE* node, int data){
    if(!node) return;
    d_NODE* newNode = createNode(data);
    
    newNode->pNext = node;
    newNode->pPrev = node->pPrev;

    if(node->pPrev) node->pPrev->pNext = newNode;
    node->pPrev = newNode;
}
bool addBefore(d_List*& L, int data, int val) {
    d_NODE* curr = L->pHead;
    while (curr) {
        if (curr->key == val) {
            if(!curr->pPrev) addHead(L,data);
            else addBefore(curr,data);
            return true;
        }
        curr = curr->pNext;
    }
    return false;
}

void printList(d_List* L) {
    d_NODE* curr = L->pHead;
    while (curr) {
        cout << curr->key << " ";
        curr = curr->pNext;
    }
    cout << endl;
}

int countElements(d_List* L) {
    int count = 0;
    d_NODE* curr = L->pHead;
    while (curr) {
        count++;
        curr = curr->pNext;
    }
    return count;
}

d_List* reverseList(d_List* L) {
    d_List* newList = new d_List();
    d_NODE* curr = L->pHead;
    while (curr) {
        addHead(newList, curr->key);
        curr = curr->pNext;
    }
    return newList;
}
void removeNode(d_NODE* node){
    if(!node) return;
    d_NODE* prev = node->pPrev;
    d_NODE* next = node->pNext;
    delete node;
    if(prev) prev->pNext = next;
    if(next) next->pPrev = prev;
}
void removeDuplicate(d_List*& L) {
    d_NODE* curr = L->pHead;
    while (curr) {
        d_List* newList = new d_List;
        newList->pHead = curr->pNext;
        if(newList->pHead) newList->pHead->pPrev = nullptr;
        newList->pTail = L->pTail;
        
        removeElement(newList,curr->key);

        L->pTail = newList->pTail;
        curr->pNext = newList->pHead;
        curr = curr->pNext;
        delete newList;
    }
}

bool removeElement(d_List*& L, int key) {
    d_NODE* curr = L->pHead;
    int count = 0;
    while (curr) {
        d_NODE* temp = curr->pNext;
        if (curr->key == key) {
            if(!curr->pPrev) removeHead(L);
            else if(!curr->pNext) removeTail(L);
            else removeNode(curr);
            count++;
        }
        curr = temp;
    }
    return count>0;
}
bool addPos(d_List *&L, int data, int pos){
    if(pos < 0) return false;
    d_NODE* curr = L->pHead;
    int count = 0;
    while(curr && count + 1 < pos){
        curr = curr->pNext;
        count++;
    }
    if(pos == 0) addHead(L,data);
    else if(curr && !curr->pNext) addTail(L,data);
    else return addAfter(curr,data);
    return true;
}
void removePos(d_List *&L, int data, int pos){
    if(pos < 0) return;
    d_NODE* curr = L->pHead;
    int count = 0;
    while(curr && count < pos){
        curr = curr->pNext;
        count++;
    }
    if(pos == 0 && curr && curr->key == data) removeHead(L);
    else if(curr && !curr->pNext && curr->key == data) removeTail(L);
    else if(curr && curr->key == data) removeNode(curr);
}
void freeList(d_List*& L) {
    if(!L || !L->pHead) return;
    d_NODE* curr = L->pHead;
    while(curr){
        d_NODE* temp = curr;
        curr = curr->pNext;
        delete temp;
    }
}
d_List* createListFromArray(int arr[], int size) {
    d_List* list = new d_List();
    for (int i = 0; i < size; ++i) {
        addTail(list, arr[i]);
    }
    return list;
}
// function to compare two lists
bool areListsEqual(d_List *list1, d_List *list2)
{
    d_NODE *current1 = list1 ? list1->pHead : nullptr;
    d_NODE *current2 = list2 ? list2->pHead : nullptr;
    while (current1 && current2)
    {
        if (current1->key != current2->key)
        {
            return false;
        }
        current1 = current1->pNext;
        current2 = current2->pNext;
    }
    return (current1 == nullptr && current2 == nullptr);
}
// Test cases
int main()
{
    std::cout << "--- Begin running test cases ---" << std::endl;

    // Test case 1: createNode /////////////////////////////////////////////////
    std::cout << "Test createNode: ";
    d_NODE *d_NODE1 = createNode(10);
    assert(d_NODE1 != nullptr && d_NODE1->key == 10 && d_NODE1->pNext == nullptr);
    std::cout << "Passed" << std::endl;
    delete d_NODE1;

    // Test case 2: createList //////////////////////////////////////////////////
    std::cout << "Test createList: ";
    d_NODE *head2 = createNode(20);
    d_List *d_List2 = createList(head2);
    assert(d_List2 != nullptr && d_List2->pHead == head2 && d_List2->pTail == head2);
    std::cout << "Passed" << std::endl;
    freeList(d_List2);

    // Test case 3: addHead //////////////////////////////////////////////////////
    std::cout << "Test addHead: ";
    d_List *d_List3 = new d_List();
    assert(addHead(d_List3, 30));
    assert(d_List3->pHead != nullptr && d_List3->pHead->key == 30 && d_List3->pTail->key == 30);
    assert(addHead(d_List3, 40));
    assert(d_List3->pHead->key == 40 && d_List3->pHead->pNext->key == 30 && d_List3->pTail->key == 30);
    std::cout << "Passed" << std::endl;
    freeList(d_List3);

    // Test case 4: addTail /////////////////////////////////////////////////////////
    std::cout << "Test addTail: ";
    d_List *d_List4 = new d_List();
    assert(addTail(d_List4, 50));
    assert(d_List4->pHead != nullptr && d_List4->pHead->key == 50 && d_List4->pTail->key == 50);
    assert(addTail(d_List4, 60));
    assert(d_List4->pHead->key == 50 && d_List4->pTail->key == 60 && d_List4->pHead->pNext->key == 60);
    std::cout << "Passed" << std::endl;
    freeList(d_List4);

    // Test case 5: removeHead //////////////////////////////////////////////////////////////////
    std::cout << "Test removeHead: ";
    int arr1[3] = {70, 80, 90};
    d_List *d_List5 = createListFromArray(arr1, 3);
    assert(removeHead(d_List5) && d_List5->pHead->key == 80);
    assert(removeHead(d_List5) && d_List5->pHead->key == 90);
    assert(removeHead(d_List5) && d_List5->pHead == nullptr && d_List5->pTail == nullptr);
    assert(!removeHead(d_List5)); // Remove from empty d_List
    std::cout << "Passed" << std::endl;
    freeList(d_List5);

    // Test case 6: removeTail ///////////////////////////////////////////////////////////////////
    std::cout << "Test removeTail: ";
    int arr2[3] = {100, 110, 120};
    d_List *d_List6 = createListFromArray(arr2, 3);
    removeTail(d_List6);
    assert(d_List6->pTail->key == 110 && d_List6->pTail->pNext == nullptr);
    removeTail(d_List6);
    assert(d_List6->pTail->key == 100 && d_List6->pTail->pNext == nullptr && d_List6->pHead == d_List6->pTail);
    removeTail(d_List6);
    assert(d_List6->pHead == nullptr && d_List6->pTail == nullptr);
    d_List *emptyd_List6 = new d_List();
    removeTail(emptyd_List6); // Remove from empty d_List
    std::cout << "Passed" << std::endl;
    freeList(emptyd_List6);
    freeList(d_List6);

    // Test case 7: removeAll /////////////////////////////////////////////////////////////////////
    std::cout << "Test removeAll: ";
    int arr3[3] = {130, 140, 150};
    d_List *d_List7 = createListFromArray(arr3, 3);
    removeAll(d_List7);
    assert(d_List7->pHead == nullptr && d_List7->pTail == nullptr);
    d_List *emptyd_List7 = new d_List();
    removeAll(emptyd_List7); // Remove from empty d_List
    assert(emptyd_List7->pHead == nullptr && emptyd_List7->pTail == nullptr);
    std::cout << "Passed" << std::endl;
    freeList(emptyd_List7);
    freeList(d_List7);

    // Test case 8: removeBefore //////////////////////////////////////////////////////////////////////
    std::cout << "Test removeBefore: ";
    int arr4[5] = {160, 170, 180, 190, 200};
    d_List *d_List8 = createListFromArray(arr4, 5);

    // testcase 1
    removeBefore(d_List8, 180);
    int expectedArr8[4] = {160, 180, 190, 200};
    d_List *expectedd_List8 = createListFromArray(expectedArr8, 4);
    assert(areListsEqual(d_List8, expectedd_List8));

    // testcase 2
    removeBefore(d_List8, 200);
    int expectedArr8_2[3] = {160, 180, 200};
    d_List *expectedd_List8_2 = createListFromArray(expectedArr8_2, 3);
    assert(areListsEqual(d_List8, expectedd_List8_2));

    // testcase 3
    removeBefore(d_List8, 170); // Don't have any element before
    int expectedArr8_2_2[3] = {160, 180, 200};
    d_List *expectedd_List8_2_2 = createListFromArray(expectedArr8_2_2, 3);
    assert(areListsEqual(d_List8, expectedd_List8_2_2));

    // free memory
    freeList(expectedd_List8);
    freeList(expectedd_List8_2);
    freeList(expectedd_List8_2_2);
    freeList(d_List8);
    std::cout << "Passed" << std::endl;

    // Test case 9: remove after ////////////////////////////////////////////////////////////
    std::cout << "Test removeAfter: ";
    int arr5[4] = {220, 230, 240, 250};
    d_List *d_List9 = createListFromArray(arr5, 4);
    // testcase 1
    removeAfter(d_List9, 220);
    int expectedArr9[3] = {220, 240, 250};
    d_List *expectedd_List9 = createListFromArray(expectedArr9, 3);
    assert(areListsEqual(d_List9, expectedd_List9));
    // testcase 2
    removeAfter(d_List9, 250); // Don't have any element after
    int expectedArr9_2[3] = {220, 240, 250};
    d_List *expectedd_List9_2 = createListFromArray(expectedArr9_2, 3);
    assert(areListsEqual(d_List9, expectedd_List9_2));
    // testcase 3
    removeAfter(d_List9, 240);
    int expectedArr9_3[2] = {220, 240};
    d_List *expectedd_List9_3 = createListFromArray(expectedArr9_3, 2);
    assert(areListsEqual(d_List9, expectedd_List9_3));
    // testcase 4
    int arr9_single[1] = {260};
    d_List *d_List9_single = createListFromArray(arr9_single, 1);
    removeAfter(d_List9_single, 260);
    int expectedArr9_single[1] = {260};
    d_List *expectedd_List9_single = createListFromArray(expectedArr9_single, 1);
    assert(areListsEqual(d_List9_single, expectedd_List9_single));
    // testcase 5
    d_List *emptyd_List9 = new d_List();
    removeAfter(emptyd_List9, 270);
    assert(areListsEqual(emptyd_List9, new d_List()));
    // free memory
    freeList(expectedd_List9);
    freeList(expectedd_List9_2);
    freeList(expectedd_List9_3);
    freeList(expectedd_List9_single);
    freeList(d_List9);
    freeList(d_List9_single);
    freeList(emptyd_List9);
    std::cout << "Passed" << std::endl;

    // // Test case 10: addPos /////////////////////////////////////////////////////////
    std::cout << "Test addPos: ";
    d_List *d_List10 = new d_List();
    assert(addPos(d_List10, 280, 0));
    assert(d_List10->pHead != nullptr && d_List10->pHead->key == 280 && d_List10->pTail->key == 280);
    assert(addPos(d_List10, 290, 1));
    assert(d_List10->pHead->key == 280 && d_List10->pTail->key == 290 && d_List10->pHead->pNext->key == 290);
    assert(addPos(d_List10, 300, 1));
    assert(d_List10->pHead->key == 280 && d_List10->pTail->key == 290 && d_List10->pHead->pNext->key == 300);
    assert(d_List10->pHead->pNext->pNext->key == 290);
    assert(addPos(d_List10, 310, 3));
    assert(d_List10->pHead->key == 280 && d_List10->pTail->key == 310 && d_List10->pHead->pNext->key == 300);
    assert(d_List10->pHead->pNext->pNext->key == 290 && d_List10->pHead->pNext->pNext->pNext->key == 310);
    assert(!addPos(d_List10, 320, 5));  // Positions out of range
    assert(!addPos(d_List10, 330, -1)); // Negative position
    // free memory
    freeList(d_List10);
    std::cout << "Passed" << std::endl;

    // Test case 11: RemovePos /////////////////////////////////////////////////////////
    std::cout << "Test RemovePos: ";
    int arr11[5] = {340, 350, 360, 370, 380};
    d_List *d_List11 = createListFromArray(arr11, 5);
    assert(d_List11->pHead->key == 340 && d_List11->pTail->key == 380);
    // testcase 1
    removePos(d_List11, 340, 0);
    assert(d_List11->pHead->key == 350 && d_List11->pTail->key == 380);
    assert(d_List11->pHead->pNext->key == 360 && d_List11->pHead->pNext->pNext->key == 370 && d_List11->pHead->pNext->pNext->pNext->key == 380);
    assert(d_List11->pHead->pNext->pNext->pNext->pNext == nullptr);
    // testcase 2
    removePos(d_List11, 370, 2);
    assert(d_List11->pHead->key == 350 && d_List11->pTail->key == 380);
    assert(d_List11->pHead->pNext->key == 360 && d_List11->pHead->pNext->pNext->key == 380);
    assert(d_List11->pHead->pNext->pNext->pNext == nullptr);
    // testcase 3
    removePos(d_List11, 350, 5); // Positions out of range
    assert(d_List11->pHead->key == 350 && d_List11->pTail->key == 380);
    assert(d_List11->pHead->pNext->key == 360 && d_List11->pHead->pNext->pNext->key == 380);
    assert(d_List11->pHead->pNext->pNext->pNext == nullptr);
    // free memory
    freeList(d_List11);
    std::cout << "Passed" << std::endl;

    // Test case 12: addBefore /////////////////////////////////////////////////////////
    std::cout << "Test addBefore: ";
    int arr12[4] = {390, 400, 410, 420};
    d_List *d_List12 = createListFromArray(arr12, 4);
    assert(d_List12->pHead->key == 390 && d_List12->pTail->key == 420);
    // testcase 1
    addBefore(d_List12, 380, 400);
    int arr12_1[5] = {390, 380, 400, 410, 420};
    d_List *expectedd_List12_1 = createListFromArray(arr12_1, 5);
    assert(areListsEqual(d_List12, expectedd_List12_1));
    // testcase 2
    addBefore(d_List12, 370, 390);
    int arr12_2[6] = {370, 390, 380, 400, 410, 420};
    d_List *expectedd_List12_2 = createListFromArray(arr12_2, 6);
    assert(areListsEqual(d_List12, expectedd_List12_2));
    // testcase 3
    addBefore(d_List12, 360, 350); // Don't have any element before
    int arr12_3[6] = {370, 390, 380, 400, 410, 420};
    d_List *expectedd_List12_3 = createListFromArray(arr12_3, 6);
    assert(areListsEqual(d_List12, expectedd_List12_3));
    // free memory
    freeList(d_List12);
    freeList(expectedd_List12_1);
    freeList(expectedd_List12_2);
    freeList(expectedd_List12_3);
    std::cout << "Passed" << std::endl;

    // Test case 13: addAfter /////////////////////////////////////////////////////////
    std::cout << "Test addAfter: ";
    int arr13[4] = {430, 440, 450, 460};
    d_List *d_List13 = createListFromArray(arr13, 4);
    assert(d_List13->pHead->key == 430 && d_List13->pTail->key == 460);
    // testcase 1
    addAfter(d_List13, 470, 440);
    int arr13_1[5] = {430, 440, 470, 450, 460};
    d_List *expectedd_List13_1 = createListFromArray(arr13_1, 5);
    assert(areListsEqual(d_List13, expectedd_List13_1));
    // testcase 2
    addAfter(d_List13, 480, 460);
    int arr13_2[6] = {430, 440, 470, 450, 460, 480};
    d_List *expectedd_List13_2 = createListFromArray(arr13_2, 6);
    assert(areListsEqual(d_List13, expectedd_List13_2));
    // testcase 3
    addAfter(d_List13, 490, 200); // Don't have any element after
    int arr13_3[6] = {430, 440, 470, 450, 460, 480};
    d_List *expectedd_List13_3 = createListFromArray(arr13_3, 6);
    assert(areListsEqual(d_List13, expectedd_List13_3));
    // free memory
    freeList(expectedd_List13_1);
    freeList(expectedd_List13_2);
    freeList(expectedd_List13_3);
    freeList(d_List13);
    std::cout << "Passed" << std::endl;

    // Test case 14: printd_List /////////////////////////////////////////////////////////
    std::cout << "Test printd_List: "; // Don't need to assert anything
    std::cout << "Passed" << std::endl;

    // Test case 15: countElements /////////////////////////////////////////////////////////
    std::cout << "Test countElements: ";
    // Test case 1
    int arr15[5] = {500, 510, 520, 530, 540};
    d_List *d_List15 = createListFromArray(arr15, 5);
    assert(countElements(d_List15) == 5);
    // Test case 2
    int arr15_2[3] = {550, 560, 570};
    d_List *d_List15_2 = createListFromArray(arr15_2, 3);
    assert(countElements(d_List15_2) == 3);
    // Test case 3
    int arr15_3[1] = {580};
    d_List *d_List15_3 = createListFromArray(arr15_3, 1);
    assert(countElements(d_List15_3) == 1);
    // Test case 4
    d_List *emptyd_List15 = new d_List();
    assert(countElements(emptyd_List15) == 0);
    // free memory
    freeList(d_List15);
    freeList(d_List15_2);
    freeList(d_List15_3);
    freeList(emptyd_List15);
    std::cout << "Passed" << std::endl;

    // Test case 16: reverseList /////////////////////////////////////////////////////////
    std::cout << "Test reverseList: ";
    // Test case 1
    int arr16[5] = {590, 600, 610, 620, 630};
    d_List *d_List16 = createListFromArray(arr16, 5);
    d_List *reversedd_List16 = reverseList(d_List16);
    int expectedArr16[5] = {630, 620, 610, 600, 590};
    d_List *expectedd_List16 = createListFromArray(expectedArr16, 5);
    assert(areListsEqual(reversedd_List16, expectedd_List16));
    // Test case 2
    int arr16_2[3] = {640, 650, 660};
    d_List *d_List16_2 = createListFromArray(arr16_2, 3);
    d_List *reversedd_List16_2 = reverseList(d_List16_2);
    int expectedArr16_2[3] = {660, 650, 640};
    d_List *expectedd_List16_2 = createListFromArray(expectedArr16_2, 3);
    assert(areListsEqual(reversedd_List16_2, expectedd_List16_2));
    // Test case 3
    int arr16_3[1] = {670};
    d_List *d_List16_3 = createListFromArray(arr16_3, 1);
    d_List *reversedd_List16_3 = reverseList(d_List16_3);
    int expectedArr16_3[1] = {670};
    d_List *expectedd_List16_3 = createListFromArray(expectedArr16_3, 1);
    assert(areListsEqual(reversedd_List16_3, expectedd_List16_3));
    // Test case 4
    d_List *emptyd_List16 = new d_List();
    d_List *reversedd_List16_4 = reverseList(emptyd_List16);
    assert(reversedd_List16_4->pHead == nullptr && reversedd_List16_4->pTail == nullptr);
    // free memory
    freeList(expectedd_List16);
    freeList(expectedd_List16_2);
    freeList(expectedd_List16_3);
    freeList(reversedd_List16);
    freeList(reversedd_List16_2);
    freeList(reversedd_List16_3);
    freeList(reversedd_List16_4);
    freeList(d_List16);
    freeList(d_List16_2);
    freeList(d_List16_3);
    freeList(emptyd_List16);
    std::cout << "Passed" << std::endl;

    // Test case 17: removeDuplicate /////////////////////////////////////////////////////////
    std::cout << "Test removeDuplicate: ";
    // Test case 1
    int arr17[6] = {680, 690, 690, 700, 710, 710};
    d_List *d_List17 = createListFromArray(arr17, 6);
    removeDuplicate(d_List17);
    int expectedArr17[4] = {680, 690, 700, 710};
    d_List *expectedd_List17 = createListFromArray(expectedArr17, 4);
    assert(areListsEqual(d_List17, expectedd_List17));
    // Test case 2
    int arr17_2[5] = {720, 730, 740, 740, 740};
    d_List *d_List17_2 = createListFromArray(arr17_2, 5);
    removeDuplicate(d_List17_2);
    int expectedArr17_2[3] = {720, 730, 740};
    d_List *expectedd_List17_2 = createListFromArray(expectedArr17_2, 3);
    assert(areListsEqual(d_List17_2, expectedd_List17_2));
    // Test case 3
    int arr17_3[4] = {750, 760, 760, 770};
    d_List *d_List17_3 = createListFromArray(arr17_3, 4);
    removeDuplicate(d_List17_3);
    int expectedArr17_3[3] = {750, 760, 770};
    d_List *expectedd_List17_3 = createListFromArray(expectedArr17_3, 3);
    assert(areListsEqual(d_List17_3, expectedd_List17_3));
    // Test case 4
    int arr17_4[2] = {780, 780};
    d_List *d_List17_4 = createListFromArray(arr17_4, 2);
    removeDuplicate(d_List17_4);
    int expectedArr17_4[1] = {780};
    d_List *expectedd_List17_4 = createListFromArray(expectedArr17_4, 1);
    assert(areListsEqual(d_List17_4, expectedd_List17_4));
    // Test case 5
    int arr17_5[1] = {790};
    d_List *d_List17_5 = createListFromArray(arr17_5, 1);
    removeDuplicate(d_List17_5);
    int expectedArr17_5[1] = {790};
    d_List *expectedd_List17_5 = createListFromArray(expectedArr17_5, 1);
    assert(areListsEqual(d_List17_5, expectedd_List17_5));
    // Test case 6
    d_List *emptyd_List17 = new d_List();
    removeDuplicate(emptyd_List17);
    assert(emptyd_List17->pHead == nullptr && emptyd_List17->pTail == nullptr);
    // free memory
    freeList(expectedd_List17);
    freeList(expectedd_List17_2);
    freeList(expectedd_List17_3);
    freeList(expectedd_List17_4);
    freeList(expectedd_List17_5);
    freeList(d_List17);
    freeList(d_List17_2);
    freeList(d_List17_3);
    freeList(d_List17_4);
    freeList(d_List17_5);
    freeList(emptyd_List17);
    std::cout << "Passed" << std::endl;

    // Test case 18: removeElement /////////////////////////////////////////////////////////
    std::cout << "Test removeElement: ";
    // Test case 1
    int arr18[5] = {800, 810, 820, 830, 840};
    d_List *d_List18 = createListFromArray(arr18, 5);
    assert(removeElement(d_List18, 820));
    int expectedArr18[4] = {800, 810, 830, 840};
    d_List *expectedd_List18 = createListFromArray(expectedArr18, 4);
    assert(areListsEqual(d_List18, expectedd_List18));
    // Test case 2
    int arr18_2[3] = {850, 860, 870};
    d_List *d_List18_2 = createListFromArray(arr18_2, 3);
    assert(removeElement(d_List18_2, 850));
    int expectedArr18_2[2] = {860, 870};
    d_List *expectedd_List18_2 = createListFromArray(expectedArr18_2, 2);
    assert(areListsEqual(d_List18_2, expectedd_List18_2));
    // Test case 3
    int arr18_3[4] = {880, 890, 900, 910};
    d_List *d_List18_3 = createListFromArray(arr18_3, 4);
    assert(removeElement(d_List18_3, 910));
    int expectedArr18_3[3] = {880, 890, 900};
    d_List *expectedd_List18_3 = createListFromArray(expectedArr18_3, 3);
    assert(areListsEqual(d_List18_3, expectedd_List18_3));
    // Test case 4
    int arr18_4[2] = {920, 930};
    d_List *d_List18_4 = createListFromArray(arr18_4, 2);
    assert(removeElement(d_List18_4, 920));
    int expectedArr18_4[1] = {930};
    d_List *expectedd_List18_4 = createListFromArray(expectedArr18_4, 1);
    assert(areListsEqual(d_List18_4, expectedd_List18_4));
    // Test case 5
    int arr18_5[1] = {940};
    d_List *d_List18_5 = createListFromArray(arr18_5, 1);
    assert(removeElement(d_List18_5, 940));
    int expectedArr18_5[0] = {};
    d_List *expectedd_List18_5 = createListFromArray(expectedArr18_5, 0);
    assert(areListsEqual(d_List18_5, expectedd_List18_5));
    // Test case 6
    d_List *emptyd_List18 = new d_List();
    assert(!removeElement(emptyd_List18, 950)); // Remove from empty d_List
    assert(emptyd_List18->pHead == nullptr && emptyd_List18->pTail == nullptr);
    // free memory
    freeList(expectedd_List18);
    freeList(expectedd_List18_2);
    freeList(expectedd_List18_3);
    freeList(expectedd_List18_4);
    freeList(expectedd_List18_5);
    freeList(d_List18);
    freeList(d_List18_2);
    freeList(d_List18_3);
    freeList(d_List18_4);
    freeList(d_List18_5);
    freeList(emptyd_List18);
    std::cout << "Passed" << std::endl;
    std::cout << "--- End running test cases ---" << std::endl;
    return 0;
}