#include <iostream>
#include <stdio.h>
#include <string.h>
#include "HAZCHEM.h"

using namespace std;

bool check(string str){
    if (str.size() > 3 || str.size() == 0){
        cout << "0 < HAZCHEM Code's length <= 3" << endl;
        return false;
    }
    if (str[0] != '1' && str[0] != '2' && str[0] != '3' && str[0] != '4') {
        cout << "Invalid at 1st position character (only in {1,2,3,4})!" << endl;
        return false;
    }
    if (str[1] != 'P' && str[1] != 'R' && str[1] != 'S' && str[1] != 'T' && str[1] != 'W' && str[1] != 'X' && str[1] != 'Y' && str[1] != 'Z') {
        cout << "Invalid at 2nd position character (only in {P,R,S,T,W,X,Y,Z})!" << endl;
        return false;
    }
    if (str.size() == 3 && str[2] != 'E') {
        cout << "Invalid at 3rd position character (only in {E})!" << endl;
        return false;
    }
    return true;
}

HAZCHEM getHazchem(){
    string code;
    bool _black = true;

    cout << "Enter HAZCHEM code (uppercase): ";
    cin >> code;
    while(!check(code)){
        cout << "Try again: ";
        cin >> code;
    }

    cout << "Is the "<< code[1] << " reverse coloured? [yes/no] ";
    string isReversed;
    cin >> isReversed;
    while (isReversed != "yes" && isReversed != "no") {
        cout << "Invalid input! \nIs the " << code[1] << " reverse coloured? [yes/no] ";
        cin >> isReversed;
    }
    if(isReversed == "yes") _black = false;

    return HAZCHEM_init(code, _black);
}

int main(int argc, const char * argv[]) {
    HAZCHEM hazchem = getHazchem();
    HAZCHEM_decode(hazchem);

    return 0;
}
