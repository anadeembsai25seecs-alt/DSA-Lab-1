#include <iostream>
#include <string>
using namespace std;


class Node {
public:
    int jobId;
    string docName;
    int pages;
    Node* next;
};


class Queue {
private:
    Node* front;
    Node* rear;
    int count;

public:
    // Constructor
    Queue() {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    // Destructor
    ~Queue() {
        clearQueue();
    }

    
    void addJob(int id, string name, int numPages) {
        Node* newNode = new Node;
        newNode->jobId = id;
        newNode->docName = name;
        newNode->pages = numPages;
        newNode->next = NULL;           // it will be the last job

        if (rear == NULL) {
            
            front = newNode;
            rear = newNode;
        }
        else {
            rear->next = newNode;     
            rear = newNode;             
        }
        count++;
        cout << "Added job " << id << " (" << name << ", " << numPages << " pages)" << endl;
    }

    
    void processJob() {
        if (front == NULL) {
            cout << "Queue is empty, no job to process." << endl;
            return;
        }
        Node* temp = front;
        cout << "Processing job " << temp->jobId << " (" << temp->docName
            << ", " << temp->pages << " pages)" << endl;

        front = front->next;            
        if (front == NULL) {
            rear = NULL;                
        }
        delete temp;
        count--;
    }

    
    void viewNextJob() {
        if (front == NULL) {
            cout << "Queue is empty, no next job." << endl;
            return;
        }
        cout << "Next job: " << front->jobId << " (" << front->docName
            << ", " << front->pages << " pages)" << endl;
    }

    
    void displayQueue() {
        if (front == NULL) {
            cout << "Queue is empty." << endl;
            return;
        }
        cout << "Waiting jobs:" << endl;
        Node* current = front;
        while (current != NULL) {
            cout << "   " << current->jobId << "  " << current->docName
                << "  " << current->pages << " pages" << endl;
            current = current->next;
        }
    }

    
    void countJobs() {
        cout << "Jobs waiting: " << count << endl;
    }

    
    bool isEmpty() {
        return front == NULL;
    }

  
    void clearQueue() {
        while (front != NULL) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
        rear = NULL;
        count = 0;
    }
};

int main() {
    Queue printer;

    // Add the four jobs
    printer.addJob(101, "Assignment1.pdf", 10);
    printer.addJob(102, "Report.docx", 25);
    printer.addJob(103, "Notes.pdf", 5);
    printer.addJob(104, "LabTask.docx", 15);

    
    cout << endl << "*Display all jobs:" << endl;
    printer.displayQueue();
    printer.countJobs();

    cout << endl << "*Process two jobs:" << endl;
    printer.processJob();
    printer.processJob();

    cout << endl << "*Remaining jobs:" << endl;
    printer.displayQueue();
    printer.countJobs();

    cout << endl << "*Add a new job:" << endl;
    printer.addJob(105, "Slides.pptx", 20);

    cout << endl << "*Next job:" << endl;
    printer.viewNextJob();

    cout << endl << "*Process all remaining jobs:" << endl;
    while (!printer.isEmpty()) {
        printer.processJob();
    }

    cout << endl << "*Process from empty queue:" << endl;
    printer.processJob();

    return 0;
}