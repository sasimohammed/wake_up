#include<iostream>
#include"OrderedLinkedList.h"
#include "StatisticalCalculation.h"
using namespace std;

int main(){
    OrderedLinkedList<int>list;
    list.insert(5);
    list.insert(0);
    list.insert(1);
    cout<<list<<endl;

    StatisticalCalculation <int>arr(5);

    arr.menu();



    return 0;
}
