#include <bits/stdc++.h>
using namespace std;

class Stack {
private:
    string* data;
    int top_index;
    int capacity;

public:
    Stack() {
        capacity = 1000;
        data = new string[capacity];
        top_index = -1;
    }

    ~Stack() {
        delete[] data;
    }

    bool is_empty() {
        return top_index == -1;
    }

    void push_element(string url) {
        if (top_index == capacity - 1) {
            capacity *= 2;
            string* temp = new string[capacity];
            for (int i = 0; i <= top_index; ++i) {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;
        }
        top_index++;
        data[top_index] = url;
    }

    void pop_element() {
        if (!is_empty()) {
            top_index--;
        }
    }

    string get_top_element() {
        if (!is_empty()) {
            return data[top_index];
        }
        return "";
    }

    void clear_stack() {
        top_index = -1;
    }
};

class BrowserHistory {
private:
    Stack back_stack;
    Stack forward_stack;
    string current_URL;

public:
    void visit_URL(string url) {
        if (!current_URL.empty()) {
            back_stack.push_element(current_URL);
        }
        current_URL = url;
        forward_stack.clear_stack();
        cout << "Visited: " << current_URL << endl;
    }

    string goBack() {
        if (back_stack.is_empty()) {
            cout << "No previous page in history." << endl;
            return current_URL;
        }
        forward_stack.push_element(current_URL);
        current_URL = back_stack.get_top_element();
        back_stack.pop_element();
        cout << "Went back to: " << current_URL << endl;
        return current_URL;
    }

    string goForward() {
        if (forward_stack.is_empty()) {
            cout << "No forward page in history." << endl;
            return current_URL;
        }
        back_stack.push_element(current_URL);
        current_URL = forward_stack.get_top_element();
        forward_stack.pop_element();
        cout << "Went forward to: " << current_URL << endl;
        return current_URL;
    }

    string getCurrentUrl() {
        return current_URL.empty() ? "No URL visited yet." : current_URL;
    }
};

int main() {
    BrowserHistory history;
    int choice;


    string* test_urls = new string[1000];
    int test_size = 0;
    int test_capacity = 1000;

    // Load URLs from file
    ifstream file("urls.txt");
    string url;
    if (file.is_open()) {
        while (getline(file, url)) {
            if (!url.empty()) {
                if (test_size == test_capacity) {
                    test_capacity *= 2;
                    string* new_array = new string[test_capacity];
                    for (int i = 0; i < test_size; ++i) {
                        new_array[i] = test_urls[i];
                    }
                    delete[] test_urls;
                    test_urls = new_array;
                }
                test_urls[test_size++] = url;
            }
        }
        file.close();
    } else {
        cout << "Warning: Could not open 'urls.txt'.\n";
    }

    int test_index = 0;

    while (true) {
        cout << "\n========== Welcome to our program ==========\n";
        cout << "1. Visit new URL (from file or manual)\n";
        cout << "2. Go back\n";
        cout << "3. Go forward\n";
        cout << "4. Show current URL\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            if (test_index < test_size) {
                history.visit_URL(test_urls[test_index]);
                test_index++;
            } else {
                cin.ignore();
                string user_url;
                cout << "All test_URLs visited.\n";
                cout << "Enter a new URL to visit: ";
                getline(cin, user_url);
                history.visit_URL(user_url);

                // Append to file
                ofstream outfile("urls.txt", ios::app);
                if (outfile.is_open()) {
                    outfile << user_url << endl;
                    outfile.close();
                } else {
                    cout << "Error: Could not write to file.\n";
                }

                // Add to dynamic array
                if (test_size == test_capacity) {
                    test_capacity *= 2;
                    string* new_array = new string[test_capacity];
                    for (int i = 0; i < test_size; ++i) {
                        new_array[i] = test_urls[i];
                    }
                    delete[] test_urls;
                    test_urls = new_array;
                }
                test_urls[test_size++] = user_url;
            }
        }
        else if (choice == 2) {
            history.goBack();
        }
        else if (choice == 3) {
            history.goForward();
        }
        else if (choice == 4) {
            cout << "Current URL: " << history.getCurrentUrl() << endl;
        }
        else if (choice == 5) {
            cout << "Exiting browser history.\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    delete[] test_urls;
    return 0;
}
