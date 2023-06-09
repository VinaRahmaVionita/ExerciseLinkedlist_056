#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }
    void addNode();
    bool search(int rollno, Node** vnt, Node** vn);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    int rollno;
    string name;
    cout << "Enter roll number: ";
    cin >> rollno;
    cout << "Enter name: ";
    cin >> name;

    Node* newNode = new Node();        //alocated memori for the new node 
    newNode->rollNumber = rollno;
    newNode->name = name;

    if (listEmpty()) {
        newNode->next = newNode;   
        LAST = newNode;
    }
    else {
        Node* vn = LAST->next;
        Node* vnt = NULL;

        do {
            vnt = vn;
            vn = vn->next;
        } while (vn != LAST->next && vn->rollNumber < rollno);

        vnt->next = newNode;
        newNode->next = vn;

        if (vn == LAST->next && vn->rollNumber > rollno) {
            LAST->next = newNode;
            LAST = newNode;
        }
    }
}

bool CircularLinkedList::search(int rollno, Node** vnt, Node** vn) {
    *vnt = LAST->next;
    *vn = LAST->next;

    while (*vn != LAST) {
        if (rollno == (*vn)->rollNumber) {
            return true;
        }
        *vnt = *vn;
        *vn = (*vn)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    if (listEmpty()) {
        cout << "List is empty. Deletion failed!" << endl;
        return false;
    }

    int rollno;
    cout << "Enter roll number of the node to delete: ";
    cin >> rollno;

    Node* vnt = NULL;
    Node* vn = NULL;

    if (!search(rollno, &vnt, &vn)) {
        cout << "Node not found. Deletion failed!" << endl;
        return false;
    }

    if (vn == LAST) {
        if (vnt == LAST) {
            LAST = NULL;
            delete vn;
            return true;
        }
        else {
            LAST = vnt;
        }
    }

    vnt->next = vn->next;
    delete vn;

    cout << "Node deleted successfully!" << endl;
    return true;
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "\nList is empty\n";
    }
    else {
        cout << "\nRecords in the list:\n";
        Node* vnNode = LAST->next;
        while (vnNode != LAST) {
            cout << vnNode->rollNumber << " " << vnNode->name << endl;
            vnNode = vnNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;

    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-5): ";
            char ch;
            cin >> ch;
            switch (ch) {
            case '1': {
                obj.addNode();
                break;
            }
            case '2': {
                obj.delNode();
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}