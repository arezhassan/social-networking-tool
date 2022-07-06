#include<iostream>
#include<fstream>
#include <ctime>
#pragma warning(disable : 4996)
#include<iomanip>
using namespace std;
class Priority_Queue {
public:
    int H[10];
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
        while (i > 0 && H[parent(i)] > H[i]) {

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

        if (l <= size && H[l] < H[maxIndex]) {
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
    Priority_Queue events;
  //  LINKLIST < event> events;  
public:
    string name;
    string email;
    string education;
    string timeline;
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
        fin.close();
       
    }
    void setevents_infile(string name,int month,int day,int hrs,int mint,int sec) {
        ofstream f;
        f.open(file_name, ios::app);
        f << name<<" " << month << " " << day << " " << hrs << " " << mint << " " << sec << endl;
        f.close();

    }
    void events_inTree() {
        ifstream fin;
        fin.open(file_name, ios::app);
        string event_name;
        int month, day, hrs, mint, sec;
       
        while (true) {
            fin >> event_name;
            fin >> month;
            fin >> day;
            fin >> hrs;
            fin >> mint;
            fin >> sec;
            if (fin.eof())
                break;
            events.insert(month);

        }
        fin.close();

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
    void display_student_record() {
       
        cout << "User Name: " << name << endl;
        cout << "User email: " << email <<"@gmail.com" << endl;
        cout << "User education: " << education << endl;
        cout << "User joining: " << joining << endl;
    }
    void events_display(int i) {
        if (i >= events.size+1)
            return;
       
        ifstream fin;
        fin.open(file_name, ios::app);
        string event_name;
        int month, day, hrs, mint, sec;
        while (true) {
            fin >> event_name;
            fin >> month;
            fin >> day;
            fin >> hrs;
            fin >> mint;
            fin >> sec;
            if (fin.eof())
                break;
            if (month == events.H[i]) {
                cout << "EVENT NAME:" << event_name << "  MONTH:" << month << "  DAY:" << day << "  HOURS:" << hrs << "  MINT:" << mint << "  SECOND:" << sec << endl;

            }
        }
        fin.close();
        events_display(i + 1);
    }
   
  
};

class Node
{
public:
    int key;
    string name;
    string email;
    string education;
    string joining;
    Node* next;
    Node(int k, string name, string email, string education, string joining)
    {
        this->key = k;
        next = NULL;
        this->name = name;
        this->email = email;
        this->education = education;
        this->joining = joining;

    }
};

class HashTable {
    Node** arr;
    int size;
public:
    HashTable()
    {
        arr = NULL;
        size = 0;
    }
    HashTable(int size)
    {
        arr = new Node * [size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = NULL;
        }
        this->size = size;
    }
    int Convert_String_in_int(string s,int size)
    {

        int sum = 0, index = 0;
        for (string::size_type i = 0; i < s.length(); i++)
        {
            sum += s[i];
        }
        index = sum%size;
        return index;
    }
    int HashFun(int data)
    {
        int key = data % size;
        return key;
    }
    void insert(int key1, string name, string email, string education, string joining)
    {
        int key = HashFun(key1);
        cout<<"KEY : "<<key<<endl;
        Node* temp = arr[key1];
        if (temp == NULL)
        {
            arr[key1] = new Node(key1, name, email, education, joining);
        }
        else
        {
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = new Node(key1, name, email, education, joining);
        }
    }

    void display()
    {

        if (arr == NULL)
        {
            cout << "Empty HashTable." << endl;
        }
        else
        {

            for (int i = 0; i < size; i++)
            {
                cout << "arr[" << i << "] : ";
                Node* temp = arr[i];
                while (temp != NULL)
                {
                    cout << temp->key << "==>";
                    cout << temp->name << " ";
                    cout << temp->email << " ";
                    cout << temp->education << " ";
                    cout << temp->joining << " ";
                    temp = temp->next;
                }
                cout << endl;
            }
        }
    }

    bool search(students& s, int data,string name)
    {
        if (arr == NULL)
        {
            cout << "HashTable is Empty." << endl;
        }
        else
        {
            int key = HashFun(data);
            Node* temp = arr[key];
            if (temp == NULL)
            {
                cout << "Data Not Found." << endl;
                return false;
            }
            else
            {
                while (temp != NULL)
                {
                    if (temp->name == name)
                    {
                        cout << data << " found." << endl;
                        s.name = temp->name;
                        s.email = temp->email;
                        s.education = temp->education;
                        s.joining = temp->joining;
                        return true;
                    }
                    temp = temp->next;
                }
            }
            cout << "Data Not Found." << endl;
            return false;
        }
    }

};
int main() {
    students s;
    //s.Setname("majid");
    //s.Setemail("majid");
    //s.Seteducation("bsse2133");
    //s.Setjoining("2342");
    //// s.display_student_record();
    //s.Creatfile();
    //s.setfriend_inFile("arez");
    //s.setfriend_inFile("sajid");
    //s.setfriend_inFile("zajid");
    //s.setfriend_inFile("xxx");
    //s.setTimeline_inFile("hellowfriend");
    //s.setTimeline_inFile("hellowfriend");
    //s.setevent_inFile("Gango", 4, 5, 6, 5, 6);

    //s.Setname("saji");
    //s.Setemail("sajid9287");
    //s.Seteducation("bsse2133");
    //s.Setjoining("2342");
    //// s.display_student_record();
    //s.Creatfile();
    //s.setfriend_inFile("arez5");
    //s.setfriend_inFile("sajid5");
    //s.setfriend_inFile("zajid5");
    //s.setfriend_inFile("xxx6");
    //s.setTimeline_inFile("hellowfriend6");
    //s.setTimeline_inFile("hellowfriend5");
    //s.setevent_inFile("Gango", 4, 5, 6, 5, 6);



    //s.Setname("kaka");
    //s.Setemail("llkk");
    //s.Seteducation("bsse2133");
    //s.Setjoining("2342");
    //// s.display_student_record();
    //s.Creatfile();
    //s.setfriend_inFile("arez5");
    //s.setfriend_inFile("sajid5");
    //s.setfriend_inFile("zajid5");
    //s.setfriend_inFile("xxx6");
    //s.setTimeline_inFile("hellowfriend6");
    //s.setTimeline_inFile("hellowfriend5");
    //s.setevent_inFile("Gango", 4, 5, 6, 5, 6);



    string name, email, education,timeline,joining;
    int size = 0;
    int key2=0;
    ifstream fin;
    fin.open("data.txt", ios::app);
    while (!fin.eof()) {
        fin >> name;
        fin >> email;
        fin >> education;
        fin >> joining;
        size++;
    }
    fin.close();

    ifstream fi;
    fi.open("data.txt", ios::app);
    HashTable HT(size-1);
 for (int i = 0; i < size-1; i++) {
        fi >> name;
        fi >> email;
        fi >> education;
        fi >> joining;
        cout << name << " " << email << endl;
        key2 = HT.Convert_String_in_int(email,size-1);
        cout << key2;
        HT.insert(key2, name,email,education,joining);
    }
    HT.display();
    cout << " enter email" << endl;
    cin >> email;
    cout << "enter name" << endl;
    cin >> name;
    
    key2 = HT.Convert_String_in_int(email,size-1);
        cout << "search";
        
        HT.search(s,key2,name);



 
    /*s.Setname("majid");
    s.Setemail("majid");
    s.Seteducation("bsse2133");
    s.Setjoining("2342");*/
   // s.display_student_record();
       s.display_student_record();
        s.Creatfile();
   /* s.setfriend_inFile("arez");
    s.setfriend_inFile("sajid");
    s.setfriend_inFile("zajid");
    s.setfriend_inFile("xxx");
    s.setTimeline_inFile("hellowfriend");
    s.setTimeline_inFile("hellowfriend");
    s.setevent_inFile("Gango",4,5,6,5,6);*/
    s.display_friends();
    s.display_Timeline();
    s.events_inTree();
    s.events_display(0);




//mxH.insert(6);
//mxH.insert(7);
//mxH.insert(4);
//mxH.insert(5);
//mxH.display(0);
    

}