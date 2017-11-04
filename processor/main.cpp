//
//  main.cpp
//  processor
//
//  Created by Эльдар Дамиров on 26.10.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <cmath>


#include "fileIO.h"
#include "stack.h" 
#include "compiler.h"






class Processor
    {
    public:
    
//        template <double> Stack processorStack;
//        Stack& <double> processorStack;
        Processor() : processorStack ( Stack <double> ( 64 ) )
            {
            
            }
    
    
        int boss()
            {
            readFromFile machineCode ( "machineCode.txt" );
            
            int currentCommandId = 0;
            std::string argument = "5";
            
            // printf ( "I was here" );
            
//            std::cout << "STATUS:" << machineCode.isEnd() << std::endl;
            
            while ( !machineCode.isEnd() )
                {
                printf ( "1\n" );
                currentCommandId = std::stoi ( machineCode.getNextString() );
                printf ( "2\n" );
                if ( currentCommandId > popS )
                    {
                    argument = machineCode.getNextString();
                    }
                printf ( "3\n" ); 
                    
                if ( doCommand ( currentCommandId, argument ) == -2 )
                    {
                    printf ( "Goodbye" );
                    break;
                    }
                printf ( "4\n" );
                
                printf ( "HEY: %f", processorStack.top() );
                
                argument = "";
                }
                
            printf ( "DDI was here" );
            
            /*
            while ( !machineCode.isEnd() )
                {
//                printf ( "I was here" );
                currentCommandId = std::stoi ( machineCode.getNextString() );
                argument= "";
                
                if ( currentCommandId > popS ) // popS, because after popS in our enum all commands need arguments;
                    {
                    argument = machineCode.getNextString();
                    }
                    
                printf ( "I was here" ); 
                printf ( "\n\nHEY:%d\n\n", doCommand ( currentCommandId, argument ) );   
                if ( doCommand ( currentCommandId, argument ) == -2 )
                    {
                    break;
                    printf ( "\n\nHEY:%d\n\n", doCommand ( currentCommandId, argument ) );
                    }
                printf ( "I was here" );
                
                }
            */
            
            return 0;
            }
        
    
    private:
        Stack <double> processorStack;
        double* myRegister = new double [ 1024 ];
        int currentFreeRegisterId = 0;
        
        
        
        int doCommand ( int commandId, std::string argument )
            {
//            printf ( "I was here" );
//            double temp = 0;
        
//            printf ( "\n III __ %d __ \n", commandId );
        
        
            switch ( commandId )
                {
                case hlt:
                    return -2; // stop;
                case nullCommand:
                    return -1; // some error occured;
                case out:
                    stackOut();
                case add:
                    stackAdd();
                case sub:
                    stackSub();
                case mul:
                    stackMul();
                case myDiv:
                    stackDiv();
                case mySin:
                    stackSin();
                case myCos:
                    stackCos();
                case mySqrt:
                    stackSqrt();
                case myAbs:
                    stackAbs();
                case myDup:
                    stackDup();
                case dump:
                    stackDump();
                case popS:
                    stackPopS();
                case popR:
                    stackPopR ();
                case pushS:
                    stackPushS ( argument );
                case pushR:
                    stackPushR ( argument );
                case in:
                    stackIn();
                default:
                    return -2;
                    
                    
                
                }
            }
            
        int stackOut()
            {
            printf ( "%f I was here", processorStack.top() );
            processorStack.pop();
            
            return 0;
            }
            
        int stackAdd()
            {
            double temp = 0;
            
            temp = temp + processorStack.top();
            processorStack.pop();
            temp = temp + processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            return 0;
            }
            
        int stackSub()
            {
            double temp = 0;
            
            temp = processorStack.top();
            processorStack.pop();
            temp = temp - processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            return 0;
            }
            
        int stackMul()
            {
            double temp = 0;
            
            temp = processorStack.top();
            processorStack.pop();
            temp = temp * processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            return 0;
            }
            
        int stackDiv()
            {
            double temp = 0;
            
            temp = processorStack.top();
            processorStack.pop();
            temp = temp / processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            return 0;
            }
            
        int stackSin()
            {
            double temp = 0;
            
            temp = processorStack.top();
            processorStack.pop();
            processorStack.push ( sin ( temp ) );
            
            return 0;
            }
            
        int stackCos()
            {
            double temp = 0;
            
            temp = processorStack.top();
            processorStack.pop();
            processorStack.push ( cos ( temp ) );
            
            return 0;
            }
            
        int stackSqrt()
            {
            double temp = 0;
            
            temp = processorStack.top();
            processorStack.pop();
            processorStack.push ( sqrt ( temp ) );
            
            return 0;
            }
            
        int stackAbs()
            {
            double temp = 0;
            
            temp = processorStack.top();
            processorStack.pop();
            processorStack.push ( abs ( temp ) );
            
            return 0;
            }
            
        int stackDup()
            {
            processorStack.push ( processorStack.top() );
            
            return 0;
            }
            
        int stackDump()
            {
            processorStack.dump();
            
            return 0;
            }
            
        int stackPopS()
            {
            processorStack.pop();
            
            return 0;
            }
            
        int stackPopR()
            {
            myRegister [ currentFreeRegisterId ] = processorStack.top();
            processorStack.pop();
            
            return 0;
            }
        
        int stackPushS ( std::string argument )
            {
            processorStack.push ( std::stod ( argument ) );
            
            
            printf ( "  %f III was here\n", processorStack.top() );
            
            
            return 0;
            }
            
        int stackPushR ( std::string argument ) 
            {
            processorStack.push ( myRegister [ std::stoi ( argument ) ] );
            
            return 0;
            }
            
        int stackIn()
            {
            double temp = 0.0;
            std::cin >> temp;
            
            processorStack.push ( temp );
            
            return 0;
            }
        
            
            
            
        
    
    };


int main ( int argc, const char * argv[] ) 
    {
    compiler myCompiler ( "humanCode.txt", "machineCode.txt" );  
    Processor myProcessor;
    myProcessor.boss();
    
    return 0;
    }
