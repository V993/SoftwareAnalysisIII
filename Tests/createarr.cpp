#include "createarr.h"


createarr::createarr() : size(0) {}


createarr::createarr(int inputsize) : size(inputsize) //Paramatarized constructor
 {  
     arr = new int[size];
    for(int i=0;i<inputsize;i++)
    {
        arr[i] = i;
    }
 }



createarr::createarr(createarr &copyarray)//Copy Constructor
{
    size = copyarray.size;
    arr = new int[size];

    
    for(int i=0; i<size;i++)
    {
        arr[i] = copyarray.arr[i];
    }
}



createarr::createarr(createarr &&movearray) //Move array
{
    size = movearray.size;
    arr = movearray.arr;
    movearray.~createarr();
}


createarr::~createarr() //Destructor
{
    delete arr;
    
}



void createarr::show()
{
    for(int i =0; i < size;i++)
    {
        cout << "{" << arr[i] << "}";
    }
        cout << endl;
}