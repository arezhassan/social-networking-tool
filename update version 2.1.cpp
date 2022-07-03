#include<iostream>
#include<fstream>
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
//
//int main() {
//    event a;
//    event b;
//    event c;
//    event d;
//    a.setdate(12);
//    b.setdate(4);
//    c.setdate(1);
//    d.setdate(9);
//
//    PriorityQ q;
//    q.insert(b.date);
//    q.insert(a.date);
//    q.insert(c.date);
//    q.insert(d.date);
//
//
//    int i = 0;
//
//    // Priority queue before extracting max
//    cout << "Priority Queue : ";
//    while (i <= q.size) {
//        cout << q.H[i] << " ";
//        i++;
//    }
//
//    cout << "\n";
//
//    // Node with maximum priority
//    cout << "Node with maximum priority : "
//        << q.extractMax() << "\n";
//    q.remove(45);
//    cout << "Node with maximum priority : "
//        << q.extractMax() << "\n";
//}




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

    void setevent(string event_Name,int mon,int da,int H, int M, int S) {

        b.setTime(H, M, S);
       event_name= event_Name;
        month= mon;
         date= da;
    }
 
};
class students {
   
   
    Node_Avl* friends=NULL;
    
  //  LINKLIST < event> events;  
public:
    string timeline;
    string name;
    string email;
    string education;
    string joining;
    string file_name  ;
    string file_name1 ;
    string file_name2;
    void setfriend_inTree(string name) {
        friends = insertNode(friends, name);
    }
    void setfriend_inFile(string n) {
        ofstream fout;
        fout.open(file_name1, ios::app);
        fout << n << endl;
        fout.close();
    }
    void setevent_inFile(string event_Name, int mon, int da, int H, int M, int S) {
        ofstream fout;
        fout.open(file_name, ios::app);
        fout << event_Name <<" " << mon << " " << da << " " << H << " " << M << " " << S<<endl;
        fout.close();
    }
   void setTimeline_inFile(string line) {
        ofstream f;
        f.open(file_name2, ios::app);
        f << line << endl;
        f.close();
    }
    void display_friends() {
        ifstream fin;
        fin.open(file_name1, ios::app);
        string name;
        while (!fin.eof()) {
            fin >> name;
            setfriend_inTree( name);
        }
        cout << "FRIENDS LIST::" << endl;
        printTree(friends);
    }
    void display_Timeline() {
        ifstream fin;
        fin.open(file_name2, ios::app);
        string lines;
        cout << "\nTime line:: " << endl;
        while (!fin.eof() ){
            fin >> lines;
            cout << lines << "\n";
        }
        
       
    }
    
    void Creatfile() {
         file_name = file_name1= file_name2=name;
         ofstream event_data;
         file_name = file_name += ".txt";
         event_data.open(file_name, ios::app);
         event_data.close();
        
        ofstream friend_data;
        file_name1 = file_name1 += "1";
        file_name1 = file_name1 += ".txt";
        friend_data.open(file_name1, ios::app);
        friend_data.close();

        ofstream timeline_data;
        file_name2 = file_name2 += "2";
        file_name2 = file_name2 += ".txt";
        timeline_data.open(file_name2, ios::app);
        timeline_data.close();
    }
    
    void Setname(string n) {
        ofstream fout;
        fout.open("data.txt", ios::app);
        fout << endl;
        fout << n<<endl;
        fout.close();
        name = n;
       
       
    }
    void Setemail(string m) {
        ofstream fout;
        fout.open("data.txt", ios::app);
       
        fout << m<<endl;
        fout.close();
       // email=m;
    }
    void Seteducation(string e) {
        ofstream fout;
        fout.open("data.txt",ios::app);
        fout << e << endl;
        fout.close();
      //  education=e;
    }
    void Setjoining(string j) {
        ofstream fout;
        fout.open("data.txt", ios::app);
        fout << j << endl;
        fout.close();
       
      //  joining=j;
    }
  
};
int main() {

    students s;
    s.Setname("majid");
    s.Setemail("majid@gmail.com");
    s.Seteducation("bsse2133");
    s.Setjoining("2342");
    s.Creatfile();
   s.setfriend_inFile("arez");
    s.setfriend_inFile("sajid");
    s.setfriend_inFile("zajid");
    s.setfriend_inFile("xxx");
    s.setTimeline_inFile("hellowfriend");
    s.setTimeline_inFile("hellowfriend");
    s.setevent_inFile("Gango",4,5,6,5,6);
    s.display_friends();
    s.display_Timeline();
    

}