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
	BigInt a(2), b(1024);
	////BigInt a, b;
	////std::cin >> a >> b;
	BigInt c;
	c = a ^ b;
	std::cout << std::endl << c;
	std::cout << std::endl;
	//std::cout << 10 % 10;
	return 0;
}
