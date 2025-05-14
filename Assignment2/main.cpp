#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct person {
private:
    string name;
    string email;
    string phone;

public:
    person() = default;

    person(string this_name, string this_email, string this_phone) {
        name = this_name;
        email = this_email;
        phone = this_phone;
    }

    string getName() const { return name; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }
};

struct node {
    person data;
    node* left;
    node* right;
    int id;
    int height;

    explicit node(person new_data, int new_id) {
        data = new_data;
        left = right = nullptr;
        id = new_id;
        height = 1;
    }
};

int height(node* root) {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

int getBalance(node* root) {
    if (root == nullptr) {
        return 0;
    }
    return height(root->left) - height(root->right);
}

node* rotateRight(node* y) {
    node* x = y->left;
    node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

node* rotateLeft(node* x) {
    node* y = x->right;
    node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

bool exists(node* root, int id) {
    if (root == nullptr) return false;
    if (id == root->id) return true;
    if (id < root->id) return exists(root->left, id);
    return exists(root->right, id);
}

node* insert(node* root, person& contact, int id) {
    if (root == nullptr) {
        return new node(contact, id);
    }



    if (id < root->id) {
        root->left = insert(root->left, contact, id);
    } else if (id > root->id) {
        root->right = insert(root->right, contact, id);
    } else {
        cout << "A contact with this ID already exists.\n";
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && id < root->left->id)
        return rotateRight(root);
    if (balance < -1 && id > root->right->id)
        return rotateLeft(root);
    if (balance > 1 && id > root->left->id) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && id < root->right->id) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}



pair<person, int> add_new_contact() {
    cout << "Enter unique ID (integer): ";
    int id;
    cin >> id;
    cin.ignore();



    string name, phone, email;
    cout << "Enter name: ";
    getline(cin, name);
    cout << "Enter phone: ";
    getline(cin, phone);
    cout << "Enter email: ";
    getline(cin, email);

    person new_contact(name, email, phone);

    return {new_contact, id};
}

void inOrderTraversal(node* root) {
    if (root == nullptr)
        return;

    inOrderTraversal(root->left);

    cout << "ID: " << root->id << "\n";
    cout << "Name: " << root->data.getName() << "\n";
    cout << "Phone: " << root->data.getPhone() << "\n";
    cout << "Email: " << root->data.getEmail() << "\n";
    cout << "-----------------------------\n";

    inOrderTraversal(root->right);
}

node* findMin(node* root) {
    while (root && root->left != nullptr) {
        root = root->left;
    }
    return root;
}




node* delete_node(node* root, int id) {
    if (!exists(root, id)) {
        cout << "ID " << id << " not found in the tree.\n";
        return root;
    }

    if (id < root->id) {
        root->left = delete_node(root->left, id);
    } else if (id > root->id) {
        root->right = delete_node(root->right, id);
    } else {
        if (root->left == nullptr) {
            node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            node* temp = root->left;
            delete root;
            return temp;
        }

        node* temp = findMin(root->right);
        root->data = temp->data;
        root->id = temp->id;
        root->right = delete_node(root->right, temp->id);
    }


    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}


void display_tree(node* root) {
    if (root == nullptr)
        return;

    display_tree(root->left);
    cout << root->id << "\n";
    display_tree(root->right);
}

node* search(node* root, int id) {
    if (root == nullptr || root->id == id)
        return root;

    if (id < root->id)
        return search(root->left, id);
    else
        return search(root->right, id);
}

int main() {
    node* root = nullptr;

    cout << "\nAddress Book Application\n";
    cout << "====================================" << endl;

    while (true) {
        cout << "1. Add New Contact\n";
        cout << "2. Search for Contact\n";
        cout << "3. Delete Contact (Optional)\n";
        cout << "4. List All Contacts (Sorted by ID)\n";
        cout << "5. Display Current Tree Structure\n";
        cout << "6. Exit\n";
        cout << "------------------------\n";
        cout << "Enter operation (1-6): ";

        int choice;
        cin >> choice;
        if (choice < 1 || choice > 6) {
            cout << "Enter a valid number (1-6)" << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                auto [contact, id] = add_new_contact();
                root = insert(root, contact, id);
                break;
            }
            case 2: {
                cout << "Enter ID to search: ";
                int search_id;
                cin >> search_id;
                node* result = search(root, search_id);
                if (result) {
                    cout << "\nContact Found:\n";
                    cout << "ID: " << result->id << "\n";
                    cout << "Name: " << result->data.getName() << "\n";
                    cout << "Phone: " << result->data.getPhone() << "\n";
                    cout << "Email: " << result->data.getEmail() << "\n";
                    cout << "-----------------------------\n";
                } else {
                    cout << "No contact found with ID: " << search_id << endl;
                }
                break;
            }
            case 3: {
                cout << "Enter ID: ";
                int id;
                cin >> id;
                root = delete_node(root, id);
                break;
            }
            case 4:
                cout << "List All Contacts selected.\n";
                inOrderTraversal(root);
                break;
            case 5:
                cout << "Display Tree Structure selected.\n";
                display_tree(root);
                break;
            case 6:
                return 0;
        }
    }
}
