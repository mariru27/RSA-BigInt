#include <iostream>
#include <string>
//here--------------------------------------------------
#include "BigInt.h"
//------------------------------------------------------
#include <random>
#include <functional>
#include <vector>
#include "Prim.h"





int main()
{
	//std::string message{ "my message" };
	//std::size_t str_hash = std::hash<std::string>{}(message);
	//std::cout << str_hash << std::endl;


	//after we generated a random number on 1024 bits, we need to determine if this is prime

	BigInt b;
	b.randomNumber(6);
	while (isPrimeStatistic(b)==false)
	{
		b.randomNumber(6);
	}
	std::cout << "am gasit nr prim";
	if(isPrimeClassic(b))
		std::cout << "\nNumarul prim este: " << b;



}




