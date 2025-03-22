#include <bits\stdc++.h>
using namespace std ;

class Guest {
private:
    string name;
    string contact;
    string iftar_date; 
public:

    Guest(){
        name=""; contact=""; iftar_date="";
    }

    Guest(string Name , string Contact ,string Iftar_date){
        name=Name;
        contact=Contact;
        iftar_date=Iftar_date;

    }
    string getName(){
        return name;
    }
    string getDate(){
        return iftar_date;
    }
    void display_guest(){
        cout<<"Guest: "<<this->name<<", Contact: "<<this->contact
            <<", Iftar Date: "<<this->iftar_date<<endl;
    }
    void display_reminder(){
        cout<<"Reminder sent to "<<this->name
            <<":Your iftar invitation is on "<<this->iftar_date<<endl;
    }
    void update_invitation(string new_date){
        cout<<"Updating invitatipn for "<<this->name<<"..."<<endl;
        this->iftar_date = new_date ;
    }
};

class IftarManager{
    Guest *guest_list ;
    int no_guest;
    int capacity;

    void resize() {
        capacity*=2; 
        Guest* newGeustList = new Guest[capacity];

        for (int i = 0; i < no_guest; i++) {
            newGeustList[i] = guest_list[i];
        }

        delete[] guest_list; //deleting old one
        guest_list = newGeustList;
    }

public:
    IftarManager(){
       no_guest=0;
       capacity=5;
       guest_list = new Guest [capacity];
    }

    IftarManager(int intialSize){
        no_guest=0;
        capacity=intialSize;
        guest_list = new Guest [capacity];
    }

    ~IftarManager() {
        cout << "May your Iftar gatherings be full of warmth and blessings!\n" << endl;
        delete[] guest_list;
    }

    void add_guest(Guest guest){
        if (no_guest == capacity) {
            resize(); //expand the list size
        }
        guest_list[no_guest++] = guest;
    }

    void remove_guest(string name){
        for (int i = 0; i < no_guest; i++) {
            if(guest_list[i].getName() == name){
                for(int j=i;  j<no_guest; j++){
                    guest_list[j]=guest_list[j+1]; //shifting left guests 
                }
                cout<<"Guest \""<<name<<"\" Deleted\n"<<endl;
                no_guest--;
            }
        }
    }

    void display_all_guests(){
        for (int i = 0; i < no_guest; i++) {
            guest_list[i].display_guest();
        }
        cout<<endl;
    }

    void update_guest_invitation(string name, string new_date){
        for (int i = 0; i < no_guest; i++) {
            if (guest_list[i].getName() == name) {
                guest_list[i].update_invitation(new_date);
            }
        }
        cout<<endl;
    }

    void send_reminders(string date){
        cout << "Sending reminders..." << endl;
        for (int i = 0; i < no_guest; i++) {
            if (guest_list[i].getDate() == date) {
                guest_list[i].display_reminder();
            }
        }
        cout<<endl;
    }

    //will be used to sort geust list
    void shellSort(Guest g_list[], int n){
        for (int gap = n/2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                Guest temp = g_list[i];
                int j;            
                for (j = i; j >= gap && g_list[j - gap].getDate() > temp.getDate(); j -= gap){
                    g_list[j] = g_list[j - gap];
                }
                g_list[j] = temp;
            }
        }
    }

    void sort_guest_list(){
        shellSort(guest_list , no_guest);
        cout<<"Guests List sorted Successfully !\n"<<endl;
    }
};


int main(){
    //Create Iftar Manager
    IftarManager manager = IftarManager();

    //Add guests
    Guest guest1 = Guest("Aisha", "aisha@example.com", "2025-03-15");
    Guest guest2 = Guest("Omar", "omar@example.com", "2025-03-18");
    Guest guest3 = Guest("Zainab", "zainab@example.com", "2025-03-20");
    manager.add_guest(guest1);
    manager.add_guest(guest2);
    manager.add_guest(guest3);
    //Display guest list
    manager.display_all_guests();
    //Update invitation date for Omar
    manager.update_guest_invitation("Omar", "2025-03-15");
    //Display updated guest lis
    manager.display_all_guests();
    //Send reminders
    manager.send_reminders("2025-03-15");

    //Deleting A guest
    manager.remove_guest("Zainab");

}
