#pragma once
#include <array>
#include <vector>

#define SIZE 1024

class BigInt
{
	std::vector<int> container;
public:
	BigInt(int number = 0)
	{
		while (container.size() <= SIZE)
		{
			container.push_back(number % 10);
			number = number / 10;
		}
		std::reverse(container.begin(), container.end());
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
		std::reverse(result.container.begin(), result.container.end());
		return result;
	}
	


};