#include "iostream"
#include "vector"
#include <fstream>

using namespace std;

class Patient
{
    string Name;
    int Severity;
    int Arrival_time;

public:
    Patient(){
        Name = "";
        Severity = 0;
        Arrival_time = 0;
    }
    Patient(string name, int severity, int arrival_time)
    {
        Name = name;
        Severity = severity;
        Arrival_time = arrival_time;
    }

    string getName(){
        return Name ;
    }

    bool operator>(const Patient &other)const
    {
        if (Severity > other.Severity)
            return true;
        else if (Severity < other.Severity)
            return false;
        else
            return (Arrival_time < other.Arrival_time);
    }
};
class MaxHeap
{
    Patient *heap;
    int no_Patient;
    int capacity;

    void resize()
    {
        capacity *= 2;
        Patient *newHeap = new Patient[capacity];

        for (int i = 0; i < no_Patient; i++)
        {
            newHeap[i] = heap[i];
        }

        delete[] heap; // deleting old one
        heap = newHeap;
    }

    int parent(int i)
    {
        return (i - 2) / 2;
    }
    int leftChild(int i)
    {
        return (2 * i + 1);
    }
    int rightChild(int i)
    {
        return (2 * i + 2);
    }

    // Moves a newly inserted patient up the heap to restore max-heap order.
    // Compares with parent and swaps if child has higher priority.
    // Repeats to the up until the patient is in the correct position.
    void heapifyUp(int index) {
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heap[index] > heap[parentIndex]) {
                swap(heap[index], heap[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }

    // Restores max-heap order after extracting the max (root) patient.
    // Compares a patient with its left and right children.
    // Swaps with the highest-priority child if exist, then continues downward
    void Max_Heapify(int i)
    {
        int l = leftChild(i);
        int r = rightChild(i);
        int largest = i;

        if (l < no_Patient && heap[l] > heap[largest])
            largest = l;
        if (r < no_Patient && heap[r] > heap[largest])
            largest = r;

        if (largest != i)
        {
            swap(heap[i], heap[largest]);
            Max_Heapify(largest);
        }
    }
    
    

public:
    MaxHeap()
    {
        capacity = 10;
        no_Patient = 0;
        heap = new Patient[capacity]; 
    }

    MaxHeap(int initialSize)
    {
        capacity = initialSize;
        no_Patient = 0;
        heap = new Patient[capacity]; 
    }

    void insert(Patient patient){
        if (no_Patient == capacity) {
            resize();
        }
        heap[no_Patient] = patient;
        heapifyUp(no_Patient);
        no_Patient++;
    }

    //To return max and delete
    //swaping root "max" with last patient and decrease the size by one "to avoid doubling last patient"
    //like that we delete max and then restore the heap again
    void extract_max(){
        if(no_Patient<1) cout<<"Heap EMPTY !"<<endl;
        Patient max = heap[0];
        heap[0] = heap[--no_Patient];
        Max_Heapify(0);
        cout<<"Treating: "<<max.getName()<<endl;
    }

    //To return max only
    Patient peek() {
        if (no_Patient > 0)
            return heap[0];
        else cout<<"Heap EMPTY !"<<endl;
    }

    void print_heap() {
        cout<<"[ ";
        for(int i=0; i<no_Patient-1; i++){
            cout<<heap[i].getName()<<",";
        }
        cout<<heap[no_Patient-1].getName();
        cout<<" ]"<<endl;
        
    }
    bool isEmpty() {
        return (no_Patient==0);
    }
};

void uploadPatientsData (MaxHeap &hospitalPatients){

    ifstream file("Data.txt");
    
    if (!file.is_open()) {
        cerr << "Failed to open file" << endl;
        return ;
    }

    string name;
    int severity, arrival_time;
    while (file >> name >> severity >> arrival_time) {
        hospitalPatients.insert(Patient(name, severity, arrival_time));
        hospitalPatients.print_heap();  //print after each insert    
        cout<<endl;
    }

    file.close();

}

int main()
{
    MaxHeap hospitalPatients;

    
    uploadPatientsData(hospitalPatients );

    while (!hospitalPatients.isEmpty()) {
        hospitalPatients.extract_max();
    }
 
    return 0;

}
