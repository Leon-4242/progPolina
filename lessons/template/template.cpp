template<typename T, typename D>
class Vector
{
	T * data;
	size_t n;
	D id;

	public:
	Vector(size_t N):
		n(N)
	{
		data = new T[n];
		id = D::gen();
	}

	~Vector()
	{
		delete[] data;
	}

	T operator[] (size_t i) const
	{
		return data[i];
	}

	T & operator[] (size_t i)
	{
		return data[i];
	}
}

class Id
{
	int k;
	Id (int K):
		k(K)
	{}

	public:
	static Id gen() const
	{
		return std::random(555)*173%15 +8;
	}
}
/*
class student
{
	static std::string uni = "MSU";
	std::string name;

	public:
	student(std::string Name):
		name(Name)
	{
	}

	static std::string Uni()
	{
		uni = "HSE";
		return uni;
	}
}

int main()
{
	std::cout << student::Uni();
}
*/
/*
class function
{
	int counter;

	public:
	function():
		counter(0)
	{}

	int operator()(int x)
	{
		++counter;
		std::cout << counter;
		return x+counter;
	}
}

int func(int x)
{
	static int counter = 0;
	++counter;
	std::cout << counter;
	return x;
}
*/

int main()
{
	Vector<double, Id> v(5);
	v[0] = 2;
	v[3] = v[0]-2;

	Vector<std::string, Id> u(7);
	u[0] = "Hello";
	u[1] = "World";
	u[2] = "!";

	func(2);
	func(2);

	function f;
	f(2);
	f(2);

	std::pair<int, double> p;
	p.first = 2;
	p.second = 1.54;

	return 0;
}
