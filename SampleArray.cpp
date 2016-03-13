
#include <iostream>

using namespace std;

template <class T>
class Array{
private:
    T *p;
    int len;

public:
    Array(int m);
    Array(T arr[], int n);
    Array(Array<T> &x);

    ~Array();

    T get(int x);
    T operator[](int d);

    void set(int an, T variabel);
};

template <class T>
Array<T>::Array(int m)
{    
    p = new T[len = m];
}

template <class T>
Array<T>::Array(Array<T> &x)
{
    len = x.len;
    p = new T[ len ];

    for (int i = 0; i < len; i++)
    {
        p[i] = x.p[i];
    }

}

template <class T>
Array<T>::Array(T arr[], int n)
{
    p = new T[len = n];

    for(int i = 0; i < n; i++)
    {
        p[i] = arr[i];
    }
}

template <class T>
T Array<T>::get(int x)
{
    if(x < len)
        return p[x];
    else
    {
        cout << "errore" << endl;
        return 0;
    }
}

template <class T>
T Array <T>::operator[](int d)
{
    return get(d);
}

template <class T>
void Array<T>::set(int an, T variabel)
{
    if (an < len)
    {
        p[an] = variabel;
    }
    else
        cout << "error" << endl;
}

template <class T>
Array<T>::~Array()
{
    delete [] p;
}

int main()
{
    int a[5] = { 6, 8, 4, 0, 2 };

    Array <int> x(a,5);
    Array <int> b(5);

    x.set(0,3);
    //x[0] = 3;

    for(int i=0;i<5;i++){
        cout << x[i] << ' ';
    }

    return 0;
}

