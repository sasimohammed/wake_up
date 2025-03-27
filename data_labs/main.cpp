#include <iostream>
#include <stack>
#include<vector>
#include<algorithm>
using namespace std;

template<typename T>
class linkedlist{
    struct node {
        T data;
        node *next;
    };
    node *start;
    node *end;
public:
    linkedlist(){
        start=NULL;
        end=NULL;

    }
    void insert(T val){
        node * newnode=new node;
        newnode->data=val;
        newnode->next=NULL;
    if(start ==NULL   ){
        start=newnode;
        end=newnode;

    }
    else{
        end->next=newnode;
        end=newnode;

    }

    }

    void deletenode(T val) {
        if (!start) return;
        // Case 1: Deleting the first node
        if (start->data == val) {
            node* temp = start;
            start = start->next;
            delete temp;
            return;
        }
        // Deleting a node in the middle or at the end
        node* temp = start;
        while (temp->next && temp->next->data != val) {
            temp = temp->next;
        }
        // If the node to delete is found
        if (temp->next) {
            node* deleted = temp->next;
            temp->next = temp->next->next;
            delete deleted;
        }
    }
    void print (){
        node *temp=start;
        if(temp){
            while(  temp ){
                cout<<temp->data<<" ";
                temp=temp->next;
            }
        }
        else{

            return ;

        }

    }
   long long  size(){
        node *temp =start;
       long long s=0;
        if(temp){
            s=1;
        }
        while(temp->next){
            s++;
            temp=temp->next;

        }
        return s;
    }

    T front (){
        if(start){
            return start->data;
        }
        throw runtime_error("List is empty");


    }

    T back(){
        if(end){
            return end->data;
        }
        throw runtime_error("List is empty");
    }
    bool isempty(){
       return start==nullptr;
    }

    void clear_list(){
        while(!isempty()) {
            node *temp = start;
            start = start->next;
            delete temp;

        }
         end=nullptr;

    }

