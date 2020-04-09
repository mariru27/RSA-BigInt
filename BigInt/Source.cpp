#include <iostream>
#include <string>
#include "BigInt.h"
#include<bitset>
#include <array>

//#include "bits/stdc++.h"

int main()
{
	std::string message{ "message" };
	std::size_t str_hash = std::hash<std::string>{}(message);
	std::cout << str_hash << std::endl;
	BigInt a(2) , b(1);

	BigInt c;
	
	c = a * b;
	c.print();

	//std::cout << 154 / 3;


	std::cout << std::endl;
	return 0;
}