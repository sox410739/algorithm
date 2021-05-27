#include <iostream>
#include <algorithm>

using namespace std;

bool whetherExist(int* arr, int num, int sum);

int main()
{
    int num = 0;
    cout << ""
    cin >> num;
    int arr[num] = {0};
    int sum = 0;
    cout << "input the objective M you want to search: ";
    cin >> sum;
    for(int i=0;i<num;i++){
        cin >> arr[i];
    }
    sort(arr, arr + num);
    if(whetherExist(&arr[0], num, sum))
        cout << "Exist!" << endl;
    else
        cout << "Not exist." << endl;

    return 0;
}

bool whetherExist(int* arr, int num, int sum){
    int small = 0;
    int big = num-1;
    while(!(small == big)){
        if(arr[small] + arr[big] == sum)
            return true;
        else if(arr[small] + arr[big] < sum)
            small++;
        else if(arr[small] + arr[big] > sum)
            big--;
    }

    return false;
}

for(int i=0;i<num;i++){
    int temp = arr[i];
    文棋打手槍演算法(sum-temp, &arr[i+1], num-i-1);
}
