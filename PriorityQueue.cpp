
#include <iostream>

using namespace std;

template <class T>
class PriorityQueue
{
    private:
        int size;
        int front;
        int back;
        int len;
        int *priority;
        T *data;

        int norm( int );

    public:
        PriorityQueue( PriorityQueue< T > & );
        PriorityQueue( int );
        ~PriorityQueue();

        void insert( T, int );
        T pull();
        T peek();
        int count();
};

template <class T>
int PriorityQueue< T >::norm( int i )
{
    i %= size;

    if ( i < 0 )
    {
        i += size;
    }

    return i;
}

template <class T>
PriorityQueue< T >::PriorityQueue( PriorityQueue< T > &pq )
{
    size = pq.size;
    front = pq.front;
    back = pq.back;
    len = pq.len;
    priority = new int [ size ];
    data = new T [ size ];

    for ( int i = 0; i < size; ++i )
    {
        priority[ i ] = pq.priority[ i ];
        data[ i ] = pq.data[ i ];
    }

}

template <class T>
PriorityQueue< T >::PriorityQueue( int s )
{
    size = s;
    front = 0;
    back = 0;
    len = 0;
    priority = new int [ size ];
    data = new T [ size ];
}

template <class T>
PriorityQueue< T >::~PriorityQueue()
{
    delete [] priority;
    delete [] data;
}

template <class T>
void PriorityQueue< T >::insert( T d, int p )
{

    if ( len == size )
    {
        cerr << "Queue is Full." << endl;

        return;
    }

    ++len;

    int i = back;
    int ip = norm( i - 1 );

    ++back;

    while ( i != front && p > priority[ ip ] )
    {
        priority[ i ] = priority[ ip ];
        data[ i ] = data[ ip ];
        i = ip;
        ip = norm( ip - 1 );
    }

    priority[ i ] = p;
    data[ i ] = d;
}

template <class T>
T PriorityQueue< T >::pull()
{

    if ( len == 0 )
    {
        cerr << "Queue is Empty." <<  endl;

        return data[ front ];
    }

    len--;

    T ret = data[ front ];

    front = norm( front + 1 );

    return ret;
}

template <class T>
T PriorityQueue< T >::peek()
{
    T ret;

    if ( len == 0 )
    {
        cerr << "Queue is Empty." <<  endl;

        return ret;
    }

    ret = data[ front ];

    return ret;
}

template <class T>
int PriorityQueue< T >::count()
{
    return len;
}

int main()
{
    PriorityQueue< int > pq( 7 );

    pq.insert( 7, 3 );
    pq.insert( 6, 4 );
    pq.insert( 5, 5 );
    pq.insert( 4, 3 );
    pq.insert( 3, 1 );
    pq.insert( 2, 2 );
    pq.insert( 1, 4 );

    while ( pq.count() != 0 )
    {
        cout << pq.pull() << ' ';
    }

    return 0;
}