    bool search(T val) {
        node *temp = start;
        while (temp) {
            if (temp->data == val) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    void insert_front(T val) {
        node* newnode = new node;
        newnode->data = val;
        newnode->next = start;
        start = newnode;
        if (!end) {
            end = newnode;
        }
    }

    void insert_back(T val) {
        node* newnode = new node;
        newnode->data = val;
        newnode->next = NULL;

        if (!start) {
            start = newnode;
            end = newnode;
        } else {
            end->next = newnode;
            end = newnode;
        }
    }






};

void  count_sort(vector<int>&arr){
    long long max_elem=*max_element(arr.begin(),arr.end());

    vector<int>freq(max_elem+1,0);

    vector<long long >out(arr.size());
    for(int i : arr){
        freq[i]++;
    }
    for(int i=1;i<=max_elem;i++){
        freq[i]=freq[i]+freq[i-1];
    }
    for(int i=arr.size()-1;i>=0;i--){
        out[freq[arr[i]]-1]=arr[i];
        freq[arr[i]]--;


    }

    for(auto i:out){
        cout<<i<<" ";

    }

cout<<endl;



}




template<typename T>
class circular_queue {
    T *arr;
    int front, rear, size, capacity;

public:
    circular_queue(int cap) {
        front = 0;
        rear = cap - 1;
        size = 0;
        capacity = cap;
        arr = new T[capacity];
    }

    ~circular_queue() {
        delete[] arr;
    }

    bool is_full() {
        return size == capacity;
    }

    bool is_empty() {
        return size == 0;
    }

    void enqueue(T val) {
        if (is_full()) {
            cout << "Queue is full!" << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = val;
        size++;
        cout<<rear<<endl;
    }

    void dequeue() {
        if (is_empty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        front = (front + 1) % capacity;
        size--;
    }

    T Front() {
        if (is_empty()) {
            cout << "Queue is empty!" << endl;
            return T();
        }
        return arr[front];
    }

    T back() {
        if (is_empty()) {
            cout << "Queue is empty!" << endl;
            return T();
        }
        return arr[rear];
    }

    void display() {
        if (is_empty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        cout << "Queue: ";

        int i = front;
        int count = size; // We need to print `size` elements

        while (count--) { // Loop exactly `size` times
            cout << arr[i] << " ";
            i = (i + 1) % capacity; // Move in a circular way
        }

        cout << endl;
    }

};
int precedence (char ope){
    if(ope=='+'|| ope=='-')return 1;
    if(ope=='*'|| ope=='/')return 2;
   if(ope=='^')return 3;
return 0;

}

string infix_postfix(const string& infix){
    string postfix;
stack<char>st;

for(auto c:infix){
    if(isdigit(c)){
        postfix+=c;
    }
    else if(c=='('){
        st.push(c);
    }
    else if(c==')'){
        while(!empty(st) && st.top()!='('){
            postfix+=' ';
            postfix+=st.top();
            st.pop();
        }
        if (!st.empty()) st.pop();
    }
    else {
        postfix += ' ';
        while (!st.empty() && precedence(st.top()) >= precedence(c)) {
            postfix += st.top();
            postfix += ' ';
            st.pop();
        }
        st.push(c);
    }

}

    while (!st.empty()) {
        postfix += ' ';
        postfix += st.top();
        st.pop();
    }
return postfix;



}

int value(const string& postfix) {
    stack<int> st;
    string num;

    for (auto c : postfix) {
        if (isdigit(c)) {
            num += c;
        } else if (c == ' ' && !num.empty()) {
            st.push(stoi(num));
            num.clear();
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (st.size() < 2) return -1;
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            if (c == '+') st.push(a + b);
            else if (c == '-') st.push(a - b);
            else if (c == '*') st.push(a * b);
            else  st.push(a / b);
        }
    }
    return st.empty() ? -1 : st.top();
}

#include <iostream>
using namespace std;

template <typename T>
struct node {
    T data;
    node* left;
    node* right;

    node(T val) { // Constructor
        data = val;
        left = right = nullptr;
    }
};

// Insert function
template <typename T>
node<T>* insert(node<T>* root, T val) {
    if (root == nullptr) {
        return new node<T>(val);
    }
    if (val < root->data) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

// Helper function to find the minimum value in a subtree
template <typename T>
node<T>* findMin(node<T>* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

template <typename T>
node<T>* findMax(node<T>* root) {
    while (root->right != nullptr) {
        root = root->right;
    }
    return root;
}

// Delete function
template <typename T>
node<T>* delete_node(node<T>* root, T value) {
    if (root == nullptr) {
        return root;
    }
    if (value < root->data) {
        root->left = delete_node(root->left, value);
    } else if (value > root->data) {
        root->right = delete_node(root->right, value);
    } else {
        // Case 1: No child or one child
        if (root->left == nullptr) {
            node<T>* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            node<T>* temp = root->left;
            delete root;
            return temp;
        }

        // Case 2: Two children -> Find the inorder successor
        node<T>* temp = findMin(root->right);
        root->data = temp->data;  // Replace with successor value
        root->right = delete_node(root->right, temp->data); // Delete successor
    }
    return root;
}

// **Inorder Traversal (Left, Root, Right)**
template <typename T>
void inorder(node<T>* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

// **Preorder Traversal (Root, Left, Right)**
template <typename T>
void preorder(node<T>* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

// **Postorder Traversal (Left, Right, Root)**
template <typename T>
void postorder(node<T>* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}







int main() {
//    linkedlist<int>s;
//    s.insert(1);
//    s.insert(2);
//    s.insert(3);
//s.insert_back(5);


    node<int>* root = nullptr;

    // Insert elements
    root = insert(root, 50);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 100);
    cout << "Inorder before deletion: ";
    preorder(root);
    root=delete_node(root,50);
    cout<<endl;
    preorder(root);
    cout << endl;
    node<int>* minNode = findMin(root);
    node<int>* maxNode = findMax(root);
    if (minNode) cout << "Minimum value: " << minNode->data << endl;
    if (maxNode) cout << "Maximum value: " << maxNode->data << endl;

//string infix;
//cin>>infix;
//string h=infix_postfix(infix);
//
//
//
//cout<<value(h);
//int arr[5]={2,2,7,0};
//vector<int>ar={2,2,2,2,40,3,0,0,0,0,1,1,7,0};
//    count_sort(ar);




//circular_queue<int>q(5);
//    q.enqueue(10);
//    q.enqueue(20);
//    q.enqueue(30);
//    q.enqueue(40);
//    q.enqueue(50);
//  q.dequeue();
//  q.dequeue();
//    q.enqueue(5);
//    q.display();
//
//    cout << "Front: " << q.Front() << endl;
//    cout << "Back: " << q.back() << endl;
//q.enqueue(4);






}
