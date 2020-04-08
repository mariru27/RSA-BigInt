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
	BigInt a(3), b(2), c;

	//b.print();
	c = a * b;
	c.print();
	return 0;
}