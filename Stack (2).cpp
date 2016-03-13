
#include <iostream>
#include <cstdlib>

using namespace std;

template <class T>
class StackNode
{
public:
    T data;
    StackNode< T > *back;

public:
    StackNode();
    ~StackNode();
};

template <class T>
StackNode< T >::StackNode()
{
    back = 0;
}

template <class T>
StackNode< T >::~StackNode()
{ }

template <class T>
class Stack
{
private:
    StackNode< T > *head;
    int len;

public:
    Stack();
    Stack( const Stack< T > & );
    ~Stack();

    void push( T d );
    T pop();
    T top();
    int size();
};

template <class T>
Stack< T >::Stack()
{
    head = 0;
    len = 0;
}

template <class T>
Stack< T >::Stack( const Stack< T > &s )
{
    Stack< T > ts;
    StackNode< T > *shead = s.head;

    while ( shead != 0 )
    {
        ts.push( shead->data );
        shead = shead->back;
    }

    head = 0;
    len = 0;
    shead = ts.head;

    while ( shead != 0 )
    {
        push( shead->data );
        shead = shead->back;
    }

}

template <class T>
Stack< T >::~Stack()
{

    while ( size() != 0 )
    {
        pop();
    }

}

template <class T>
void Stack< T >::push( T d )
{
    StackNode< T > *tnode = new StackNode< T >();

    tnode->data = T( d );
    tnode->back = head;
    head = tnode;
    ++len;
}

template <class T>
T Stack< T >::pop()
{

    if ( head == 0 )
    {
        cerr << "ERROR" << endl;

        return T();
    }

    T ret( head->data );
    StackNode< T > *tnode = head;

    head = head->back;

    delete tnode;

    len--;

    return ret;
}

template <class T>
T Stack< T >::top()
{

    if ( head == 0 )
    {
        cerr << "ERROR" << endl;

        return T();
    }

    T ret( head->data );

    return ret;
}

template <class T>
int Stack< T >::size()
{
    return len;
}

float str2Num( char *, int * = 0 );
float postfix( char * );

int main()
{
    Stack< int > s;

    s.push( 1 );
    s.push( 2 );
    s.push( 3 );

    cout << s.top() << " " << s.size() << endl;

    Stack< int > c( s );

    cout << s.pop() << " ";
    cout << s.pop() << " ";
    cout << s.pop() << "\n";
    cout << c.top() << " " << c.size() << endl;

    cout << postfix( "1.5 2.0 * 2 + 2 /" ) << endl;

    system( "pause" );

    return 0;
}

float postfix( char *str )
{
    Stack<float> s;

    while ( *str != '\0' )
    {

        if ( '0' <= *str && *str <= '9' )
        {
            int num_len;
            float num = str2Num( str, &num_len );

            str += ( num_len + 1 );
            s.push( num );
        }
        else
        {
            float num2 = s.pop();
            float num1 = s.pop();

            switch ( *str )
            {

                case '+':
                    s.push( num1 + num2 );
                    break;

                case '-':
                    s.push( num1 - num2 );
                    break;

                case '*':
                    s.push( num1 * num2 );
                    break;

                case '/':
                    s.push( num1 / num2 );
                    break;

                case '^':
                    s.push( pow( num1, num2 ) );
                    break;

            }

            str += 2;
        }

    }

    float res = s.pop();

    return res;
}

float str2Num( char *str, int *len_ptr )
{
    float ret = 0;
    int sign = 1;
    int len = 0;

    switch ( *str )
    {

        case '+':
            ++str;
            ++len;
            break;

        case '-':
            sign = -1;
            ++str;
            ++len;
            break;

    }

    while ( '0' <= *str && *str <= '9' )
    {
        ret *= 10;
        ret += *str - '0';
        ++str;
        ++len;
    }

    if ( *str != '.' )
    {

        if ( len_ptr != 0 )
        {
            *len_ptr = len;
        }

        return ret * sign;
    }

    float pow = 10;

    ++str;
    ++len;

    while ( '0' <= *str && *str <= '9' )
    {
        ret += ( *str - '0' ) / pow;
        ++str;
        pow *= 10;
        ++len;
    }

    if ( len_ptr != 0 )
    {
        *len_ptr = len;
    }

    return ret * sign;
}
