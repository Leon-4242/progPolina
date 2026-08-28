#include "LongInt.h"


    LongInt::LongInt (const int * array, int N, bool neg):
        n(N), 
        number_is_negative(neg)
    {
        // Была ошибка : 1 - 999 = -8
        data = new int[n];
        for (int i = 0; i < n; ++i)
        {
            data[i] = array[i];
        }
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

    bool LongInt::operator== (const LongInt & a) const
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
        // иначе проблемы с удалением памяти
        LongInt result(array + m, N - m, false);
        delete[] array; 
        return result;
       
        

    }

    LongInt LongInt::operator+ (const LongInt & a) const
    {
        //a+b
        if (number_is_negative == a.number_is_negative)
        {
            LongInt res = add_abs(a);     
            res.number_is_negative = number_is_negative; 
            return res;
        }
        //1 + (-2) и -2 + 3
        if (abs_less_abs(a)) 
        {
            LongInt res = a.sub_abs(*this);  //2 - 1 и 3 - 2
            res.number_is_negative = a.number_is_negative; //-1 и 1
            return res;
        }
        // -2 + 1 и 3 + (-2)
        else 
        {
            LongInt res = sub_abs(a);     // 2 - 1 и 3 - 2
            res.number_is_negative = number_is_negative;  // -1 и 1
            return res;
        }
    }

    LongInt LongInt::operator- (const LongInt & a) const
    {
        // -a - b = -(a+b) и a -(-b) = a+b
        if (number_is_negative != a.number_is_negative)
        {
            LongInt res = add_abs(a);                    
            res.number_is_negative = number_is_negative;  
            return res;
        }

        if (abs_less_abs(a)) 
        {
            //1-2 и -1-(-2) 
            LongInt res = a.sub_abs(*this); // 2 - 1 и 2 -1
            res.number_is_negative = !number_is_negative;// -1 и 1
            
            //a - a
            if (res.data[0] == 0)
            {
                res.number_is_negative = false;
            }

            return res;
        }
        else 
        {
            //2 -1 и -2 - (-1)
            LongInt res = sub_abs(a);   // 2 -1 и 2 -1                   
            res.number_is_negative = number_is_negative;    // 1 и -1
            
            if (res.data[0] == 0)
            {
                res.number_is_negative = false;
            }
            
            return res;
        }
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
   
    std::string LongInt::print(const LongInt & a) const
    {
        if (*this == a)
        {
            return view() + " == " + a.view();
        }
        else if (*this < a)
        {
            return view() + " < " + a.view();
        }
        else
        {
            return view() + " > " + a.view();
        }
    }