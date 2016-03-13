
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================

int f[ 256 ];
int g[ 256 ];

void init();
int tokenLen( char *, char * = 0 );
char *Infix2Postfix1( char * );
float Infix2Postfix2( char * );
float str2Num( char *, int * = 0 );

int main()
{
    init();

    char exp[] = "((2.5+3)*0.50-2.25)^(0.0-1.0)";

    cout << Infix2Postfix1( exp ) << "\n"
         << Infix2Postfix2( exp ) << endl;

    return 0;
}

/*
    \   ||     |     |     |     |     |     |     |     |    
     \ g|| n=5 | +=1 | -=1 | *=3 | /=3 | ^=5 | (=5 | )=0 | $=0
    f \ ||     |     |     |     |     |     |     |     |    
   =====||=====|=====|=====|=====|=====|=====|=====|=====|=====
    n=6 ||     | .>  | .>  | .>  | .>  | .>  |     | .>  | .> 
   -----||-----|-----|-----|-----|-----|-----|-----|-----|-----
    +=2 || <.  | .>  | .>  | <.  | <.  | <.  | <.  | .>  | .> 
   -----||-----|-----|-----|-----|-----|-----|-----|-----|-----
    -=2 || <.  | .>  | .>  | <.  | <.  | <.  | <.  | .>  | .> 
   -----||-----|-----|-----|-----|-----|-----|-----|-----|-----
    *=4 || <.  | .>  | .>  | .>  | .>  | <.  | <.  | .>  | .> 
   -----||-----|-----|-----|-----|-----|-----|-----|-----|-----
    /=4 || <.  | .>  | .>  | .>  | .>  | <.  | <.  | .>  | .> 
   -----||-----|-----|-----|-----|-----|-----|-----|-----|-----
    ^=4 || <.  | .>  | .>  | .>  | .>  | <.  | <.  | .>  | .> 
   -----||-----|-----|-----|-----|-----|-----|-----|-----|-----
    (=0 || <.  | <.  | <.  | <.  | <.  | <.  | <.  |     |    
   -----||-----|-----|-----|-----|-----|-----|-----|-----|-----
    )   ||     |     |     |     |     |     |     |     |    
   -----||-----|-----|-----|-----|-----|-----|-----|-----|-----
    $=0 || <.  | <.  | <.  | <.  | <.  | <.  | <.  |     |    
        ||     |     |     |     |     |     |     |     |    

                            {f(n)}
                               |
                               |
       {g(n), g(()}         {g(^)}
              \               /
               \             /
              {f(*), f(/), f(^)}
                       |
                       |
                  {g(*), g(/)}
                       |
                       |
                  {f(+), f(-)}
                   /      \
                  /        \
                 /          \
        {g(+), g(-)}      {g()), g($)}
             |
             |
        {f((), f($)}


          || n | + | - | * | / | ^ | ( | ) | $
       ===||===|===|===|===|===|===|===|===|===
        f || 6 | 2 | 2 | 4 | 4 | 4 | 0 |   | 0
       ===||===|===|===|===|===|===|===|===|===
        g || 5 | 1 | 1 | 3 | 3 | 5 | 5 | 0 | 0
       
*/

void init()
{
    f[ '.' ] = f[ '0' ] = f[ '1' ] = f[ '2' ] = f[ '3' ] = f[ '4' ] = f[ '5' ] = f[ '6' ] = f[ '7' ] = f[ '8' ] = f[ '9' ] = 6;
    f[ '+' ] = f[ '-' ] = 2;
    f[ '*' ] = f[ '/' ] = f[ '^' ] = 4;
    f[ '(' ] = f[ '$' ] = f[ '\0' ] = 0;

    g[ '.' ] = g[ '0' ] = g[ '1' ] = g[ '2' ] = g[ '3' ] = g[ '4' ] = g[ '5' ] = g[ '6' ] = g[ '7' ] = g[ '8' ] = g[ '9' ] 
        = g[ '^' ] = g[ '(' ] = 5;
    g[ '+' ] = g[ '-' ] = 1;
    g[ '*' ] = g[ '/' ] = 3;
    g[ ')' ] = g[ '$' ] = f[ '\0' ] = 0;
}

int tokenLen( char *src, char *dest )
{
    int len = 0;
    char tmp[ 1024 ];
    char *head = tmp;

    if ( *src == '+' || *src == '-' || *src == '*' || *src == '/' || *src == '^' || *src == '(' )
    {
        *head = *src;
        ++src;
        ++head;
        ++len;
    }
    else
    {

        while ( ( '0' <= *src && *src <= '9' ) || *src == '.' )
        {
            *head = *src;
            ++src;
            ++head;
            ++len;
        }

    }

    *head = '\0';

    if ( dest != 0 )
    {
        head = tmp;

        while ( *head != '\0' )
        {
            *dest = *head;
            ++dest;
            ++head;
        }

        *dest = '\0';
    }

    return len;
}

char *Infix2Postfix1( char *ip )
{
    Stack< char* > s;
    static char res[ 1024 ];
    char *head = res;
    char empty[] = { '$' };

    s.push( empty );

    while ( 1 )
    {
        char a = *s.top();
        char b = *ip;

        if ( a == *empty && b == '\0' )
        {
            break;
        }

        if ( a == '(' && b == ')' )
        {
            s.pop();
            ++ip;

            continue;
        }

        if ( f[ a ] < g[ b ] || f[ a ] == g[ b ] )
        {
            s.push( ip );
            ip += tokenLen( ip );
        }
        else
        {
            head += tokenLen( s.pop(), head );
            *head = ' ';
            ++head;
        }

    }

    *head = '\0';

    return res;
}

float Infix2Postfix2( char *ip )
{
    Stack< char* > s;
    Stack< float > res;
    char empty[] = { '$' };

    s.push( empty );

    while ( 1 )
    {
        char a = *s.top();
        char b = *ip;

        if ( a == *empty && b == '\0' )
        {
            break;
        }

        if ( a == '(' && b == ')' )
        {
            s.pop();
            ++ip;

            continue;
        }

        if ( f[ a ] < g[ b ] || f[ a ] == g[ b ] )
        {
            s.push( ip );
            ip += tokenLen( ip );
        }
        else
        {
            char *handle = s.pop();

            if ( ( '0' <= *handle && *handle <= '9' ) || *handle == '.' )
            {
                res.push( str2Num( handle ) );
            }
            else
            {
                float num2 = res.pop();
                float num1 = res.pop();

                switch ( *handle )
                {

                    case '+':
                        res.push( num1 + num2 );
                        break;

                    case '-':
                        res.push( num1 - num2 );
                        break;

                    case '*':
                        res.push( num1 * num2 );
                        break;

                    case '/':
                        res.push( num1 / num2 );
                        break;

                    case '^':
                        res.push( pow( num1, num2 ) );
                        break;

                }

            }

        }

    }

    return res.pop();
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
