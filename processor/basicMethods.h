//
//  basicMethods.h
//  processor
//
//  Created by Эльдар Дамиров on 23.11.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#ifndef basicMethods_h
#define basicMethods_h

bool isDigit ( char inputChar )
    {
    if ( ( inputChar >= '0' ) && ( inputChar <= '9' ) )
        return true;
    else
        return false;
    }
    
bool isLetter ( char inputChar ) // lowerCase ONLY;
    {
    int temp = inputChar;
    if ( ( temp >= 'a' ) && ( temp <= 'z' ) )
        {
        return true;
        
        }
    else
        {
        return false;
        std::cout << "OO";
        }
        
    }
    
bool isArithmetic ( char inputChar )
    {
    if ( ( inputChar == '+' ) || ( inputChar == '-' ) || ( inputChar == '*' ) || ( inputChar == '/' ) )
        return true;
    else
        return false;
    }


#endif /* basicMethods_h */
