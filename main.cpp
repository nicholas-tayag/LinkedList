#include <vector>
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class LinkedList {
public: 
    // declare node struct  
    struct Node {
        T data;       // node info
        Node* next;   // pointer for next node
        Node* prev;   // pointer for previous node

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}  // node constructor
    };

private: 
    Node* head;       // pointer for start of list
    Node* tail;       // pointer for end of list
    unsigned int count;  // total count of nodes

public: 
    // default constructor
    LinkedList();
    
    // destructor 
    ~LinkedList();

    // add to the start
    void AddHead(const T& value);
    
    // add to the end
    void AddTail(const T& value);

    // add mult. to the start
    void AddNodesHead(const T* arr, unsigned int size);

    // add mult. to the end
    void AddNodesTail(const T* arr, unsigned int size);

    // count 
    unsigned int NodeCount() const;

    // show start to end 
    void PrintForward() const;

    // show end to start
    void PrintReverse() const; 

    // pointer to head w const and non-const versions.
    Node* Head();
    const Node* Head() const;

    // pointer to tail w const and non-const versions
    Node* Tail();
    const Node* Tail() const;

    // pointer to the node at the given index
    Node* GetNode(unsigned int index);
    const Node* GetNode(unsigned int index) const;

    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;

    // find first node with matching data
    Node* Find(const T& value);
    const Node* Find(const T& data) const;
    
    // find all nodes which match the passed in parameter value
    void FindAll(vector<Node*>& outData, const T& value) const;
    
    // deletes all nodes
    void Clear();
 
    LinkedList(const LinkedList<T>& list);

    LinkedList<T>& operator=(const LinkedList<T>& rhs);

    // create new nod before indicated node
    void InsertBefore(Node* node, const T&data);

    // create node after indicated node
    void InsertAfter(Node* node, const T& data);

    // create new node at index
    void InsertAt(const T& data, unsigned int index);

    // overloaded equality operator 
    bool operator==(const LinkedList<T>& rhs) const;

    // delete first node 
    bool RemoveHead();

    // delete last node
    bool RemoveTail();

    // deelete indexd node 
    bool RemoveAt(unsigned int index);

    // remove all nodes containing matching values 
    unsigned int Remove(const T&data);

    // This function takes in a pointer to a Node—a starting node. From that node,
    // recursively visit each node that follows, in forward order, and print their values.
    // MUST be implemented using recursion  
    void PrintForwardRecursive(const Node* node) const;

    // Same deal as PrintForwardRecursive, but in reverse.
    void PrintReverseRecursive(const Node* node) const;
    
};

// Constructor 
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}


// Desctructor ~
template <typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
}


// AddHead
template <typename T>
void LinkedList<T>::AddHead(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    count++;
}


// AddTail
template <typename T>
void LinkedList<T>::AddTail(const T& value) {
    Node* newNode = new Node(value);
    if (!tail) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}


// AddNodesHead 
template <typename T>
void LinkedList<T>::AddNodesHead(const T* arr, unsigned int size) {
    for (int i = size - 1; i >= 0; i--) {
        AddHead(arr[i]);
    }
}


// AddNodesTail
template <typename T>
void LinkedList<T>::AddNodesTail(const T* arr, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        AddTail(arr[i]);
    }
}

// NodeCount
template <typename T>
unsigned int LinkedList<T>::NodeCount() const {
    return count;
}

// PrintForward
template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* temp = head;
    while (temp) {
        cout << temp->data << endl;  // print each on a new line
        temp = temp->next;
    }
}


// PrintReverse
template <typename T>
void LinkedList<T>::PrintReverse() const {
    Node* temp = tail;
    while (temp) {
        cout << temp->data << endl;  // print each on a new line
        temp = temp->prev;
    }
}


// Head non-const
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head;
}

// Head const
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const {
    return head;
}

// Tail non-const
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}

// Tail const
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}

// GetNode const
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    if (index >= count) throw std::out_of_range("Invalid index provided!");
    Node* temp = head;
    for (unsigned int i = 0; i < index && temp; i++) {
        temp = temp->next;
    }
    return temp;
}

