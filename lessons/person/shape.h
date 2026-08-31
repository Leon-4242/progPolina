class Shape
{
	virtual double S () const = 0;
};

class Circle: public Shape
{
	double S () const override
	{
		return R*R*PI;
	}
}

class Square: public Shape
{
	double a;
	public:
	Square(double a):
		a(a)
	{}

	double S () const override
	{
		return a*a;
	}
}

double func(Shape * obj)
{
	return obj->S()+2;
}

int main()
{
	Shape * ptr = nullptr;
	bool a;
	std::cin >> a;
	if (a)
	{
		ptr = new Circle(5);
	}
	else
	{
		ptr = new Square(5);
	}

	std::cout << func(ptr);

	delete ptr;

	return 0;
}
