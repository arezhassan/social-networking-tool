#include<iostream>
#include <ctime>
#pragma warning(disable : 4996)
#include<iomanip>

using namespace std;


class Node_Avl {
public:
    string key;
    Node_Avl* left;
    Node_Avl* right;
    int height;
};

string max(string a, string b);

// Calculate height
int height(Node_Avl* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

string max(string a, string b) {
    return (a > b) ? a : b;
}

// New node creation
Node_Avl* newNode(string key) {
    Node_Avl* node = new Node_Avl();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

// Rotate right
Node_Avl* rightRotate(Node_Avl* y) {
    Node_Avl* x = y->left;
    Node_Avl* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left),
        height(y->right)) +
        1;
    x->height = max(height(x->left),
        height(x->right)) +
        1;
    return x;
}

// Rotate left
Node_Avl* leftRotate(Node_Avl* x) {
    Node_Avl* y = x->right;
    Node_Avl* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left),
        height(x->right)) +
        1;
    y->height = max(height(y->left),
        height(y->right)) +
        1;
    return y;
}

// Get the balance factor of each node
int getBalanceFactor(Node_Avl* N) {
    if (N == NULL)
        return 0;
    return height(N->left) -
        height(N->right);
}

// Insert a node
Node_Avl* insertNode(Node_Avl* node, string key) {
    // Find the correct postion and insert the node
    if (node == NULL)
        return (newNode(key));
    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    // Update the balance factor of each node and
    // balance the tree
    node->height = 1 + max(height(node->left),
        height(node->right));
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return rightRotate(node);
        }
        else if (key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (key > node->right->key) {
            return leftRotate(node);
        }
        else if (key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

// Node with minimum value
Node_Avl* nodeWithMimumValue(Node_Avl* node) {
    Node_Avl* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Delete a node
Node_Avl* deleteNode(Node_Avl* root, string key) {
    // Find the node and delete it
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) ||
            (root->right == NULL)) {
            Node_Avl* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }
        else {
            Node_Avl* temp = nodeWithMimumValue(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right,
                temp->key);
        }
    }

    if (root == NULL)
        return root;

    // Update the balance factor of each node and
    // balance the tree
    root->height = 1 + max(height(root->left),
        height(root->right));
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

// Print the tree
void printTree(Node_Avl* root) {
    if (root != nullptr) {
        printTree(root->left);
        cout << root->key << " , ";
        printTree(root->right);
    }
}
class Node
{
public:
    float data;
    Node* next;
};

template<class T>
class node
{
private:

    T  data;
    node* nextnode;
public:
    node() {

        this->data = 0;

        this->nextnode = NULL;
    }
    node(T data) {

        this->data = data;

        this->nextnode = NULL;
    }
    void setdata(T marks) {
        this->data = marks;
    }
    void setnextnode(node* nextnode) {
        this->nextnode = nextnode;
    }
    T getdata() {
        return this->data;
    }
    node* getnextnode() {
        return this->nextnode;
    }
};
template<class T>
class LINKLIST
{
private:
    node<T>* head;
    node<T>* tail;
public:
    LINKLIST<T>()
    {
        head = NULL;
        tail = NULL;
    }
    void enque(T data)
    {

        node< T>* t = new node<T>(data);
        if (head == NULL)
        {
            head = t;
            tail = t;
        }
        else
        {
            tail->setnextnode(t);
            tail = t;

        }


    }
    void display()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
        }
        else
        {
            node<T>* temp = head;
            while (temp != NULL)
            {
                cout << temp->getdata() << endl;
                temp = temp->getnextnode();
            }
        }
    }
    void deleteFromStart()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
        }
        else
        {
            node<T>* temp = head;

            if (head == tail)
            {
                head = tail = NULL;
                delete temp;
            }
            else
            {
                head = head->getnextnode();
                delete temp;
            }
        }
    }


    void deleteData(T data)
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
        }
        else
        {
            node<T>* temp = head;

            if (head->getdata() == data)
            {
                deleteFromStart();
            }
            else if (tail->getdata() == data)
            {
                deleteFromEnd();
            }
            else
            {
                node<T>* prev = head;
                node<T>* temp = prev->getnextnode();

                bool found = false;

                while (temp->getnextnode() != NULL)
                {
                    if (temp->getdata() == data)
                    {
                        prev->setnextnode(temp->getnextnode());
                        delete temp;
                        found = true;
                        break;
                    }

                    prev = temp;
                    temp = temp->getnextnode();
                }

                if (found == false)
                {
                    cout << "Data not found" << endl;
                }
                else
                {
                    cout << "Data deleted successfully" << endl;
                }
            }
        }
    }



    void deleteFromEnd()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
        }
        else
        {
            node<T>* temp = head;

            if (head == tail)
            {
                head = tail = NULL;
                delete temp;
            }
            else
            {
                while (temp->getnextnode() != tail)
                {
                    temp = temp->getnextnode();
                }
                tail = temp;
                temp = temp->getnextnode();
                delete temp;
                tail->setnextnode(NULL);
            }
        }
    }
    node<T>* getHead() {
        return head;
    }
    void update_element(T d, T update_ele)
    {
        int count = 0;

        node<T>* temp = head;
        while (temp != NULL) // Start traversing from head node
        {
            if (temp->getdata() == d)
            {

                temp->setdata(update_ele);// change the element in the list
            }
            else
            {
                count = count + 1;
                temp = temp->getnext();
            }
        }
    }
    void Contactdelet(string n)
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
        }
        else
        {
            node<T>* temp = head;

            if (head->getdata().name == n || head->getdata().cell_phone == n)
            {
                deleteFromStart();
            }
            else if (tail->getdata().name == n || tail->getdata().cell_phone == n)
            {
                deleteFromEnd();
            }
            else
            {
                node<T>* prev = head;
                node<T>* temp = prev->getnextnode();

                bool found = false;

                while (temp->getnextnode() != NULL)
                {
                    if (temp->getdata().name == n || temp->getdata().cell_phone == n)
                    {
                        prev->setnextnode(temp->getnextnode());
                        delete temp;
                        found = true;
                        break;
                    }

                    prev = temp;
                    temp = temp->getnextnode();
                }

                if (found == false)
                {
                    cout << "Data not found" << endl;
                }
                else
                {
                    cout << "Data deleted successfully" << endl;
                }
            }
        }
    }
    void eventprint()
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
        }
        else
        {

            node<T>* temp = head;
            while (temp != NULL)
            {

                cout << temp->getdata().event_name << "   ";
                cout << temp->getdata().date << " ";
                cout << temp->getdata().month << " ";
                cout << temp->getdata().year << endl;

                temp = temp->getnextnode();
            }
        }
    }
    T search(string n, bool& check)
    {
        if (head == NULL)
        {
            cout << "List is empty" << endl;
        }
        else
        {

            node<T>* temp = head;
            while (temp != NULL)
            {

                if (temp->getdata().name == n || temp->getdata().cell_phone == n) {
                    check = true;
                    return temp->getdata();
                }
                temp = temp->getnextnode();
            }
        }
        check = false;
        return head->getdata();

    }


};


