#include <iostream>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;
string Karatsuba(string str1, string str2, int len);
string Karatsuba(string str1, string str2);
string strAdd(string str1, string str2, int len);
string strAdd(string str1, string str2);
string strSub(string str1, string str2);
string Fin(char ch1, char ch2);
int charToInt(char c);
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
    //   cout << "Cannot open the file." << endl;
    //}
    double START, END;
    //for(int i=1;i<1000;i++){
    //    len = i;
    //    str1 = '9' + str1;
    //    str2 = '9' + str2;
        START = clock();
        cout << "Answer is " << Karatsuba(str1, str2, len) << endl;
        END = clock();
    //    Fout << i << "\t" << (END-START)/CLOCKS_PER_SEC << endl;
        cout << "The calculation Spend " << (END-START)/CLOCKS_PER_SEC << " second." << endl;
    //}
    //Fout.close();

    return 0;
}

string Karatsuba(string str1, string str2, int len){
   // cout << str1 << " " << str2 << "   ";
    if(len == 1){
        return Fin(str1[0], str2[0]);
    }
    string a = str1.substr(0, len/2);
    string b = str1.substr(len/2, len-len/2);
    string c = str2.substr(0, len/2);
    string d = str2.substr(len/2, len-len/2);
    string ac = Karatsuba(a, c, len/2);
    string bd = Karatsuba(b, d, len-len/2);
    string mid = Karatsuba(strAdd(a, b), strAdd(c, d));
    mid = strSub(mid, ac);
    mid = strSub(mid, bd);
    for(int i=0;i<len-len/2;i++){
        mid = mid + "0";
    }
    for(int i=0;i<(len-len/2)*2;i++){
        ac = ac + "0";
    }
    string answer = strAdd(ac, bd);
    answer = strAdd(answer, mid);
    int counter = 0;
    while(answer[counter] == '0'){
        counter++;
    }
    answer = answer.substr(counter, answer.length());
    if(answer == ""){
        answer = "0";
    }

    return answer;
}

string Karatsuba(string str1, string str2){
    int len1 = str1.length();
    int len2 = str2.length();
    int len = 0;
    if(len1 >= len2){
        len = len1;
        for(int i=0;i<len1-len2;i++){
            str2 = "0" + str2;
        }
    }
    else if(len1 < len2){
        len = len2;
        for(int i=0;i<len2-len1;i++){
            str1 = "0" + str1;
        }
    }

    return Karatsuba(str1, str2, len);
}

string strAdd(string str1, string str2, int len){
    string regist = "";
    int carry = 0;
    for(int i=len-1;i>=0;i--){
        int temp = 0;
        temp = charToInt(str1[i]) + charToInt(str2[i]) + carry;
        carry = temp / 10;
        regist = intTochar(temp%10) + regist;
    }
    if(carry != 0){
        regist = intTochar(carry) + regist;
    }

    return regist;
}

string strAdd(string str1, string str2){
    int len1 = str1.length();
    int len2 = str2.length();
    int len = 0;
    if(len1 >= len2){
        len = len1;
        for(int i=0;i<len1-len2;i++){
            str2 = "0" + str2;
        }
    }
    else if(len1 < len2){
        len = len2;
        for(int i=0;i<len2-len1;i++){
            str1 = "0" + str1;
        }
    }

    return strAdd(str1, str2, len);
}

string strSub(string str1, string str2){
    int len1 = str1.length();
    int len2 = str2.length();
    for(int i=0;i<len1-len2;i++){
        str2 = "0" + str2;
    }
    string regist = "";
    int carry = 0;
    for(int i=len1-1;i>=0;i--){
        int temp = 0;
        temp = charToInt(str1[i]) - charToInt(str2[i]) + carry;
        if(temp < 0){
            temp = temp + 10;
            carry = -1;
        }
        else{
            carry = 0;
        }
        regist = intTochar(temp) + regist;
    }

    return regist;
}

string Fin(char ch1, char ch2){
    string regist = "";
    int temp = charToInt(ch1) * charToInt(ch2);
    if(temp > 9){
        regist = regist + intTochar(temp/10) + intTochar(temp%10);
    }
    else{
        regist = regist + intTochar(temp);
    }

    return regist;
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
