#pragma once
#include <string>
#include <algorithm>
#include <vector>

#define SIZE 310

class BigInt
{
	std::vector<int> container;
	bool isEmpty(std::vector<int>& v)
	{
		for (auto& i : v)
		{
			if (i != 0)
				return false;
		}
		return true;
	}
	bool isEmpty(BigInt& Container)
	{
		for (auto& i : Container.container)
		{
			if (i != 0)
				return false;
		}
		return true;
	}
	int firstDifferentNr(std::vector<int>& v, int nr = 0)
	{
		for (int i = 0; i <= SIZE; ++i)
		{
			if (v[i] != nr && v[i - 1] == nr)
				return i-1;
		}
		return 0;
	}
	bool allZeros()
	{
		bool zeros = std::all_of(container.begin(), container.end(), [](int i) { return i == 0; });
		return zeros;
	}
	bool _allZeros(int abegin = SIZE, int aend = SIZE)
	{
		if(SIZE != abegin)
			++abegin;
		bool zeros = std::all_of(container.begin()+ abegin, container.begin()+aend+1, [](int i) { return i == 0; });
		return zeros;
	}
	BigInt findMultiple(BigInt& b, BigInt& a)
	{
		BigInt multiple(a);
		BigInt index(1);
		while (multiple * index < b || multiple*index == b)
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
		for (int i = SIZE; i > 0; --i)
		{
			if (v1[i] == 0)
				k = i;
		}

		if (k != -1)
		{
			int j = k;
			for (int i = SIZE; i > 0; --i)
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
	void saveMultiple(BigInt& result,BigInt& multiple)
	{
		
		int i = actualSize(multiple.container);
		move(result.container,SIZE - i);
		result = result + multiple;
	}
	void fillVector(std::vector<int>& v)
	{
		for (int i = v.size() - 1; i < SIZE; ++i)
			v.push_back(0);
	}
public:
	void setBigInt(int number = 0)
	{
		while (container.size() <= SIZE)
		{
			container.push_back(number % 10);
			number = number / 10;
		}
		std::reverse(container.begin(), container.end());
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
		while (container.size() <= SIZE)
		{
			container.push_back(number % 10);
			number = number / 10;
		}
		std::reverse(container.begin(), container.end());
	}
	BigInt(std::vector<int>& v)
	{
		container.clear();
		for (std::size_t i = 0; i <= SIZE; ++i)
		{
			container.push_back(v[i]);
		}
	}
	BigInt(BigInt& other)
	{
		for (auto& i : other.container)
		{
			container.push_back(i);
		}
	}
	void print()
	{
		for (auto& i : container) 
		{
			std::cout << i;
		}
	}
	BigInt operator *(BigInt b1)
	{
		BigInt result;
		int remember = 0;
		BigInt a, b, c;
		for (std::size_t i = SIZE; i > 0; --i)
		{
			if (firstDifferentNr(b1.container) - 1 == i)
				break;
			a.container.clear();
			for (std::size_t j = SIZE; j > 0; --j)
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
		return b;
	}
	BigInt operator +(BigInt& b1)
	{
		int remember = 0;
		BigInt result;
		result.container.clear();
		for (std::size_t i = SIZE; i > 0; --i)
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
		std::reverse(result.container.begin(), result.container.end());
		return result;
	}
	BigInt operator -(BigInt& b1)
	{
		BigInt result;
		result.container.clear();
		for (std::size_t i = SIZE; i != 0; --i)
		{
			if (container[i] - b1.container[i] >= 0)
			{
				result.container.push_back(container[i] - b1.container[i]);
			}
			else
			{
				container[i - 1]  -= 1;
				int a = 10 + container[i];
				result.container.push_back(a - b1.container[i]);
			}
		}
		result.container.push_back(0);
		std::reverse(result.container.begin(), result.container.end());
		return result;
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
		int x = SIZE;
		for (std::size_t i = SIZE; i > 0; --i)
		{
			if (container[i] != b.container[i])
				x = i;
		}
		return container[x] < b.container[x];
			
	}
	bool operator >(BigInt& b)
	{
		int x = SIZE;
		for (std::size_t i = SIZE; i > 0; --i)
		{
			if (container[i] != b.container[i])
				x = i;
		}
		return container[x] > b.container[x];
	}
	BigInt operator ^(BigInt& power)
	{
		BigInt result(1), one(1), two(2);
		BigInt zero, number(container);
		while (power != zero)
		{
			if (power % two == one)
				result = (result * number);
			number = (number * number) ;
			power = power / two;
		}
		return result;

	}
	BigInt operator /(BigInt& b1)
	{
		BigInt result;
		int it = firstDifferentNr(container)+1;
		BigInt a, multiple;
		BigInt Container(container);
		BigInt zero;
		int size = SIZE - actualSize(Container.container);
		bool getDownDigit = false;
		while (true)
		{
			if (isEmpty(Container.container) == true && a < b1 && size==0)
				break;
			//if (size == 0)
			//	break;
			if (a < b1 && size > 0)
			{
				a.move(a.container, 1);
				if (it <= SIZE)
				{
					if (getDownDigit == true)
						move(result.container, 1);
					a.container[SIZE] = Container.container[it];
					Container.container[it] = 0;
					//if (a != zero)
					//{

						--size;
					//}
					//if (size > 0 && a == zero)
					//{
					//		move(result.container, size);
					//		size = 0;
					//}
					++it;
				}
				else 
					break;
				getDownDigit = true;
			}
			else
			{
				multiple = findMultiple(a, b1);
				saveMultiple(result,multiple);
				multiple = multiple * b1;
				a = a - multiple;
				
				//eraseZerosFromBack(a.container);
				//if (size > 0 && a == zero)
					//if (_allZeros(SIZE - size - 2) == true)
					//{
					//	move(result.container, size);
					//	size = 0;
					//}
				if (_allZeros(SIZE - size) == true &&  a==zero)
				{
					move(result.container, size);
					size = 0;
				}
				getDownDigit = false;
			}
		}
		return result;
	}

	BigInt operator %(BigInt& b1)
	{
		BigInt result;
		int it = firstDifferentNr(container) + 1;
		BigInt a, multiple;
		BigInt Container(container);
		int size = SIZE - actualSize(Container.container);

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
		return a;
	}
	friend std::ostream& operator <<(std::ostream& out, const BigInt& b)
	{
		for (auto& i : b.container)
		{
			out << i;
		}
		return out;
		
	}

	friend std::istream& operator >>(std::istream& in, BigInt& b)
	{
		b.container.clear();
		std::string str;
		in >> str;

		for (auto& i : str)
		{
			if (i >= '0' && i <= '9')
				b.container.push_back(i - 48);
		}
		for (int i = b.container.size() - 1; i < SIZE; ++i)
			b.container.push_back(0);
		std::reverse(b.container.begin(), b.container.end());
		return in;
	}
	
};