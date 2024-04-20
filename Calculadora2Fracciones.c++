#include <stdlib.h>
#include <iostream>

using namespace std;

class Fraccion {
    private:
        int numerador, denominador; 


        void simplificar(){
            int menor = abs(numerador);
            if (menor > abs(denominador)) {
                menor = abs(denominador);
            }
            for (int i = menor; i >= 2 ; i--){
                if (numerador % i == 0 && denominador % i == 0){
                    numerador = numerador / i;
                    denominador = denominador / i;
                }
            }    
        }

    public:
        // Constructor
        /*
        Fraccion(){
            Fraccion(0,1);
        }

        Fraccion(int numerador, int denominador){
            this->numerador = numerador, this->denominador = denominador;
        }
        */

        Fraccion(int numerador = 0, int denominador = 1){
            //cout << "** Creando Objeto (Constructor) **" << endl;
            this->numerador = numerador, this->denominador = denominador;
        }

        Fraccion(Fraccion *objeto_a_clonar){
            this->numerador = objeto_a_clonar->getNumerador();
            this->denominador = objeto_a_clonar->getDenominador();
        }

        //~Fraccion();

        float aPuntoFlotante() {
            return (float)this->numerador / this->denominador;
        }

        void invertir(){
            int aux = this->numerador;
            this->numerador = this->denominador;
            this->denominador = aux;
        }

        Fraccion *sumar(Fraccion *Fraccionsumando){
            int nuevoDeno = this->denominador * Fraccionsumando->getDenominador();
            int nuevoNum = (this->numerador * Fraccionsumando->getDenominador()) + (this->denominador * Fraccionsumando->getNumerador());
            Fraccion *resultante = new Fraccion(nuevoNum, nuevoDeno);
            resultante->simplificar();
            return resultante;
        }

        Fraccion *multiplicar(Fraccion *otraFraccion){
            int nuevoNum = (this->numerador * otraFraccion->getNumerador());
            int nuevoDeno = this->denominador * otraFraccion->getDenominador();
            Fraccion *resultante = new Fraccion(nuevoNum, nuevoDeno);
            resultante->simplificar();
            return resultante;
        }

        Fraccion *dividir(Fraccion *otraFraccion){
            //Fraccion *clon = new Fraccion(otraFraccion->getNumerador(), otraFraccion->getDenominador());
            Fraccion *clon = new Fraccion(otraFraccion);
            clon->invertir();
            return multiplicar(clon);
        }

        string tipoFraccion(){
            if (numerador >= denominador) {
                return "IMPROPIA";
            } else {
                return "PROPIA";
            }
        }

        

        // getter Obtener informacion de atributos
        // setters fijar nueva infromación a los atributos
        int getNumerador(){
            return this->numerador;
        }

        void setNumerador(int valor){
            this->numerador = valor;
        }

        int getDenominador(){
            return this->denominador;
        }

        void setDenominador(int valor){
            this->denominador = valor;
        } 

        string toString(){
            string str = "[" + to_string(this->numerador);
            if (this->denominador != 1) {
                str = str + "/" + to_string(this->denominador);
            } 
            str = str + "]";
            return str;
        }

};

class CalculadorFraccion{
    private:
        Fraccion *fracciones;
        int numeroFracciones;

        
        Fraccion *sumar(){
            Fraccion *rta;
            if (numeroFracciones > 1) {
                for (int i = 0; i < this->numeroFracciones-1; i++){
                    rta = &this->fracciones[i];
                    rta = rta->sumar(&this->fracciones[i+1]);
                }
            } else {
                rta = &this->fracciones[0];
            }
            return rta;
        }

       /*
       Fraccion *sumar(){
            Fraccion *rta = new Fraccion(0,1);
            for (int i = 0; i < this->numeroFracciones; i++){
                rta = rta->sumar(&this->fracciones[i]);
            }            
            return rta;
        }
        */
    public:
        
        CalculadorFraccion(int numeroFracciones = 2){
            this->numeroFracciones = numeroFracciones;
            fracciones = (Fraccion *)malloc(sizeof(Fraccion) * this->numeroFracciones);
        }

        CalculadorFraccion(int numeroFracciones, Fraccion *fracciones){
            this->numeroFracciones = numeroFracciones;
            this->fracciones = fracciones;
        }



        //~CalculadorFraccionn();

        Fraccion * calcular(char operacion){
            Fraccion *rta;
            switch (operacion) {
                case '+':
                    rta = this->sumar();
                    break;
                
                default:
                    break;
                }
            return rta;
        }

        void agregarFraccion(Fraccion *fraccion, int posicion) {
            
            this->fracciones[posicion] = fraccion;
        }

        int getNumeroFracciones(){
            return this->numeroFracciones;
        }    

        Fraccion * getFracciones(){
            return this->fracciones;
        }
};

/// VISTA
Fraccion * ingresarFraccion(string mensaje);
CalculadorFraccion * crearCalculadora();

void presentarCalculo(Fraccion *operandos, int limite, char operacion, Fraccion *rta);
void calcular(CalculadorFraccion *cf, char operacion);

int main(int argc, char const *argv[]){
    system("@cls||clear");
    CalculadorFraccion *calculadorFraccion = crearCalculadora();
    
    char operacion;
    cout << " Operaciona que desea realizar (+,-,*,/)? ";
    cin >> operacion;

    //Fraccion *rta = calculadorFraccion->calcular(operacion);
    //presentarCalculo(calculadorFraccion->getFracciones(), calculadorFraccion->getNumeroFracciones(), operacion, rta);
    calcular(calculadorFraccion, operacion);
    return 0;
}

Fraccion * ingresarFraccion(string mensaje){
    Fraccion *f = new Fraccion ();
    cout << mensaje << endl;
    int ingreso;
    cout << "Ingrese numerador: ";
    cin >> ingreso;
    f->setNumerador(ingreso);
    cout << "Ingrese denominador: ";
    cin >> ingreso;
    f->setDenominador(ingreso);
    return f;
}

CalculadorFraccion * crearCalculadora(){
    int limite;
    cout << "Cuantas fracciones desea operar: " << endl;
    cin >> limite;

    CalculadorFraccion *cf = new CalculadorFraccion(limite);
    for (int i = 0; i < limite; i++){
        Fraccion *f = ingresarFraccion("Fraccion " + to_string(i+1));
        cf->agregarFraccion(f,i);
    }
    return cf;

}

void presentarCalculo(Fraccion *operandos, int limite, char operacion, Fraccion *rta){
    for (int i = 0; i < limite; i++){
        cout << operandos[i].toString() << operacion;
    }
    cout << endl;
    cout << " = " << rta->toString() << " ==>  " << rta->aPuntoFlotante() <<endl;
}

void calcular(CalculadorFraccion *cf, char operacion){
    Fraccion *rta = cf->calcular(operacion);
    Fraccion *operandos = cf->getFracciones();
    for (int i = 0; i < cf->getNumeroFracciones(); i++){
        cout << operandos[i].toString() << operacion;
    }
    cout << endl;
    cout << " = " << rta->toString() << " ==>  " << rta->aPuntoFlotante() <<endl;
}