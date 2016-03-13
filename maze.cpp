
#include <iostream>
#include <cstdlib>

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

struct pos
{
    int x;
    int y;
};

pos *makePos( int, int );
pos *next( pos *, char **, int );
void solve( char **, int );

int main()
{
    char maze[ 22 ][ 22 ] = {
        "#####################",
        "      #   #         #",
        "# ### # # ######### #",
        "# #   # # #       # #",
        "# # ##### # ##### # #",
        "# # #   # # #   #   #",
        "# # ### # # # # #####",
        "# # #   # # # # #   #",
        "# # # ### # ### # # #",
        "# # # #   # #   # # #",
        "# # # # ### # ##### #",
        "# #   #   # # # #   #",
        "# ####### # # # # # #",
        "# #       #       # #",
        "# # ### ##### # ### #",
        "#   # #   #   # # # #",
        "##### ### # ### # # #",
        "# #       #   # # # #",
        "# # # ######### # # #",
        "#   #           #    ",
        "#####################",
        ""
    };

    char *map[ 21 ];

    for ( int i = 0; i < 21; ++i )
    {
        maze[ i ][ 21 ] = '\n';
        map[ i ] = maze[ i ];
    }

    cout << *maze << "\n";
    solve( map, 21 );
    cout << *maze << endl;

    return 0;
}

void solve( char **maze, int size )
{
    Stack< pos* > path;

    path.push( makePos( 1, 0 ) );

    while ( 1 )
    {
        pos *cur = path.top();
        pos *ext = next( cur, maze, size );

        if ( ext == 0 )
        {
            delete cur;
            path.pop();
        }
        else
        {
            path.push( ext );

            if ( ext->x == size - 2 && ext->y == size - 1 )
            {
                break;
            }

            maze[ ext->x ][ ext->y ] = '1';
        }

    }

    for ( int i = 0; i < size; ++i )
    {

        for ( int j = 0; j < size; ++j )
        {

            if( maze[ i ][ j ] == '1' )
            {
                maze[ i ][ j ] = ' ';
            }

        }

    }

    while ( path.size() != 0 )
    {
        pos *p = path.pop();

        maze[ p->x ][ p->y ] = '.';
        delete p;
    }

}

pos *makePos( int x, int y )
{
    pos *ret = new pos();

    ret->x = x;
    ret->y = y;

    return ret;
}

pos *next( pos *cur, char **maze, int size )
{
    pos *neighbor[] = { makePos( cur->x, cur->y + 1 ),
                        makePos( cur->x - 1, cur->y ),
                        makePos( cur->x, cur->y - 1 ),
                        makePos( cur->x + 1, cur->y ) };
    pos *res = 0;
    int i;

    for ( i = 0; i < 4; ++i )
    {
        int x = neighbor[ i ]->x;
        int y = neighbor[ i ]->y;

        if ( 0 <= x && x < size && 0 <= y && y < size )
        {

            if ( maze[ x ][ y ] == ' ' )
            {
                res = neighbor[ i ];

                break;
            }

        }

    }

    if ( res != 0 )
    {
        res = makePos( res->x, res->y );
    }

    delete neighbor[ 0 ];
    delete neighbor[ 1 ];
    delete neighbor[ 2 ];
    delete neighbor[ 3 ];

    return res;
}
