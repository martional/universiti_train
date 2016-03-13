
#include <iostream>

using namespace std;

template <class T>
class Array
{
private:
    T *p;
    int len;

public:
    Array( int );
    Array( Array<T> & );
    ~Array();

    void append( T );
    void extend( Array<T> * );
    void extend( T [], int );

    T &operator[]( int );
};

template <class T>
Array<T>::Array( int size )
{
    len = size;
    p = new T [ len ];
}

template <class T>
Array<T>::Array( Array<T> &a )
{
    len = a.len;
    p = new T [ len ];

    for ( int i = 0; i < len; ++i )
    {
        p[ i ] = a.p[ i ];
    }

}

template <class T>
Array<T>::~Array()
{
    delete [] p;
}

template <class T>
void Array<T>::append( T e )
{
    T t[] = { e };

    extend( t, 1 );
}

template <class T>
void Array<T>::extend(T a[], int size)
{
    T *t = new T [ len + size ];
    int i, x = 0;

    for ( i = 0; i < len; ++i )
    {
        t[ x ] = p[ i ];
        ++x;
    }

    for ( i = 0; i < size; ++i )
    {
        t[ x ] = a[ i ];
        ++x;
    }

    delete [] p;
    p = t;
    len += size;
}

template <class T>
void Array<T>::extend( Array<T> *a )
{
    extend( a->p, a->len );
}

template <class T>
T &Array<T>::operator[]( int i )
{

    if ( i < -len || i >= len )
    {
        cerr << "ERROR" << endl;

        return p[ 0 ];
    }

    return p[ ( i + len ) % len ];
}

int main()
{

    Array<int> a( 3 );

    a[ 3 ] = 0;     // error
    a[ -4 ] = 0;    // error

    a[ -1 ] = 3;
    a[ -2 ] = 2;
    a[ -3 ] = 1;

    Array<int> b( a );
    int c[] = { 4, 5, 6 };

    b.extend( c, 3 );

    Array<int> d( 1 );

    d[ 0 ] = 0;
    d.extend( &b );
    d.append( 7 );
    d.append( 8 );
    d.append( 9 );

    for ( int i = 0; i < 10; ++i )
    {
        cout << d[ i ] << " ";
    }

    cout << endl;
}
