#include "createarr.cpp"
/*

1. Our prof is a shithead
2. our prof is using his own software hes doing research in for plagerism detection
3. he is probably in our server
4. do not post the server link on the blackboard
5. he is shostak 2.0














*/




void arrbyvalue(createarr arradd);
void arrbyref(createarr arradd);


int main()
{
    createarr newarray(5);
    createarr copiedarray(newarray);
    //copiedarray.show();
    //newarray.~createarr();
    //copiedarray.show();
    
  

    
    createarr arrcopying = createarr(10);
    //createarr temparray = createarr(5);
   // createarr copyarray = createarr(arrcopying);
    createarr movearray = createarr(createarr(5));
    //std::move(copyarray);
    movearray.show();

}