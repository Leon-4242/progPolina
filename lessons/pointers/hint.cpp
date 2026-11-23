template <typename T>
class unique_ptr
{
private:
    T *data;
public:
    unique_ptr(T *ptr) : data(ptr) {}
    ~unique_ptr() { delete data; }
    T & operator * ()
    {
        return *data;
    }
    T * operator -> ()
    {
        return data;
    }
};

unique_ptr<A> ptr(new A());
ptr->doSomething();
