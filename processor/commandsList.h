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


//enum commands
//    {
//    hlt, nullCommand,
//    in, out,
//    add, sub, mul, myDiv, // 7
//    mySin, myCos, mySqrt, myAbs, // 11
//    myDup, dump,
//    borderJump,
//    jmp, jne, ja, jae, jb, jbe, 
//    borderArgument,
//    pushR, popR, 
//    pop, // 24
//    pushS, popS,
//    pushRAM, popRAM, 
//    push // 29
//    };


enum commands
    {
    hlt, nullCommand,
    in, out,
    add, sub, mul, myDiv, // 7
    mySin, myCos, mySqrt, myAbs, // 11
    myDup, dump,
    borderJump,
    jmp, jne, ja, jae, jb, jbe, 
    borderArgument,
    pushR, popR, 
    pop, // 24
    pushS, popS,
    pushRAM, popRAM, 
    push // 29
    };
    
enum registers
    {
    ax, bx, cx, dx,
    r1, r2, r3, r4,
    n1, n2, nS
    };


enum argumentTypes
    {
    empty = -1, 
    numberRAM, registerRAM,
    numberRegisterAddRAM, register2AddRAM,
    numberRegisterSubRAM, register2SubRAM,
    myNumber, myRegister
    };


//// ------------------------------------------------------------------------------------------------

const char* haultCommandHuman = "hlt";

const char* pushCommandHuman = "push";
const char* popCommandHuman = "pop";

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

const char* jmpCommandHuman = "jmp";
const char* jneCommandHuman = "jne";
const char* jaCommandHuman = "ja";
const char* jaeCommandHuman = "jae";
const char* jbCommandHuman = "jb";
const char* jbeCommandHuman = "jbe";

//// ------------------------------------------------------------------------------------------------


