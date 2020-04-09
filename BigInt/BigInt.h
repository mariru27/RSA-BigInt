#pragma once
#include <array>
#include <algorithm>
#include <vector>

#define SIZE 1024

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
	int firstDifferentNr(std::vector<int>& v, int nr = 0)
	{
		for (int i = SIZE; i != 0; --i)
		{
			if (v[i] == nr && v[i - 1] == nr)
				return i;
		}
		return 0;
	}
	bool allZeros()
	{
		bool zeros = std::all_of(container.begin(), container.end(), [](int i) { return i == 0; });
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
	BigInt operator *(BigInt& b1)
	{
		BigInt result;
		int remember = 0;
		BigInt a, b, c;
		for (std::size_t i = SIZE; i > 0; --i)
		{
			a.container.clear();
			for (std::size_t j = SIZE; j > 0; --j)
			{
				//if (firstDifferentNr(container) == j)
				//	break;
				if ((b1.container[i] * container[j]) + remember >= 10)
				{
					int r = (b1.container[i] * container[j]) + remember;
					a.container.push_back(r % 10);
					remember = r / 10;
					////////////////////////////////////////////////////////////////////

				}
				else
				{
					a.container.push_back((b1.container[i] * container[j]) + remember); 
					remember = 0; 
				}
			}
			a.container.push_back(0);
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
	BigInt operator ^(BigInt b1)
	{
		BigInt result(1);
		BigInt a(container);
		BigInt end(0);
		for (; b1 != end; --b1)
		{
			result = result * a;
		}
		return result;
	}
	BigInt operator /(BigInt& b1)
	{
		BigInt result;
		int it = firstDifferentNr(container)+1;
		BigInt a, multiple;
		while (true)
		{
			if (isEmpty(container) == true && a < b1)
				break;
			if (a < b1)
			{
				a.move(a.container, 1);
				if (it <= SIZE)
				{
					a.container[SIZE] = container[it];
					container[it] = 0;
					++it;
				}
				else 
					break;
			}
			else
			{
				multiple = findMultiple(a, b1);
				saveMultiple(result,multiple);
				multiple = multiple * b1;
				a = a - multiple;
				//eraseZerosFromBack(a.container);
			}
		}
		return result;
	}

	BigInt operator %(BigInt& b1)
	{
		BigInt result;
		int it = firstDifferentNr(container) + 1;
		BigInt a, multiple;
		while (true)
		{
			if (isEmpty(container) == true && a < b1)
				break;
			if (a < b1)
			{
				a.move(a.container, 1);
				if (it <= SIZE)
				{
					a.container[SIZE] = container[it];
					container[it] = 0;
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
				//eraseZerosFromBack(a.container);
			}
		}
		return a;
	}
};