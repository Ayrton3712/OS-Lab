#include <iostream>
#include <vector>

using namespace std;

int P, R;
vector<vector<int>> Max, Allocation, Need;
vector<int> Available;

void readInput(){
    cout << "Enter number of processes: ";
    cin >> P;
    cout << "Enter number of resources: ";
    cin >> R;

    Available.resize(R);
    Max.assign(P, vector<int>(R));
    Allocation.assign(P, vector<int>(R));
    Need.assign(P, vector<int>(R));

    cout << "Enter available resources:\n";
    for (int j = 0; j < R; j++)
        cin >> Available[j];

    cout << "Enter Max matrix (" << P << "x" << R << "):\n";
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            cin >> Max[i][j];

    cout << "Enter Allocation matrix (" << P << "x" << R << "):\n";
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            cin >> Allocation[i][j];
}

void calculateNeed(){
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}

bool isSafe(vector<int>& safeSeq){
    vector<int> work = Available;
    vector<bool> finish(P, false);
    safeSeq.clear();

    while ((int)safeSeq.size() < P){
        bool progress = false;
        for (int i = 0; i < P; i++){
            if (finish[i]) continue;

            // Check if Need[i] <= work for all resources
            bool canRun = true;
            for (int j = 0; j < R; j++){
                if (Need[i][j] > work[j]){
                    canRun = false;
                    break;
                }
            }

            if (canRun){
                for (int j = 0; j < R; j++)
                    work[j] += Allocation[i][j];
                finish[i] = true;
                safeSeq.push_back(i);
                progress = true;
            }
        }

        if (!progress) return false;
    }

    return true;
}

void printSafeSeq(const vector<int>& safeSeq){
    cout << "Safe Sequence: ";
    for (int i = 0; i < (int)safeSeq.size(); i++){
        cout << "P" << safeSeq[i] + 1;
        if (i + 1 < (int)safeSeq.size()) cout << " -> ";
    }
    cout << endl;
}

int main(){
    readInput();
    calculateNeed();

    vector<int> safeSeq;
    if (isSafe(safeSeq)){
        cout << "\nSystem is in SAFE state.\n";
        printSafeSeq(safeSeq);
    } else {
        cout << "\nSystem is in UNSAFE state.\n";
    }

    return 0;
}
