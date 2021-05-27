#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;
string answer(string str1, string str2, int len);
string multi(string str1, int num, int zeroCounter);
string Add(string str1, string str2);
int charToInt(char);
char intTochar(int i);

int main()
{
    int len = 0;
    cout << "The length of number: ";
    cin >> len;
    string str1 = "";
    string str2 = "";
    cout << "The multiplicand: ";
    getline(cin, str1);
    getline(cin, str1);
    cout << "The multiplier: ";
    getline(cin, str2);
    //ofstream Fout("time.txt");
    //if(!Fout){
       // cout << "Cannot open the file." << endl;
    //}
    double START, END;
    //for(int i=1;i<1000;i++){
    //    len = i;
    //    str1 = '9' + str1;
    //    str2 = '9' + str2;
        START = clock();
        cout << "Answer is " << answer(str1, str2, len) << endl;
        END = clock();
    //    Fout << i << "\t" << (END-START)/CLOCKS_PER_SEC << endl;
        cout << "The calculation Spend " << (END-START)/CLOCKS_PER_SEC << " second." << endl;
    //}
    //Fout.close();

    return 0;
}

string answer(string str1, string str2, int len){
    string temp = multi(str1, charToInt(str2[0]), len-0-1);
    for(int i=1;i<len;i++){
        temp = Add(temp, multi(str1, charToInt(str2[i]), len-i-1));
    }

    return temp;
}

string multi(string str1, int num, int zeroCounter){
    int carry = 0;
    string temp = "";
    for(int i=str1.length()-1;i>=0;i--){
        temp = intTochar((charToInt(str1[i]) * num + carry)%10) + temp;
        carry = (charToInt(str1[i]) * num + carry)/10;
    }
    if(carry != 0){
        temp = intTochar(carry) + temp;
    }
    for(int i=0;i<zeroCounter;i++){
        temp = temp + "0";
    }

    return temp;
}

string Add(string str1, string str2){
    int len = str1.length();
    int subtraction = len - str2.length();
    for(int i=0;i<subtraction;i++){
        str2 = "0" + str2;
    }
    int carry = 0;
    string temp = "";
    for(int i=len-1;i>=0;i--){
        temp = intTochar((charToInt(str1[i]) + charToInt(str2[i]) + carry)%10) + temp;
        carry = (charToInt(str1[i]) + charToInt(str2[i]) + carry)/10;
    }
    if(carry != 0){
        temp = intTochar(carry) + temp;
    }

    return temp;
}

int charToInt(char c){
    int temp = 0;
    switch(c){
    case '0':
        temp = 0;
        break;
    case '1':
        temp = 1;
        break;
    case '2':
        temp = 2;
        break;
    case '3':
        temp = 3;
        break;
    case '4':
        temp = 4;
        break;
    case '5':
        temp = 5;
        break;
    case '6':
        temp = 6;
        break;
    case '7':
        temp = 7;
        break;
    case '8':
        temp = 8;
        break;
    case '9':
        temp = 9;
        break;
    }

    return temp;
}

char intTochar(int i){
    char temp;
    switch(i){
    case 0:
        temp = '0';
        break;
    case 1:
        temp = '1';
        break;
    case 2:
        temp = '2';
        break;
    case 3:
        temp = '3';
        break;
    case 4:
        temp = '4';
        break;
    case 5:
        temp = '5';
        break;
    case 6:
        temp = '6';
        break;
    case 7:
        temp = '7';
        break;
    case 8:
        temp = '8';
        break;
    case 9:
        temp = '9';
        break;
    }

    return temp;
}
