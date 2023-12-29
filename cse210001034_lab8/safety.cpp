#include <bits/stdc++.h>
using namespace std;

int main() {
    // Safety Algorithm for Banker's Algorithm

    // Input:
    // 1. Number of processes
    // 2. Number of resources
    // 3. Available matrix
    // 4. Max matrix
    // 5. Allocation matrix
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;
    int alloc[n][m], max[n][m], avail[m];
    cout << "Enter available matrix: " << endl;
    for(int i = 0; i < m; i++) {
        cin >> avail[i];
    }
    cout << "Enter max matrix: " << endl;
    for(int i = 0; i < n; i++) {
        cout << "Process " << i << ": ";
        for(int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }
    cout << "Enter allocation matrix: " << endl;
    for(int i = 0; i < n; i++) {
        cout << "Process " << i << ": ";
        for(int j = 0; j < m; j++) {
            cin >> alloc[i][j];
        }
    }

    // Need matrix    
    int need[n][m];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) need[i][j] = max[i][j] - alloc[i][j];        // Need = Max - Allocation
    }

    int work[m];    // Work matrix
    for(int i = 0; i < m; i++) work[i] = avail[i];      // Initially work = available

    bool finish[n];         // Finish matrix
    memset(finish, false, sizeof(finish));          // Initially finish = false

    // Safety Algorithm
    int safeSeq[n], ind = 0;
    while(true) {
        bool flag = false;      // Flag to check if any process is allocated
        for(int i = 0; i < n; i++) {        // Iterate over all processes
            if(!finish[i]) {                // If process is not finished
                bool check = true;          // Check if need <= work
                for(int j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {      // If need > work, then process cannot be allocated
                        check = false;              // Set check to false
                        break;                      // Break out of loop
                    }
                }
                if(check) {
                    flag = true;                    // Set flag to true
                    finish[i] = true;               // Set finish to true
                    safeSeq[ind++] = i;             // Add process to safe sequence
                    for(int j = 0; j < m; j++) work[j] += alloc[i][j];          // Add allocated resources to work
                }
            }
        }
        if(!flag) break;                    // If no process is allocated, break out of loop
    }
    for(int i = 0; i < n; i++) {
        if(!finish[i]) {                    // If any process is not finished, then unsafe state
            cout << "Unsafe State" << endl;
            return 0;
        }
    }
    // Else, safe state
    cout << "Safe State" << endl;
    cout << "Safe Sequence: ";
    for(int i = 0; i < ind; i++) cout << safeSeq[i] << " "; 
    cout << endl;
    return 0;
}