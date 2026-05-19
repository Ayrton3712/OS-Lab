#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(){
    int n, quantum;

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> quantum;

    vector<int> at(n), bt(n), remaining(n);
    vector<int> wt(n), tat(n), ct(n);

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++){
        cin >> at[i] >> bt[i];
        remaining[i] = bt[i];
    }

    // Sort indices by arrival time so we can enqueue in order
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b){ return at[a] < at[b]; });

    queue<int> readyQueue;
    int time = 0, completed = 0, nextArrival = 0;

    // Enqueue all processes that have already arrived
    auto enqueueArrivals = [&](){
        while (nextArrival < n && at[order[nextArrival]] <= time)
            readyQueue.push(order[nextArrival++]);
    };

    enqueueArrivals();

    while (completed < n){
        if (readyQueue.empty()){
            // CPU idle: jump to next arrival
            time = at[order[nextArrival]];
            enqueueArrivals();
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        int runTime = min(remaining[idx], quantum);
        remaining[idx] -= runTime;
        time += runTime;

        // Enqueue processes that arrived during this time slice before re-queuing
        enqueueArrivals();

        if (remaining[idx] == 0){
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            completed++;
        } else {
            readyQueue.push(idx);
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
