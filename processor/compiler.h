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


class compiler
    {
    public:
        compiler ( std::string tempHumanCodeFileName, std::string tempMachineCodeFileName )
            {
            compilationStartTime = time ( NULL );
            
            printf ( "COMPILATION...\n" );
            
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
        
        int makeMachineCode()
            {
            readFromFile humanCodeFile ( "humanCode.txt" );
            writeToFile machineCodeFile ( "machineCode.txt", ( humanCodeFile.getFileSize() + 1 ) );
            
            std::string currentCommand = "";
            int currentCommandId = 0;
            
            
            while ( !humanCodeFile.isEnd() )
                {
                currentCommand = humanCodeFile.getNextString();
                currentCommandId = getCommandId ( currentCommand );

                
                
                machineCodeFile.writeString ( std::to_string ( currentCommandId ) );
                

                if ( currentCommandId > popS ) // popS, because after popS in our enum all commands need arguments;
                    {
                    machineCodeFile.writeString ( ( " " + ( humanCodeFile.getNextString() ) ) );
                    }
                    
                machineCodeFile.writeNextChar ( '\n' );
                }
            
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
        
        //// ------------------------------------------------------------------------------------------------
        
    };


#endif /* compiler_h */
