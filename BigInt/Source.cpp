#include <iostream>
#include <string>
//here--------------------------------------------------
#include "BigInt.h"
//------------------------------------------------------
#include<bitset>
#include <array>
#include <random>
#include <functional>
#include <ctime>
#include "rng.h"
#include <vector>



BigInt one(1), two(2), zero;
void initVector(std::vector<int>& v)
{
	for (std::size_t it = 0; it <= SIZE; ++it)
		v.push_back(0);
}

void printVector(std::vector<int>& v)
{
	for (std::size_t it = 0; it <= SIZE; ++it)
	{
		std::cout << v[it];
	}
}

BigInt power(BigInt x, BigInt y, BigInt p)
{
	BigInt result(1);
	x = x % p;
	while (y > zero)
	{
		if (y % two != zero)
		{
			result = result * x;
			result = result % p;
		}
		y = y / two;
		x = x * x;
		x = x % p;
	}
	return result;
}

bool millerRabin(BigInt& d, BigInt& n)
{
	BigInt rand;
	rand.randomNumber();
	BigInt a, randN;
	randN = rand % n;
	a = two + randN;

	BigInt x;
	x = power(a, d, n);


	BigInt nOne;
	nOne = n - one;
	if (x == one || x == nOne)
		return true;



	while (d != nOne)
	{
		x = (x * x) % n;
		d = d * two;
		if (x == one)
			return false;
		if (x == nOne)
			return true;

	}
	return false;
}

bool isPrimeStatistic(BigInt n)
{
	BigInt d;
	d = n - one;

	while (d % two == zero)
	{
		d = d / two;
	}
	for (std::size_t i = 0; i < 4; ++i)
	{
		if (!millerRabin(d, n))
			return false;
	}

	return true;
}

bool isPrimeClassic(BigInt& n)
{
	BigInt one(1);
	if (n == one)
		return false;
	BigInt zero, sqrt;
	BigInt i(1);
	sqrt = n.sqrt();
	while (i < sqrt)
	{
		++i;
		if (n % i == zero)
			return false;
	}
	return true;
}

int main()
{
	//std::string message{ "message" };
	//std::size_t str_hash = std::hash<std::string>{}(message);
	//std::cout << str_hash << std::endl;


	//after we generated a random number on 1024 bits, we need to determine if this is prime
	/*BigInt a;
	a.randomNumber();
	while (isPrimeClassic(a) == false)
	{
	std::cout << a;
	std::cout << std::endl;

		a.randomNumber();
	}
	std::cout << "------------\n";
	std::cout << a;*/

	//a.randomNumber();

	/*while (isPrimeClassic(a) == false)
	{

		a.randomNumber();
		std::cout << a << std::endl << std::endl;
	}*/
	//BigInt b, a;
	//a.setPosition(SIZE - 3, 1);
	//b.randomNumber();
	//while (isPrimeStatistic(b)==false)
	//{
	//	if (b < a)
	//	{
	//		b.randomNumber();
	//	}
	//	--b;
	//	while (b%two == zero)
	//	{
	//		b = b / two;
	//	}
	//
	//	std::cout << b << std::endl;
	//}


	//std::vector<int> v{ 4,64,3,4,7,9,6,5,1,3,8,0,1,7 };
	//BigInt b(v);
	//if(isPrimeStatistic(b))
	//std::cout << "Numarul prim este: " << b;


	//BigInt a(234), b(23);
	BigInt a(23), b(10);
	//BigInt a, b;
	//std::cin >> a;
	//std::cin >> b;
	if (isPrimeStatistic(a))
		std::cout << "numar prim: " << a;
	std::cout << std::endl << a;
	std::cout << std::endl << b;
	std::cout << "\nsuma:" << a + b << std::endl;
	std::cout << "diferenta: " << a - b << std::endl;
	std::cout << "inmultire: " << a * b << std::endl;
	//BigInt c;
	//c = a ^ b;
	//std::cout << "putere: " << c << std::endl;
	std::cout << "div: " << a / b << std::endl;
	std::cout << "mod: " << a % b << std::endl;

}




