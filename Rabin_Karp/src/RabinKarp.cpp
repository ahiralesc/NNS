// RabinKarp.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <regex>

using namespace std;

/*
Los operadores binarios en C/C++ incluyen

&	operador AND
|	operador OR
^	operador XOR
~	operador de negaciom
<<	corrimiento a la izquierda
>>	corrimiento a la derecha

Los tipos de datos en c/c++ se almacenan en bytes e.g

Tipo de dato			Bytes	Rango								Bandera de formato
short int				2		-32,768 to 32,767					%hd
unsigned short			2		0 to 65,535							%hu
unsigned int			4		0 to 4,294,967,295					%u
int						4		-2,147,483,648 to 2,147,483,647		%d
long int				4		-2,147,483,648 to 2,147,483,647		%ld
unsigned long int		4		0 to 4,294,967,295					%lu
long long int			8		-(2^63) to (2^63)-1					%lld
unsigned long long int	8		0 to 18,446,744,073,709,551,615		%llu
signed char				1		-128 to 127							%c
unsigned char			1		0 to 255							%c
float					4											%f
double					8											%lf
long double				16											%Lf
*/

typedef unsigned int tipo;

void operaciones_basicas_sobre_bits(void) {
	/*	
		Suponga un mapa de bits de 4 bytes (32 bits) inicializado a 0
		En este mapa, el bit mas significativo se encuentra a la izquierda y
		el menos significativo a la derecha. 
	*/
	tipo mapa{ 0 };

	/*	Suponga desea prender el bit 16. La cadena binaria equivalente a 16 decimal es
		
		0000 0000  0000 0000  0000 0000  0001 0000
	
		que almacena el valor con frecuencia es denominada mascara 
	*/
	tipo mascara{ 16 };

	/*	
		El operador binario que facilita un bit y que mantiene prendidos los bits en
		el mapa es el operador OR 
	*/
	mapa = mapa | mascara;

	/*	
		Suponga desea prender el segundo bit del mapa de bits. Tal corresponde a 1 binario
	
		0000 0000  0000 0000  0000 0000  0000 0010

		El siguiente ejemplo,  ilustra como inicializar el mapa utilizando mapa = mapa | mascara;
	*/
	mapa |= 1;

	/*	
		Ahora, suponga desea crear dinaminamente la bandera 32 esto corresponde a la mascara
	
		0000 0000  0000 0000  0000 0000  0010 0000

		Esta corresponde a 1 con un corrimiento a la izquierda de 6
	*/
	mascara = 1 << 5;

	mapa |= mascara;

	std::cout << "Estado de la mascara : " << mascara << std::endl;
	std::cout << "Estado del mapa : " << mapa << std::endl;

	/*
		Note los desplazamientos
	*/
	for(auto i=0; i<=4; i++)
		cout << "1 << " << i << " = " << (1 << i) << endl;
}



/*
	The following code is based on Horner polynomial encoding
	https://en.wikipedia.org/wiki/Horner%27s_method#:~:text=Alternatively%2C%20Horner's%20method%20also%20refers,into%20general%20use%20around%201970.
*/
tipo encode(string cadena, int base) {
	
	auto len  = cadena.length();
	tipo mascara{ 0 };
	
	for (auto i = 1; i <= len; i++)
		mascara += ((tipo)cadena[i]) * (tipo) pow(base, i);
	mascara += (unsigned int) cadena[0];
	
	return mascara;
}


void RabinKarp(string subcadena, tipo codigo) {

}


int main()
{
	// La siguiente funcion ejemplifica algunas funciones basicas con
	// operadores binarios
	operaciones_basicas_sobre_bits();
	
	// Visto lo anterior. El algoritmo de Rabin Karp transforma cadenas
	// a un entero aplicando un operador hash. Primero, se requiere transformar
	// la cadena a un entero.
	string cadena = "tijuana";

	// A simple transformation to a hash
	cout << encode(cadena, 256) << endl;
	
	string texto = "La ciudad de tijuana es muy dinamica. La cuidad de tijuana es una metropolis";

	/* 
		El caracter R"(\s+)" indica que se debe utilizar como criterio de separacion de cadenas la existencia
		de uno o mas espacios. El iterador se coloca al inicio de la cadena y finaliza en un caracter oculto 
		que indica la terminacion de la cadena.
	
	auto const re = std::regex{ R"(\s+)" };
	auto const tokens = std::vector<std::string>(
		std::sregex_token_iterator{ begin(texto), end(texto), re, -1 },
		std::sregex_token_iterator{}
	);

	int index = 0;
	for (string token : tokens) {

		cout << token << endl;
	} */

	tipo cadena_codificada = encode(cadena, 256);
	int len		= texto.length();
	int bloque	= cadena.length();
	
	int i	= 0;
	int f	= bloque;

	// Implementacion no eficiente
		while( (i + bloque) < len ) {
		 
		if( encode(texto.substr(i, f), 256) == cadena_codificada)
			cout << "Encontro una instancia en el indice : " << i << endl;
		i += 1;
		f += 1;
	}
	return 0;
}

