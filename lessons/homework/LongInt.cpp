#include "LongInt.h"


    LongInt::LongInt (int * array, int N, bool neg):
        data(array),
        n(N), 
        number_is_negative(neg)
{
    
}
    LongInt::LongInt(int k)
    {
        if (k < 0) 
        {
            number_is_negative = true;  
            k = -k;              
        }
        else 
        {
            number_is_negative = false; 
        }

        int buff = k; 

        n = 1;              

        while (buff /= 10)
        {
            ++n; 
        }

        data = new int[n]; 

        buff = k;          

        for (int i = n - 1; i >= 0; --i)
        {
            data[i] = buff % 10; 
            buff /= 10;          
        }
    }

    LongInt::LongInt(const LongInt & obj)
    {
        number_is_negative = obj.number_is_negative; 

        n = obj.n;                     

        data = new int[n];             

        for (int i = 0; i < n; ++i)
        {
            data[i] = obj.data[i];
        }
    }

    LongInt & LongInt::operator= (const LongInt & obj)
    {

        delete[] data; 

        number_is_negative = obj.number_is_negative; 

        n = obj.n;                    

        data = new int[n];             

        for (int i = 0; i < n; ++i)
        {
            data[i] = obj.data[i];
        }

        return *this; 
    }

   LongInt::~LongInt()
    {
        delete[] data; 
    }

    bool LongInt::operator==(const LongInt & a) const
    {

        if (number_is_negative != a.number_is_negative)
        {
            return false;
        }

        if (n != a.n)
        {
            return false;
        }

        for (int i = 0; i < n; ++i)
        {
            if (data[i] != a.data[i])
                return false; 
        }

        return true; 
    }

     bool LongInt::abs_less_abs(const LongInt & a) const
    {
        if (n < a.n) 
        {
             return true;  
        }
            
        if (n > a.n) 
        {
            return false;  
        }

        for (int i = 0; i < n; ++i)
        {
            if (data[i] < a.data[i]) 
            {
                return true;  
            }
                
            if (data[i] > a.data[i]) 
            {
                return false; 
            }
                
        }
        return false; 
    }

    bool LongInt::operator< (const LongInt & a) const
    {
        if (*this == a) 
            return false;

        if (number_is_negative && !a.number_is_negative) 
            return true;  

        if (!number_is_negative && a.number_is_negative) 
            return false; 

        if (!number_is_negative && !a.number_is_negative)
        {
            return abs_less_abs(a);
        }

        return a.abs_less_abs(*this); 
    }

    bool LongInt::operator> (const LongInt & a) const
    {
        return a < *this; 
    }

    bool LongInt::operator<= (const LongInt & a) const
    {
        return !(a < *this); 
    }

    bool LongInt::operator>= (const LongInt & a) const
    {
        return !(a > *this); 
    }


 	LongInt LongInt::operator+ (const LongInt & a) const
 	{
 		if (*this < 0)
 		{
 			if (a < 0)
 		    {
			    return -((-(*this)) + (-a));
		    }
		else
		{
			return a - (-(*this));
		}
 	    }
	    else
		{
			if (a < 0)
			{
			return (*this) - (- a);
		    }
            else
            {
              return add_abs(a);
            }
	    }
 
			
	}

    LongInt & LongInt::operator+= (const LongInt & a) 
    {
        *this = *this + a;
        return *this;
    }

	LongInt LongInt::operator- (const LongInt & a) const
{
    if (*this < 0)
    {
        if (a < 0)
        {
            if (abs_less_abs(a))
            {
                return (-a) - (-(*this));
            }
            else
            {
                return -((-(*this)) - (-a));
            }
        }
        else
        {
            return -((-(*this)) + a);
        }
    }
    else
    {
        if (a < 0)
        {
            return (*this) + (-a);
        }
        else
        {
            if (abs_less_abs(a))
            {
                return -(a.sub_abs(*this));
            }
            else
            {
                return sub_abs(a);
            }
        }
    }
}

    LongInt & LongInt::operator-= (const LongInt & a) 
    {
        *this = *this - a;
        return *this;
    }

    LongInt LongInt::operator- () const
    {
        LongInt new_sgn = *this; 

        if (new_sgn.data[0] == 0)
        {
            new_sgn.number_is_negative = false;
        }
        else
        {
            new_sgn.number_is_negative = !new_sgn.number_is_negative; 
        }
        return new_sgn; 
    }

    LongInt LongInt::add_abs (const LongInt & a) const
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

		return LongInt(array, N, false);
	}


    LongInt LongInt::sub_abs(const LongInt & a) const
    {
        int N = n;                 
        int * array = new int[N];  

        int diff = 0; 

        int i = n - 1;  
        int j = a.n - 1; 
        int k = N - 1;

        while (i >= 0 && j >= 0)
        {
            array[k] = data[i] - a.data[j] - diff; 

            if (array[k] < 0)
            {
                array[k] += 10;  
                diff = 1; 
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
            array[k] = data[i] - diff;

            if (array[k] < 0)
            {
                array[k] += 10;  
                diff = 1; 
            }
            else
            {
                diff = 0; 
            }

            --i;
            --k;
        }

        int m = 0;
        while (m < N - 1 && array[m] == 0)
        {
            ++m; 
        }
    

		if (m != 0) 
        {
			int *buff = new int[N-m];

			for (int i = 0; i < N-1; ++i)
			{
				buff[i] = array[i+m];
			}

			delete[] array;

			array = buff;

			N -= m;	
		}

		return LongInt(array, N, false);
    }


    std::string LongInt::view() const
    {
        std::string res = ""; 

        if (number_is_negative && !(data[0] == 0))
        {
            res += "-";
        }

        for (int i = 0; i < n; ++i)
        {
            res += std::to_string(data[i]);
        }

        return res; 
    }
   
    std::ostream & operator<< (std::ostream & out, const LongInt & a)  
	{
		return out << a.view();
	}


