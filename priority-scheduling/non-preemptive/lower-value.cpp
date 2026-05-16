#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main(){
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), priority(n);
    vector<int> wt(n), tat(n);
    vector<bool> done(n, false);

    cout << "Enter arrival time, burst time, and priority for each process:\n";
    for (int i = 0; i < n; i++){
        cin >> at[i] >> bt[i] >> priority[i];
    }

    int completed = 0, time = 0;

    while (completed < n){
        int idx = -1, bestPriority = INT_MAX;
        for (int i = 0; i < n; i++){
            if (!done[i] && at[i] <= time && priority[i] < bestPriority){
                bestPriority = priority[i];
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

    cout << "\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++){
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << priority[i] << "\t\t" << wt[i] << "\t" << tat[i] << endl;
    }

    return 0;
}
