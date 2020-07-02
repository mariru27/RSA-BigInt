#pragma once

BigInt one(1), two(2), zero;

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
	rand.randomNumbermin(n);
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

int countNrOfDigits(int n)
{
	int count = 0;
	while (n != 0)
	{
		++count;
		n /= 10;
	}

	return count;
}