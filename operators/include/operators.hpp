#include <string>
#include <iostream>
#include <unordered_map>
#include <cmath>

// All operators assume ISO-Latin 1 encoding

/*
 *
 * Adler hash operator
 *
 */
struct Adler32_hash
{
	std::size_t operator()(std::string const& str) const noexcept
	{
		std::size_t a{ 0 }, b{ 0 }, m = 65521;
		
		for(std::string::size_type i = 0; i < str.size(); i++)
			a += ( b += str[i]);
		return ((a % m) << 16) | (b % m);

	}

};


/*
 *
 * Sedgewick hash operator, 1998
 *
 */
struct Sedgewick_hash
{
	std::size_t operator()(std::string const& str) const noexcept
	{
		std::size_t h{ 0 };

		for (std::string::size_type i = 0; i < str.size(); i++)
			h += str[i] * pow(256, i);

		return h;
	}
	
};
