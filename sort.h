//
// Created by sebaa on 3/16/2025.
//

#ifndef DATASTRUCTURESASS__SORT_H
#define DATASTRUCTURESASS__SORT_H


#include <iostream>
#include<algorithm>

using namespace std;

template<typename T>
class SortingSystem{
private:
    T* data;
    int size;
public:
    SortingSystem(T arr[],int n);
    ~SortingSystem();

    void insertionSort();
    void selectionSort();
    void bubbleSort();
    void shellSort();
    void mergeSort(int left,int right);
    void quickSort(int left,int right);


    void countSort(int digit =1);


    void radixSort();

    void bucketSort();

    void merge(int left,int mid,int right);
    int partition(int low,int high);

    void displayData();
    void measureSortTime(void(SortingSystem::*sortFunc)());

    void showMenu();
};

template<typename T>
SortingSystem<T>::~SortingSystem()
{
    delete[] data;
    cout<<"destructor called"<<endl;
}

//
// Created by sebaa on 3/16/2025.
//





template<typename T>
SortingSystem<T>::SortingSystem(T arr[],int n)
{



    data = new T[n];
    for (int i = 0; i < n; i++)
        data[i] = arr[i];
    size = n;
}




template<typename T>
void SortingSystem<T>::insertionSort()
{
    for(int i=0;i<size;i++)
    {
        T key = data[i];
        int j = i-1;
        // shifting loop
        while(j>=0 && data[j]>key)
        {
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
        displayData();
    }
}

template<typename T>
void SortingSystem<T>::displayData() {
    for (int i = 0; i < size; i++) {
        cout << data[i] << ' ';
    }
    cout<<endl;
}


template<typename T>
void SortingSystem<T>::selectionSort()
{

    for(int i=0;i<size;i++)
    {
        int min = i;
        for(int j=i+1;j<size;j++)
        {
            if(data[min]>data[j])
            {
                min = j;
            }


        }
        if(min!=i)
        {
            T temp = data[i];
            data[i] = data[min];
            data[min] = temp;

        }
        displayData();
    }
}

template<typename T>
void SortingSystem<T>::bubbleSort()
{
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size-i-1;j++)
        {
            if(data[j]>data[j+1])
            {
                swap(data[j],data[j+1]);
            }
        }
        displayData();
    }
}

template<typename T>
void SortingSystem<T>::shellSort()
{
    for(int gap = size/2;gap>0 ;gap/=2) // log n -> complexity
    {
        for(int j=gap;j<size;j++)
        {
            T temp = data[j];
            int i=0;
            cout<<"temp: "<<temp<<endl;
            for( i=j;data[i-gap]>temp && i>=gap; i-=gap )
            {
                cout<<"data[i-gap]: "<<data[i-gap]<<"         "<<"data[i]: "<<data[i]<<endl;
                data[i] = data[i-gap];

            }
            data[i]=temp; //j
            cout<<"i: "<<i<<endl;
            cout<<"data[i]: "<<data[i]<<endl;
            displayData();
            cout<<"========================"<<endl;
        }
        displayData();
    }
}

template<typename T>
void SortingSystem<T>::merge(int left,int mid,int right)
{
    T temp[size];
    int arr1 = left;
    int arr2 = mid+1;
    int temp_arr = left;
    while(arr1<=mid && arr2 <= right)
    {
        if(data[arr1]<=data[arr2])
        {
            temp[temp_arr] = data[arr1];
            arr1++;
            temp_arr++;

        }
        else if(data[arr1]>data[arr2])
        {
            temp[temp_arr] = data[arr2];
            arr2++;
            temp_arr++;
        }

    }
    while(arr1<=mid)
    {
        temp[temp_arr] = data[arr1];
        arr1++;
        temp_arr++;
    }
    while(arr2<=right)
    {
        temp[temp_arr] = data[arr2];
        arr2++;
        temp_arr++;
    }
    for(int i=left;i<=right;i++)
    {
        data[i] = temp[i];
    }

}

template<typename T>
void SortingSystem<T>::mergeSort(int left,int right)
{
    if(left<right)
    {
        displayData();
        int middle = (right+left)/2;
        mergeSort(left,middle);
        mergeSort(middle+1,right);
        merge(left,middle,right);
    }
}

template<typename T>
void SortingSystem<T>::quickSort(int left,int right)
{
    if(left<right)
    {
        int middle = partition(left,right);
        quickSort(left,middle-1);
        quickSort(middle+1,right);

    }

}

