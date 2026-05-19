#include<iostream>
using namespace std;

int main()
{
    int pages[50], frames[10], time[10];
    int n, f, i, j, pos, fault = 0, hit = 0, counter = 0;
    bool found;

    cout<<"Enter number of pages: ";
    cin>>n;

    cout<<"Enter page reference string:\n";
    for(i=0;i<n;i++)
        cin>>pages[i];

    cout<<"Enter number of frames: ";
    cin>>f;

    for(i=0;i<f;i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    for(i=0;i<n;i++)
    {
        found = false;

        // Check hit
        for(j=0;j<f;j++)
        {
            if(frames[j] == pages[i])
            {
                counter++;
                time[j] = counter;
                found = true;
                break;
            }
        }

        // Page fault
        if(!found)
        {
            pos = 0;

            for(j=1;j<f;j++)
            {
                if(time[j] < time[pos])
                    pos = j;
            }

            frames[pos] = pages[i];

            counter++;
            time[pos] = counter;

            fault++;
        }
        else
            hit++;

        // Display frames
        cout<<"\nPage "<<pages[i]<<" -> Frames: ";
        for(j=0;j<f;j++)
            cout<<frames[j]<<" ";
        cout<<(found ? "| HIT" : "| FAULT");
    }

    cout<<"\n\nTotal Page Hits = "<<hit;
    cout<<"\nTotal Page Faults = "<<fault;

    return 0;
}