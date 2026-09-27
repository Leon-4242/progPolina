#include <iostream>

class  Data
{
	int * v;
	int k;
	public:
	Data(int kk)
	{
		k = kk;
		v = new int[k];
		for (int i = 0; i < k; ++i)
		{
			v[i] = i;
		}
	}

	Data (const Data & obj)
	{
		k = obj.k;
		v = new int[k];
		for (int i = 0; i < k; ++i)
		{
			v[i] = obj.v[i];
		}

		std::cout << "copy obj: new memory" << std::endl;
	}

	~Data(u)
	{
		if (v)
		{
			delete[] v;
		}
		k = 0;

		std::cout << "del obj" << std::endl;
	}

	Data(Data && obj)
	{
		v = obj.v;
		obj.v = nullptr;
		k = obj.k;
		obj.k = 0;

		std::cout << "copy obj: old memory" << std::endl;
	}

	void print() const
	{
		std::cout << k << std::endl;
	}
};


int main(void)
{
	Data p(8);
	p.print();

	Data a(p);
	a.print();

	Data b = p;
	b.print();

	Data c{p};
	c.print();

	p.print();

	Data aa(std::move(p));
	aa.print();
	p.print();

//	Data aa(Data(8)); // Data aa(8)
//	Data bb = Data(8);
//	Data cc{Data(8)};

	return 0;
}


class Data
{
	Data();
	
	Data(const Data &);
	Data& operator= (const Data &);

	Data(Data &&);
	Data& operator= (Data &&);
	

}
