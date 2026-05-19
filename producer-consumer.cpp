#include <iostream>

using namespace std;

const int SIZE = 5;

int buffer[SIZE];
int in = 0, out = 0, bufferCount = 0;

void produce(int);
void consume();
void printBuffer();

int main(){
    int choice, item;
    
    do{
        cout << "\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch(choice){
            case 1:
                cout << "Enter item: ";
                cin >> item;
                produce(item);
                break;
            case 2:
                consume();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 3);

    return 0;
}

void printBuffer(){
    cout << "Buffer [" << bufferCount << "/" << SIZE << "]: [ ";
    for (int i = 0; i < SIZE; i++){
        if (i < bufferCount)
            cout << buffer[(out + i) % SIZE];
        else
            cout << "_";
        if (i < SIZE - 1) cout << " | ";
    }
    cout << " ]\n";
}

void produce(int item){
    if (bufferCount == SIZE){
        cout << "Buffer is full\n";
        printBuffer();
        return;
    }

    buffer[in] = item;
    in = (in + 1) % SIZE;
    bufferCount++;

    cout << "Produced " << item << "\n";
    printBuffer();
}

void consume(){
    if (bufferCount == 0){
        cout << "Buffer is empty\n";
        printBuffer();
        return;
    }

    int item = buffer[out];
    out = (out + 1) % SIZE;
    bufferCount--;

    cout << "Consumed " << item << "\n";
    printBuffer();
}