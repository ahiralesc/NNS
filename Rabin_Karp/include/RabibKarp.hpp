#ifndef __rabin_karp_hpp_
#define __rabin_karp_hpp_

/*
    See Richard. M. Karp and Michael O. Rabin. Efficiet randomized pattern matching algorithms
    IBM J. Res. Develp. Vol 31, No. 2 1987.
*/


#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;



template<typename T>
class ordenamiento {
    private:
        
        /* TODO: reemplace la cadena y coloque el nombre de su algoritmo de ordenamiento */ 
        void name() { std::cout << "My sorting method" << std::endl; }

    public:
        
        /*
            Esta interfaz recibe como entrada un vector de tipo T y produce un 
            ordenamiento creciente de sus elementos.
            
            Entrada:
                La direccion del primer elemento del vector.
                La direccion del ultimo elemento del vector.
        */
        static void ordena(typename std::vector<T>::iterator &&b, typename std::vector<T>::iterator &&e) {

            ordenamiento<T>* instance = new ordenamiento<T>();

            
            /* TODO: 
                La instruccion std::sort(b, e) ejemplifica una llamada statica a una clase. Esto permite
                invocar el metodo sin crear una instancia del algoritmo. Usted debe sustituir
                esta linea por su algoritmo de ordenamiento. El metodo de ordenamiento debe llamarse sort
                y debe permitir realizar llamadas estaticas sobre el. Si no tiene conocimiento de como realizar
                una llamada estatica vea el siguiente tutoreal: https://www.learncpp.com/cpp-tutorial/static-member-functions/
            */
            std::sort(b, e);

            instance->name();

            
            /* TODO DELETE: 
               El siguiente codigo ejemplifica como iterar sobre una estructura de datos iterable.
            */
            for(auto p=b; p!=e; p++)
                std::cout << " -- " << *p; 
            std::cout << std::endl;
        }
        
        
        /*
            Esta interfaz recibe como entrada un vector de tipo T y un apuntador a una funcion de comparacion.
            Como salida, genera un ordenamiento en acorde al criterio de ordenamiento que se proporcione.

            Entrada:
                La direccion del primer elemento del vector.
                La direccion del ultimo elemento del vector.

        */
        static void ordena(typename std::vector<T>::iterator &&b, typename std::vector<T>::iterator &&e,
            bool (*fp)(T& i, T&j)) {

            
            /* TODO: Reemplazar la linea de codigo con un llamado estatico a un metodo de ordenamiento
               de su clase.
            */
            std::sort(b, e, fp);

            /* TODO DELETE:
               El siguiente codigo ejemplifica dos formas de ejecutar una funcion que se recibio a traves 
               de un apuntador a una funcion 
            */
               
            T x{1}; // Inicializacion de la variable x a 1
            T y{2}; // Inicializacion de la variable y a 2
            // Invocacion de la funcion aputada por fp
            std::cout << "First call to callback function: " << (* fp)(x,y) << std::endl;
            // Invocacion, standard, de la funcion aputada por fp
            std::cout << "Second call to callback function: " << fp(x,y) << std::endl;
        }
};

#endif
