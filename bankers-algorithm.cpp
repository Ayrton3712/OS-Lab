#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

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

void printTable(const vector<int>& safeSeq){
    // Replay the safe sequence to capture available resources before each step
    vector<vector<int>> workBefore(safeSeq.size());
    vector<int> work = Available;
    for (int i = 0; i < (int)safeSeq.size(); i++){
        workBefore[i] = work;
        int proc = safeSeq[i];
        for (int j = 0; j < R; j++)
            work[j] += Allocation[proc][j];
    }
    // work now holds total resources (final available after all processes finish)

    auto printVec = [&](const vector<int>& v){
        for (int j = 0; j < R; j++)
            cout << setw(4) << v[j];
    };
    auto printLabels = [&](){
        for (int j = 0; j < R; j++)
            cout << setw(4) << (char)('A' + j);
    };

    const int procW = 10, colW = 4 * R;
    const string sep(procW + colW * 4 + 10, '-');

    cout << "\n";
    cout << left << setw(procW) << "Process"
         << setw(colW + 2) << "Allocation"
         << setw(colW + 2) << "Maximum"
         << setw(colW + 6) << "Current Available"
         << "Remaining Needed\n";

    cout << setw(procW) << "";
    printLabels(); cout << "  ";
    printLabels(); cout << "  ";
    printLabels(); cout << "      ";
    printLabels(); cout << "\n";
    cout << sep << "\n";

    for (int i = 0; i < (int)safeSeq.size(); i++){
        int proc = safeSeq[i];

        cout << left << setw(procW) << ("P" + to_string(proc + 1));
        printVec(Allocation[proc]); cout << "  ";
        printVec(Max[proc]);        cout << "  ";
        printVec(workBefore[i]);    cout << "      ";
        printVec(Need[proc]);       cout << "\n";

        // Show allocation released after this process finishes
        cout << setw(procW) << ""
             << string(colW + 2, ' ')
             << string(colW + 2, ' ')
             << " +";
        for (int j = 0; j < R; j++)
            cout << setw(4) << Allocation[proc][j];
        cout << "\n";
    }

    cout << sep << "\n";

    // Total row: sum of all allocations, and final available (total resources)
    vector<int> totalAlloc(R, 0);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            totalAlloc[j] += Allocation[i][j];

    cout << left << setw(procW) << "Total";
    printVec(totalAlloc); cout << "  ";
    cout << setw(colW + 2) << "";
    printVec(work); cout << "\n\n";
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
        printTable(safeSeq);
        printSafeSeq(safeSeq);
    } else {
        cout << "\nSystem is in UNSAFE state.\n";
    }

    return 0;
}
