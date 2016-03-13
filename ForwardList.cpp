
#include <iostream>

using namespace std;

template<class T>
struct Cell
{
    T data;
    int next;
};

template <class T>
class ForwardList
{
    private:
        Cell< T > mem[ 5 ];
        int head;
        int free;
        int size;
        int len;

    public:
        ForwardList( ForwardList< T > & );
        ForwardList( int );
        ~ForwardList();

        int insert( T, int );
        int erase( int );
        T &operator[]( int );
        int count();
};

template <class T>
ForwardList< T >::ForwardList( ForwardList< T > &fl )
{
    head = fl.head;
    free = fl.free;
    size = fl.size;
    len = fl.len;
    //mem = new Cell< T > [ size ];

    for ( int i = 0; i < size; ++i )
    {
        mem[ i ] = fl.mem[ i ];
    }

}

template <class T>
ForwardList< T >::ForwardList( int s )
{
    head = -1;
    free = 0;
    size = s;
    len = 0;
    //mem = new Cell< T > [ size ];

    for ( int i = 0; i < size; ++i )
    {
        mem[ i ].next = i + 1;
    }

    mem[ size - 1 ].next = -1;
}

template <class T>
ForwardList< T >::~ForwardList()
{
    //delete [] mem;
}

template <class T>
int ForwardList< T >::insert( T d, int i )
{

    if ( free == -1 )
    {
        cerr << "List is Full." << endl;

        return -1;
    }

    if ( i < 0 || i > len )
    {
        cerr << "index out of range" << endl;

        return -1;
    }

    ++len;

    int next_free;

    if ( i == 0 )
    {
        next_free = mem[ free ].next;
        mem[ free ].data = d;
        mem[ free ].next = head;
        head = free;
        free = next_free;;

        return 0;
    }

    int index = 0;
    int back = head;

    for ( ; index < i - 1; ++index )
    {
        back = mem[ back ].next;
    }

    next_free = mem[ free ].next;
    mem[ free ].data = d;
    mem[ free ].next = mem[ back ].next;
    mem[ back ].next = free;
    free = next_free;

    return index + 1;
}

template <class T>
int ForwardList< T >::erase( int i )
{

    if ( i < 0 || i >= len )
    {
        cerr << "index out of range" << endl;

        return -1;
    }

    len--;

    int next;

    if ( i == 0 )
    {
        next = mem[ head ].next;
        mem[ head ].next = free;
        free = head;
        head = next;

        return 0;
    }

    int index = 0;
    int back = head;

    for ( ; index < i - 1; ++index )
    {
        back = mem[ back ].next;
    }

    next = mem[ back ].next;
    mem[ back ].next = mem[ next ].next;
    mem[ next ].next = free;
    free = next;

    return index + 1;
}

template <class T>
T &ForwardList< T >::operator[]( int i )
{

    if ( i < 0 || i >= len )
    {
        static int m1 = -1;
        cerr << "index out of range" << endl;

        return m1;
    }

    int ret = head;

    for ( int index = 0; index < i; ++index )
    {
        ret = mem[ ret ].next;
    }

    return mem[ ret ].data;
}

template <class T>
int ForwardList< T >::count()
{
    return len;
}

int main()
{
    ForwardList< int > fl( 5 );

    fl.insert( 1, 0 );
    fl.insert( 5, 1 );
    fl.insert( 2, 1 );
    fl.insert( 3, 2 );
    fl.insert( 4, 3 );

    for ( int i = 0; i < fl.count(); ++i )
    {
        cout << fl[ i ] << ' ';
        fl[ i ] = 2 * i;
    }

    cout << '\n';

    fl.erase( 1 );
    fl.erase( 1 );
    fl.erase( 1 );

    for ( int i = 0; i < fl.count(); ++i )
    {
        cout << fl[ i ] << ' ';
    }

    return 0;
}
