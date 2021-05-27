#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <time.h>

using namespace std;
struct markElement{
    int from = -1;
    int kind = 0;
};
void fullTheTable(int* maxTable, int* minTable, struct markElement *markMax, struct markElement *markMin, char* Ope, int len, int posX, int posY);
int calculate(int num1, char operand, int num2);
string output(vector<int> &Num, vector<char> &Ope, int len, struct markElement *markMax, struct markElement *markMin, int posX, int posY, bool Max);


int main()
{
    /*ofstream Fout("time.txt");
    if(!Fout){
        cout << "Cannot open file." << endl;
    }
    double START, END;*/
    string input = "9";
    getline(cin, input);
    //for(int k=1;k<1000;k++){
        stringstream ss;
        vector<int> Num;
        vector<char> Ope;
        //input = input + "+9";

        //START = clock();

        int len = 0; //number length
        ss << input;
        int tempInt = 0;
        char tempChar;
        while(ss >> tempInt){
            ss >> tempChar;
            Num.push_back(tempInt);
            Ope.push_back(tempChar);
            len++;
        }
        Ope.pop_back();
        int maxTable[len][len], minTable[len][len];
        struct markElement markMax[len][len], markMin[len][len];
        for(int i=0;i<len;i++){
            for(int j=0;j<len;j++){
                maxTable[i][j] = 0;
                minTable[i][j] = 0;
            }
        }
        for(int i=0;i<len;i++){
            maxTable[i][i] = Num.at(i);
            minTable[i][i] = Num.at(i);
        }
        for(int i=len-1;i>=0;i--){
            for(int j=0;j<i;j++){
                fullTheTable(&maxTable[0][0], &minTable[0][0], &markMax[0][0], &markMin[0][0], &Ope[0], len, j, len-i+j);
            }
        }
        cout << output(Num, Ope, len, &markMax[0][0], &markMin[0][0], 0, len-1, true) << " = " << maxTable[0][len-1] << endl;

        //END = clock();

        //Fout << k << "\t" << (END-START)/CLOCKS_PER_SEC << endl;
    //}
    //Fout.close();

    return 0;
}

void fullTheTable(int* maxTable, int* minTable, struct markElement *markMax, struct markElement *markMin, char* Ope, int len, int posX, int posY){
    int Max = -32768;
    int Min = 32767;
    int temp = 0;
    for(int i=posX,j=posX+1;i<posY;i++,j++){
        temp = calculate(maxTable[posX*len+i], Ope[i], maxTable[j*len+posY]);
        if(temp > Max){
            Max = temp;
            markMax[posX*len+posY].from = i;
            markMax[posX*len+posY].kind = 1;
        }
        if(temp < Min){
            Min = temp;
            markMin[posX*len+posY].from = i;
            markMin[posX*len+posY].kind = 1;
        }
        temp = calculate(maxTable[posX*len+i], Ope[i], minTable[j*len+posY]);
        if(temp > Max){
            Max = temp;
            markMax[posX*len+posY].from = i;
            markMax[posX*len+posY].kind = 2;
        }
        if(temp < Min){
            Min = temp;
            markMin[posX*len+posY].from = i;
            markMin[posX*len+posY].kind = 2;
        }
        temp = calculate(maxTable[posX*len+i], Ope[i], minTable[j*len+posY]);
        if(temp > Max){
            Max = temp;
            markMax[posX*len+posY].from = i;
            markMax[posX*len+posY].kind = 3;
        }
        if(temp < Min){
            Min = temp;
            markMin[posX*len+posY].from = i;
            markMin[posX*len+posY].kind = 3;
        }
        temp = calculate(maxTable[posX*len+i], Ope[i], minTable[j*len+posY]);
        if(temp > Max){
            Max = temp;
            markMax[posX*len+posY].from = i;
            markMax[posX*len+posY].kind = 4;
        }
        if(temp < Min){
            Min = temp;
            markMin[posX*len+posY].from = i;
            markMin[posX*len+posY].kind = 4;
        }
    }

    maxTable[posX*len+posY] = Max;
    minTable[posX*len+posY] = Min;
}

int calculate(int num1, char operand, int num2){
    if(operand == '+'){
        return num1 + num2;
    }
    else if(operand == '-'){
        return num1 - num2;
    }
    else if(operand == '*'){
        return num1 * num2;
    }

    return num1 / num2; //error
}

string output(vector<int> &Num, vector<char> &Ope, int len, struct markElement *markMax, struct markElement *markMin, int posX, int posY, bool Max){
    string temp = "";
    if(posX == posY){
        stringstream ss;
        ss << Num.at(posX);
        ss >> temp;

        return temp;
    }
    if(Max == true){ //find markMax
        int center = markMax[posX*len+posY].from;
        switch(markMax[posX*len+posY].kind){
        case 1:     //both from max
            temp = "(" + output(Num, Ope, len, &markMax[0], &markMin[0], posX, center, true)  + Ope[center] + output(Num, Ope, len, &markMax[0], &markMin[0], center+1, posY, true) + ")";
            break;
        case 2:
            temp = "(" + output(Num, Ope, len, &markMax[0], &markMin[0], posX, center, true)  + Ope[center] + output(Num, Ope, len, &markMax[0], &markMin[0], center+1, posY, false) + ")";
            break;
        case 3:
            temp = "(" + output(Num, Ope, len, &markMax[0], &markMin[0], posX, center, false)  + Ope[center] + output(Num, Ope, len, &markMax[0], &markMin[0], center+1, posY, true) + ")";
            break;
        case 4:
            temp = "(" + output(Num, Ope, len, &markMax[0], &markMin[0], posX, center, false)  + Ope[center] + output(Num, Ope, len, &markMax[0], &markMin[0], center+1, posY, false) + ")";
            break;
        }
    }
    else{ //find markMin
        int center = markMin[posX*len+posY].from;
        switch(markMin[posX*len+posY].kind){
        case 1:     //both from max
            temp = "(" + output(Num, Ope, len, &markMax[0], &markMin[0], posX, center, true)  + Ope[center] + output(Num, Ope, len, &markMax[0], &markMin[0], center+1, posY, true) + ")";
            break;
        case 2:
            temp = "(" + output(Num, Ope, len, &markMax[0], &markMin[0], posX, center, true)  + Ope[center] + output(Num, Ope, len, &markMax[0], &markMin[0], center+1, posY, false) + ")";
            break;
        case 3:
            temp = "(" + output(Num, Ope, len, &markMax[0], &markMin[0], posX, center, false)  + Ope[center] + output(Num, Ope, len, &markMax[0], &markMin[0], center+1, posY, true) + ")";
            break;
        case 4:
            temp = "(" + output(Num, Ope, len, &markMax[0], &markMin[0], posX, center, false)  + Ope[center] + output(Num, Ope, len, &markMax[0], &markMin[0], center+1, posY, false) + ")";
            break;
        }
    }

    return temp;
}
