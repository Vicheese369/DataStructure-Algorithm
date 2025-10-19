
#include <iostream>
#include <cstring>
struct Employee{
    int id;
    char* name = nullptr;
    char* position = nullptr;
    Employee* next;
    Employee* previous;
    // Constructor for Node
    Employee(int ID,const char* n,const char* p){
        id = ID;
        name = new char[strlen(n) + 1];// Left 1 space for null terminator
        strcpy(name,n);
        position = new char[strlen(p) + 1];
        strcpy(position,p);
        next = nullptr;
        previous = nullptr;
    }
    // Destructor to clear Employee's variable's memory
    // Only delete name and position cause they are allocated with memory
    ~Employee(){
        delete [] name;
        delete [] position;
    }
};
class DoublyLinkedList{
private:
    Employee* head;
    Employee* tail;
public:
    // Constructor for head and tail
    DoublyLinkedList():head(nullptr),tail(nullptr){}
    void insertAtEnd(int id,const char* name,const char* position){
        Employee* new_Node = new Employee(id, name,position);
        if(!head){
            head = tail = new_Node;
        } else{
            tail->next = new_Node;
            new_Node->previous = tail;
            // Make tail now point to the next created note
            tail = new_Node;
        }
    }
    void insertAtBeginning(int id,const char* name,const char* position){
        Employee* new_Node = new Employee(id,name,position);
        if(!head){
            head = tail = new_Node;
        } else{
            new_Node->next = head;
            head->previous = new_Node;
            head = new_Node;
        }
    }
    int count_Node() {
        int count = 0;
        Employee* current = head; // temp pointer
        while(current) {
            count++;
            current = current->next;
        }
        std::cout<<count<<" node\n";
        return count;
    }
    void insertAtGiven_Value(int index,int id,const char* name,const char* position){
        if(index<=0 || index>count_Node() + 1){
            std::cout<<"Index is out of range\n";
            return;
        }
        if(index == 1){
            insertAtBeginning(id, name,position);
            return;
        }
        if(index == count_Node() + 1){
            insertAtEnd(id, name,position);
            return;
        }
        Employee* current = head;
        // N -2
        for(int i = 1;i < index - 1;i++){
            current = current->next;
        }
        Employee* new_Node = new Employee(id, name,position);
        Employee* temp = current->next;
        new_Node->next = current->next;
        new_Node->previous = current;
        current->next = new_Node;
        temp->previous = new_Node;
    }
    bool search(int id) const{
        if( id <= 0 ){
            std::cout<<"Seriously? Get outtttt\n";
            return false;
        }
        if(!head){
            std::cout<<"you search for id in node that doesn't exist yet, what you want exactly huh?\n";
            return false;
        }
        Employee* temp = head;
        int count = 1;
        while (temp){
            if(temp->id == id){
                std::cout<<"ID "<<id<< " is found at index "<< count << "with info \n";
                std::cout<<"Employee ID: "<<temp->id<<", Employee name : "<<temp->name<<", Employee position "
                         <<temp->position<<" -> \n";
                return true;
            }
            temp = temp->next;
            count++;
        }
        std::cout<<"ID " <<id<< " is not found in the nodes\n";
        return false;
    }
    void delete_At_First(){
        if(!head) return;
        Employee* delete_Node = head;
        head = head->next;
        // If head still has address to point to or not null
        if(head){
            head->previous= nullptr;
        } else{
            tail = nullptr;
        }
        delete delete_Node;
    }
    void delete_At_End(){
        if(!tail) return;
        Employee* delete_Node = tail;
        tail = tail->previous;
        if(tail)
            tail->next = nullptr;
        else
            head = nullptr;
        delete delete_Node;
    }

    void delete_at_given_id(int index){
        if(!head){
            std::cout<<"Well, no node exist, what else to delete?\n";
            return;
        }
        if(index<=0 || index>count_Node() ){
            std::cout<<"Index is out of range\n";
            return;
        }
        Employee* delete_Node = head;
        // N -2
        for(int i = 1;i < index;i++){
            delete_Node = delete_Node->next;
        }
        // Checking if delete node point to the same address as head
        if(delete_Node == head){
            delete_At_First();
            return;
        }
        else if(delete_Node == tail){
            delete_At_End();
            return;
        }
        delete_Node->next->previous = delete_Node->previous;
        delete_Node->previous->next = delete_Node->next;
        delete delete_Node;
        std::cout<<"Successfully delete node at index "<<index<<"\n";
    }
    void displayForward() const{
        if(!head){
            std::cout<<"List is empty\n";
            return;
        }
        Employee* current = head;
        while (current){
            std::cout<<"Employee ID: "<<current->id<<", Employee name : "<<current->name<<", Employee position "
                <<current->position<<" -> \n";
            current = current->next;
        }
        std::cout<<"\n";
    }
    void displayBackward() const{
        if(!head){
            std::cout<<"List is empty\n";
            return;
        }
        Employee* current = tail;
        while (current){
            std::cout<<"Employee ID: "<<current->id<<", Employee name : "<<current->name<<", Employee position "
                <<current->position<<" -> \n";
            current = current->previous;
        }
        std::cout<<"\n";
    }
    void delete_all_Node(Employee*& head){
        if(!head){
            std::cout<<"List is empty\n";
            return;
        }
        Employee* temp = head;
        while (head){
            temp = temp->next;
            delete head;
            head = temp;
        }
    }
    // Use to clear head and tail memory
    // Needing to delete employee cause employee was allocated along with name and position
    // Employee* new_Node = new Employee(id, name,position);
    ~DoublyLinkedList(){
        Employee* current = head;
        while (current){
            Employee* next_Node = current->next;
            delete current;
            current = next_Node;
        }
    }
};