class Time
{
public:
    int hour;
    int minute;
    int second;


    Time(int h = 0, int m = 0, int s = 0);

    void setTime(int h, int m, int s);

    void print();

    bool equals(Time);
};

Time::Time(int h, int m, int s)
{
    hour = h;
    minute = m;
    second = s;
}

void Time::setTime(int h, int m, int s)
{
    hour = h;
    minute = m;
    second = s;
}

void Time::print()
{
    cout << setw(2) << setfill('0') << hour << ":"
        << setw(2) << setfill('0') << minute << ":"
        << setw(2) << setfill('0') << second << "\n";
}

bool Time::equals(Time otherTime)
{
    if (hour == otherTime.hour &&
        minute == otherTime.minute &&
        second == otherTime.second)
        return true;
    else
        return false;
}
class event {
public:
    string event_name;
    int month;
    int date;
    Time b;
    void setTIME(Time a) {
        b.setTime(a.hour, a.minute,a.second);
    }
    void seteventname(string ev) {
        this->event_name = ev;
    }
    void setmon(int m) {
        this->month = m;
    }
    void setdate(int d) {
        this->date = d;
    }

    void ltime() {
        time_t curr_time;
        curr_time = time(NULL);
        tm* a = localtime(&curr_time);
        int ldate = a->tm_mday;
        int lmonth = a->tm_mon;
        int lhour = a->tm_hour;
        int lmin = a->tm_min;
        int lsec = a->tm_sec;
        cout << "LOCAL DATE IS : \n";
        cout << ldate << "/" << lmonth << "/2022\n";
        cout << "LOCAL TIME IS : " << lhour << " " << lmin << "mins\n";
        
    }
  


};
class students {
    LINKLIST <string> timeline;
    LINKLIST <string >friends;
    LINKLIST < event> events;
public:
    void Settimeline(string data) {
        timeline.enque(data);
    }
    void setfriends(string data) {
        friends.enque(data);
    }
    void setevents(event e) {
        events.enque(e);
    }
    void getfriends() {
        friends.display();
    }
    void getevents() {
        //  events.display();
    }
    void gettimeline() {
        timeline.display();
    }
};

