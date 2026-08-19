#include <iostream>
#include <string>

/*
double * minus1 (int * arr, int n)
{

	int diff = -1;

	for (int i = n-1; i >= 0; --i)
	{
		if (diff == 0)
		{
			break;
		}

		arr[i] += diff;

		if (arr[i] == -1)
		{
			arr[i] = 9;
			diff = -1;
		}
		else
		{
			diff = 0;
		}
	}

}

[1, 2, 3]
*/

class LongInt 
{
	int * data;
	int n;

	LongInt (int * array, int N):
		data(array),
		n(N)
	{
	}

	public:
	LongInt(int k = 0)
	{
		int buff = k;

		n = 1;
		while (buff /= 10)
		{
			++n;
		}

		data = new int[n];

		buff = k;

		for (int i = n-1; i >= 0; --i)
		{
			data[i] = buff%10;
			buff /= 10;
		}
	}

	LongInt(const LongInt & obj)
	{
		n = obj.n;

		data = new int[n];

		for (int i = 0; i < n; ++i)
		{
			data[i] = obj.data[i];
		}
	}

	LongInt & operator= (const LongInt & obj)
	{
		delete[] data;

		n = obj.n;

		data = new int[n];

		for (int i = 0; i < n; ++i)
		{
			data[i] = obj.data[i];
		}

		return *this;
	}

	~LongInt()
	{
		delete[] data;
	}

	bool operator== (const LongInt & a) const
	{
		if (n != a.n)
		{
			return false;
		}

		for (int i = 0; i < n; ++i)
		{
			if (data[i] != a.data[i])
			{
				return false;
			}
		}

		return true;
	}

	LongInt operator+ (const LongInt & a) const
	{
		int N = (n > a.n ? n : a.n) + 1;
		int * array = new int[N];

		for (int i = 0; i < N; ++i)
		{
			array[i] = 0;
		}

		int diff = 0;

		int i = n-1, j = a.n-1, k = N-1;

		while (i >= 0 && j >= 0)
		{
			array[k] = data[i] + a.data[j] + diff;

			if (array[k] >= 10)
			{
				diff = 1;
				array[k] %= 10;
			}
			else
			{
				diff = 0;
			}

			--i; 
			--j;
			--k;
		}

		while (i >= 0)
		{
			if (diff == 0)
			{
				break;
			}

			array[k] = data[i] + diff;

			if (array[k] >= 10)
			{
				diff = 1;
				array[k] %= 10;
			}
			else
			{
				diff = 0;
			}

			--i;
			--k;
		}

		while (j >= 0)
		{
			if (diff == 0)
			{
				break;
			}

			array[k] = a.data[j] + diff;

			if (array[k] >= 10)
			{
				diff = 1;
				array[k] %= 10;
			}
			else
			{
				diff = 0;
			}

			--j;
			--k;
		}

		if (diff == 1)
		{
			array[0] = diff;
		}
		else
		{
			int *buff = new int[N-1];

			for (int i = 0; i < N-1; ++i)
			{
				buff[i] = array[i+1];
			}

			delete[] array;

			array = buff;

			buff = nullptr;

			--N;
		}

		return LongInt(array, N);
	}

	LongInt operator- (...) const
	{
		if (a < b)
			return -(b-a);
	}

	std::string view () const
	{
		std::string res = "";
		for (int i = 0; i < n; ++i)
		{
			res += std::to_string(data[i]);
		}

		return res;
	}
};

int main()
{
	LongInt a(123);

	LongInt b(1);

	LongInt c(999);
	
	LongInt d = b+c;

	std::cout << 
		a.view() << "\n" <<
		b.view() << "\n" <<
		c.view() << "\n" <<
		d.view() << std::endl;
	return 0;
}
