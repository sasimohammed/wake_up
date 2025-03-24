#include<iostream>
using namespace std;
#include "sort.h"

int main()
{
    while(true)
    {

        cout<<"Enter the number of items to sort: ";
        int choice;
        cin>>choice;
        float arr[choice];
        for(int i=0;i<choice;i++)
        {
            cout<<"Enter data "<<i+1<<": ";
            cin>>arr[i];

        }
        SortingSystem<float> obj(arr,choice);
        obj.showMenu();

        cout<<"Do you want to sort another dataset? (y/n):"<<endl;
        char c;
        cin>>c;
        if(c=='n')
        {
            cout<<"Thank you for using the sorting system! Goodbye!"<<endl;
            break;
        }
    }

}