#include <iostream>
using namespace std;

template <class T>
class PriorityQueue 
{
private:
    T *input;
	int *priority;
    int len;
	int counter;

public:
    PriorityQueue ( int );
    PriorityQueue ( PriorityQueue <T> & );
    ~PriorityQueue ();

	
    void insert( T , int );
	int SearchMax();
	T pull ();
	T peek ();
	int count ();
};

template <class T>
PriorityQueue <T>::PriorityQueue ( int size )
{
	counter=0;
    len = size;
    input = new T [ len ];
    priority = new int [ len ];
}

template <class T>
PriorityQueue <T>::PriorityQueue ( PriorityQueue <T> &a)
{
	len = a.len;
	counter = a.counter;
    input = new T [ len ];
	priority = new int [ len ];

    for ( int i = 0; i < len; ++i )
    {
        input[ i ] = a.input[ i ];
		priority[ i ] = a.priority[ i ];
    }
}

template <class T>
PriorityQueue <T>::~PriorityQueue ()
{
    delete [] input;
	delete [] priority;
}



template <class T>
void PriorityQueue <T>::insert( T a , int b )
{
	input[counter]=a;
	priority[counter]=b;
	counter++;
	
}

template <class T>
int PriorityQueue <T>::SearchMax()
{
	int index_max=0;
	if (counter != 0)
	{
	T max = priority[0];
	for (int i = 0; i < counter; i++)
	{
		if (priority[i] > max)
		{
			max = priority[i];
			index_max = i;
		}
	}
	return(index_max);
	}
	else
	{
		cout << "ERROR";
	}
	return(0);
	
}


template <class T>
T PriorityQueue <T>::peek()
{
	T max_priority_peek;

	if (counter != 0)
	{
		int index_max = SearchMax();
		max_priority_peek = input[index_max];
	}
	else
	{
		cout << "ERROR"<<endl;
	}

	return(max_priority_peek);
}


template <class T>
T PriorityQueue <T>::pull()
{
	T max_priority_pull;

	if (counter != 0)
	{
		int index_max = SearchMax();
		max_priority_pull = input[index_max];
		if (index_max != counter)
		{
			for (int i = index_max; i < counter-1; i++)//as araye biroon nazane
			{
				priority [ i ] = priority [ i + 1 ];
				input [ i ] = input [ i + 1 ];
			}
		counter--;
		}

		else
		{
			cout << "ERROR"<<endl;
		}
	
	}
	else
	{
		cout << "ERROR"<<endl;
	}

	return(max_priority_pull);
}


template <class T>
int PriorityQueue <T>::count()
{
	return(counter);
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
