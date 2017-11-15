//
//  commandsList.cpp
//  processor
//
//  Created by Эльдар Дамиров on 01.11.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#include <stdio.h>

//// ------------------------------------------------------------------------------------------------

//enum commands
//    {
//    hlt,
//    pushS, pushR,
//    popS, popR,
//    in, out, 
//    add, sub, mul, myDiv, 
//    mySin, myCos, mySqrt, myAbs,
//    myDup, dump,
//    nullCommand  
//    };


enum commands
    {
    hlt, nullCommand,
    in, out,
    add, sub, mul, myDiv, // 7
    mySin, myCos, mySqrt, myAbs, // 11
    myDup, dump,
    pushR, popR, // 14 - 15
    pushS, popS,
    border,
    pushRAM, popRAM,
    push, pop // 21 - 22
    };


//// ------------------------------------------------------------------------------------------------

const char* haultCommandHuman = "hlt";

const char* pushCommandHuman = "push";
const char* popCommandHuman = "pop";

//const char* pushRegisterCommandHuman = "pushR";
//const char* popRegisterCommandHuman = "popR";

//const char* pushStackCommandHuman = "pushS";
//const char* popStackCommandHuman = "pushR";

const char* inputFromKeyboardCommandHuman = "in";
const char* outputCommandHuman = "out";

const char* additionCommandHuman = "add";
const char* substituteCommandHuman = "sub";
const char* multiplicationCommandHuman = "mul";
const char* divisionCommandHuman = "div";

const char* sinusCommandHuman = "sin";
const char* cosinusCommandHuman = "cos";
const char* squareRootCommandHuman = "sqrt";
const char* moduleCommandHuman = "abs";

const char* duplicationCommandHuman = "dup";
const char* dumpCommandHuman = "dump";

//// ------------------------------------------------------------------------------------------------


