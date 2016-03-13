
#include <iostream>

using namespace std;

template < class T >
class LinkedList
{
    public:
        int priority;
        T data;
        LinkedList< T > *next;

        LinkedList( LinkedList< T > & );
        LinkedList();
        ~LinkedList();
};

template < class T >
LinkedList< T >::LinkedList( LinkedList< T > &ll )
{
    data = ll.data;
    priority = ll.priority;

    if ( ll.next == 0 )
    {
        return;
    }

    next = new LinkedList< T >( *ll.next );
}

template < class T >
LinkedList< T >::LinkedList()
{
    next = 0;
}

template < class T >
LinkedList< T >::~LinkedList()
{}

template < class T >
class PriorityQueue
{
    private:
        LinkedList< T > *front;
        int len;

    public:
        PriorityQueue( PriorityQueue< T > & );
        PriorityQueue();
        ~PriorityQueue();

        void insert( T, int );
        T pull();
        T peek();
        int count();
};

template < class T >
PriorityQueue< T >::PriorityQueue( PriorityQueue< T > &pq )
{
    front = 0;
    len = pq.len;

    if ( len == 0 )
    {
        return;
    }

    front = new LinkedList< T >( *pq.front );
}

template <class T>
PriorityQueue< T >::PriorityQueue()
{
    front = 0;
    len = 0;
}

template <class T>
PriorityQueue< T >::~PriorityQueue()
{

    while ( len != 0 )
    {
        pull();
    }

}

template <class T>
void PriorityQueue< T >::insert( T d, int p )
{
    ++len;

    LinkedList< T > *in = new LinkedList< T > ();

    in->data = d;
    in->priority = p;
    in->next = 0;

    if ( front == 0 )
    {
        front = in;

        return;
    }

    if ( p > front->priority )
    {
        in->next = front;
        front = in;

        return;
    }

    LinkedList< T > *it = front;

    while ( it->next != 0 && it->next->priority >= p )
    {
        it = it->next;
    }

    in->next = it->next;
    it->next = in;
}

template <class T>
T PriorityQueue< T >::pull()
{

    if ( len == 0 )
    {
        cerr << "Queue is Empty." <<  endl;

        return T();
    }

    len--;

    LinkedList< T > *retll = front;

    front = front->next;
    retll->next = 0;

    T ret = retll->data;

    delete retll;

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

    ret = front->data;

    return ret;
}

template <class T>
int PriorityQueue< T >::count()
{
    return len;
}

int main()
{
    PriorityQueue< int > pq;

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
