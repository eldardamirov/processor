// SORRY, it is C98, i can't initialize doubles in structs properly;

typedef struct tagColor 
    {
    float red;
    float green;
    float blue;
    float alpha;
    } color;
    
typedef struct tagPosition
    {
    int x;
    int y;
    } position;



__kernel void vector_add(__global const int *A, __global const int *B, __global int *C) {

    // Get the index of the current element to be processed
    int i = get_global_id(0);

    // Do the operation
    C[i] = A[i] + B[i];
}


__kernel void unitSetPixel ( __global int *l3Memory, __global const color* pixelColor, __global const position* pixelAddress, int screenX, int screenY  )
    {
    int l3MemoryAddress = pixelAddress->y * screenX + pixelAddress->x;  
    // HERE IS NO CHECK OF BAD_ACCESS, or exceeding array;
    if ( l3MemoryAddress % 4 == 0 ) // because each pixel color consists of 4 variables;
        {
        l3Memory [ l3MemoryAddress ] = pixelColor->red;
        l3Memory [ l3MemoryAddress + 1 ] = pixelColor->green;
        l3Memory [ l3MemoryAddress + 2 ] = pixelColor->blue;
        l3Memory [ l3MemoryAddress + 3 ] = pixelColor->alpha;
        }
    }
    
__kernel 

