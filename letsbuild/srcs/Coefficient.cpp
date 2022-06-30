#include "./Coefficient.hpp"
    
//CONSTRUCTORS
Coefficient::Coefficient()
: _a(0), _b(0), _c(0) {}
	
Coefficient::Coefficient(Number a, Number b, Number c)
: _a(a), _b(b), _c(c) {}

Coefficient::Coefficient(Coefficient const &src)
{
    *this = src;
}

Coefficient::~Coefficient()
{}


//OVERLOADS
Coefficient	&Coefficient::operator=(Coefficient const &rhs)
{
    this->_a    = src.getA();
    this->_b    = src.getB();
    this->_c    = src.getC();

}


//GETTERS
Number	Coefficient::getA()	const
{
    return (this->getA());
}
Number	Coefficient::getB()	const
{
    return (this->getB());
}
Number	Coefficient::getC()	const
{
    return (this->getC());
}

//SETTERS
void	Coefficient::setA(const Number value)
{
    this->_a = value;
}        
void	Coefficient::setB(const Number value)
{
    this->_a = value;
}        
void	Coefficient::setC(const Number value)
{
    this->_a = value;
}        


//METHODS
string  Coefficient::repr()	const
{
    return ("A = " + this->getA() + "; B = " + this->getB() + "; C = " + this->getC() + "\n");
}


//OSTREAM
ostream	&operator<<(ostream &out, Coefficient const &src)
{
	out << src.repr();

	return (out);
}