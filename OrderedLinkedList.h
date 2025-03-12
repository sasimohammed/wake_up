#ifndef ORDEREDLINKEDLIST_H
#define ORDEREDLINKEDLIST_H

#include<iostream>
using namespace std;

template<typename T>
class OrderedLinkedList{
    struct node{
        T data;
        node*next;
        node():next(nullptr){}
    };

    node*start;
    node*end;

public:
    OrderedLinkedList();
    ~OrderedLinkedList();

    void insert(T val);
    void remove(T val);

    friend ostream&operator<<(ostream&os,const OrderedLinkedList<T>&list){
        node*temp=list.start;
        os<<"[ ";
        while(temp){
            os<<temp->data;
            if(temp->next)os<<" -> ";
            temp=temp->next;
        }
        os<<" ]";
        return os;
    }

    T&operator[](int index);
};

// Constructor
template<typename T>
OrderedLinkedList<T>::OrderedLinkedList():start(nullptr),end(nullptr){}

// Destructor
template<typename T>
OrderedLinkedList<T>::~OrderedLinkedList(){
    node*temp;
    while(start){
        temp=start;
        start=start->next;
        delete temp;
    }
    end=nullptr;
}

// Insert function
template<typename T>
void OrderedLinkedList<T>::insert(T val){
    node*newnode=new node;
    newnode->data=val;
    newnode->next=nullptr;

    if(start==nullptr){
        start=newnode;
        end=newnode;
    }
    else{
        node*temp=start;
        node*temp2=nullptr;
        while(temp&&temp->data<val){
            temp2=temp;
            temp=temp->next;
        }
        if(temp==start){
            newnode->next=start;
            start=newnode;
        }
        else{
            temp2->next=newnode;
            newnode->next=temp;
            if(temp==nullptr){
                end=newnode;
            }
        }
    }
}

// Remove function
template<typename T>
void OrderedLinkedList<T>::remove(T val){
    if(start==nullptr)return;

    node*temp=start;
    node*temp2=nullptr;

    while(temp&&temp->data<val){
        temp2=temp;
        temp=temp->next;
    }

    if(temp==nullptr||temp->data!=val)return;
    if(temp==start){
        start=start->next;
        if(start==nullptr)end=nullptr;
    }
    else{
        temp2->next=temp->next;
        if(temp->next==nullptr){
            end=temp2;
        }
    }

    delete temp;
}

// Operator[] overload
template<typename T>
T&OrderedLinkedList<T>::operator[](int index){
    if(index<0){
        throw out_of_range("Index cannot be negative");
    }

    node*temp=start;
    int count=0;

    while(temp){
        if(count==index){
            return temp->data;
        }
        temp=temp->next;
        count++;
    }

    throw out_of_range("Index out of bounds");
}

#endif
