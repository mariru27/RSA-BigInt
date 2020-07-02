#include<iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>
#include <functional>

#define SIZE 60

class BigInt
{
	std::vector<int> container;
	bool isEmpty(std::vector<int>& v)
	{

		for (std::vector<int>::iterator i = v.begin() + 1; i < v.end(); ++i)
		{
			if (*i != 0)
				return false;
		}
		return true;
	}
	bool isEmpty(BigInt& Container)
	{

		for (std::vector<int>::iterator i = Container.container.begin() + 1; i < Container.container.end(); ++i)
		{
			if (*i != 0)
				return false;
		}
		return true;
	}
	int firstDifferentNr(std::vector<int>& v, int nr = 0)
	{
		for (int i = 1; i <= SIZE; ++i)
		{
			if (v[i] != nr && v[i - 1] == nr)
				return i - 1;
		}
		return 0;
	}
	bool allZeros()
	{
		bool zeros = std::all_of(container.begin() + 1, container.end(), [](int i) { return i == 0; });
		return zeros;
	}
	bool _allZeros(int abegin = SIZE, int aend = SIZE)
	{
		if (SIZE != abegin)
			++abegin;
		bool zeros = std::all_of(container.begin() + abegin, container.begin() + aend + 1, [](int i) { return i == 0; });
		return zeros;
	}
	BigInt findMultiple(BigInt& b, BigInt& a)
	{
		BigInt multiple(a);
		BigInt index(1);
		while (multiple* index < b || multiple * index == b)
		{
			++index;
		}
		--index;
		return index;
	}
	void eraseZerosFromBack(std::vector<int>& v1)
	{
		std::vector<int> v2 = v1;
		int k = -1;
		for (int i = SIZE; i > 1; --i)
		{
			if (v1[i] == 0)
				k = i;
		}

		if (k != -1)
		{
			int j = k;
			for (int i = SIZE; i > 1; --i)
			{
				if (j >= 0)
				{
					v1[i] = v2[j];
					--j;
				}
				else
					v1[i] = 0;
			}
		}
	}
	void move(std::vector<int>& v1, int n = 0)
	{
		std::vector<int> v2 = v1;
		n = SIZE - n;
		for (int i = SIZE; i > n; --i)
		{
			v1[i] = 0;
		}

		int j = SIZE;
		for (int i = n; i > 0; --i)
		{
			v1[i] = v2[j];
			--j;
		}
	}
	int actualSize(std::vector<int>& v)
	{
		return firstDifferentNr(v);
	}
	void saveMultiple(BigInt& result, BigInt& multiple)
	{

		int i = actualSize(multiple.container);
		if (i == 0)
			i = SIZE - 1;
		move(result.container, SIZE - i);
		result = result + multiple;
	}
	void fillVector(std::vector<int>& v)
	{
		for (int i = v.size() - 1; i < SIZE; ++i)
			v.push_back(0);
	}
	bool isNegative = false;
	void makeNegative()
	{
		isNegative = true;
		container[0] = 1;
	}
	void makePositive()
	{
		isNegative = false;
		container[0] = 0;
	}
public:
	int size()
	{
		return SIZE - actualSize(container);
	}
	int getValue(int pos = 0)
	{
		return container[pos];
	}
	void setBigInt(std::string str)
	{
		
		container.clear();
		std::vector<int> v;

		int j;
		if (str[0] == '-')
			j = 1;
		else
			j = 0;
		for (j; j < str.size(); ++j)
		{
			if (str[j] >= '0' && str[j] <= '9')
				v.push_back(str[j] - 48);
		}
		while ((container.size() + v.size()) - 1 < SIZE)
		{
			container.push_back(0);
		}
		for (std::size_t i = 0; i < v.size(); ++i)
		{
			container.push_back(v[i]);
		}
		if (str[0] == '-')
		{
			container[0] = 1;
			makeNegative();
		}
	}
	BigInt(std::string str)
	{

		container.clear();
		std::vector<int> v;

		int j;
		if (str[0] == '-')
			j = 1;
		else
			j = 0;
		for (j; j < str.size(); ++j)
		{
			if (str[j] >= '0' && str[j] <= '9')
				v.push_back(str[j] - 48);
		}
		while ((container.size() + v.size()) - 1 < SIZE)
		{
			container.push_back(0);
		}
		for (std::size_t i = 0; i < v.size(); ++i)
		{
			container.push_back(v[i]);
		}
		if (str[0] == '-')
		{
			container[0] = 1;
			makeNegative();
		}
	}