// GetNode non-const
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) {
    if (index >= count) throw std::out_of_range("Invalid index provided!");
    Node* temp = head;
    for (unsigned int i = 0; i < index && temp; i++) {
        temp = temp->next;
    }
    return temp;
}

// operator[] non-const 
template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    return GetNode(index)->data;
}

// operator[] const 
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
    return GetNode(index)->data;
}

// Find non-const
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& value) {
    Node* temp = head;
    while (temp && temp->data != value) {
        temp = temp->next;
    }
    return temp;
}

// Find const
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& value) const {
    Node* temp = head;
    while (temp && temp->data != value) {
        temp = temp->next;
    }
    return temp;
}

// FindAll
template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const {
    Node* temp = head;
    while (temp) {
        if (temp->data == value) {
            outData.push_back(temp);
        }
        temp = temp->next;
    }
}

// Clear
template <typename T>
void LinkedList<T>::Clear() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;
}

// big three

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) : head(nullptr), tail(nullptr), count(0) {
    Node* temp = list.head;
    while (temp) {
        AddTail(temp->data);
        temp = temp->next;
    }
}

// operator=
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs) {
    if (this != &rhs) {  
        Clear();  
        Node* temp = rhs.head;
        while (temp) {
            AddTail(temp->data);
            temp = temp->next;
        }
    }
    return *this;
}

// InsertBefore
template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data) {
    if (!node) return;
    Node* newNode = new Node(data);
    newNode->next = node;
    newNode->prev = node->prev;
    if (node->prev) {
        node->prev->next = newNode;
    } else {
        head = newNode;
    }
    node->prev = newNode;
    count++;
}

// InsertAfter
template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data) {
    if (!node) return;
    Node* newNode = new Node(data);
    newNode->prev = node;
    newNode->next = node->next;
    if (node->next) {
        node->next->prev = newNode;
    } else {
        tail = newNode;
    }
    node->next = newNode;
    count++;
}

// InsertAt
template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {
    if (index == 0) {
        AddHead(data);
    } else if (index == count) {
        AddTail(data);
    } else {
        Node* nodeAtIndex = GetNode(index);
        if (nodeAtIndex) {
            InsertBefore(nodeAtIndex, data);
        } else {
            throw std::out_of_range("Index out of range");
        }
    }
}

// operator==
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const {
    if (count != rhs.count) return false;
    Node* temp1 = head;
    Node* temp2 = rhs.head;
    while (temp1 && temp2) {
        if (temp1->data != temp2->data) return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

// RemoveHead 
template <typename T>
bool LinkedList<T>::RemoveHead() {
    if (!head) return false;  
    Node* temp = head;
    head = head->next;
    if (head) head->prev = nullptr;  
    else tail = nullptr;  
    delete temp;
    count--;
    return true;
}

// RemoveTail 
template <typename T>
bool LinkedList<T>::RemoveTail() {
    if (!tail) return false;  
    Node* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;  
    else head = nullptr;  
    delete temp;
    count--;
    return true;
}

// RemoveAt
template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    if (index >= count) return false;  // If the index is out of range, return false
    Node* nodeToRemove = GetNode(index);
    if (nodeToRemove->prev) nodeToRemove->prev->next = nodeToRemove->next;
    else head = nodeToRemove->next;
    if (nodeToRemove->next) nodeToRemove->next->prev = nodeToRemove->prev;
    else tail = nodeToRemove->prev;
    delete nodeToRemove;
    count--;
    return true;
}

// Remove
template <typename T>
unsigned int LinkedList<T>::Remove(const T& value) {
    unsigned int removedCount = 0;
    Node* current = head;
    while (current) {
        if (current->data == value) {
            Node* toDelete = current;
            if (current->prev) current->prev->next = current->next;
            else head = current->next;
            if (current->next) current->next->prev = current->prev;
            else tail = current->prev;
            current = current->next;
            delete toDelete;
            count--;
            removedCount++;
        } else {
            current = current->next;
        }
    }
    return removedCount;
}

// PrintForwardRecursive
template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const {
    if (!node) return;  
    cout << node->data << endl;  
    PrintForwardRecursive(node->next); 
}

// PrintReverseRecursive
template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const {
    if (!node) return; 
    cout << node->data << endl;  
    PrintReverseRecursive(node->prev); 
}
