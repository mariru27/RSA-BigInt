#pragma once

BigInt p(58991), q(54851), e, n, f, pOne, qOne;
BigInt d;

BigInt gcd(BigInt a, BigInt b, BigInt& x, BigInt& y) {
	x.setBigInt(1);
	y.setBigInt(0);
	BigInt x1(0), y1(1), a1(a), b1(b);
	while (b1 != zero) {
		BigInt q;
		q = a1 / b1;
		BigInt res;
		res = q * x1;
		res = x - res;
		std::tie(x, x1) = std::make_tuple(x1, res);
		res = q * y1;
		res = y - res;
		std::tie(y, y1) = std::make_tuple(y1, res);
		res = q * b1;
		res = a1 - res;
		std::tie(a1, b1) = std::make_tuple(b1, res);
	}
	return a1;
}

BigInt find_d(BigInt a, BigInt m)
{
	BigInt x, y;
	BigInt g;
	g = gcd(a, m, x, y);
	if (g != one)
	{
		g.setBigInt(0);
		return g;
	}
	else
	{
		BigInt resultat;
		resultat = x % m;
		resultat = resultat + m;
		resultat = resultat % m;
		return resultat;
	}
}

BigInt find_e()
{
	BigInt e;
	while (e < f)
	{
		e.randomNumber(5);
		while (isPrimeStatistic(e)==false)
		{
			++e;
		}
		if (isPrimeClassic(e) == true)
			return e;
	}
	return one;
}

BigInt modularExponentation(BigInt a, BigInt b, BigInt c)
{
	if (b == zero)
	{
		return one;
	}
	else if (b % two == zero)
	{
		BigInt d = modularExponentation(a, b / two, c);
		BigInt z = d * d;
		z = z % c;
		return z;
	}
	else {
		BigInt z = a % c;
		z = z * modularExponentation(a, b - one, c);
		z = z % c;

		return z;
	}
}


void encryptAndDecrypt(BigInt m)
{
	BigInt c, dec;
	m.setBigInt(1241);
	std::cout << "message: " << m << std::endl;
	c = modularExponentation(m, e, n);
	std::cout << "encypted meeage: " << c;
	dec  = modularExponentation(c, d, n);
	std::cout << std::endl << "decrypted message: " << dec;
}

void RSA()
{
	bool pIsPrime = false, qIsPrime = false;

	//int numberOfDigits = 5;
	//while (pIsPrime == false && qIsPrime == false)
	//{
	//	//find p, a prime number
	//	p.randomNumber(numberOfDigits);
	//	while (isPrimeStatistic(p) == false)
	//	{
	//		p.randomNumber(numberOfDigits);
	//		
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
	std::cout<< "n = " << n <<std::endl;
	pOne = p - one;
	qOne = q - one;
	f = pOne * qOne;
	std::cout<< "f = " << f <<std::endl;

	e = find_e();
	std::cout<< "e = " << e <<std::endl;

	d = find_d(e, f);
	std::cout<< "d = " << d <<std::endl;


	BigInt message(3837);
	encryptAndDecrypt(message);

}
