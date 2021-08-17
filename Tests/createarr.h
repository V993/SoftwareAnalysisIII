#ifndef CREATEARR_
#define CREATEARR_

#include <iostream>
#include <vector>
using namespace std;

class createarr
{
    private:
        int size;
        int* arr;
    public:
        createarr(); ///Default constructor

        createarr(int inputsize); //Paramaterized Constructor

        createarr(createarr &copyarray); //Copy Constructor

        createarr(createarr &&movearray); //Move array

        ~createarr(); //Delete Array

        void show();


};


#endif // !CREATARR_