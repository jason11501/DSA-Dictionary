//
//  main.cpp
//  hashTable
//
//  Created by jason on 21/07/2022.
//

#include <string>
#include <iostream>
#include <fstream>
#define num 176009
using namespace std;
#include <time.h>

struct Node
{
    string key;
    Node* nextNode;
};

struct LinkedList
{
    Node* head;
};

Node* GetNode(string e)
{
    Node* newNode = new Node;
    newNode->key = e;
    newNode->nextNode = nullptr;
    return newNode;
}

void AddLast(Node* &head, string &e)
{
    Node* newNode = GetNode(e);
    if (!head)
        head = newNode;
    else
    {
        Node* p = head;
        while (p->nextNode)
            p = p->nextNode;
        p->nextNode = newNode;
    }
}

struct HashTable
{
    LinkedList* container;
    int size;

    HashTable()
    {
        container = nullptr;
        size = 0;
    }

    HashTable(int newSize)
    {
        container = new LinkedList[newSize];
    }

    LinkedList& operator[](const int& index)
    {
        return container[index];
    }
    
    int getKey(string &s)
    {
        int key=0;
        for (int i=0; i<s.length(); i++) {
            key += int(s[i]);
        }
        return key % size;
    }
    
    bool search(Node* head, string k)
    {
        for (Node *p= head; p!=nullptr; p=p->nextNode) {
            if(p->key.substr(0,p->key.find(',')) == k)
            {
                cout<< p->key;
                return true;
            }
        }
        cout<<"Not found\n";
        return false;
    }
    
    void Destroy(Node* &head)
    {
        Node* current = head;
        while (head)
        {
            Node* next = current->nextNode;
            delete current;
            current = next;
        }
        head = 0;
    }
    
    ~HashTable()
    {
        if (container)
        {
            for(int i=0;i<size;i++)
                Destroy(container[i].head);
        }
    }
};

void insert(HashTable &htb, string &k){//k là string cần insert
    string wordTraversal = k.substr(0,k.find(','));
    int hash = 0;
    
    for (int i=0; i<wordTraversal.length(); i++)
        hash += int(k[i]);
    
    AddLast(htb.container[hash % htb.size].head, k);
}

string Input()
{
    string input;
    cout << "\nInput : ";
    getline (cin, input);
    
    return input;
}

void edit(Node* &head, string k)
{
    for (Node *p= head; p!=nullptr; p=p->nextNode) {
        if(p->key.substr(0,p->key.find(',')) == k)
        {
            p->key = k;
            return;
        }
    }
}

void remove(Node* &head, string val)
{
     
    // Check if list is empty or we
    // reach at the end of the
    // list.
    if (head == NULL) {
        return;
    }
    // If current node is the node to be deleted
    if (head->key.substr(0, head->key.find(',')) == val) {
        Node* t = head;
        head = head->nextNode; // If it's start of the node head
                           // node points to second node
        delete (t); // Else changes previous node's link to
                    // current node's link
        return;
    }
    remove(head->nextNode, val);
}

int main(){
//LOAD
    cout << "Loading...\n";
    fstream in;
    in.open("/Users/jason/Downloads/OPTED-Dictionary.csv");
    HashTable htb(50000);
    
    if (in)
    {
        string line;
        
        for (int i=0; i<num; i++) {
            getline(in, line, '\n');

            int firstLetter = int(line[0]);
            if (
                (
                 (firstLetter <= 122 && firstLetter >= 97) || (firstLetter <= 90 && firstLetter >= 65)
                )
                &&
                i > 0
                )
            {
                insert(htb, line);
            }
        }
    }
    in.close();
    cout << "[DONE] Load";
    
    clock_t start, end;
    start = clock();
//SEARCH
    cout << "\nSearching...";
    string lookUp = Input();
    htb.search(htb.container[htb.getKey(lookUp)].head, lookUp);
    cout << "\n[DONE] Search";
//ADD
    cout << "\nAdding...";
    cout << "\nFollow format below\n<stringWord>,<intCount>,<stringPOS><stringDefinition>";
    string newVocabulary = Input();
    insert(htb, newVocabulary);
    cout << "\n[DONE] Add";
//DELETE
    cout << "\nRemoving...";
    string inputRemove = Input();
    cout<< htb.getKey(inputRemove);
    remove(htb.container[htb.getKey(inputRemove)].head, inputRemove);
    cout << "\n[DONE] Remove";
//EDIT
    cout << "\nEditing...";
    string inputEdit = Input();
    edit(htb.container[htb.getKey(inputEdit)].head, inputEdit);
    cout << "\n[DONE] Edit";

    end = clock();
    cout<<(double(end - start) * 1000) / double(CLOCKS_PER_SEC)<<endl;
    return 0;
}
