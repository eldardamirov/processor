//
//  dgpu.h
//  processor
//
//  Created by Эльдар Дамиров on 24.12.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#ifndef dgpu_h
#define dgpu_h

// d is for "discrete"

#include <stdlib.h>
#include <stdio.h>
#include <deque>
#include <OpenCL/OpenCL.h>


#define MAX_SOURCE_SIZE  (0x100000)





const int l3MemorySize = 8192;
const int l2MemorySize = 1024;
const int l1MemorySize = 128;


typedef struct tag_color
    {
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    double alpha = 0.0;
    } color;
    
typedef struct tag_position
    {
    int x = 0;
    int y = 0;
    } position;
    
struct gpuCommand
    {
    int commandId = 0;
    int operandaModifier = 0;
    position currentScreenPosition;
    color currentColor;
    };


class dGPU
    {
    public:
        dGPU ( int screenXTemp, int screenYTemp )
            {
            screenX = screenXTemp;
            screenY = screenYTemp;
            }
        
        int addCommand ( gpuCommand newCommand )
            {
            inputLine.push_back ( newCommand );
            
            return 0;
            }
            
        double getResult()
            {
            double temp = outputLine.front();
            outputLine.pop_front();
            
            return temp;
            }
            
        
    
    private:
        std::deque <gpuCommand> inputLine;
        std::deque <double> outputLine;
        int screenX = 0, screenY = 0;
        double* l3Memory = new double [ l3MemorySize ]; // 0 ... ( ( screenX * screenY ) - 1 ); then other raw data;
        
        
    
    };
    

class gpuBlock
    {
    public:
        
    
    private:
        double* l2Memory = new double [ l2MemorySize ];
        
    
    
    };
    
    //    stpxl, drln, drcr, drplg,
//    stcl, 
//    gmrc, smrc 

class gpuUnit
    {
    public:
        gpuUnit ( int frequency, int l1MemorySize, int screenXTemp, int screenYTemp )
            {
            screenX = screenXTemp;
            screenY = screenYTemp;
            
            delay = 1 / frequency;
            
            }
            
     
        
        int setPixel ( position pixelAddress, color pixelColor, double* l3Memory )
            {
            int l3MemoryAddress = pixelAddress.y * screenX + pixelAddress.x;  
            // HERE IS NO CHECK OF BAD_ACCESS, or exceeding array;
            if ( l3MemoryAddress % 4 == 0 ) // because each pixel color consists of 4 variables;
                {
                l3Memory [ l3MemoryAddress ] = pixelColor.red;
                l3Memory [ l3MemoryAddress + 1 ] = pixelColor.green;
                l3Memory [ l3MemoryAddress + 2 ] = pixelColor.blue;
                l3Memory [ l3MemoryAddress + 3 ] = pixelColor.alpha;
                }
                
            
            return 0;
            } 
            
        bool busy()
            {
            return isBusy;
            }
    
    
    
    
    private:
        int frequency = 0, l1MemorySize = 0;
        double delay = 0;
        double* l1Memory = new double [ l1MemorySize ]; 
        int screenX = 0, screenY = 0;
        bool isBusy = false;
        
        
        
    
    
    
    
    };






#endif /* dgpu_h */
