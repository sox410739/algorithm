#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;
struct answer{
    string str1 = "";
    string str2 = "";
};
void buildGrid(int* scoreGrid, int* mark, int row, int col);
int similarity(string str1, string str2, int* scoreGrid, int* mark, int row, int col);
int Max(int left, int top, int left_top);
void printMark(string str1, string str2, int* mark, int row, int col, vector<answer>& Ans, int position, answer temp);

int main()
{
    string str1 = "";
    string str2 = "";
    cout << "String1: ";
    getline(cin, str1);
    cout << "String2: ";
    getline(cin, str2);
    int len1 = str1.length();
    int len2 = str2.length();
    int scoreGrid[len1+1][len2+1] = {0};
    int mark[len1+1][len2+1] = {0};
    vector<answer> Ans;
    answer temp;
    buildGrid(&scoreGrid[0][0], &mark[0][0], len1+1, len2+1);
    cout << "Similarity: " << similarity(str1, str2, &scoreGrid[0][0], &mark[0][0], len1+1, len2+1) << endl;
    printMark(str1, str2, &mark[0][0], len1+1, len2+1, Ans, len1*(len2+1)+len2, temp);
    cout << "There are " << Ans.size() << " answer." << endl;
    for(int i=0;i<Ans.size();i++){
        cout << "Answer" << i+1 << ": " << Ans.at(i).str1 << " " << Ans.at(i).str2 << endl;
    }
    /*for(int i=0;i<len1+1;i++){
        for(int j=0;j<len2+1;j++){
            cout << scoreGrid[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i=0;i<len1+1;i++){
        for(int j=0;j<len2+1;j++){
            cout << mark[i][j] << " ";
        }
        cout << endl;
    }*/


    return 0;
}

void buildGrid(int* scoreGrid, int* mark, int row, int col){
    int temp = 0;
    scoreGrid[0] = temp;
    for(int i=1;i<col;i++){
        temp--;
        scoreGrid[i] = temp;
        mark[i] = 1;
    }
    temp = 0;
    for(int i=1;i<row;i++){
        temp--;
        scoreGrid[i*col] = temp;
        mark[i*col] = 3;
    }
}

int similarity(string str1, string str2, int* scoreGrid, int* mark, int row, int col){
    int left = 0;
    int top = 0;
    int left_top = 0;
    for(int i=1;i<row;i++){
        for(int j=1;j<col;j++){
            left = scoreGrid[col*i+(j-1)] - 1;
            top = scoreGrid[col*(i-1)+j] - 1;
            if(str1[i-1] == str2[j-1]){
                left_top = scoreGrid[col*(i-1)+(j-1)] + 1;
            }
            else{
                left_top = scoreGrid[col*(i-1)+(j-1)] - 1;
            }
            scoreGrid[col*i+j] = Max(left, top, left_top);
            if(scoreGrid[col*i+j]==left && scoreGrid[col*i+j]==top && scoreGrid[col*i+j]==left_top){
                mark[col*i+j] = 7;
            }
            else if(scoreGrid[col*i+j]==left && scoreGrid[col*i+j]==top){
                mark[col*i+j] = 6;
            }
            else if(scoreGrid[col*i+j]==top && scoreGrid[col*i+j]==left_top){
                mark[col*i+j] = 5;
            }
            else if(scoreGrid[col*i+j]==left && scoreGrid[col*i+j]==left_top){
                mark[col*i+j] = 4;
            }
            else if(scoreGrid[col*i+j]==top){
                mark[col*i+j] = 3;
            }
            else if(scoreGrid[col*i+j]==left_top){
                mark[col*i+j] = 2;
            }
            else if(scoreGrid[col*i+j]==left){
                mark[col*i+j] = 1;
            }
            else{
                cout << "error1" << endl;
            }
        }
    }

    return scoreGrid[(row-1)*col + (col-1)];
}

int Max(int left, int top, int left_top){
    int temp = -99999999;
    if(left > temp){
        temp = left;
    }
    if(top > temp){
        temp = top;
    }
    if(left_top > temp){
        temp = left_top;
    }

    return temp;
}

void printMark(string str1, string str2, int* mark, int row, int col, vector<answer>& Ans, int position, answer temp){
    if(position == 0){
        Ans.push_back(temp);
        return;
    }
    answer Register = temp;
    switch(mark[position]){
    case 7:
        temp.str1 = str1[position/col - 1] + temp.str1;
        temp.str2 = '-' + temp.str2;
        printMark(str1, str2, &mark[0], row, col, Ans, position-col, temp);
        temp = Register;
    case 4:
        temp.str1 = str1[position/col - 1] + temp.str1;
        temp.str2 = str2[position%col - 1] + temp.str2;
        printMark(str1, str2, &mark[0], row, col, Ans, position-col-1, temp);
        temp = Register;
    case 1:
        temp.str1 = '-' + temp.str1;
        temp.str2 = str2[position%col - 1] + temp.str2;
        printMark(str1, str2, &mark[0], row, col, Ans, position-1, temp);
        break;
    case 5:
        temp.str1 = str1[position/col - 1] + temp.str1;
        temp.str2 = '-' + temp.str2;
        printMark(str1, str2, &mark[0], row, col, Ans, position-col, temp);
        temp = Register;
    case 2:
        temp.str1 = str1[position/col - 1] + temp.str1;
        temp.str2 = str2[position%col - 1] + temp.str2;
        printMark(str1, str2, &mark[0], row, col, Ans, position-col-1, temp);
        break;
    case 6:
        temp.str1 = '-' + temp.str1;
        temp.str2 = str2[position%col - 1] + temp.str2;
        printMark(str1, str2, &mark[0], row, col, Ans, position-1, temp);
        temp = Register;
    case 3:
        temp.str1 = str1[position/col - 1] + temp.str1;
        temp.str2 = '-' + temp.str2;
        printMark(str1, str2, &mark[0], row, col, Ans, position-col, temp);
        break;
    }
}
