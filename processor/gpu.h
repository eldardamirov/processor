//
//  gpu.h
//  processor
//
//  Created by Эльдар Дамиров on 14.12.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#ifndef gpu_h
#define gpu_h

// d is for "discrete"

template <typename color> struct colorData
    {
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    double alpha = 0.0;
    }


class dGPU
    {
    public:
        dGPU ( int screenX, int screenY )
            {
            
            }
    
    private:
        color* l3Memory = new color [ ( screenX * screenY ) ]; 
    
    
    }
    
    

class gpuUnit
    {
    public:
        gpuUnit ( int frequency, int l1MemorySize )
            {
        
            }
    
    
    
    
    private:
        int frequency = 0, l1MemorySize = 0;
        
        int setPixel ( int pixelAdress, color pixelColor, color* l3Memory )
            {
            l3MemoryAdress 
            
            return 0;
            }
    
    
    
    }



#endif /* gpu_h */
