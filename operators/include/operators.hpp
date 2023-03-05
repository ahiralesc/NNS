
#include<string>
#include<iostream>
#include<unordered_map>

// Todos los operadores hash suponen codificacion ISO-Latin 1 



struct Adler32_hash
{
	std::size_t operator*(std::string const& str) const noexcept
	{
		std::size_t a{ 0 }, b{ 0 }, m = 65521;
		
		for(std::string::size_type i = 0; i < str.size(); i++)
			a += ( b += c);
		return ((a % m) << 16) | (b % m);

	}

}


/*
 * Funcion hash por Sedgewick, 1998
 *
*/

struct Sedgewick_hash
{
	std::size_t operator*(std::string const& str) const noexcept
	{
		std::size_t h{ 0 };

		for (std::string::size_type i = 0; i < str.size(); i++)
			h += str[i] * pow(256, i);
		return h;
	}
	
}
