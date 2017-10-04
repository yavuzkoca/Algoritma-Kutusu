#include <cstdio>
#include "SmallVector.h"

/* Creates an empty SmallVector */
SmallVector::SmallVector(){ currSize = 0; capacity = 32; dynamicBuffer = 0;}

/* Takes an array and its size and creates a SmallVector with them */
SmallVector::SmallVector(int *arr, int size){
    currSize = size;
    if (size < 32){
        capacity = 32;
        dynamicBuffer = 0; 
        /* For the rest of the code if dynamicBuffer is empty it will be 0 */
        for(int i = 0; i < size; ++i)
            staticBuffer[i] = arr[i]; // Put values in arr into new SmallVector
    }
    else { // size >= 32
        capacity = size; 
        /* capacity will exceed 32 so we will directly set it to size */
        dynamicBuffer = new int[size - 32]; // This is initialization so no need to delete
        /* The size of dynamicBuffer will be the total size - 32 since
            firstly the staticBuffer will be filled with 32 elements. */
        for(int i = 0; i < 32; ++i)
            staticBuffer[i] = arr[i]; // First fill staticBuffer
        for(int i = 0; i < (size - 32); ++i)
            dynamicBuffer[i] = arr[32 + i]; // Then dynamicBuffer
    }
}

// Copy constructor of SmallVector
SmallVector::SmallVector(const SmallVector & object_in){
    currSize = object_in.currSize;
    // First we assign the copied SmallVector's size to our newly created SmallVector
    if (currSize < 32){
        capacity = 32;
        dynamicBuffer = 0;
        for(int i = 0; i < currSize; ++i)
            staticBuffer[i] = object_in.staticBuffer[i]; // Copy staticBuffer items
        // Since currSize < 32, dynamicBuffer is empty so we assign 0 to it
    }
    else{ // currSize >= 32
        capacity = currSize;
        // Since capacity exceed 32 we do this, in the rest of the code I'll be doing this
        dynamicBuffer = new int[currSize - 32];
        // Total size - 32 gives us the size of dynamicBuffer, this also will go on like this
        for(int i = 0; i < 32; ++i)
            staticBuffer[i] = object_in.staticBuffer[i]; // Copy staticBuffer
        for(int i = 0; i < (currSize - 32); ++i)
            dynamicBuffer[i] = object_in.dynamicBuffer[i]; // Copy dynamicBuffer
    }
    
}

// Adds a number to the end of the SmallVector
void SmallVector::push_back(int number){
    if (currSize < 32){ // staticBuffer has at least 1 empty space
        staticBuffer[currSize] = number;
        // currSize also yields for last index + 1, so number is added to the end
        ++currSize; // size increased
    }
    else{
        int *temp = new int[currSize];
        /*  temp will hold values in dynamicBuffer since it will be reallocated */
        for(int i = 0; i < (currSize - 32); ++i)
            temp[i] = dynamicBuffer[i]; // Add all already existing values to temp
        /* There is a possibility that it is the initialization of dynamicBuffer */
        if(dynamicBuffer != 0) 
        	delete[] dynamicBuffer;
        dynamicBuffer = new int[currSize - 31];
        /* Reallocate dynamicBuffer with increased size by 1, normally I was
            substracting 32 as you remember, so the size increased by 1 */
        for(int i = 0; i < (currSize - 32); ++i)
            dynamicBuffer[i] = temp[i]; // Transfer the elements to new dynamicBuffer
        dynamicBuffer[currSize++ - 32] = number; // Add number, also increment currSize
        capacity = currSize; // Since capacity > 32 it will be equal to currSize
        delete[] temp; // Better to have no memory leaks :)))
    }
}

