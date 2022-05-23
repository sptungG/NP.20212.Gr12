//
// Created by ngovi on 17-Apr-22.
//

#ifndef EX01_HAZCHEM_H
#define EX01_HAZCHEM_H

#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define MAXL_HAZCHEM_CODE 3

typedef enum {
    material,
    reactivity,
    protection,
    containment,
    evacuation,
} HAZCHEM_attribute;

typedef struct _HAZCHEM {
    string code;
    bool black;
} HAZCHEM;

HAZCHEM HAZCHEM_init(string _code, bool _black) {
    HAZCHEM hazchem;
    hazchem.black = _black;
    hazchem.code = _code;
    return hazchem;
}

// Material
char* HAZCHEM_decodeFirstCharacter(char c) {
    switch(c) {
        case '1': return "Jets";
        case '2': return "Fog";
        case '3': return "Foam";
        case '4': return "Dry agent";
        default: return "";
    }
}

// Reactivity, Protection, Containment
char* HAZCHEM_decodeSecondCharacter(char c, bool black, HAZCHEM_attribute a) {
    // Reactivity
    if(a == reactivity) {
        switch(c) {
            case 'P':
            case 'S':
            case 'W':
            case 'Y':
            case 'Z':
                return "can be violently reactive";
            default:
                return "";
        }
    }

    // Protection
    if(a == protection) {
        if(black == false) {
            switch(c) {
                case 'S':
                case 'T':
                case 'Y':
                case 'Z':
                    return "breathing apparatus, protective gloves for fire only";
                default:
                    return "";
            }
        }
        switch(c) {
            case 'P':
            case 'R':
            case 'W':
            case 'X':
                return "full protective clothing must be worn";
            case 'S':
            case 'T':
            case 'Y':
            case 'Z':
                return "breathing apparatus, protective gloves";
            default:
                return "";
        }
    }

    // Containment
    if(a == containment) {
        switch(c) {
            case 'P':
            case 'R':
            case 'S':
            case 'T':
                return "Dilute";
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                return "Contain";
            default:
                return "";
        }
    }
    return "";
}

// Evacuation
char* HAZCHEM_decodeThirdCharacter(char c) {
    if(c == 'E')
        return "Consider Evacuation";
    return "";
}

// Decode HAZCHEM code
void HAZCHEM_decode(HAZCHEM hazchem) {
    cout << "***Emergency action advice***" << endl;
    cout << "Material: " << HAZCHEM_decodeFirstCharacter(hazchem.code[0]) << endl;
    cout << "Reactivity: " << HAZCHEM_decodeSecondCharacter(hazchem.code[1], hazchem.black, reactivity) << endl;
    cout << "Protection: " << HAZCHEM_decodeSecondCharacter(hazchem.code[1], hazchem.black, protection) << endl;
    cout << "Containment: " << HAZCHEM_decodeSecondCharacter(hazchem.code[1], hazchem.black, containment) << endl;
    cout << "Evacuation: " << HAZCHEM_decodeThirdCharacter(hazchem.code[2]) << endl;
    cout << "*****************************" << endl;
}



#endif //EX01_HAZCHEM_H
