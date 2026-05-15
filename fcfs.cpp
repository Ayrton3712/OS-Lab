#include <iostream>

using namespace std;

int main(){
    int n, bt[10], wt[10], tat[10], i;

    cout << "Enter the number of processes: ";
    cin >> n;

    cout << "Enter burst time:\n";
    for (i = 0; i < n; i++){
        cin >> bt[i];
    }

    wt[0] = 0; // First waiting time, this corresponds to the waiting time of the first process

    // Calculating waiting times of the other processes
    for (i = 1; i < n; i++){
        wt[i] = wt[i - 1] + bt[i - 1]; // Waiting time for the current process = Waiting time of the previous process + Its burst time
    }

    cout << "\nProcess\tBurst\tWaiting\tTurnaround\n";

    for (i = 0; i < n; i++){
        tat[i] = wt[i] + bt[i];
        cout << "P" << i + 1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }

    return 0;
}