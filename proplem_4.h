//
// Created by Gaming 3 on 3/24/2025.
//

#ifndef ASS_1_PROPLEM_4_H
#define ASS_1_PROPLEM_4_H


#include <iostream>
#include<algorithm>
#include <vector>
#include <chrono>
using namespace std;

template<typename T>
class SortingSystem{
private:
    T* data;
    int size;
public:
 SortingSystem(int n);
    ~SortingSystem();

    void insertionSort();
    void selectionSort();
    void bubbleSort();
    void shellSort();
    void mergeSort(int left,int right);
    void quickSort(int left,int right);

   void  countSortForRadix(int digit=1);

void input();


    void countSort();


    void radixSort();

    void bucketSort();

    void merge(int left,int mid,int right);
    int partition(int low,int high);

    void displayData(bool isFinal = false);
//    void measureSortTime(void(SortingSystem::*sortFunc)());

    void showMenu();


    void measureSortTime(void (SortingSystem::*sortFunc)()) {
        auto start = std::chrono::high_resolution_clock::now();
        (this->*sortFunc)();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Sorting Time: " << duration.count() << " ms" << std::endl;
    }

    // For member functions with parameters (using variadic templates)
    template <typename... Args>
    void measureSortTime(void (SortingSystem::*sortFunc)(Args...), Args... args) {
        auto start = std::chrono::high_resolution_clock::now();
        (this->*sortFunc)(args...);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Sorting Time: " << duration.count() << " ms" << std::endl;
    }
};

template<typename T>
void SortingSystem<T>::input() {
    cout<<"\nEnter "<<size<<" elements, one at a time:\n";
    for(int i=0;i<size;i++) {
        cout<<"Element "<<(i+1)<<": ";
        cin>>data[i];
    }
    cout<<"Data input completed successfully!\n";
}

template<typename T>
SortingSystem<T>::~SortingSystem()
{
    delete[] data;
    cout<<"destructor called"<<endl;
}






template<typename T>
SortingSystem<T>::SortingSystem(int n)
{
    data = new T[n];
    size = n;
}




template<typename T>
void SortingSystem<T>::insertionSort() {
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
void SortingSystem<T>::displayData(bool isFinal ) {
    static int iteration = 0;  // Keep track of iterations

    if (isFinal) {
        cout << "Final result: [";
    } else {
        iteration++;
        cout << "Iteration " << iteration << ": [";
    }

    for (int i = 0; i < size; i++) {
        cout << data[i];
        if (i != size - 1) cout << ", ";  // Add commas between elements
    }

    cout << "]" << endl;
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
    T pivot = data[low];
 int   inc_ptr = low;
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
  T temp = data[low];
    data[low] = data [inc_ptr];
    data[inc_ptr] = temp;
    displayData();
    return inc_ptr;
}

template<typename T>

#include <algorithm>


void SortingSystem<T>::countSort()  {

    int output_arr[size];
    int maxi = *std::max_element(data, data + size);

    int count_arr[maxi + 1] ;


    for (int i = 0; i < size; i++) {
        count_arr[data[i]]++;
    }

    for (int i = 1; i <= maxi; i++) {
        count_arr[i] += count_arr[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output_arr[--count_arr[data[i]]] = data[i];
    }

    for (int i = 0; i < size; i++) {
        data[i] = output_arr[i];
    }

    }


template<typename T>
void SortingSystem<T>::countSortForRadix(int digit) {
    int output_arr[size];
    int count_arr[10] = {0};

    for (int i = 0; i < size; i++) {
        count_arr[(data[i] / digit) % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count_arr[i] += count_arr[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output_arr[--count_arr[(data[i] / digit) % 10]] = data[i];
    }

    for (int i = 0; i < size; i++) {
        data[i] = output_arr[i];
    }
}

template<typename T>
void SortingSystem<T>::radixSort() {
    if (typeid(T) == typeid(int)) {
        int maxi = *std::max_element(data, data + size);

        for (int digit = 1; maxi / digit > 0; digit *= 10) {
            countSortForRadix(digit);
        }
    }
}







template<typename T>
void SortingSystem<T>::bucketSort() {
    vector<vector<T>> buckets(size);

    if constexpr (is_arithmetic<T>::value) {

        T max_val = *max_element(data, data + size);

        for (int i = 0; i < size; i++) {
            int index;
            if constexpr (is_floating_point<T>::value) {
                index = size * (data[i] / max_val);
            } else {
                index = (size * data[i]) / (max_val + 1);
            }
            if (index >= size) index = size - 1;
            buckets[index].push_back(data[i]);


            displayData();
        }


        for (auto &bucket : buckets) {
            sort(bucket.begin(), bucket.end());
        }

    }
    else if constexpr (is_same<T, string>::value) {

        vector<T> bucket;

        for (int i = 0; i < size; i++) {
            bucket.push_back(data[i]);
        }

        // Apply Insertion Sort on the bucket
        for (int i = 1; i < bucket.size(); i++) {
            T key = bucket[i];
            int j = i - 1;

            while (j >= 0 && bucket[j] > key) {
                bucket[j + 1] = bucket[j];
                j--;
            }
            bucket[j + 1] = key;

            displayData();
        }


        for (int i = 0; i < size; i++) {
            data[i] = bucket[i];
        }
        return;
    }


    int idx = 0;
    for (int i = 0; i < size; i++) {
        for (T& num : buckets[i]) {
            data[idx++] = num;
        }
    }
}


template<typename T>
void SortingSystem<T>::showMenu()
{



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
        displayData(true );
    }
    else if( system ==2)
    {
        measureSortTime(&SortingSystem<T>::selectionSort) ;
        displayData(true);
    }
    else if(system ==3)
    {
        bubbleSort();
        displayData(true);
    }
    else if(system ==4)
    {
        shellSort();
        displayData(true);
    }
    else if(system ==5)
    {
        measureSortTime(&SortingSystem<int>::mergeSort);
        
        displayData(true);
    }
    else if(system ==6)
    {
        quickSort(0,size-1);
        displayData(true);
    }
    else if(system ==7)
    {
        if constexpr (std::is_integral<T>::value) {
            countSort();
            displayData(true);

        }


    }
    else if(system ==8)
    {
        if constexpr (std::is_integral<T>::value) {
            radixSort();
            displayData(true);

        }



    }
    else if(system ==9)
    {
        bucketSort();
        displayData(true);
    }

}



#endif



