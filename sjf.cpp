#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> pid(n), bt(n);

    cout << "Enter burst time:\n";
    for (int i = 0; i < n; i++){
        pid[i] = i + 1;
        cin >> bt[i];
    }

    // Sort processes by burst time (shortest first), keeping pid in sync
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b){
        return bt[a] < bt[b];
    });

    vector<int> wt(n), tat(n);
    wt[0] = 0;
    for (int i = 1; i < n; i++){
        wt[i] = wt[i - 1] + bt[order[i - 1]];
    }

    cout << "\nProcess\tBurst\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++){
        int idx = order[i];
        tat[i] = wt[i] + bt[idx];
        cout << "P" << pid[idx] << "\t" << bt[idx] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }

    return 0;
}