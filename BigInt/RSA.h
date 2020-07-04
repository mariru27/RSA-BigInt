#pragma once

BigInt p, q, e, n, f, pOne, qOne;
BigInt d;

std::vector<std::string> blocks;



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

template <class T>
std::vector<BigInt> encryptAndDecrypt(std::vector<T> v, BigInt exponent, BigInt n)
{
	std::vector<BigInt> resultedBlocks;

	for (auto it = v.begin(); it != v.end(); ++it)
	{
		resultedBlocks.push_back(modularExponentation(*it, exponent, n));
	}
	return resultedBlocks;
}

std::string fromSizeToString(std::size_t size)
{
	std::string str;
	int n;
	while (size != 0)
	{
		char s = size % 10;
		s += '0';
		str.push_back(s);
		size /= 10;
	}
	std::reverse(str.begin(), str.end());
	return str;
}

void combineBlocks(std::string str)
{
	int i = 0;
	std::string block;
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		if (i == 4)
		{
			i = 0;
			blocks.push_back(block);
			block.clear();
		}
		++i;
		int a = (*it) - ' ';
		std::string s = std::to_string(a);
		
		if (a <= 9)
		{
			block += '0';
		}
		block += s;
	}
	while (block.size() < 8)
	{
		block += '00';
	}
	blocks.push_back(block);
}

std::string devideBlocks(std::vector<BigInt> v, bool hash = false)
{
	std::string message;
	int size = SIZE - 7;
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		for (auto i = size; i < SIZE ; i = i + 2)
		{
			int a = (*it).getValue(i);
			int b = (*it).getValue(i + 1);
			if (a == 0)
			{
				b += ' ';
				char c = b;
				std::cout << c;
				message.push_back(c);
			}
			else
			{
				a *= 10;
				a += b;
				a += ' ';
				char c = a;
				std::cout << c;
				message.push_back(c);
			}
		}
	}
	if (hash == true)
	{
		std::string hashMessage;
		for (auto it = message.begin(); it != message.end(); ++it)
		{
			if ((*it) != ' ')
				hashMessage.push_back(*it);
		}
		return hashMessage;
	}
	return message;
	
}


template <class T>
void print(std::vector<T> v)
{
	std::vector<BigInt> resultedBlocks;
	std::cout << "---------------------------------------------------------------------\n";
	for (auto it = v.begin(); it != v.end(); ++it)
	{
		std::cout << (*it) << std::endl;
	}
}



void RSA()
{
	bool pIsPrime = false, qIsPrime = false;

	int numberOfDigits = 6;
	std::cout << "You need to wait  ......\n";
	while (pIsPrime == false && qIsPrime == false)
	{
		//find p, a prime number
		p.randomNumber(numberOfDigits);
		while (isPrimeStatistic(p) == false)
		{
			p.randomNumber(numberOfDigits);
			
		}
		std::cout << "I found a number that is possible prime:";
		if (isPrimeClassic(p))
		{
			std::cout << "\nPrime number \"p\" is: " << p;
			pIsPrime = true;
		}
		else
			std::cout << "\nThis number is not prime: " << p;
		//find q, a prime number
		q.randomNumber(numberOfDigits);
		while (isPrimeStatistic(q) == false)
		{
			q.randomNumber(numberOfDigits);
		}
		std::cout << "\nI found a number that is possible prime";
		if (isPrimeClassic(p))
		{
			std::cout << "\nPrime number \"q\" is: " << q;
			qIsPrime = true;
		}
		else
			std::cout << "\nThis number is not prime: " << q;
	}

	n = p * q;
	std::cout<< "\nn = " << n <<std::endl;
	pOne = p - one;
	qOne = q - one;
	f = pOne * qOne;
	std::cout<< "f = " << f <<std::endl;

	e = find_e();
	std::cout<< "e = " << e <<std::endl;

	d = find_d(e, f);
	std::cout<< "d = " << d <<std::endl;

	std::string message;
	std::cout << "Enter the message you want to send to Bob: ";
	getline(std::cin, message);
	combineBlocks(message);
	std::cout << "blocks: ";
	print(blocks);
	

	std::cout << "\nNow we will encrypt this message(with private key) using RSA alghoritm:\n ";
	std::vector<BigInt> encryptedBlocks = encryptAndDecrypt(blocks, d, n);
	std::cout << "encrypted blocks: ";
	print(encryptedBlocks);
	blocks.clear();

	std::string HashMessage{ message };
	std::size_t str_hash = std::hash<std::string>{}(HashMessage);
	std::cout << "Hash message: " << str_hash << std::endl;
	std::string HashMessage1 = fromSizeToString(str_hash);
	combineBlocks(HashMessage1);
	std::cout << "blocks: ";
	print(blocks);

	std::cout << "\nNow we will encrypt this Hash message(with private key) using RSA algorithm:\n ";
	std::vector<BigInt> encryptedHashBlocks = encryptAndDecrypt(blocks, d, n);
	std::cout << "encrypted Hash blocks: ";
	print(encryptedHashBlocks);


	std::cout << "\nNow Bob will decrypt this encrypted message, and Hash message(with your public key) using RSA algorithm:\n ";
	std::vector<BigInt> decryptedBlocks = encryptAndDecrypt(encryptedBlocks, e, n);
	std::cout << "decrypted bloks: ";
	print(decryptedBlocks);

	std::cout << "Decypt hash message blocks: ";
	std::vector<BigInt> decryptedHashBlocks = encryptAndDecrypt(encryptedHashBlocks, e, n);
	std::cout << "decrypted Hash blocks: ";
	print(decryptedHashBlocks);

	std::cout << "\ndecrypted message: ";
	std::string receivedMessage = devideBlocks(decryptedBlocks);

	std::cout << "\ndecrypted Hash message: ";
	std::string receivedHashMessage = devideBlocks(decryptedHashBlocks, true);
	std::cout << "\nNow Bob will verify if this message come from you, he will hash this message(that has been decrypted by Bob with your public key)\nand compare obtained hash with your hash(which you sent)";
	
	std::size_t str_hashMessage = std::hash<std::string>{}(HashMessage);
	std::cout << "\nmessage: " << receivedMessage << " <----------------> Hash message: " << str_hashMessage;

	std::cout << std::endl;
	std::string resultHash = fromSizeToString(str_hashMessage);
	if (resultHash == receivedHashMessage)
		std::cout << std::endl << "The message was sent by you(the hash i received and calculated are the same)" << std::endl;
	else
		std::cout << std::endl << "The message has been modified(the hash i received and calculated are different)" << std::endl;
}