// Adds an array to the end of the SmallVector
void SmallVector::push_back(int *arr, int size){ // The array, its size
	if(size == 0) // A little error handling here
		return;
    if(currSize + size <= 32){ // Check if added version exceed 32
        for(int i = 0; i < size; ++i)
            staticBuffer[currSize + i] = arr[i];
        currSize += size;
    }
    else{ // If dynamicBuffer will have elements = total size > 32
        if(currSize < 32){ // If staticBuffer is not full
            for(int i = 0; i < (32 - currSize); ++i)
                staticBuffer[currSize + i] = arr[i];
            if(dynamicBuffer != 0) // If dynamicBuffer is 0 obviously don't delete
            	delete[] dynamicBuffer;
            dynamicBuffer = new int[currSize + size - 32]; // Total size - 32 is dB's size
            for(int i = 0; i < (currSize + size - 32); ++i)
                dynamicBuffer[i] = arr[32 - currSize + i]; // Filling it
            // I'm bacically filling staticBuffer then dynamicBuffer
            currSize += size; // currSize increased by the size of the array
            capacity = currSize; // Capacitiy exceeds 32
        }
        else{ // If staticBuffer is full
            int *temp = new int[currSize - 32];
            for(int i = 0; i < (currSize - 32); ++i)
                temp[i] = dynamicBuffer[i];
            delete[] dynamicBuffer; // Dynamic buffer definetely has elements
            dynamicBuffer = new int[currSize + size - 32];
            for(int i = 0; i < (currSize - 32); ++i)
                dynamicBuffer[i] = temp[i];
            for(int i = 0; i < size; ++i)
                dynamicBuffer[currSize - 32 + i] = arr[i];
            // Reallocate dynamicBuffer and add new elements
            currSize += size;
            capacity = currSize;
            delete[] temp;
        }
    }
}

// Delete the last element from the SmallVector and return it.
int SmallVector::pop_back(){
    if(currSize == 0)
        return 0;
    if(currSize <= 32){ // All elements in staticBuffer
        int temp = staticBuffer[--currSize];
        staticBuffer[currSize] = 0;
        return temp;
    }
    else if(currSize == 33){ // Only one element in dynamicBuffer
        int temp = dynamicBuffer[0];
        delete[] dynamicBuffer;
        dynamicBuffer = 0;
        capacity = --currSize;
        return temp;
    }
    else{ // Many elements in dynamicBuffer so reallocation is needed
        int *temp = new int[currSize - 32];
        for(int i = 0; i < (currSize - 32); ++i)
            temp[i] = dynamicBuffer[i]; // Store all elements in temp
        delete[] dynamicBuffer;
        dynamicBuffer = new int[--currSize - 32]; // Create a decremented sized dynamicBuffer
        for(int i = 0; i < (currSize - 32); ++i) // currSize is updated above with --
            dynamicBuffer[i] = temp[i]; // Transfer from temp to new dynamicBuffer
        capacity = currSize; // capacity exceeds 32
        int lastElement = temp[currSize - 32]; // The last element of old dynamicBuffer
        delete[] temp;
        return lastElement; // Return the deleted last element
    }
}

// Returns the reversed SmallVector
SmallVector SmallVector::reverse() const{
    int *temp = new int[currSize];
    if(currSize < 32) // Put values in reversed order to a new array
        for(int i = 0; i < currSize; ++i)
            temp[currSize - 1 - i] = staticBuffer[i];
    else{ // If dynamicBuffer also has elements
        for(int i = 0; i < 32; ++i)
            temp[currSize - 1 - i] = staticBuffer[i];
        for(int i = 0; i < (currSize - 32); ++i)
            temp[currSize - i - 33] = dynamicBuffer[i];
    }
    SmallVector vector(temp, currSize);
    // Used array constructor the create reversed SmallVector.
    delete[] temp;
    return vector; // Return the reversed SmallVector
}

// This function prints the SmallVector, its size and its capacity
void SmallVector::print() const{
    if(currSize == 0)
        printf("[]\n");
    else if(currSize <= 32){
        printf("[");
        for(int i = 0; i < currSize - 1; ++i)
            printf("%d, ", staticBuffer[i]);
        printf("%d]\n", staticBuffer[currSize - 1]);
    }
    else{
        printf("[");
        for(int i = 0; i < 32; ++i)
            printf("%d, ", staticBuffer[i]);
        for(int i = 0; i < currSize - 33; ++i)
            printf("%d, ", dynamicBuffer[i]);
        printf("%d]\n", dynamicBuffer[currSize - 33]);
    }
    printf("Size: %d, Capacity: %d\n", currSize, capacity);
}

