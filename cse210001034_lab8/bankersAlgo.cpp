#include <bits/stdc++.h>
using namespace std;

bool safety(int processes, int resources, vector<int> available, vector<vector<int>> maximum, vector<vector<int>> allocation, vector<int> &safeSeq){
    vector<vector<int>> need(processes, vector<int>(resources));
    for(int i = 0; i < processes; i++){
        for(int j = 0; j < resources; j++){
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    vector<int> work(available);
    vector<bool> finish(processes, false);

    int ind = 0;
    while(true){
        bool flag = false;
        for(int i = 0; i < processes; i++){
            if(!finish[i]){
                bool check = true;
                for(int j = 0; j < resources; j++){
                    if(need[i][j] > work[j]){
                        check = false;
                        break;
                    }
                }
                if(check){
                    flag = true;
                    finish[i] = true;
                    safeSeq[ind++] = i;
                    for(int j = 0; j < resources; j++){
                        work[j] += allocation[i][j];
                    }
                }
            }
        }
        if(!flag) break;
    }

    for(int i = 0; i < processes; i++){
        if(!finish[i]) return false;
    }
    return true;
};

int main(){
    int processes, resources;
    cout << "Enter number of processes: ";
    cin >> processes;
    cout << "Enter number of resources: ";
    cin >> resources;
    vector<int> available(resources);
    cout << "Enter available matrix: " << endl;
    for(int i = 0; i < resources; i++){
        cin >> available[i];
    }
    vector<vector<int>> maximum(processes, vector<int>(resources));
    cout << "Enter maximum matrix: " << endl;
    for(int i = 0; i < processes; i++){
        cout << "Process " << i << ": ";
        for(int j = 0; j < resources; j++){
            cin >> maximum[i][j];
        }
    }
    vector<vector<int>> allocation(processes, vector<int>(resources));
    cout << "Enter allocation matrix: " << endl;
    for(int i = 0; i < processes; i++){
        cout << "Process " << i << ": ";
        for(int j = 0; j < resources; j++){
            cin >> allocation[i][j];
        }
    }
    vector<int> safeSeq(processes, -1);
    bool safety_check = safety(processes, resources, available, maximum, allocation, safeSeq);
    if(!safety_check){
        cout << "System is not in safe state" << endl;
    }
    else{
        cout << "Safe sequence: ";
        for(int i = 0; i < processes; i++){
            cout << safeSeq[i] << " ";
        }
    }
    return 0;
}