
#include <iostream>
#include <cmath>

using namespace std;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <class T>
class Array
{
private:
    T *p;
    int len;

public:
    Array();
    Array( int );
    Array( Array<T> & );
    ~Array();

    void append( T );
    void extend( Array<T> * );
    void extend( T [], int );
    int Len();

    T &operator[]( int );
};

template <class T>
Array<T>::Array()
{
    len = 0;
    p = 0;
}

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
    p = ( len == 0 ? 0 : new T [ len ] );

    for ( int i = 0; i < len; ++i )
    {
        p[ i ] = a.p[ i ];
    }

}

template <class T>
Array<T>::~Array()
{

    if ( len == 0 )
    {
        return;
    }

    delete [] p;
}

template <class T>
void Array<T>::append( T e )
{
    T t[] = { e };

    extend( t, 1 );
}

template <class T>
void Array<T>::extend( T a[], int size )
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

    if ( len != 0 )
    {
        delete [] p;
    }

    p = t;
    len += size;
}

template <class T>
void Array<T>::extend( Array<T> *a )
{
    extend( a->p, a->len );
}

template <class T>
int Array<T>::Len()
{
    return len;
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

// ============================================================================
// ============================================================================
// ============================================================================
// ============================================================================

float str2Num( char *, int * = 0 );
char *num2Str( float, char *, bool = false );

class Polynomial
{
private:
    Array<int> *exp;
    Array<float> *coef;

public:
    Polynomial( char * );
    Polynomial( Polynomial & );

    ~Polynomial();

    char *str();
    float val( float );

    Polynomial operator+( Polynomial );
    Polynomial operator-( Polynomial );
    Polynomial operator*( Polynomial );
    Polynomial operator/( float );
};

Polynomial::Polynomial( char *p )
{
    exp = new Array<int>();
    coef = new Array<float>();

    int t_exp;
    float t_coef;
    int num_len;

    while ( *p != '\0' )
    {
        t_coef = 1;

        if ( ( '0' <= *p && *p <= '9' ) || *p == '.' || ( ( *p == '+' || *p == '-' ) && p[ 1 ] != 'x' ) )
        {
            t_coef = str2Num( p, &num_len );
            p += num_len;
        }
        else
        {

            switch ( *p )
            {

                case '+':
                    ++p;
                    break;

                case '-':
                    t_coef = -1;
                    ++p;
                    break;

                case 'x':
                    break;

            }

        }
        
        if ( *p != 'x' )
        {
            exp->append( 0 );
            coef->append( t_coef );

            continue;
        }

        ++p;

        if ( *p != '^' )
        {
            exp->append( 1 );
            coef->append( t_coef );

            continue;
        }

        ++p;

        t_exp = int( str2Num( p, &num_len ) );
        p += num_len;
        exp->append( t_exp );
        coef->append( t_coef );
    }

}

Polynomial::Polynomial( Polynomial &p )
{
    exp = new Array<int>( *p.exp );
    coef = new Array<float>( *p.coef );
}

Polynomial::~Polynomial()
{
    delete exp;
    delete coef;
}

char *Polynomial::str()
{
    static char ret[ 1024 ];
    char *ret_ptr = ret;

    float coef_t;
    int exp_t;

    int len = coef->Len();

    for ( int i = 0; i < len; ++i )
    {
        coef_t = (*coef)[ i ];
        exp_t = (*exp)[ i ];

        if ( fabs( coef_t ) != 1 || exp_t == 0 )
        {
            ret_ptr = num2Str( coef_t, ret_ptr, i != 0 );
        }
        else
        {

            if ( coef_t < 0 )
            {
                *ret_ptr = '-';
                ++ret_ptr;
            }
            else if ( i != 0 )
            {
                *ret_ptr = '+';
                ++ret_ptr;
            }

        }

        if ( exp_t > 0 )
        {
            *ret_ptr = 'x';
            ++ret_ptr;

            if ( exp_t > 1 )
            {
                *ret_ptr = '^';
                ++ret_ptr;
                ret_ptr = num2Str( exp_t, ret_ptr );
            }

        }

    }

    ret_ptr = '\0';

    return ret;
}

float Polynomial::val( float x )
{
    float ret = 0;
    int len = coef->Len();

    for ( int i = 0; i < len; ++i )
    {
        ret += (*coef)[ i ] * pow( x, (*exp)[ i ] );
    }

    return ret;
}

Polynomial Polynomial::operator+( Polynomial p )
{
    Array< int > *res_exp = new Array< int >();
    Array< float > *res_coef = new Array< float >();

    int l = 0;
    int r = 0;
    int llen = coef->Len();
    int rlen = p.coef->Len();

    while ( l < llen || r < rlen )
    {
        float lcoef;
        float rcoef;
        int lexp;
        int rexp;

        if ( r == rlen )
        {
            lcoef = (*coef)[ l ];
            lexp = (*exp)[ l ];

            if ( lcoef != 0 )
            {
                res_exp->append( lexp );
                res_coef->append( lcoef );
            }

            ++l;

            continue;
        }

        if ( l == llen )
        {
            rcoef = (*p.coef)[ r ];
            rexp = (*p.exp)[ r ];

            if ( rcoef != 0 )
            {
                res_exp->append( rexp );
                res_coef->append( rcoef );
            }

            ++r;

            continue;
        }

        lcoef = (*coef)[ l ];
        rcoef = (*p.coef)[ r ];
        lexp = (*exp)[ l ];
        rexp = (*p.exp)[ r ];

        int cmp = lexp - rexp;

        if ( cmp > 0 )
        {
            res_exp->append( lexp );
            res_coef->append( lcoef );
            ++l;
        }
        else if ( cmp < 0 )
        {
            res_exp->append( rexp );
            res_coef->append( rcoef );
            ++r;
        }
        else
        {
            float coef_sum = lcoef + rcoef;

            if ( coef_sum != 0 )
            {
                res_exp->append( lexp );
                res_coef->append( coef_sum );
            }

            ++l;
            ++r;
        }

    }

    if ( res_exp->Len() == 0 )
    {
        res_exp->append( 0 );
        res_coef->append( 0 );
    }

    Polynomial res( "0" );

    delete res.exp;
    delete res.coef;

    res.exp = res_exp;
    res.coef = res_coef;

    return res;
}

Polynomial Polynomial::operator-( Polynomial p )
{
    int len = p.coef->Len();

    for ( int i = 0; i < len; ++i )
    {
        (*p.coef)[ i ] *= -1;
    }

    return *this + p;
}

Polynomial Polynomial::operator*( Polynomial p )
{
    Polynomial res( "0" );

    int llen = coef->Len();

    for ( int l = 0; l < llen; ++l )
    {
        Polynomial pp( p );
        int rlen = pp.coef->Len();

        for ( int r = 0; r < rlen; ++r )
        {
            (*pp.coef)[ r ] *= (*coef)[ l ];
            (*pp.exp)[ r ] += (*exp)[ l ];
        }

        Polynomial temp( res + pp );

        delete res.exp;
        delete res.coef;

        res.exp = new Array< int >( *temp.exp );
        res.coef = new Array< float >( *temp.coef );
    }

    return res;
}

Polynomial Polynomial::operator/( float c )
{
    Polynomial res( *this );
    int len = res.coef->Len();

    for ( int i = 0; i < len; ++i )
    {
        (*res.coef)[ i ] /= c;
    }

    return res;
}

int main()
{
    Polynomial p1( "x^2" );
    Polynomial p2( "x+1" );
    Polynomial p3( "x-1" );
    Polynomial p4( "5" );

    Polynomial pr( p4 * p3 * ( p1 + p2 ) );

    cout << pr.str() << "\n"
         << pr.val( 1 ) << endl;

    system( "pause" );

    return 0;
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

char *num2Str( float num, char *str, bool show_sign )
{
    char sign = '+';

    if ( num < 0 )
    {
        sign = '-';
        num *= -1;
    }

    float num_i = floor( num );
    float num_f = num - num_i;

    char tmp[ 1024 ];
    int head = 0;

    while ( num_i >= 1 )
    {
        tmp[ head ] = '0' + int( fmod( num_i, 10 ) );
        num_i /= 10;
        ++head;
    }

    if ( sign == '-' || show_sign )
    {
        *str = sign;
        ++str;
    }

    if ( head == 0 )
    {
        *str = '0';
        ++str;
    }

    head--;

    while ( head >= 0 )
    {
        *str = tmp[ head ];
        ++str;
        head--;
    }

    *str = '.';
    ++str;

    for ( int i = 1; i <= 6; ++i )
    {
        num_f *= 10;
        *str = '0' + int( num_f );
        ++str;
        num_f -= floor( num_f );
    }

    *str = '\0';
    --str;

    while ( *str == '0' )
    {
        *str = '\0';
        --str;
    }

    if ( *str == '.' )
    {
        *str = '\0';
        --str;
    }

    ++str;

    return str;
}
