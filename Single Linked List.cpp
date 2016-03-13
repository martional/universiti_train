#include <iostream>
using namespace std;

template <class T>
class ForwardList 
{
private:
    T *input;
	int *map;
    int len;
	int first_empty_index;
	int first_full_index;
	
public:
    ForwardList ( int );
    ForwardList ( ForwardList <T> & );
    ~ForwardList ();

    int insert( T , int );
	int erase(int);
	int count ();
	int previous_node_index (int a);

	T &operator[]( int );
};

template <class T>
ForwardList <T>::ForwardList ( int size )
{
    len = size;
	first_empty_index = 0;
	first_full_index = -1;

    input = new T [ len ];
    map = new int [ len ];

	for (int i = 0; i < len; i++)
	{
		map [i] = i+1;
	}
	map[len-1]=-1;
}

template <class T>
ForwardList <T>::ForwardList ( ForwardList <T> &a)
{
	len = a.len;
	first_empty_index = a.first_empty_index;
	first_full_index = a.first_full_index;

    input = new T [ len ];
	map = new int [ len ];+

    for ( int i = 0; i < len; ++i )
    {
        input[ i ] = a.input[ i ];
		map[ i ] = a.map[ i ];
    }

}

template <class T>
ForwardList <T>::~ForwardList ()
{
    delete [] input;
	delete [] map;
}

template <class T>
int ForwardList <T>::insert( T a , int index )
{
	int counter = count();
	int next_empty;
	int inserted_index;

	if (counter >= index && index >= 0 && first_empty_index != -1)
	{	 
		input[first_empty_index] = a;
		next_empty = map[first_empty_index];

		if (index > 0)
		{
			map[first_empty_index] = map[previous_node_index (index)];
			map[previous_node_index (index)] = first_empty_index;
		}
		else
		{
			map[first_empty_index] = first_full_index;
			first_full_index = first_empty_index;
		}
		inserted_index= first_empty_index;
		first_empty_index = next_empty;

		return (inserted_index);
	}
	else
	{
		cerr << "ERROR";
	}

	return(0);
}

template <class T>
int ForwardList <T>::erase(int index)
{
	int counter = count();
	int erased_index;

	if (counter >= index && index >= 0 && first_full_index != -1)
	{
		if (index > 0)
		{
			erased_index = map[previous_node_index (index)];
			map[previous_node_index (index)] = map[erased_index];
		}
		else
		{
			first_full_index = map[first_full_index];
		}
		map[erased_index] = first_empty_index;
		first_empty_index = erased_index;

		return (erased_index);
	}
	else
	{
		cerr << "ERROR";
	}

	return(0);
}

template <class T>
int ForwardList <T>::count()
{
	int counter = 0;
	int next = first_full_index;

	while (next != -1)
	{
		next = map[next];
		counter ++;
	}

	return(counter);
}


template <class T>
int ForwardList <T>::previous_node_index(int a)
{
	int counter = 0;
	int index = a-1; //we need previous node index
	int next = first_full_index;

	while (counter<index)
	{
		next = map[next];
		counter ++;
	}

	return(next);
	
}


template <class T>
T &ForwardList<T>::operator[]( int index )
{
	int counter = count();
	int target_index;

	if (counter > index && index >= 0)
	{
		if (index > 0)
		{
			target_index = map[previous_node_index (index)];
		}
		else
		{
			target_index = first_full_index;
		}
		
		return input[target_index];
	}
	else
	{
		cerr << "ERROR";
	}

	return input[0];
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
