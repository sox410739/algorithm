#include <iostream>
#include <queue>

using namespace std;
struct Node{
    char key;
    int frequency;
    string code;
    Node* left = NULL;
    Node* right = NULL;
};
void generateCode(Node* root, string Code);
struct Node* buildTree(Node* dataptr[], int num);
struct Node* combine(Node* n1, Node* n2);
void quickSort(Node* data[], int start, int fin);

int main()
{
    int num = 0;
    cin >> num;
    struct Node data[num];
    struct Node* dataptr[num];
    for(int i=0;i<num;i++){
        cin >> data[i].key;
        cin >> data[i].frequency;
        dataptr[i] = &data[i];
    }
    quickSort(dataptr, 0, num);
    generateCode(buildTree(dataptr, num), "");

    cout << endl;
    for(int i=0;i<num;i++){
        cout << data[i].key << " " << data[i].code << endl;
    }

    return 0;
}

void generateCode(Node* root, string Code){
    if(root == NULL){
        return;
    }
    root->code = Code;
    generateCode(root->left, Code + "0");
    generateCode(root->right, Code + "1");
}

struct Node* buildTree(Node* dataptr[], int num){
    queue<Node*> q1;
    queue<Node*> q2;
    Node* temp1;
    Node* temp2;
    for(int i=0;i<num;i++){
        q1.push(dataptr[i]);
    }
    for(int i=0;i<num-1;i++){
        if(q1.size() == 0){
            temp1 = q2.front();
            q2.pop();
        }
        else if(q2.size() == 0){
            temp1 = q1.front();
            q1.pop();
        }
        else if(q1.front()->frequency < q2.front()->frequency){
            temp1 = q1.front();
            q1.pop();
        }
        else{
            temp1 = q2.front();
            q2.pop();
        }

        if(q1.size() == 0){
            temp2 = q2.front();
            q2.pop();
        }
        else if(q2.size() == 0){
            temp2 = q1.front();
            q1.pop();
        }
        else if(q1.front()->frequency < q2.front()->frequency){
            temp2 = q1.front();
            q1.pop();
        }
        else{
            temp2 = q2.front();
            q2.pop();
        }
        q2.push(combine(temp1, temp2));
    }


    return q2.front();
}

struct Node* combine(Node* n1, Node* n2){
    Node* temp = new Node;
    temp->frequency = n1->frequency + n2->frequency;
    temp->left = n1;
    temp->right = n2;

    return temp;
}

void quickSort(Node* dataptr[], int start, int fin){
    if(start >= fin){
        return;
    }
    int pivot = dataptr[start]->frequency;
    int End = fin;
    Node* temp;
    for(int i=fin-1;i>start;i--){
        if(dataptr[i]->frequency > pivot){
            End--;
            temp = dataptr[i];
            dataptr[i] = dataptr[End];
            dataptr[End] = temp;
        }
    }
    End--;
    temp = dataptr[start];
    dataptr[start] = dataptr[End];
    dataptr[End] = temp;
    quickSort(dataptr, start, End);
    quickSort(dataptr, End+1, fin);
}