template<typename T>
int SortingSystem<T>::partition(int low,int high)
{
    int pivot = data[low];
    int inc_ptr = low;
    cout<<"the pivot is "<<pivot<<": " <<endl; ;
    for(int j=low+1;j<=high;j++)
    {
        if(data[j]<pivot)
        {
            inc_ptr++;
            T temp = data[inc_ptr];
            data[inc_ptr] = data[j];
            data[j]=temp;

        }
    }
    int temp = data[low];
    data[low] = data [inc_ptr];
    data[inc_ptr] = temp;
    displayData();
    return inc_ptr;
}

template<typename T>

void SortingSystem<T>::countSort(int digit )
{
    cout<<typeid(T).name()<<endl;
    if(typeid(T).name()=="i")
    {
        int output_arr[size];
        int maxi =data[0];
        for(int i=1;i<size;i++)
        {
            if(maxi<data[i])
            {
                maxi = data[i];
            }

        }
        maxi++;
        int count_arr[maxi];
        if(digit == 2)  // for normal counting sort
        {

            for(int i=0;i<maxi;i++)
            {
                count_arr[i]=0;
            }
            for(int i=0;i<size;i++)
            {
                count_arr[data[i]]++;
            }


            for(int i=1;i<maxi;i++)
            {
                count_arr[i] = count_arr[i] + count_arr[i-1];
            }


            for (int i = size - 1; i >= 0; i--)
            {
                output_arr[--count_arr[data[i]]] = data[i];
            }


            for(int i=0;i<size;i++)
            {
                data[i] = output_arr[i];
            }
        }
        else   // for radix counting sort
        {


            for(int i=0;i<maxi;i++)
            {
                count_arr[i]=0;
            }
            for(int i=0;i<size;i++)
            {
                count_arr[(data[i]/digit) %10]++;
            }


            for(int i=1;i<maxi;i++)
            {
                count_arr[i] = count_arr[i] + count_arr[i-1];
            }



            for (int i = size - 1; i >= 0; i--)
            {
                output_arr[--count_arr[(data[i]/digit) %10]] = data[i];
            }


            for(int i=0;i<size;i++)
            {
                data[i] = output_arr[i];
            }
        }

    }



}


template<typename T>

void SortingSystem<T>::radixSort()
{

    if(typeid(T).name()=="i")
    {
        int maxi = data[0];
        for(int i=1;i<size;i++)
        {
            if(maxi<data[i])
            {
                maxi = data[i];
            }
        }
        for(int i=1;maxi/i>0;i*=10)
        {
            countSort(i);
        }

    }

}

template<typename T>
void SortingSystem<T>::bucketSort()
{

}

template<typename T>
void SortingSystem<T>::showMenu()
{
    cerr<<typeid(T).name()<<endl;


    cout<<"Select a sorting algorithm:"<<endl;
    cout<<"1. Insertion Sort"<<endl;
    cout<<"2. Selection Sort"<<endl;
    cout<<"3. Bubble Sort"<<endl;
    cout<<"4. Shell Sort"<<endl;
    cout<<"5. Merge Sort"<<endl;
    cout<<"6. Quick Sort"<<endl;

    if (typeid(T) == typeid(int))
    {
        cout<<"7. Count Sort (Only for integers)"<<endl;
        cout<<"8. Radix Sort (Only for integers)"<<endl;
    }






    cout<<"9. Bucket Sort"<<endl;
    cout<<"Enter your choice (1-9): ";
    int system;
    cin>>system;
//    while(!isdigit(system) || system<=0 || system>=10)
//    {
//        cout<<"Please enter a valid choice"<<endl;
//        cin>>system;
//    }

    if(system ==1)
    {
        insertionSort();
        displayData();
    }
    else if( system ==2)
    {
        selectionSort();
        displayData();
    }
    else if(system ==3)
    {
        bubbleSort();
        displayData();
    }
    else if(system ==4)
    {
        shellSort();
        displayData();
    }
    else if(system ==5)
    {
        mergeSort(0,size-1);
        displayData();
    }
    else if(system ==6)
    {
        quickSort(0,size-1);
        displayData();
    }
    else if(system ==7)
    {
        if constexpr (std::is_integral<T>::value) {
            countSort(2);
            displayData();

        }
        countSort(2);

    }
    else if(system ==8)
    {
        if constexpr (std::is_integral<T>::value) {
            radixSort();
            displayData();

        }



    }
    else if(system ==9)
    {
        bucketSort();
        displayData();
    }

}



#endif //DATASTRUCTURESASS__SORT_H