	void setBigInt(int number = 0)
	{
		container.clear();
		if (number < 0)
		{
			number *= -1;
			isNegative = true;
		}
		while (container.size() <= SIZE)
		{
			container.push_back(number % 10);
			number = number / 10;
		}
		std::reverse(container.begin(), container.end());
		if (isNegative == true)
			makeNegative();
	}
	void setBigInt(std::vector<int>& v)
	{
		container.clear();
		for (std::size_t i = 0; i <= SIZE; ++i)
		{
			container.push_back(v[i]);
		}
	}
	BigInt(int number = 0)
	{
		if (number < 0)
		{
			number *= -1;
			isNegative = true;
		}
		while (container.size() <= SIZE)
		{
			container.push_back(number % 10);
			number = number / 10;
		}
		std::reverse(container.begin(), container.end());
		if (isNegative == true)
			makeNegative();
	}
	BigInt(std::vector<int>& v)
	{
		container.clear();
		while ((container.size() + v.size()) - 1 < SIZE)
		{
			container.push_back(0);
		}
		for (std::size_t i = 0; i < v.size(); ++i)
		{
			container.push_back(v[i]);
		}
		if (v[0] == 1)
			this->makeNegative();
		else
			this->makePositive();
	}
	BigInt(const BigInt& other)
	{
		for (auto& i : other.container)
		{
			container.push_back(i);
		}
		if (other.isNegative == true)
		{
			this->makeNegative();
		}
	}

