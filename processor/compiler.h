//
//  compiler.h
//  processor
//
//  Created by Эльдар Дамиров on 02.11.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#ifndef compiler_h
#define compiler_h

#include <stdio.h>
#include <time.h>
#include <string>

#include "fileIO.h"
#include "commandsList.h"
#include "basicMethods.h"

struct command  
    {
    int commandId = 0;
    int operandaModifier = 0;
    double argument = 0;
    double argument2 = 0; // for int part in memory adressing;
    std::string argumentS = "";
    };


class compiler
    {
    public:
        compiler ( std::string tempHumanCodeFileName, std::string tempMachineCodeFileName )
            {
            compilationStartTime = time ( NULL );
            
            printf ( "COMPILATION...\n");
            
            humanCodeFileName = tempHumanCodeFileName;
            machineCodeFileName = tempMachineCodeFileName;

            makeMachineCode();
            }
            
        ~compiler()
            {
            compilationEndTime = time ( NULL );
            }
    
    
    
    private:
        //// ------------------------------------------------------------------------------------------------
        int compilationStartTime = 0, compilationEndTime = 0;
        //// ------------------------------------------------------------------------------------------------
        std::string humanCodeFileName = "", machineCodeFileName = "";
        //// ------------------------------------------------------------------------------------------------      
        
        command* makeMachineCode()
            {
            
            
            
//////---
            readFromFile humanCodeFile ( "humanCode.txt" );
            writeToFile machineCodeFile ( "machineCode.txt", ( humanCodeFile.getFileSize() + 1 ) );
            
            command* commandsArray = new command [ humanCodeFile.calculateLinesQuantity() ];
            
            checkArgumentState ( "[n2-6]", commandsArray, 0 );
            std::cout << "A:" << commandsArray [ 0 ].commandId << "B:" << commandsArray [ 0 ].operandaModifier << "C:" << commandsArray [ 0 ].argument << "D:" << commandsArray [ 0 ].argument2 << "E:" << commandsArray [ 0 ].argumentS; 
            
//            printf ( "CHEEECK: %f, %f", commandsArray [ 0 ].argument, commandsArray [ 0 ].argument2 );
            
//            std::string currentCommand = "";
//            int currentCommandId = 0;
//            std::string preAnalysedArgument = "";
//            
//            
//            while ( !humanCodeFile.isEnd() )
//                {
//                currentCommand = humanCodeFile.getNextString();
//                currentCommandId = getCommandId ( currentCommand );
//                
//                if ( currentCommandId > borderArgument )
//                    {
//                    preAnalysedArgument = humanCodeFile.getTillEndOfLine();
//                    
//                    
//                    }
//                else if ( currentCommandId > borderJump )
//                    {
//                    
//                    }

/////--
                
                
//                machineCodeFile.writeString ( std::to_string ( currentCommandId ) );
                

//                if ( currentCommandId > popS ) // popS, because after popS in our enum all commands need arguments;
//                    {
//                    machineCodeFile.writeString ( ( " " + ( humanCodeFile.getNextString() ) ) );
//                    }
                    
//                machineCodeFile.writeNextChar ( '\n' );
//                }
            
            return 0;
            }
        
        
        //// ------------------------------------------------------------------------------------------------
        
        int getCommandId ( std::string tempCommand )
            {
        
            if ( tempCommand == haultCommandHuman )
                {                
                return hlt;
                }
            if ( tempCommand == pushCommandHuman )
                {                
                return push;
                }
            if ( tempCommand == popCommandHuman )
                {                
                return pop;
                }
            if ( tempCommand == inputFromKeyboardCommandHuman )
                {                
                return in;
                }
            if ( tempCommand == outputCommandHuman )
                {                
                return out;
                }
            if ( tempCommand == additionCommandHuman )
                {
                return add;
                }
            if ( tempCommand == substituteCommandHuman )
                {
                return sub;
                }
            if ( tempCommand == multiplicationCommandHuman )
                {                
                return mul;
                }
            if ( tempCommand == divisionCommandHuman )
                {                
                return myDiv;
                }
            if ( tempCommand == sinusCommandHuman )
                {                
                return mySin;
                }  
            if ( tempCommand == cosinusCommandHuman )
                {                
                return myCos;
                }
            if ( tempCommand == squareRootCommandHuman )
                {
                return mySqrt;
                }
            if ( tempCommand == moduleCommandHuman )
                {                
                return myAbs;
                }
            if ( tempCommand == duplicationCommandHuman )
                {                
                return myDup;
                }
            if ( tempCommand == dumpCommandHuman )
                {                
                return dump;
                }
            
            return nullCommand;
            }
            
           
        int checkArgumentState ( std::string preAnalysedArgument, command* commandsArray, int currentCommandNumber )
            {
            
            size_t argumentLength = preAnalysedArgument.size();
            if ( argumentLength > 0 )
                {
                if ( preAnalysedArgument [ 0 ] != '[' )
                    {
                    return -1; // Error: it isn't argument, it is command, should pass control to usual command analyze next iteration;
                    }
                    
                if ( isDigit ( preAnalysedArgument [ 1 ] ) == true )
                    {
                    std::string tempStringForInt = "";
                    
                    for ( int i = 1; i < argumentLength; i++ ) 
                        {
                        if ( isDigit ( preAnalysedArgument [ i ] ) == true )
                            {
                            tempStringForInt = tempStringForInt + preAnalysedArgument [ i ];
                            }
                        else
                            {
                            break;
                            }
                        }
                    
//                    commandsArray [ currentCommandNumber ].argument = tempStringForInt;
                    commandsArray [ currentCommandNumber ].operandaModifier = 0;
                    
                    printf ( "0" );
                    
                    return 0;
                    }
                
                if ( isLetter ( preAnalysedArgument [ 1 ] ) == true )
                    { 
                    std::string tempStringForRegister = tempStringForRegister + preAnalysedArgument [ 1 ];
                    tempStringForRegister = tempStringForRegister + preAnalysedArgument [ 2 ];
                    std::cout << "HEEY: " << preAnalysedArgument [ 1 ] << " " << preAnalysedArgument [ 2 ]  << std::endl;
                    
                    if ( preAnalysedArgument [ 3 ] == ']' )
                        {
                        commandsArray [ currentCommandNumber ].argument = recogniseRegister ( tempStringForRegister );
                        commandsArray [ currentCommandNumber ].operandaModifier = 1;
                        printf ( "1" );
                        
                        return 0;
                        }
                    
                    if ( isArithmetic ( preAnalysedArgument [ 3 ] ) == true )
                        {
                        if ( isDigit ( preAnalysedArgument [ 4 ] ) == true )
                            {
        
                            std::string tempStringForInt = "";
                            for ( int i = 4; i < argumentLength; i++ )
                                {
                                if ( isDigit ( preAnalysedArgument [ i ] ) == true )
                                    {
                                    tempStringForInt = tempStringForInt + preAnalysedArgument [ i ];
                                    }
                                else
                                    {
                                    break;
                                    }
                                }
                            
                            
                            commandsArray [ currentCommandNumber ].argument = recogniseRegister ( tempStringForRegister );
                            commandsArray [ currentCommandNumber ].argumentS = tempStringForInt;
                            if ( preAnalysedArgument [ 3 ] == '+' )
                                {
                                commandsArray [ currentCommandNumber ].operandaModifier = 2;
                                printf ( "2" );
                                }
                            else if ( preAnalysedArgument [ 3 ] == '-' )
                                {
                                commandsArray [ currentCommandNumber ].operandaModifier = 4;
                                printf ( "4" );
                                }
                            
                            return 0;
                            }

//                         std::cout << "!!" << ( int ) preAnalysedArgument [ 4 ] << "!!";
                         if ( isLetter ( preAnalysedArgument [ 4 ] ) == true )
                            {
                            printf ( "EEEFG" );
                            std::string tempStringForRegister2 = tempStringForRegister2 + preAnalysedArgument [ 4 ];
                            tempStringForRegister2 = tempStringForRegister2 + preAnalysedArgument [ 5 ];
                            
                            commandsArray [ currentCommandNumber ].argument = recogniseRegister ( tempStringForRegister );
                            std::cout << "CHECK:" << tempStringForRegister << " " << tempStringForRegister2 << "END";
                            commandsArray [ currentCommandNumber ].argument2 = recogniseRegister ( tempStringForRegister2 );
                            if ( preAnalysedArgument [ 3 ] == '+' )
                                {
                                commandsArray [ currentCommandNumber ].operandaModifier = 3;
                                printf ( "3" );
                                }
                            else if ( preAnalysedArgument [ 3 ] == '-' )
                                {
                                printf ( "5" );
                                commandsArray [ currentCommandNumber ].operandaModifier = 5;
                                }
                                
                            return 0;
                            }
                        }
                        
            
                    }
                                
                }
            
            return 0;
            }
            
        
        int recogniseRegister ( std::string registerName )
            {
//            printf ( "HERE WHAT I'VE GOT: %s\n", registerName.c_str() );
            std::cout << std::endl << "II:" << registerName << std::endl;
            if ( registerName == "ax" )
                {
                return ax;
                }
            if ( registerName == "bx" )
                {
                return bx;
                }
            if ( registerName == "cx" )
                {
                return cx;
                }
            if ( registerName == "dx" )
                {
                return dx;
                }
            //// ------------------------------------------------------------------------------------------------    
            if ( registerName == "r1" )
                {
                return r1;
                }
            if ( registerName == "r2" )
                {
                return r2;
                }
            if ( registerName == "r3" )
                {
                return r3;
                }
            if ( registerName == "r4" )
                {
                return r4;
                }
            //// ------------------------------------------------------------------------------------------------
            if ( registerName == "n1" )
                {
                return n1;
                }
            if ( registerName == "n2" )
                {
                return n2;
                }
            if ( registerName == "nS" )
                {
                return nS;
                }
                
            //// HERE SHOULD BE ERROR, register not found during parsing;    
            
            return -1;
            }

            
        
        //// ------------------------------------------------------------------------------------------------
        
    };


#endif /* compiler_h */
