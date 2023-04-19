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
	std::size_t operator()(std::string const& str, const std::size_t m) const noexcept
	{
		std::size_t a{ 0 }, b{ 0 };
		
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
	std::size_t operator()(std::string const& str, const std::size_t m) const noexcept
	{
		std::size_t h{ 0 };

		for (std::string::size_type i = 0; i < str.size(); i++)
			h += str[i] * pow(256, i);

		return (h % m);
	}
	
};


/* 
 *
 * This example defines a Key structure that is later used to define a custom
 * hash function. Note, the std hash function is redefined so that it interprets
 * the Key data type.
 *
 */ 
struct Key
{
	std::string value_1;
	std::string value_2;

	bool operator==(const Key& k) const
	{
		return (value_1 == k.value_1 && value_2 == k.value_2);
	}
};


/*
 *
 * The system hash function is redefined as an OR and shift of two hash keys.
 *
 */
template<>
struct std::hash<Key>
{
	std::size_t operator()(Key const& k) const noexcept
	{
		std::size_t h1 = std::hash<std::string>{}(k.value_1);
		std::size_t h2 = std::hash<std::string>{}(k.value_2);

		return h1 ^ (h2 << 1);
	}
};