	void swap(BigInt& a1, BigInt& b1)
	{
		BigInt aux(a1);
		for (auto i = a1.container.begin(), j = b1.container.begin(); i != a1.container.end() || j != b1.container.end(); ++i, ++j)
		{
			*i = *j;
		}
		for (auto i = b1.container.begin(), j = aux.container.begin(); i != b1.container.end() || j != aux.container.end(); ++i, ++j)
		{
			*i = *j;
		}
	}
	void print()
	{
		if (container[0] == 1)
			std::cout << "-";
		for (std::vector<int>::iterator i = container.begin() + 1; i < container.end(); ++i)
		{
			std::cout << *i;
		}
	}
	BigInt operator *(BigInt b1)
	{
		BigInt result;
		int remember = 0;
		BigInt a, b, c;
		for (std::size_t i = SIZE; i > 1; --i)
		{
			if (firstDifferentNr(b1.container) - 1 == i)
				break;
			a.container.clear();
			for (std::size_t j = SIZE; j > 1; --j)
			{

				if (firstDifferentNr(container) - 1 == j)
					break;
				if ((b1.container[i] * container[j]) + remember >= 10)
				{
					int r = (b1.container[i] * container[j]) + remember;
					a.container.push_back(r % 10);
					remember = r / 10;
				}
				else
				{
					a.container.push_back((b1.container[i] * container[j]) + remember);
					remember = 0;
				}
			}
			fillVector(a.container);
			std::reverse(a.container.begin(), a.container.end());
			move(a.container, SIZE - i);
			b = b + a;
		}
		if ((b1.isNegative == true && this->isNegative == false) || (b1.isNegative == false && this->isNegative == true))
			b.makeNegative();
		return b;
	}
	BigInt operator +(BigInt b1)
	{


		BigInt res;
		BigInt a1(container);
		if (b1.isNegative == true && this->isNegative == false || b1.isNegative == false && this->isNegative == true)
		{
			bool b = false, a = false;
			b = b1.isNegative;
			a = a1.isNegative;
			b1.makePositive();
			a1.makePositive();
			if (b1 > a1)
			{

				res = b1 - a1;
				b1.isNegative = b;
				a1.isNegative = a;
				if (b1.isNegative == true)
					res.makeNegative();
				else
					res.makePositive();
			}
			else
			{
				res = a1 - b1;
				b1.isNegative = b;
				a1.isNegative = a;
				if (this->isNegative == true)
					res.makeNegative();
				else
					res.makePositive();
			}
			return res;
		}
		else
		{

			int remember = 0;
			BigInt result;
			result.container.clear();
			for (std::size_t i = SIZE; i > 1; --i)
			{
				if (b1.container[i] + container[i] + remember < 10)
				{
					result.container.push_back(b1.container[i] + container[i] + remember);
					remember = 0;
				}
				else
				{
					int a = b1.container[i] + container[i] + remember;
					result.container.push_back(a % 10);
					remember = a / 10;
				}
			}
			result.container.push_back(0);
			result.container.push_back(0);

			std::reverse(result.container.begin(), result.container.end());
			if (this->isNegative == true && b1.isNegative == true)
				result.makeNegative();
			return result;
		}
	}
	BigInt operator -(BigInt b1)
	{
		BigInt a1(container);
		BigInt res;
		bool resultOp = true;
		if (b1.isNegative == true)
		{
			resultOp = false;
		}
		else
		{
			resultOp = true;
		}
		if (this->isNegative == true && resultOp == true)
		{
			a1.makePositive();
			b1.makePositive();
			res = a1 + b1;
			b1.makeNegative();
			res.makeNegative();
			return res;
		}
		if (a1.isNegative == true && resultOp == false)
		{
			bool b;
			b = b1.isNegative;
			a1.makePositive();
			b1.makePositive();
			BigInt res;
			res = b1 - a1;
			b1.isNegative = b;
			a1.makeNegative();
			return res;
		}
		if (this->isNegative == false && b1.isNegative == true || b1.isNegative && resultOp == false)
		{
			bool b = false, a = false;
			b = resultOp;
			a = a1.isNegative;
			b1.makePositive();
			a1.makePositive();
			res = a1 + b1;
			b1.isNegative = b;
			a1.isNegative = a;
			if (a1 > b1)
				res.isNegative = a;
			else
				res.isNegative = resultOp;
			return res;
		}
		else
		{

			BigInt result;
			BigInt Container(container);
			result.container.clear();
			if (b1.isNegative == false && a1.isNegative == false && a1 < b1)
			{

				BigInt res;
				res = b1 - a1;
				res.makeNegative();
				return res;
			}
			for (std::size_t i = SIZE; i != 1; --i)
			{
				if (Container.container[i] - b1.container[i] >= 0)
				{
					result.container.push_back(Container.container[i] - b1.container[i]);
				}
				else
				{
					Container.container[i - 1] -= 1;
					int a = 10 + Container.container[i];
					result.container.push_back(a - b1.container[i]);
				}
			}
			result.container.push_back(0);
			result.container.push_back(0);

			std::reverse(result.container.begin(), result.container.end());
			return result;


		}
	}
	bool operator ==(BigInt& b1)
	{
		for (std::size_t i = SIZE; i > 0; --i)
		{
			if (container[i] != b1.container[i])
				return false;
		}
		return true;
	}
	bool operator !=(BigInt& b1)
	{
		for (std::size_t i = SIZE; i > 0; --i)
		{
			if (container[i] != b1.container[i])
				return true;
		}
		return false;
	}
	void operator --()
	{
		BigInt a(container), b(1);
		a = a - b;
		container = a.container;
	}
	void operator ++()
	{
		BigInt a(container), b(1);
		a = a + b;
		container = a.container;
	}
	bool operator <(BigInt& b)
	{
		if (b.isNegative == true && this->isNegative == false || b.isNegative == false && this->isNegative == true)
			return container[0] > b.container[0];
		int x = SIZE;
		for (std::size_t i = SIZE; i > 0; --i)
		{
			if (container[i] != b.container[i])
				x = i;
		}
		if (b.isNegative == true && this->isNegative == true)
			return container[x] > b.container[x];
		return container[x] < b.container[x];

	}
	bool operator >(BigInt& b)
	{
		if (b.isNegative == true && this->isNegative == false || b.isNegative == false && this->isNegative == true)
			return container[0] < b.container[0];
		int x = SIZE;
		for (std::size_t i = SIZE; i > 0; --i)
		{
			if (container[i] != b.container[i])
				x = i;
		}
		if (b.isNegative == true && this->isNegative == true)
			return container[x] < b.container[x];
		return container[x] > b.container[x];
	}
	BigInt operator ^(BigInt power)
	{
		BigInt result(1), one(1), two(2);
		BigInt zero, number(container);
		while (power != zero)
		{
			if (power % two == one)
				result = (result * number);
			number = (number * number);
			power = power / two;
		}
		if (power % two != zero && power.isNegative == true)
			result.makeNegative();
		return result;

	}
	BigInt operator /(BigInt& b1)
	{

		bool finish = false;
		BigInt result;
		int it = firstDifferentNr(container) + 1;
		BigInt a, multiple;
		BigInt Container(container);
		BigInt zero;
		int size = SIZE - actualSize(Container.container);
		bool getDownDigit = false;

		bool bRem = false, aRem = false;
		bRem = b1.isNegative;
		aRem = Container.isNegative;
		b1.makePositive();
		Container.makePositive();
		while (true)
		{
			if (isEmpty(Container.container) == true && a < b1 && size == 0 && finish == true)
				break;
			if (a < b1 && size > 0)
			{
				a.move(a.container, 1);
				if (it <= SIZE)
				{
					if (getDownDigit == true)
						move(result.container, 1);
					a.container[SIZE] = Container.container[it];
					Container.container[it] = 0;


					--size;

					++it;
				}
				else
					break;
				getDownDigit = true;
				finish = false;
			}
			else
			{
				multiple = findMultiple(a, b1);
				saveMultiple(result, multiple);
				multiple = multiple * b1;
				a = a - multiple;

				if (_allZeros(SIZE - size) == true && a == zero)
				{
					move(result.container, size);
					size = 0;
				}
				getDownDigit = false;
				finish = true;
			}
		}
		b1.isNegative = bRem;
		Container.isNegative = aRem;
		if (b1.isNegative == true && Container.isNegative == false || b1.isNegative == false && Container.isNegative == true)
			result.makeNegative();
		else
			result.makePositive();
		return result;
	}

