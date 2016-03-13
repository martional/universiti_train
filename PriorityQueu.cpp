#include <iostream>
using namespace std;

template <class T>
class PriorityQueue 
{

	struct node
	{
		T data;
		int priority;
		node *next;
	};

private:
	int counter;
	node * head;
	node * last;
	node * node_A;
	
public:
    PriorityQueue ();
    PriorityQueue ( PriorityQueue <T> & );
    ~PriorityQueue ();

    void insert( T , int );
	T pull ();
	T peek ();
	int count ();	
};

template <class T>
PriorityQueue <T>::PriorityQueue ()
{
	counter = 0;
	head = nullptr;
	last = nullptr;
}

template <class T>
PriorityQueue <T>::PriorityQueue ( PriorityQueue <T> &a)
{
	counter = a.counter;
	node * temp_copy;

	node_A = new node;
	node_A -> data = a.head -> data;
	node_A -> priority = a.head -> priority;
	node_A -> next = a.head -> next;
	head = node_A;
	temp_copy = head;

	for (int i = 1; i < counter; i++) // i=1 because head copy Before loop
	{
		node_A = new node;
		node_A -> data = temp_copy -> next -> data;
		node_A -> priority = temp_copy -> next -> priority;
		node_A -> next = temp_copy -> next -> next
		temp_copy = temp_copy -> next;
	}
	last =node_A;
}

template <class T>
PriorityQueue <T>::~PriorityQueue ()
{
	delete [] node_A;
	node *temp_delete;

	if (counter != 0)
	{
		for (int i = 0; i < counter; i++)
		{
			temp_delete = head -> next;
			delete head;
			head = temp_delete;
		}	
	}
}

template <class T>
void PriorityQueue <T>::insert( T a , int b )
{
	node * node_A;
	node_A = new node;

	if (head != nullptr)
	{
		node_A ->data = a;
		node_A ->priority = b;
		node_A ->next = nullptr;
		last -> next = node_A;
		last = node_A;
		counter++;
	}
	else
	{
		node_A -> data = a;
		node_A -> priority = b;
		node_A ->next = nullptr;
		head = node_A;
		last = node_A;
		counter++;
	}
}


template <class T>
T PriorityQueue <T>::peek()
{
	struct node *max;
	struct node *temp_peek;
	T max_priority_peek;

	if (counter != 0)
	{
		max = head;
		temp_peek = head;
		while(temp_peek != nullptr)
		{
			if (max -> priority < temp_peek -> priority)
			{
				max = temp_peek;
			}
			temp_peek = temp_peek -> next;
		}

		max_priority_peek = max -> data;
		return(max_priority_peek);
	}
	else
	{
		cerr << "ERROR";
	}	
}


template <class T>
T PriorityQueue <T>::pull()
{
	struct node *max;
	struct node *max_previous; 
	struct node *temp1; 
	struct node *temp2;
	T max_priority_pull;
	int temp3;

	temp2 =nullptr;
	max_previous = nullptr;
	temp3 = 0;

	if (counter != 0)
	{
		max = head;
		temp1 = head;
		for (int i = 0; i < counter; i++)
		{
			if (max -> priority < temp1 -> priority)
			{
				max = temp1;
				max_previous = temp2;
				temp3 = i;
			}
			temp2 = temp1;
			temp1 = temp1 -> next;
		}
		if (temp3 == 0)  // max in last of list
		{
			max_priority_pull = max -> data;
			head = max -> next;
			delete max;
			counter--;
			return(max_priority_pull);
		}
		else if (temp3 == counter) // max in head of list
		{
			max_priority_pull = max -> data;
			max_previous -> next = max -> next;
			delete max;
			last = max_previous;
			counter--;
			return(max_priority_pull);
		}
		else 
		{
			max_priority_pull = max -> data;
			max_previous -> next = max -> next;
			delete max;
			counter--;
			return(max_priority_pull);
		}
	}
	else
	{
		cerr << "ERROR"<<endl;
	}
}

template <class T>
int PriorityQueue <T>::count()
{
	return(counter);
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
    
