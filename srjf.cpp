#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main(){
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), remaining(n);
    vector<int> wt(n, 0), tat(n, 0), ct(n, 0);
    vector<bool> done(n, false);

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++){
        cin >> at[i] >> bt[i];
        remaining[i] = bt[i];
    }

    int completed = 0, time = 0;

    while (completed < n){
        // Pick arrived process with shortest remaining burst time
        int idx = -1, minRem = INT_MAX;
        for (int i = 0; i < n; i++){
            if (!done[i] && at[i] <= time && remaining[i] < minRem){
                minRem = remaining[i];
                idx = i;
            }
        }

        if (idx == -1){
            time++;  // CPU idle: no process has arrived yet
            continue;
        }

        remaining[idx]--;
        time++;

        if (remaining[idx] == 0){
            done[idx] = true;
            completed++;
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
        }
    }

    cout << "\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++){
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t\t" << wt[i] << "\t" << tat[i] << endl;
    }

    double avgWt = 0;
    for (int i = 0; i < n; i++) avgWt += wt[i];
    cout << "\nAverage Waiting Time: " << avgWt / n << endl;

    double avgTat = 0;
    for (int i = 0; i < n; i++) avgTat += tat[i];
    cout << "Average Turnaround Time: " << avgTat / n << endl;

    return 0;
}
