#include <bits\stdc++.h>
using namespace std ;

//will be used to sort geust list

class Guest {
private:
    string name;
    string contact;
    string iftar_date; 
public:
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
    vector<Guest> guest_list ;
public:
    void add_guest(Guest guest){
        guest_list.push_back(guest);
    }
    void display_all_guests(){
        for(Guest g :guest_list){
            g.display_guest();
        }
        cout<<endl;
    }
    void update_guest_invitation(string name, string new_date){
        for(Guest &g : guest_list){
            if(g.getName()==name){
                g.update_invitation(new_date);
            }
        }
        cout<<endl;
    }
    void send_reminders(string date){
        cout<<"Sending reminders..."<<endl;
        for(Guest g : guest_list){
            if(g.getDate()==date){
                g.display_reminder();
            }
        }
        cout<<"\nMay your Iftar gatherings be full of warmth and blessings!\n"<<endl;
    }

    void shellSort(vector<Guest> &guests, int n){
        for (int gap = n/2; gap > 0; gap /= 2)
        {
            for (int i = gap; i < n; i += 1)
            {
                Guest temp = guests[i];
                int j;            
                for (j = i; j >= gap && guests[j - gap].getDate() > temp.getDate(); j -= gap)
                    guests[j] = guests[j - gap];
                guests[j] = temp;
            }
        }
    }
    void sort_guest_list(){
        shellSort(guest_list , guest_list.size());
        cout<<"Geust List sorted Successfully !\n"<<endl;
    }

    void load_guests_from(string filename){
        ifstream file(filename);
        if (!file) {
            cout << "can't open file " << filename << endl;
            return;
        }

        string name, contact, date;
        while (file >> name >> contact >> date) {
            Guest guest(name, contact, date);
            add_guest(guest);
        }

        file.close();
        cout << "Guests loaded successfully :)\n" << endl;
    }
};


int main(){
IftarManager manager = IftarManager();  
// //1)Add guests manually
// Guest guest1 = Guest("Aisha", "aisha@example.com", "2025-03-15");
// Guest guest2 = Guest("Omar", "omar@example.com", "2025-03-18");
// Guest guest3 = Guest("Zainab", "zainab@example.com", "2025-03-20");
// manager.add_guest(guest1);
// manager.add_guest(guest2);
// manager.add_guest(guest3);

// //2)load guests from file
manager.load_guests_from("test.txt");
manager.display_all_guests();
manager.update_guest_invitation("Omar", "2025-03-15");
manager.sort_guest_list();
manager.display_all_guests();
manager.send_reminders("2025-03-15");
}