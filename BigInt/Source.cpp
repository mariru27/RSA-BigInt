#include <iostream>
#include <string>
#include "BigInt.h"
#include<bitset>

//#include "bits/stdc++.h"



int main()
{
	std::string message{ "message" };
	std::size_t str_hash = std::hash<std::string>{}(message);
	std::cout << str_hash << std::endl;
	BigInt a, b, c;
	b.setBit(1);
	b.setBit(3);
	c.setBit(2);
	c.setBit(1);
	
	b.print();
	std::cout << " + ";
	c.print();
	std::cout << " = ";
	a = b + c;
	a.print();

	return 0;
}