	BigInt operator %(BigInt& b1)
	{
		BigInt result;
		int it = firstDifferentNr(container) + 1;
		BigInt a, multiple;
		BigInt Container(container);
		int size = SIZE - actualSize(Container.container);

		bool bRem = false, aRem = false;
		bRem = b1.isNegative;
		aRem = Container.isNegative;
		b1.makePositive();
		Container.makePositive();

		while (true)
		{
			if (isEmpty(Container) == true && a < b1 && size == 0)
				break;
			if (a < b1)
			{
				a.move(a.container, 1);
				if (it <= SIZE)
				{
					a.container[SIZE] = Container.container[it];
					Container.container[it] = 0;
					--size;
					++it;
				}
				else
					break;
			}
			else
			{
				multiple = findMultiple(a, b1);
				saveMultiple(result, multiple);
				multiple = multiple * b1;
				a = a - multiple;

			}
		}
		b1.isNegative = bRem;
		Container.isNegative = aRem;
		if (Container.isNegative == true)
			a.makeNegative();
		else
			a.makePositive();
		return a;
	}
	friend std::ostream& operator <<(std::ostream& out, const BigInt& b)
	{

		if (b.container[0] == 1)
			out << "-";
		for (int i = 1; i <= SIZE; ++i)
		{
			out << b.container[i];
		}
		return out;

	}

	friend std::istream& operator >>(std::istream& in, BigInt& b)
	{
		b.container.clear();
		std::string str;
		std::vector<int> v;
		in >> str;


		int j;
		if (str[0] == '-')
			j = 1;
		else
			j = 0;
		for (j; j < str.size(); ++j)
		{
			if (str[j] >= '0' && str[j] <= '9')
				v.push_back(str[j] - 48);
		}
		while ((b.container.size() + v.size()) - 1 < SIZE)
		{
			b.container.push_back(0);
		}
		for (std::size_t i = 0; i < v.size(); ++i)
		{
			b.container.push_back(v[i]);
		}
		if (str[0] == '-')
		{
			b.container[0] = 1;
			b.makeNegative();
		}
		return in;
	}


	void randomNumber(int size = SIZE - 2)
	{
		std::vector<int> oddNr{ 1,3,5,7 };
		std::random_device device;
		std::mt19937 generate(device());
		std::uniform_int_distribution<int> distribution(0, 9);
		std::uniform_int_distribution<int> distribution1(1, 9);
		std::uniform_int_distribution<int> distribution2(0, 3);
		for (std::size_t it = SIZE - size + 1; it <= SIZE; ++it)
		{
			container[it] = distribution(generate);
		}
		container[SIZE - size + 1] = distribution1(generate);
		container[SIZE] = oddNr[distribution2(generate)];

	}

	void randomNumbermin(BigInt& b)
	{
		std::vector<int> oddNr{ 1,3,5,7 };
		std::random_device device;
		std::mt19937 generate(device());
		std::uniform_int_distribution<int> distribution(0, 9);
		std::uniform_int_distribution<int> distribution1(1, 9);
		std::uniform_int_distribution<int> distribution2(1, 3);
		for (std::size_t it = actualSize(b.container) + 3; it <= SIZE; ++it)
		{
			container[it] = distribution(generate);
		}
		container[SIZE - actualSize(b.container)] = distribution1(generate);
		container[SIZE] = oddNr[distribution2(generate)];

	}

	BigInt sqrt()
	{
		//we will use binary search algorithml.
		BigInt a, b(container), two(2);
		BigInt Container(container);
		BigInt mid1, one(1), result;
		while (a < b || a == b)
		{
			mid1 = (a + b) / two;
			if (mid1 * mid1 == Container)
				return mid1;
			if (mid1 * mid1 > Container)
			{
				b = mid1 - one;

			}
			else
			{
				a = mid1 + one;
				result = mid1;
			}

		}
		return result;
	}



};