// Concatenation operator
SmallVector SmallVector::operator+(const SmallVector &object_in) const{
    int *concArray = new int[currSize + object_in.currSize];
    if(currSize <= 32){
        for(int i = 0; i < currSize; ++i)
            concArray[i] = staticBuffer[i];
    }
    else{
        for(int i = 0; i < 32; ++i)
            concArray[i] = staticBuffer[i];
        for(int i = 0; i < (currSize - 32); ++i)
            concArray[32 + i] = dynamicBuffer[i];
    }
    if(object_in.currSize <= 32){
        for(int i = 0; i < object_in.currSize; ++i)
            concArray[currSize + i] = object_in.staticBuffer[i];
    }
    else{
        for(int i = 0; i < 32; ++i)
            concArray[currSize + i] = object_in.staticBuffer[i];
        for(int i = 0; i < (object_in.currSize - 32); ++i)
            concArray[currSize + 32 + i] = object_in.dynamicBuffer[i];
    }
    /*  Above operations creates a new array, first puts all values of the 
        first SmallVector in the array then the second, after that the
        below code will create a new SmallVector with that array then return it */
    SmallVector vector(concArray, currSize + object_in.currSize);
    delete[] concArray;
    return vector;
}

// Multiple concatenation operator
SmallVector SmallVector::operator*(int mult) const{
    int *concArray = new int[currSize * mult];
    if(currSize <= 32){
        for(int i = 0; i < mult; ++i)
            for(int j = 0; j < currSize; ++j)
                concArray[i * currSize + j] = staticBuffer[j];
    }
    else{
        for(int i = 0; i < mult; ++i){
            for(int j = 0; j < 32; ++j)
                concArray[i * currSize + j] = staticBuffer[j];
            for(int j = 0; j < (currSize - 32); ++j)
                concArray[i * currSize + 32 + j] = dynamicBuffer[j];
        }
    }
    /* Above code creates a new array then puts the elements of the SmallVector
        int it as many times as wanted, then below a new SmallVector is created
        with the arrays elements */
    SmallVector vector(concArray, currSize * mult);
    delete[] concArray;
    return vector;
}

// This operator is used to reach elements of the SmallVector, since it returns
// a reference it is possible to modify the reached variable
int& SmallVector::operator[](const int index){
    if(index >= currSize){
        if(currSize <= 32)
            return staticBuffer[currSize - 1];
        else
            return dynamicBuffer[currSize - 33];
    }
    else if(index < 0 && index * (-1) > currSize)
        return staticBuffer[0];
    else if(index < 0){
        if(currSize + index < 32)
            return staticBuffer[currSize + index];
        else
            return dynamicBuffer[currSize + index - 32];
    }
    else{
        if(index < 32)
            return staticBuffer[index];
        else
            return dynamicBuffer[index - 32];
    }
}

// This operator copies the argument SmallVector to the current SmallVector
const SmallVector & SmallVector::operator=(const SmallVector &object_in){
    currSize = object_in.currSize;
    if(currSize <= 32){
        for(int i = 0; i < currSize; ++i)
            staticBuffer[i] = object_in.staticBuffer[i];
        for(int i = currSize; i < 32; ++i)
            staticBuffer[i] = 0;
        if(dynamicBuffer != 0){
            delete[] dynamicBuffer; // Sil baba
            dynamicBuffer = 0;
        }
        capacity = 32;
    }
    else{
        delete[] dynamicBuffer; // If I don't do this it is a memory leak :((
        dynamicBuffer = new int[currSize - 32]; // new memory space for dynamicBuffer
        for(int i = 0; i < 32; ++i)
            staticBuffer[i] = object_in.staticBuffer[i]; // copy staticBuffer
        for(int i = 0; i < currSize - 32; ++i)
            dynamicBuffer[i] = object_in.dynamicBuffer[i]; // copy dynamicBuffer
        capacity = currSize;
    }
    return object_in;
}

int SmallVector::getSize() const{
    return currSize;
}

int SmallVector::getCapacity() const{
    return capacity;
}

SmallVector::~SmallVector(){
    if(capacity > 32)
        delete[] dynamicBuffer;
}
