#pragma once

BigInt p(16553), q(14717), e(5), n, f, pOne, qOne;

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

BigInt gcd(BigInt a, BigInt b, BigInt& x, BigInt& y) {
	//x = 1, y = 0;
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
	//while (e < f)
	//{
	//	if (cmmdc(e, f) == one)
	//		break;
	//	else
	//		++e;
	//}




	BigInt e;
	while (e < f)
	{

		e.randomNumber(3);
		while (isPrimeStatistic(e)==false)
		{
			++e;
		}
		if (isPrimeClassic(e) == true)
			return e;
	}
	return one;
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
	e = find_e();

	BigInt d;
	d = find_d(e, f);


	BigInt message(2);
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
