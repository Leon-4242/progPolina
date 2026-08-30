
#include "LongInt.h"

int main()
{
    LongInt a(12);
    LongInt b(18);
    LongInt c(-4);
    LongInt d(-27);
    LongInt e(-3);
    LongInt f(-3);
    LongInt g(9);
    LongInt h(-19);


    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "e = " << e << std::endl;
    std::cout << "f = " << f << std::endl;
    std::cout << "g = " << g << std::endl;
    std::cout << "h = " << h << std::endl;

	std::cout << "c - d = " << c - d << std::endl;
    std::cout << "e - f = " << e - f << std::endl;
    std::cout << "g - h = " << g - h << std::endl;

    return 0;
}
