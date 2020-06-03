#pragma once

BigInt cmmdc(BigInt a, BigInt h)
{
	//check if a is coprime with h
	BigInt temp;
	while (true)
	{
		temp = a % h;
		if (temp == zero)
			return h;
		a = h;
		h = temp;
	}
}

void RSA()
{
	bool pIsPrime = false, qIsPrime = false;
	BigInt one(1);
	BigInt p, q, e(4), n, f, pOne, qOne;
	int numberOfDigits = 6;
	while (pIsPrime == false && qIsPrime == false)
	{
		//find p, a prime number
		p.randomNumber(numberOfDigits);
		while (isPrimeStatistic(p) == false)
		{
			p.randomNumber(numberOfDigits);
		}
		std::cout << "am gasit un numar care este posibil prim, acum o sa verific daca este prim";
		if (isPrimeClassic(p))
		{
			std::cout << "\nNumarul prim \"p\" este: " << p;
			pIsPrime = true;
		}
		else
			std::cout << "\nAcest numar nu este prim: " << p;
		//find q, a prime number
		q.randomNumber(numberOfDigits);
		while (isPrimeStatistic(q) == false)
		{
			q.randomNumber(numberOfDigits);
		}
		std::cout << "\nam gasit un numar care este posibil prim, acum o sa verific daca este prim";
		if (isPrimeClassic(p))
		{
			std::cout << "\nNumarul prim \"q\" este: " << q;
			qIsPrime = true;
		}
		else
			std::cout << "\nAcest numar nu este prim: " << q;
	}
	n = p * q;
	pOne = p - one;
	qOne = q - one;
	f = pOne * qOne;

	//e.randomNumber(1);
	while (e < f)
	{
		if (cmmdc(e, f) == one)
			break;
		else
			++e;
	}
	BigInt k(4);
	BigInt d;
	d = k * f;
	d = d + one;
	d = d / e;


	BigInt result;
	result = d * e;
	result = result % f;


	BigInt message(2546);
	std::cout << "\nmessage is: " << message << std::endl;

	BigInt c;
	c = message ^ e;
	c = c % n;
	std::cout << "mesajul criptat: " << c << std::endl;

	BigInt m;
	m = c ^ d;
	m = m % n;

	//std::cout << "mesajul dupa decriptare este: " << m << std::endl;
}
