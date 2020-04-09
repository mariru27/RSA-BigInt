#include <iostream>
#include <string>
//here--------------------------------------------------
#include "BigInt.h"
//------------------------------------------------------
#include<bitset>
#include <array>

int main()
{
	std::string message{ "message" };
	std::size_t str_hash = std::hash<std::string>{}(message);
	//std::cout << str_hash << std::endl;
	//BigInt a(23312421), b(32872113);	
	BigInt a, b;
	std::cin >> a >> b;
	BigInt c;
	std::cout << std::endl << a*b;
	std::cout << std::endl;
	return 0;
}