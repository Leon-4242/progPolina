
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

    LongInt i = -a; 
    LongInt j = c - d; 
    LongInt k = e - f; 
    LongInt l = g - h; 

    std::cout << "a = " << a.view() << std::endl;
    std::cout << "b = " << b.view() << std::endl;
    std::cout << "c = " << c.view() << std::endl;
    std::cout << "d = " << d.view() << std::endl;
    std::cout << "e = " << e.view() << std::endl;
    std::cout << "f = " << f.view() << std::endl;
    std::cout << "g = " << g.view() << std::endl;
    std::cout << "h = " << h.view() << std::endl;

    std::cout << "-a = " << i.view() << std::endl;
    std::cout << "c - d = " << j.view() << std::endl;
    std::cout << "e - f = " << k.view() << std::endl;
    std::cout << "g - h = " << l.view() << std::endl;

    std::cout << a.print(b) << std::endl;
    std::cout << e.print(f) << std::endl; 
    std::cout << c.print(d) << std::endl; 


    return 0;
}