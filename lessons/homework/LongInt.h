#ifndef LONGINTCLASS_H
#define LONGINTCLASS_H

#include <iostream>
#include <string>

class LongInt 
{
private:
    int* data; 
    int n; 
    bool number_is_negative; 

    LongInt(const int* array, int N, bool neg);
    bool abs_less_abs(const LongInt& a) const;
    LongInt add_abs(const LongInt& a) const;
    LongInt sub_abs(const LongInt& a) const;

public:
    LongInt(int k = 0);
    LongInt(const LongInt& obj);
    ~LongInt();

    LongInt& operator=(const LongInt& obj);

    bool operator==(const LongInt& a) const;
    bool operator<(const LongInt& a) const;
    bool operator>(const LongInt& a) const;

    LongInt operator-() const;
    LongInt operator+(const LongInt& a) const;
    LongInt operator-(const LongInt& a) const;

    std::string view() const;
    std::string print(const LongInt& a) const;
};

#endif // LONGINTCLASS_H