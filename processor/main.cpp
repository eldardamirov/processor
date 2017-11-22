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
        Processor() : processorStack ( Stack <double> ( 256, LOW ) )
            {
            
            }
    
        int boss()
            {
            readFromFile machineCode ( "machineCode.txt" );
            
            int currentCommandId = 0;
            std::string argument = "";
            
            //printf ( "%s", machineCode.getNextString().c_str() );
            
            while ( !machineCode.isEnd() )
                {
                currentCommandId = std::stoi ( machineCode.getNextString() );
                
//                if ( currentCommandId > border )
//                    {
//                    argument = machineCode.getNextString();
//
//                    }
                    
                if ( doCommand ( currentCommandId, argument ) == -2 )
                    {
                    printf ( "Goodbye" );
                    return 0;
                    }
            
//                processorStack.printItAll();
                
                argument = "";
                }
                
            
            return 0;
            }
        
    
    private:
        Stack <double> processorStack;
        double* myRegister = new double [ 1024 ];
        int currentFreeRegisterId = 0;
        
        
        // REGISTERS
        double ax = 0.0, bx = 0.0, cx = 0.0, dx = 0.0;
        double n1 = 0.0, n2 = 0.0, nS = 0.0;
        double r1 = 0.0, r2 = 0.0, r3 = 0.0, r4 = 0.0;
        
        
        int doCommand ( int commandId, std::string argument )
            {
//            printf ( "\nNow I'm doing command with id %d and argument %s\n", commandId, argument.c_str() );
            
            switch ( commandId )
                {
                case hlt:
                    return -2; // stop;
                case nullCommand:
                    return -1; // some error occured;
                case out:
                    stackOut();
                    return 0;
                case add:
                    stackAdd();
                    return 0;
                case sub:
                    stackSub();
                    return 0;
                case mul:
                    stackMul();
                    return 0;
                case myDiv:
                    stackDiv();
                    return 0;
                case mySin:
                    stackSin();
                    return 0;
                case myCos:
                    stackCos();
                    return 0;
                case mySqrt:
                    stackSqrt();
                    return 0;
                case myAbs:
                    stackAbs();
                    return 0;
                case myDup:
                    stackDup();
                    return 0;
                case dump:
                    stackDump();
                    return 0;
                case pop:
                    stackPopS();
                    return 0;
                case popR:
                    stackPopR ();
                    return 0;
                case push:
                    stackPushS ( argument );
                    return 0;
                case pushR:
                    stackPushR ( argument );
                    return 0;
                case in:
                    stackIn();
                    return 0;
                default:
                    return -7;
                }
            return 0;
            }
            
        int stackOut()
            {
            printf ( "%f\n", *processorStack.top() );
            processorStack.pop();
            
            return 0;
            }
            
        int stackAdd()
            {
            double temp = 0;
            
            temp = temp + *processorStack.top();
            processorStack.pop();
            temp = temp + *processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            return 0;
            }
            
        int stackSub()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            temp = temp - *processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            return 0;
            }
            
        int stackMul()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            temp = temp * *processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            return 0;
            }
            
        int stackDiv()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            temp = temp / *processorStack.top();
            processorStack.pop();
            processorStack.push ( temp );
            
            return 0;
            }
            
        int stackSin()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            processorStack.push ( sin ( temp ) );
            
            return 0;
            }
            
        int stackCos()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            processorStack.push ( cos ( temp ) );
            
            return 0;
            }
            
        int stackSqrt()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            processorStack.push ( sqrt ( temp ) );
            
            return 0;
            }
            
        int stackAbs()
            {
            double temp = 0;
            
            temp = *processorStack.top();
            processorStack.pop();
            processorStack.push ( abs ( temp ) );
            
            return 0;
            }
            
        int stackDup()
            {
            processorStack.push ( *processorStack.top() );
            
            return 0;
            }
            
        int stackDump()
            {
//            processorStack.dump();
            
            return 0;
            }
            
        int stackPopS()
            {
            processorStack.pop();
            
            return 0;
            }
            
        int stackPopR()
            {
            myRegister [ currentFreeRegisterId ] = *processorStack.top();
            processorStack.pop();
            
            return 0;
            }
        
        int stackPushS ( std::string argument )
            {
            double temp = std::stod ( argument ); 
            processorStack.push ( temp );
            
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



/*

int main()
    {
    compiler testCompiler ( "humanCode.txt", "machineCode.txt" );
    Processor tempProcessor;
    tempProcessor.boss();
    
    
    
    return 0;
    }

*/


int main ( int argc, const char * argv[] ) 
    {
    compiler myCompiler ( "humanCode.txt", "machineCode.txt" );  
//    Processor myProcessor;
//    myProcessor.boss();
    
    return 0;
    }
    

    

/*
int main()
    {
    readFromFile action ( "humanCode.txt" );
    
    std::cout << action.getNextString() << std::endl;
    std::cout << "AAA:" << action.getTillEndOfLine() << std::endl;
        
    
    return 0;
    }
/*


/*

int main()
    {
    Stack <double> tempStack ( 2, LOW );
    
    for ( int i = 0; i < 20000000; i++ )
        {
        tempStack.push ( 5.488573848 );
        }
        
    tempStack.push ( 6 );
    tempStack.pop();
        
    
        
		
	printf ( "ALL is ok!! %f", *tempStack.top() );
		
        
    
    
    return 0;
    }

    
*/
    
    
    
    
