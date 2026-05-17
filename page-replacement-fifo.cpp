#include<iostream>
using namespace std;

int main()
{
    int pages[50], frames[10];
    int n, f, i, j, k = 0, fault = 0;
    bool found;

    cout<<"Enter number of pages: ";
    cin>>n;

    cout<<"Enter page reference string:\n";
    for(i=0;i<n;i++)
        cin>>pages[i];

    cout<<"Enter number of frames: ";
    cin>>f;

    for(i=0;i<f;i++)
        frames[i] = -1;

    for(i=0;i<n;i++)
    {
        found = false;

        // Check page hit
        for(j=0;j<f;j++)
        {
            if(frames[j] == pages[i])
            {
                found = true;
                break;
            }
        }

        // Page fault
        if(!found)
        {
            frames[k] = pages[i];
            k = (k + 1) % f;
            fault++;
        }

        // Display frames
        cout<<"\nFrames: ";
        for(j=0;j<f;j++)
            cout<<frames[j]<<" ";
    }

    cout<<"\n\nTotal Page Faults = "<<fault;

    return 0;
}