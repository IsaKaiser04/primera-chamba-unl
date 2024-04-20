#include <iostream>
using namespace std;


class SumaNum{
private:
    int num1,num2;
public:
    SumaNum(){
       num1 = 0;
       num2 = 0;
    }
    void ingresar(){
        cout <<"Ingrese el primer numero:";
        cin >> num1;
        cout << "Ingrese el primer numero:";
        cin >> num2;
    }
    int sumar(){
    return num1+num2;
    }
   
};

int main(){
    SumaNum suma;
    suma.ingresar();
    cout<<"La sum total es:"<<suma.sumar()<<endl;
    return 0;
}