#include <iostream>
#include <vector>
#include <stack>

using namespace std;
struct graph{
    int vertex;
    bool stage;
};
void insertBoth(vector<graph> adj[], int num1, int num2);
void quickSort(vector<graph> &arr, int start, int End);
void check(vector<graph> adj[], int numOfVertex);
void checkConnectDFS(vector<graph> adj[], vector<graph> &allVector, int currentPoint);
bool notConnect(vector<graph> &allVector, int length);
int numOfOddDegree(vector<graph> adj[], int numOfVervex);
void goThough(vector<graph> adj[], stack<int> &circuit, int currentPoint);
void changeBoth(vector<graph> adj[], int num1, int num2, bool change);
void print(stack<int> &circuit);

int main()
{
    int numOfVertex, numOfEdge;
    cin >> numOfVertex >> numOfEdge;
    vector<graph> allVertex;
    vector<graph> adj[numOfVertex+1];
    stack<int> circuit;
    for(int i=0;i<numOfEdge;i++){
        int temp1, temp2;
        cin >> temp1 >> temp2;
        insertBoth(adj, temp1, temp2);
    }
    for(int i=1;i<numOfVertex+1;i++){
        quickSort(adj[i], 0, adj[i].size()-1);
        graph temp;
        temp.vertex = i;
        temp.stage = false;
        allVertex.push_back(temp);
    }
    checkConnectDFS(adj, allVertex, 0);
    //cout << adj[8890].size() << endl;
    if(notConnect(allVertex, numOfVertex)){
        cout << "not exist" << endl;
    }
    else{
        switch(numOfOddDegree(adj, numOfVertex)){
        case 0:
            goThough(adj, circuit, 1);
            print(circuit);
            break;
        case -1:
            cout << "not exist" << endl;
            break;
        default:
            goThough(adj, circuit, numOfOddDegree(adj, numOfVertex));
            print(circuit);
            break;
        }
    }
    //check(adj, numOfVertex);

    return 0;
}

void insertBoth(vector<graph> adj[], int num1, int num2){
    graph temp1;
    graph temp2;
    temp1.vertex = num1;
    temp1.stage = false;
    temp2.vertex = num2;
    temp2.stage = false;
    adj[num1].push_back(temp2);
    adj[num2].push_back(temp1);
}

void quickSort(vector<graph> &arr, int start, int End){
    if(start >= End){
        return;
    }
    int pivot = arr.at(End).vertex;
    int i = -1;
    graph temp;
    for(int j=0;j<End;j++){
        if(arr.at(j).vertex < pivot){
            i++;
            temp = arr.at(i);
            arr.at(i) = arr.at(j);
            arr.at(j) = temp;
        }
    }
    i++;
    temp = arr.at(i);
    arr.at(i) = arr.at(End);
    arr.at(End) = temp;
    quickSort(arr, start, i-1);
    quickSort(arr, i+1, End);
}

void check(vector<graph> adj[], int numOfVertex){
    int length = 0;
    for(int i=1;i<numOfVertex+1;i++){
        //cout << i << ": ";
        length = adj[i].size();
        for(int j=0;j<length;j++){
            //cout << adj[i].at(j).vertex << "/" << adj[i].at(j).stage << "\t";
            if(adj[i].at(j).stage == true){
                cout << adj[i].at(j).vertex << endl;
            }
        }
        //cout << endl;
    }
}

void checkConnectDFS(vector<graph> adj[], vector<graph> &allVector, int currentPoint){
    allVector.at(currentPoint).stage = true;
    int length = adj[currentPoint+1].size();
    for(int i=0;i<length;i++){
        if(allVector.at(adj[currentPoint+1].at(i).vertex - 1).stage == false){
            checkConnectDFS(adj, allVector, adj[currentPoint+1].at(i).vertex - 1);
        }
    }
}

bool notConnect(vector<graph> &allVector, int length){
    int counter = 0;
    for(int i=0;i<length;i++){
        if(allVector.at(i).stage == true){
            counter++;
        }
    }
    if(counter == length){
        return false;
    }

    return true;
}

int numOfOddDegree(vector<graph> adj[], int numOfVervex){
    int oddCounter = 0;
    int oddPoint = 0;
    for(int i=numOfVervex;i>0;i--){
        if(adj[i].size()%2 == 1){
            oddCounter++;
            oddPoint = i;
        }
    }
    if(oddCounter == 0){
        return 0;
    }
    if(oddCounter >=4){
        return -1;
    }

    return oddPoint;
}

void goThough(vector<graph> adj[], stack<int> &circuit, int currentPoint){
    int length = adj[currentPoint].size();
    for(int i=0;i<length;i++){
        if(adj[currentPoint].at(i).stage == false){
            changeBoth(adj, currentPoint, adj[currentPoint].at(i).vertex, true);
            goThough(adj, circuit, adj[currentPoint].at(i).vertex);
        }
    }
    circuit.push(currentPoint);
}

void changeBoth(vector<graph> adj[], int num1, int num2, bool change){
    int length = adj[num1].size();
    for(int i=0;i<length;i++){
        if(adj[num1].at(i).vertex == num2){
            adj[num1].at(i).stage = change;
            break;
        }
    }
    length = adj[num2].size();
    for(int i=0;i<length;i++){
        if(adj[num2].at(i).vertex == num1){
            adj[num2].at(i).stage = change;
            break;
        }
    }
}

void print(stack<int> &circuit){
    int length = circuit.size();
    for(int i=0;i<length;i++){
        cout << circuit.top() << " ";
        circuit.pop();
    }
    cout << endl;
}
