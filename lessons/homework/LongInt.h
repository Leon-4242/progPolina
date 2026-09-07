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

    LongInt(int* array, int N, bool neg);
    bool abs_less_abs(const LongInt & a) const;
    LongInt add_abs(const LongInt & a) const;
    LongInt sub_abs(const LongInt & a) const;
    LongInt mul_by_10() const;
    LongInt mul_by_digit(int digit) const;
    LongInt mul_abs(const LongInt & a) const;

public:
    LongInt(int k = 0);
    LongInt(const LongInt& obj);
    ~LongInt();

    LongInt & operator= (const LongInt & obj);

    bool operator== (const LongInt & a) const;
    bool operator< (const LongInt & a) const;
    bool operator> (const LongInt & a) const;
    bool operator<= (const LongInt & a) const;
    bool operator>= (const LongInt & a) const;
    
    LongInt operator+ (const LongInt & a) const;
    LongInt & operator+= (const LongInt & a);
    LongInt operator- (const LongInt & a) const;
    LongInt & operator-= (const LongInt & a);
    LongInt operator- () const;
    LongInt operator* (const LongInt & a) const;
    LongInt & operator*= (const LongInt & a);
    

    std::string view() const;
    //friend std::ostream & operator<< (std::ostream & out, const LongInt & a);
};

std::ostream & operator<< (std::ostream & out, const LongInt & a);

#endif // LONGINTCLASS_H