class PriorityQ {
public:
    int H[50];
    int size = -1;

    // Function to return the index of the
    // parent node of a given node
    int parent(int i)
    {

        return (i - 1) / 2;
    }

    // Function to return the index of the
    // left child of the given node
    int leftChild(int i)
    {

        return ((2 * i) + 1);
    }

    // Function to return the index of the
    // right child of the given node
    int rightChild(int i)
    {

        return ((2 * i) + 2);
    }

    // Function to shift up the node in order
    // to maintain the heap property
    void shiftUp(int i)
    {
        while (i > 0 && H[parent(i)] < H[i]) {

            // Swap parent and current node
            swap(H[parent(i)], H[i]);

            // Update i to parent of i
            i = parent(i);
        }
    }

    // Function to shift down the node in
    // order to maintain the heap property
    void shiftDown(int i)
    {
        int maxIndex = i;

        // Left Child
        int l = leftChild(i);

        if (l <= size && H[l] > H[maxIndex]) {
            maxIndex = l;
        }

        // Right Child
        int r = rightChild(i);

        if (r <= size && H[r] > H[maxIndex]) {
            maxIndex = r;
        }

        // If i not same as maxIndex
        if (i != maxIndex) {
            swap(H[i], H[maxIndex]);
            shiftDown(maxIndex);
        }
    }

    // Function to insert a new element
    // in the Binary Heap
    void insert(int p)
    {
        size = size + 1;
        H[size] = p;

        // Shift Up to maintain heap property
        shiftUp(size);
    }

    // Function to extract the element with
    // maximum priority
    int extractMax()
    {
        int result = H[0];

        // Replace the value at the root
        // with the last leaf
        H[0] = H[size];
        size = size - 1;

        // Shift down the replaced element
        // to maintain the heap property
        shiftDown(0);
        return result;
    }

    // Function to change the priority
    // of an element
    void changePriority(int i, int p)
    {
        int oldp = H[i];
        H[i] = p;

        if (p > oldp) {
            shiftUp(i);
        }
        else {
            shiftDown(i);
        }
    }

    // Function to get value of the current
    // maximum element
    int getMax()
    {

        return H[0];
    }

    // Function to remove the element
    // located at given index
    void remove(int i)
    {
        H[i] = getMax() + 1;

        // Shift the node to the root
        // of the heap
        shiftUp(i);

        // Extract the node
        extractMax();
    }
};

int main(){
    event a;
    event b;
    event c;
    event d;
    a.setdate(12);
    b.setdate(4);
    c.setdate(1);
    d.setdate(9);

    PriorityQ q;
    q.insert(a.date);
    q.insert(b.date);
    q.insert(c.date);
    q.insert(d.date);
   
    
    int i = 0;

    // Priority queue before extracting max
    cout << "Priority Queue : ";
    while (i <= q.size) {
        cout << q.H[i] << " ";
        i++;
    }

    cout << "\n";

    // Node with maximum priority
    cout << "Node with maximum priority : "
        << q.extractMax() << "\n";
    q.remove(45);
    cout << "Node with maximum priority : "
        << q.extractMax() << "\n";


    return 0;

}
