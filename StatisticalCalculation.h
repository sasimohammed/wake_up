#ifndef STATISTICALCALCULATION_H
#define STATISTICALCALCULATION_H

#include<iostream>
#include<algorithm>

using namespace std;

template<typename T>
class StatisticalCalculation {
    T*data;
    int size;

public:
    StatisticalCalculation(int size) {
        this->size=size;
        data=new T[size];
        cout<<"StatisticalCalculation object created for "<<size<<" elements.\n";
    }

    ~StatisticalCalculation() {
        delete[]data;
        cout<<"Memory cleared. StatisticalCalculation object destroyed.\n";
    }

    void sortarray() {
        sort(data,data+size);
    }

    T findmin() {
        return *min_element(data,data+size);
    }

    T findmax() {
        return *max_element(data,data+size);
    }

    double findmean() {
        T sum=0;
        for(int i=0;i<size;i++)
            sum+=data[i];
        return static_cast<double>(sum)/size;
    }

    T findsummation() {
        T sum=0;
        for(int i=0;i<size;i++)
            sum+=data[i];
        return sum;
    }

    T findmedian() {
        sortarray();
        if(size%2==0)
            return (data[size/2-1]+data[size/2])/2;
        else
            return data[size/2];
    }

    void input() {
        cout<<"\nEnter "<<size<<" elements, one at a time:\n";
        for(int i=0;i<size;i++) {
            cout<<"Element "<<(i+1)<<": ";
            cin>>data[i];
        }
        cout<<"Data input completed successfully!\n";
    }

    void display() {
        cout<<"\nCurrent data: ";
        for(int i=0;i<size;i++)
            cout<<data[i]<<" ";
        cout<<"\n";
    }

    void menu() {
        int choice;
        input();
        while(true) {
            cout<<"\nStatistical Operations Menu:\n";
            cout<<"--------------------------------------\n";
            cout<<"1. Find Minimum\n";
            cout<<"2. Find Maximum\n";
            cout<<"3. Find Mean (Average)\n";
            cout<<"4. Find Median\n";
            cout<<"5. Find Summation\n";
            cout<<"6. Display Data\n";
            cout<<"7. Re-enter Data\n";
            cout<<"8. Exit Program\n";
            cout<<"--------------------------------------\n";
            cout<<"Please enter your choice: ";
            cin>>choice;

            switch(choice) {
                case 1: cout<<"Minimum value: "<<findmin()<<endl; break;
                case 2: cout<<"Maximum value: "<<findmax()<<endl; break;
                case 3: cout<<"Mean (Average): "<<findmean()<<endl; break;
                case 4: cout<<"Median value: "<<findmedian()<<endl; break;
                case 5: cout<<"Summation of values: "<<findsummation()<<endl; break;
                case 6: display(); break;
                case 7: input(); break;
                case 8: cout<<"Exiting program. Thank you!\n"; return;
                default: cout<<"Invalid choice! Please enter a number between 1 and 8.\n";
            }
        }
    }
};

#endif
