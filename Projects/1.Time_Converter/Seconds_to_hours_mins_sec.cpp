#include<iostream>
using namespace std;

int main(){

    int seconds;
    cout<< "enter seconds = ";
    cin >> seconds;

    int hours = seconds/3600;
    int mins = (seconds % 3600) /60;
    int sec = seconds % 60;

    cout << " Time : " << hours << " Hours " << mins << " Minutes " << sec << " Seconds " ;

    return 0;
}
