#pragma once
#include<bitset>

class BigInt
{
	std::bitset<10> bitsContainer;

	void complement()
	{
		for (auto it =  1; it <= bitsContainer.size(); ++it)
		{
			~(bitsContainer[it]);
		}
	}

public:

	BigInt()
	{
		bitsContainer.reset();
	}
	void setBit(int pozition, int value = 1)
	{
		bitsContainer[pozition] = value;
	}
	void print()
	{
		int sum = 0;
		int pozition = 1;
		for (auto it = 1; it < bitsContainer.size(); ++it)
		{
			sum += bitsContainer[it]*pozition;
			pozition = pozition << 1;
		}
		std::cout << sum ;
	}

	BigInt& operator -(BigInt other)
	{
		BigInt bitsResult;
		BigInt one;

		//one represent number one on bits
		one.setBit(1);
		other.complement();

		//add one
		bitsResult = other + one;
		BigInt a = bitsResult.bitsContainer + bitsContainer;
		return bitsResult;
	}

	BigInt& operator +(BigInt& other)
	{
		BigInt bitsResult;
		int remember = 0;
		for (auto it = 1; it < this->bitsContainer.size(); ++it)
		{
			int result = this->bitsContainer[it] + other.bitsContainer[it];
			result += remember;
			bitsResult.bitsContainer[it] = result;
			switch (result)
			{
			case 1:bitsResult.bitsContainer[it] = result;
				remember = 0;
				continue;
			case 2:
				bitsResult.bitsContainer[it] = 0;
				remember = 1;
				continue;
			case 3:
				remember = 1;
				continue;
			default:
				break;
			}
		}
		return bitsResult;
	}
};