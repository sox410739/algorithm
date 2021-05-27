#include <iostream>
#include <vector>

using namespace std;
void DFSarrReset(int DFSarr[], int num);
void DFS(vector<int> adjacentList[], bool DFSarr[], int current);

int main()
{
    int numOfVertex;
    int numOfEdge;
    cin >> numOfVertex >> numOfEdge;
    vector<int> adjacentList[numOfVertex];
    bool DFSarr[numOfVertex];
    DFSarrReset(DFSarr, numOfVertex);
    for(int i=0;i<numOfEdge;i++){
        int temp1, temp2;
        cin >> temp1 >> temp2;
        adjacentList[temp1-1].push_back(temp2);
        adjacentList[temp2-1].push_back(temp1);
    }
    int edgeConnectivity = 0;


    return 0;
}

void DFSarrReset(bool DFSarr[], int num){
    for(int i=0;i<num;i++){
        DFSarr[i] = false;
    }
}

void DFS(vector<int> adjacentList[], bool DFSarr[], int current){
    DFSarr[current-1] = true;
    for(int i=0;i<adjacentList[current-1].size();i++){
        if(DFSarr[adjacentList[current-1].at(i)-1] == false){
            DFS(adjacentList, DFSarr, adjacentList[current-1].at(i));
        }
    }
}

void removeEdge()
