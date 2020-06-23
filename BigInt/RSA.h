#pragma once

BigInt p(11), q(19), e(5), n, f, pOne, qOne;

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

BigInt find_d()
{
	BigInt d;
	BigInt random_number(3);
	BigInt result;
	while (random_number < e || random_number == e)
	{
		d = random_number * f;
		d = d + one;
		d = d / e;

		result.setBigInt(0);
		result = d * e;
		result = result % f;
		if (result == one)
			return d;
		else
			++random_number;
	}

	return result;
	std::cout << "Nu s-a gasit d\n";

}
void RSA()
{
	bool pIsPrime = false, qIsPrime = false;

	//int numberOfDigits = 2;
	//while (pIsPrime == false && qIsPrime == false)
	//{
	//	//find p, a prime number
	//	p.randomNumber(numberOfDigits);
	//	while (isPrimeStatistic(p) == false)
	//	{
	//		p.randomNumber(numberOfDigits);
	//	}
	//	std::cout << "am gasit un numar care este posibil prim, acum o sa verific daca este prim";
	//	if (isPrimeClassic(p))
	//	{
	//		std::cout << "\nNumarul prim \"p\" este: " << p;
	//		pIsPrime = true;
	//	}
	//	else
	//		std::cout << "\nAcest numar nu este prim: " << p;
	//	//find q, a prime number
	//	q.randomNumber(numberOfDigits);
	//	while (isPrimeStatistic(q) == false)
	//	{
	//		q.randomNumber(numberOfDigits);
	//	}
	//	std::cout << "\nam gasit un numar care este posibil prim, acum o sa verific daca este prim";
	//	if (isPrimeClassic(p))
	//	{
	//		std::cout << "\nNumarul prim \"q\" este: " << q;
	//		qIsPrime = true;
	//	}
	//	else
	//		std::cout << "\nAcest numar nu este prim: " << q;
	//}
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

	BigInt d;
	d = find_d();


	BigInt message(26);
	std::cout << "\nmessage is: " << message << std::endl;

	BigInt c;
	c = message ^ e;
	c = c % n;
	std::cout << "mesajul criptat: " << c << std::endl;

	BigInt m;
	m = c ^ d;
	m = m % n;

	std::cout << "mesajul dupa decriptare este: " << m << std::endl;
}
