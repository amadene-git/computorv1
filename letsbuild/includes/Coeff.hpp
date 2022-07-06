#ifndef COEFF_HPP
# define COEFF_HPP

# include <map>
# include <utility>

# include "Number.hpp"

using namespace std;


class Coeff 
{
    private:

    map<Number, Number> *_sum;


    public:

    Coeff();
    Coeff(Coeff const &src);
    Coeff(Number nbr, Number x);

    ~Coeff();

    Coeff &operator=(Coeff const &rhs);

    map<Number, Number> &getSum() const;

    void            setSum(map<Number, Number> sum);


    //Number operator overload
    Coeff   operator+(Number const &rhs);
    Coeff   operator-(Number const &rhs);
    Coeff   operator*(Number const &rhs);
    Coeff   operator/(Number const &rhs);
    
    Coeff   &operator+=(Number const &rhs);
    Coeff   &operator-=(Number const &rhs);
    Coeff   &operator*=(Number const &rhs);
    Coeff   &operator/=(Number const &rhs);


    //Coeff operator overload
    Coeff   operator+(Coeff const &rhs);
    Coeff   operator-(Coeff const &rhs);
    Coeff   operator*(Coeff const &rhs);
    Coeff   operator/(Coeff const &rhs);

    operator bool();
    
    //methods
    Coeff   exponent(Coeff const &rhs);

};

ostream &operator<<(ostream &out, Coeff const &rhs);
bool	operator==(const Number& lhs, const Number& rhs);
bool	operator!=(const Number& lhs, const Number& rhs);
bool	operator<(const Number& lhs, const Number& rhs);
bool	operator<=(const Number& lhs, const Number& rhs);
bool	operator>(const Number& lhs, const Number& rhs);
bool	operator>=(const Number& lhs, const Number& rhs);


#endif