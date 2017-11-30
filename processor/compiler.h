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
#include <unordered_map>

#include "fileIO.h"
#include "commandsList.h"
#include "basicMethods.h"


#define commandState commandsArray [ currentLine ].operandaModifier


struct command  
    {
    int commandId = 0;
    int operandaModifier = -1;
    double argument = 0;
    double argument2 = 0; // for int part in memory adressing;
    std::string argumentS = "";
    std::string argumentS2 = "";
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
        std::unordered_map <std::string, int> jumpMarks {};
        
        
        command* makeMachineCode()
            {
            //// ------------------------------------------------------------------------------------------------
            readFromFile humanCodeFile ( "humanCode.txt" );
            writeToFile machineCodeFile ( "machineCode.txt", ( humanCodeFile.getFileSize() + 1 ) );
            
            int linesQuantity = humanCodeFile.calculateLinesQuantity();
            
            command* commandsArray = new command [ linesQuantity ];
            int commandInMemoryLocation = 0;
            
            std::string currentInputLine = "";
            
            //// ------------------------------------------------------------------------------------------------
            std::string currentCommandTemp = "";
            std::string currentArgumentTemp = "";
            int currentCommandIdTemp = 0;
            //// ------------------------------------------------------------------------------------------------
            
            
            for ( int currentCommand = 0; currentCommand < linesQuantity; currentCommand++ )
                {
                currentInputLine = humanCodeFile.getTillEndOfLine();
                currentCommandTemp = getWordInString ( currentInputLine, 0 );
                
                
                currentCommandIdTemp = getCommandId ( currentCommandTemp );
                commandsArray [ currentCommand ].commandId = currentCommandIdTemp;
                
                std::cout << currentCommandIdTemp << "\n";
                
                if ( ( currentCommandIdTemp < borderJump ) && ( currentCommandIdTemp != nullCommand ) )
                    {
                    commandInMemoryLocation++;
                    }
                else if ( currentCommandIdTemp != nullCommand ) 
                    {
                    if ( currentCommandIdTemp < borderArgument )
                        {
                        // JUMPs HERE;
                        commandsArray [ currentCommand ].commandId = currentCommandIdTemp;
                        commandsArray [ currentCommand ].operandaModifier = -2;
                        commandsArray [ currentCommand ].argumentS = clearFromSpaces ( getWordInString ( currentInputLine, 1 ) );
                        }
                    else
                        {
                        currentArgumentTemp = clearFromSpaces ( getWordInString ( currentInputLine, 1 ) );
                    
                        if ( currentArgumentTemp.size() == 0 )
                            {
                            commandsArray [ currentCommand ].operandaModifier = -1;
                            commandInMemoryLocation = commandInMemoryLocation + 2;
                            }
                        else
                            {
                            commandInMemoryLocation = commandInMemoryLocation + argumentAnalyser( commandsArray, currentCommand, currentArgumentTemp );
                            }
                        
                        }
                    }
                else
                    {
                    std::cout << "\nGGG:" << currentInputLine << " " << currentCommandIdTemp << "\n";
                    commandsArray [ currentCommand ].operandaModifier = -3;
                    commandsArray [ currentCommand ].argumentS = currentInputLine;
                    jumpMarks [ currentInputLine ] = commandInMemoryLocation;
                    }
            
                }
            
            /*
            for ( int i = 0; i < linesQuantity; i++ )
                {
                std::cout << commandsArray [ i ].commandId << " " << commandsArray [ i ].operandaModifier << " " << commandsArray [ i ].argument << " " << commandsArray [ i ].argument2 << " " << commandsArray [ i ].argumentS << " " << commandsArray [ i ].argumentS2 << std::endl;
                }
            */
            
            /// -- PASSING JUMPS MEMORY LOCATIONS 
            
            for ( int i = 0; i < linesQuantity; i++ )
                {
                if ( commandsArray [ i ].operandaModifier == -2 )
                    {
                    commandsArray [ i ].argument = jumpMarks [ commandsArray [ i ].argumentS ];
                    }
                }
            
            ////
            
            std::string lineToWrite = "";
            std::cout << commandsArray [ 1 ].commandId << " " << commandsArray [ 1 ].operandaModifier << " " << commandsArray [ 1 ].argumentS << " " << commandsArray [ 1 ].argumentS2 << " " << commandsArray [ 1 ].argument << " " << commandsArray [ 1 ].argument2 << "\n";
            
            for ( int currentLine = 0; currentLine < linesQuantity; currentLine++ ) 
                {
                lineToWrite = "";
                
                if ( commandState == -1 )
                    {
                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].operandaModifier ) + "\n";
                    }
                if ( commandState == 0 )
                    {
//                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].operandaModifier ) + " " + commandsArray [ currentLine ].argumentS + "\n";
                    std::string temp = commandsArray [ currentLine ].argumentS; // !!!!
                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].operandaModifier ) + " " + temp + "\n";
                    }
                if ( commandState == 1 )
                    {
                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].operandaModifier ) + " " + std::to_string ( commandsArray [ currentLine ].argument ) + "\n";
                    }
                if ( commandState == 2 )
                    {
                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].operandaModifier ) + " " + std::to_string ( commandsArray [ currentLine ].argument ) + " " + commandsArray [ currentLine ].argumentS2 + "\n"; // !!!!
                    }
                if ( commandState == 3 )
                    {
                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].operandaModifier ) + " " + std::to_string ( commandsArray [ currentLine ].argument ) + " " + std::to_string ( commandsArray [ currentLine ].argument2 ) + "\n";
                    }
                if ( commandState == 4 )
                    {
                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].operandaModifier ) + " " + commandsArray [ currentLine ].argumentS + " " + commandsArray [ currentLine ].argumentS2 + "\n"; // !!!!
                    }
                if ( commandState == 5 )
                    {
                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].operandaModifier ) + " " +    std::to_string ( commandsArray [ currentLine ].argument ) + " " + std::to_string ( commandsArray [ currentLine ].argument2 ) + "\n";
                    }
                if ( commandState == 6 )
                    {
                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].operandaModifier ) + " " + commandsArray [ currentLine ].argumentS + "\n";
                    }
                if ( commandState == 7 )
                    {
                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].operandaModifier ) + " " + std::to_string ( commandsArray [ currentLine ].argument ) + "\n"; 
                    }
                if ( commandState == -2 )
                    {
                    lineToWrite = std::to_string ( commandsArray [ currentLine ].commandId ) + " " + std::to_string ( commandsArray [ currentLine ].argument ) + "\n";
                    }
                if ( commandState == -3 )
                    {
                    std::string temp = commandsArray [ currentLine ].argumentS;
                    lineToWrite = temp + "\n";
                    }
                    
                machineCodeFile.writeString ( lineToWrite );
            
                }
                
            
            
            return 0;
            }
            
        std::string getWordInString ( std::string inputString, int mode ) // mode = 0 -> returns command; mode = 1 -> returns argument;
            {
            std::string result = "";
            
            if ( mode == 0 )
                {
                int currentChar = 0;
                
                while ( ( inputString [ currentChar ] != ' ' ) && ( inputString [ currentChar ] != '\n' ) && ( inputString [ currentChar ] != '\0' ) )
                    {
                    result = result + inputString [ currentChar ];
                    currentChar++;
                    }
                    
                return result;
                }
                
            if ( mode == 1 )
                {
                int currentChar = 0;
                
                while ( ( inputString [ currentChar ] != ' ' ) && ( inputString [ currentChar ] != '\n' ) && ( inputString [ currentChar ] != '\0' ) )
                    {
                    currentChar++;
                    }
                    
                if ( ( inputString [ currentChar ] != '\n' ) && ( inputString [ currentChar ] != '\0' ) )
                    {
                    
                    while ( ( inputString [ currentChar ] != '\n' ) && ( inputString [ currentChar ] != '\0' ) )
                        {
                        result = result + inputString [ currentChar ];
                        currentChar++;
                        }
                    
                    return result;
                    }
                }
                
            return "";
            }
            
        std::string getArgumentFromString ( std::string inputArgument, int mode ) // mode = 0 -> returns first argument; mode = 1 -> returns second argument ( if exists );
            {
            std::string result = "";
            size_t inputArgumentLength = inputArgument.length();
            
            if ( mode == 0 )
                {
                for ( int currentChar = 1; currentChar < inputArgumentLength; currentChar++ )
                    {
                    if ( ( inputArgument [ currentChar ] != ']' ) && ( inputArgument [ currentChar ] != '+' ) && ( inputArgument [ currentChar ] != '-' ) )
                        {
                        result = result + inputArgument [ currentChar ];
                        }
                    else
                        {
                        break;
                        }
                    
                    }
                }
            else
                {
                int currentChar = 0;
                for ( currentChar = 1; currentChar < inputArgumentLength; currentChar++ )
                    {
                    if ( ( inputArgument [ currentChar ] == '+' ) || ( inputArgument [ currentChar ] == '-' ) )
                        {
                        currentChar++;
                        break;
                        }
                    if ( inputArgument [ currentChar ] == ']' )
                        {
                        break;
                        }
                    }
                    
                
                for ( int currentChar2 = currentChar; currentChar2 < inputArgumentLength; currentChar2++ )
                    {
                    if ( ( inputArgument [ currentChar2 ] != ']' ) && ( inputArgument [ currentChar2 ] != '+' ) && ( inputArgument [ currentChar2 ] != '-' ) )
                        {
                        result = result + inputArgument [ currentChar2 ];
                        }
                    else
                        {
                        break;
                        }
                    }
                }
            
            return result;
            }
            
        int argumentAnalyser ( command* commandsArray, int currentCommand, std::string currentArgumentTemp )
            {
//            std::cout << "HEEY: " << currentArgumentTemp << '\n';
            int memoryShift = 0;
            
            if ( currentArgumentTemp [ 0 ] == '[' )
                {
                if ( isDigit ( currentArgumentTemp [ 1 ] ) )
                    {
                    commandsArray [ currentCommand ].operandaModifier = 0;
                    commandsArray [ currentCommand ].argumentS = getArgumentFromString ( currentArgumentTemp, 0 );
                    
                    memoryShift = 3;
                    }
                else
                    {
                    if ( isLetter ( currentArgumentTemp [ 1 ] ) )
                        {
                        commandsArray [ currentCommand ].argument = recogniseRegister ( getArgumentFromString ( currentArgumentTemp, 0 ) );
                        ////////////////////////////////////////////////////////////////////////////////
                        ////////////////////////////////////////////////////////////////////////////////
                        std::string secondArgument = getArgumentFromString( currentArgumentTemp, 1 );
                        if ( secondArgument.length() != 0 )
                            {
                            int tempShift = 0;
//                            std::cout << currentArgumentTemp [ commandsArray [ currentCommand ].argumentS.length() + 3 ];
                            if ( currentArgumentTemp [ commandsArray [ currentCommand ].argumentS.length() + 3 ] == '-' )
                                {
                                tempShift = 2;
                                }

                            if ( isDigit ( currentArgumentTemp [ ( commandsArray [ currentCommand ].argumentS.length() + 4 ) ] ) )
                                {
                                commandsArray [ currentCommand ].operandaModifier = 2 + tempShift;
                                commandsArray [ currentCommand ].argumentS2 = secondArgument;
                                }
                            else
                                {
                                commandsArray [ currentCommand ].operandaModifier = 3 + tempShift;
//                                    printf ( "%s", secondArgument.c_str() );
                                commandsArray [ currentCommand ].argument2 = recogniseRegister ( secondArgument );
                                }
                            
                            memoryShift = 4;
                            }
                        else
                            {
                            commandsArray [ currentCommand ].operandaModifier = 1;
                            memoryShift = 3;
                            }
                        }
                    }
                }
            else
                {
                if ( isDigit ( currentArgumentTemp [ 0 ] ) )
                    {
                    commandsArray [ currentCommand ].operandaModifier = 6;
                    commandsArray [ currentCommand ].argumentS = currentArgumentTemp;
                    
                    memoryShift = 3;
                    }
                else if ( isLetter ( currentArgumentTemp [ 0 ] ) )
                    {
                    commandsArray [ currentCommand ].operandaModifier = 7;
                    commandsArray [ currentCommand ].argument = recogniseRegister ( currentArgumentTemp );
                    
                    memoryShift = 3;
                    }
                }
            
            return memoryShift;
            }
            
        std::string clearFromSpaces ( std::string currentArgumentTemp )
            {
            std::string result = "";
            size_t argumentLength = currentArgumentTemp.size();
            for ( int currentChar = 0; currentChar < argumentLength; currentChar++ )
                {
                if ( currentArgumentTemp [ currentChar ] != ' ' )
                    {
                    result = result + currentArgumentTemp [ currentChar ];
                    }
                }
                
            return result;
            }

        
        //// ------------------------------------------------------------------------------------------------
        
        int getCommandId ( std::string tempCommand )
            {
//            printf ( "HERE WHAT I GET: %s\n", tempCommand.c_str() );
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
            if ( tempCommand == jmpCommandHuman )
                {
                return jmp;
                }
            if ( tempCommand == jneCommandHuman )
                {
                return jne;
                }
            if ( tempCommand == jaCommandHuman )
                {
                return ja;
                }
            if ( tempCommand == jaeCommandHuman )
                {
                return jae;
                }
            if ( tempCommand == jbCommandHuman )
                {
                return jb;
                }
            if ( tempCommand == jbeCommandHuman )
                {
                return jbe;
                }
            
            
            return nullCommand;
            }
            
           
        
        
        int recogniseRegister ( std::string registerName )
            {
//            printf ( "HERE WHAT I'VE GOT: %s\n", registerName.c_str() );
//1            std::cout << std::endl << "II:" << registerName << std::endl;
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
