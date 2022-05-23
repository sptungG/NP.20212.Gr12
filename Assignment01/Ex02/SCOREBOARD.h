//
// Created by ngovi on 17-Apr-22.
//

#ifndef EX02_SCOREBOARD_H
#define EX02_SCOREBOARD_H

#include "STUDENT.h"

typedef struct scoreBoard {
    string subjectID;
    string subjectName;
    int progressPercentage;
    int finalPercentage;
    string semester;
    int studentCount;
    Student students[100];
} ScoreBoard;



#endif //EX02_SCOREBOARD_H
