#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main(){
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> at(n), bt(n), ct(n), wt(n), tat(n);

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++){
        cin >> at[i] >> bt[i];
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b){ return at[a] < at[b]; });

    int time = 0;
    for (int i = 0; i < n; i++){
        int idx = order[i];
        time = max(time, at[idx]);
        wt[idx] = time - at[idx];
        time += bt[idx];
        ct[idx] = time;
        tat[idx] = time - at[idx];
    }

    cout << "\nProcess\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++){
        cout << "P" << i + 1 << "\t" << at[i] << "\t" << bt[i] << "\t" << ct[i] << "\t\t" << wt[i] << "\t" << tat[i] << endl;
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
