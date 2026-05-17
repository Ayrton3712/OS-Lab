#include <iostream>
using namespace std;

int main(){
    int pages, frames, pageSize;

    cout << "Enter the number of pages: ";
    cin >> pages;

    cout << "Enter the number of frames: ";
    cin >> frames;

    cout << "Enter page size: ";
    cin >> pageSize;

    int pageTable[20];

    cout << "Enter frame number for each page:\n";
    for (int i = 0; i < pages; i++){
        cout << "Page " << i << ": ";
        cin >> pageTable[i];
    }

    int logicalAddress;

    cout << "Enter the logical address: ";
    cin >> logicalAddress;

    // Step 1: Find page number
    int pageNumber = logicalAddress / pageSize;

    // Step 2: Find offset
    int offset = logicalAddress % pageSize;

    // Step 3: Check valid page
    if (pageNumber >= pages){
        cout << "Invalid logical address\n";
        return 0;
    }

    // Step 4: Get frame number
    int frameNumber = pageTable[pageNumber];

    // Step 5: Calculate physical address
    int physicalAddress = frameNumber * pageSize + offset;

    cout << "\nPage Number: " << pageNumber;
    cout << "\nOffset: " << offset;
    cout << "\nFrame number: " << frameNumber;
    cout << "\nPhysical Address: " << physicalAddress << endl;

    return 0;
}