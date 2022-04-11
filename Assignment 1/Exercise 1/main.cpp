//
//  main.cpp
//  Toxic chemicals
//
//  Created by Nguyễn Trường on 11/04/2022.
//

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

string input;
string form[10] = {"jets", "fog", "foam", "fry agent"};
int rv = 0; //0 - white; 1 - black

bool check(string s) {
    if (s.size() != 2 && s.size() != 3) {
        return false;
    }
    if (s[0] != '1' && s[0] != '2' && s[0] != '3' && s[0] != '4') {
        return false;
    }
    if (s[1] != 'P' && s[1] != 'R' && s[1] != 'S' && s[1] != 'T' && s[1] != 'W' && s[1] != 'X' && s[1] != 'Y' && s[1] != 'Z') {
        return false;
    }
    if (s.size() == 3 && s[2] != 'E') {
        return false;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    cout << "Enter HAZCHEM code: ";
    cin >> input;
    while (!check(input)) {
        cout << "Invalid input! \nEnter HAZCHEM code again: ";
        cin >> input;
    }
    if (input[1] == 'S' || input[1] == 'T' || input[1] == 'Y' || input[1] == 'Z') {
        cout << "Is the " << input[1] << " reverse coloured? [Yes/No] ";
        string ans;
        cin >> ans;
        while (ans != "Yes" && ans != "No") {
            cout << "Invalid input! \nIs the " << input[1] << " reverse coloured? [Yes/No] ";
            cin >> ans;
        }
        if (ans == "Yes") {
            rv = 1;
        }
    }
    cout << "\n***Emergency action advice***\n";
    cout << "Material:   \t" << form[(int)input[0]-48-1] << "\n";
    switch (input[1]) {
        case 'P': {
            cout << "Reactivity: \tcan be violently reactive\n";
            cout << "Protection: \tfull protective clothing must be worn\n";
            cout << "Containment: \tmay be diluted and washed down the drain\n";
            break;
        }
        case 'R': {
            cout << "Protection: \tfull protective clothing must be worn\n";
            cout << "Containment: \tmay be diluted and washed down the drain\n";
            break;
        }
        case 'S': {
            cout << "Reactivity: \tcan be violently reactive\n";
            if (rv == 0) {
                cout << "Protection: \tbreathing apparatus, protective gloves for fire only\n";
            } else {
                cout << "Protection: \tbreathing apparatus for fire only\n";
            }
            cout << "Containment: \tmay be diluted and washed down the drain\n";
            break;
        }
        case 'T': {
            if (rv == 0) {
                cout << "Protection: \tbreathing apparatus, protective gloves for fire only\n";
            } else {
                cout << "Protection: \tbreathing apparatus for fire only\n";
            }
            cout << "Containment: \tmay be diluted and washed down the drain\n";
            break;
        }
        case 'W': {
            cout << "Reactivity: \tcan be violently reactive\n";
            cout << "Protection: \tfull protective clothing must be worn\n";
            cout << "Containment: \ta need to avoid spillages from entering drains or water courses.\n";
            break;
        }
        case 'X': {
            cout << "Protection: \tfull protective clothing must be worn\n";
            cout << "Containment: \ta need to avoid spillages from entering drains or water courses.\n";
            break;
        }
        case 'Y': {
            cout << "Reactivity: \tcan be violently reactive\n";
            if (rv == 0) {
                cout << "Protection: \tbreathing apparatus, protective gloves for fire only\n";
            } else {
                cout << "Protection: \tbreathing apparatus for fire only\n";
            }
            cout << "Containment: \ta need to avoid spillages from entering drains or water courses.\n";
            break;
        }
        case 'Z': {
            cout << "Reactivity: \tcan be violently reactive\n";
            if (rv == 0) {
                cout << "Protection: \tbreathing apparatus, protective gloves for fire only\n";
            } else {
                cout << "Protection: \tbreathing apparatus for fire only\n";
            }
            cout << "Containment: \ta need to avoid spillages from entering drains or water courses.\n";
            break;
        }
    }
    if (input.size() == 3) {
        cout << "Evacuation: \tconsider evacuation\n";
    }
    cout << "*****************************\n";
    return 0;
}
