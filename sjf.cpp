#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main(){
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), wt(n), tat(n);
    vector<bool> done(n, false);

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++){
        cin >> at[i] >> bt[i];
    }

    int completed = 0, time = 0;

    while (completed < n){
        int idx = -1, minBt = INT_MAX;
        for (int i = 0; i < n; i++){
            if (!done[i] && at[i] <= time && bt[i] < minBt){
                minBt = bt[i];
                idx = i;
            }
        }

        if (idx == -1){
            time++;
            continue;
        }

        wt[idx] = time - at[idx];
        time += bt[idx];
        tat[idx] = time - at[idx];
        done[idx] = true;
        completed++;
    }

    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++){
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }

    double avgWt = 0, avgTat = 0;
    for (int i = 0; i < n; i++){
        avgWt += wt[i];
        avgTat += tat[i];
    }
    cout << "\nAverage Waiting Time: " << avgWt / n << endl;
    cout << "Average Turnaround Time: " << avgTat / n << endl;

    return 0;
}
