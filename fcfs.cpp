#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> bt(n), wt(n), tat(n);

    cout << "Enter burst time:\n";
    for (int i = 0; i < n; i++){
        cin >> bt[i];
    }

    wt[0] = 0;

    for (int i = 1; i < n; i++){
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    cout << "\nProcess\tBurst\tWaiting\tTurnaround\n";

    for (int i = 0; i < n; i++){
        tat[i] = wt[i] + bt[i];
        cout << "P" << i + 1 << "\t" << bt[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }

    return 0;
}