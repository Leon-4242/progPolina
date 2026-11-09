void ff(void) //ПЛОХО
{
	static std::size_t number = 0;

	for (std::size_t i{}; i < number; ++i)
	{
		std::cout << "hello\n";
	}
	++number;
} 

class Hello-er //ХОРОШО
{
	std::size_t number{};
	public:
	void operator() (void)
	{
		for (std::size_t i{}; i < number; ++i)
		{
			std::cout << "hello\n";
		}
		++number;
	}
}

int main()
{
//	Hello-er f;
//	f();

	ff();
	ff();

	int n = 0;

	auto f = [&](void){
		for (std::size_t i{}; i < number; ++i) 
		{
			std::cout << "hello\n";
		}
		++n;
	};
	f();

	std::function<void(void)> = ff;
}
