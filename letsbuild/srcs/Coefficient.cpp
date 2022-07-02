#include "./Coefficient.hpp"
    
//CONSTRUCTORS
Coefficient::Coefficient()
: _a(), _b(), _c() {}
	
Coefficient::Coefficient(Number a, Number b, Number c)
: _a(a), _b(b), _c(c) 
{
    // cout << "constructor: " << *this << endl;
    // cout << "_c: " << this->_c << " : " << _c.getDefined() << endl;
}

Coefficient::Coefficient(Coefficient const &src)
{
    *this = src;
}

Coefficient::~Coefficient()
{}


//OVERLOADS
Coefficient	&Coefficient::operator=(Coefficient const &rhs)
{
    this->_a    = rhs.getA();
    this->_b    = rhs.getB();
    this->_c    = rhs.getC();

    return (*this);
}


//GETTERS
Number	Coefficient::getA()	const
{
    return (this->_a);
}
Number	Coefficient::getB()	const
{
    return (this->_b);
}
Number	Coefficient::getC()	const
{
    return (this->_c);
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
    stringstream ss;

    // if (_a.getDefined())
        ss << _a << "x²";
    // if (_b.getDefined())
    // {
    //     if (_a.getDefined())
            ss << " + ";
        ss << _b << "x";
    // }
    // if (_c.getDefined())
    // {
    //     if (_b.getDefined())
            ss << " + ";
        ss << _c;
    // }
    
    return (ss.str());
}


//OSTREAM
ostream	&operator<<(ostream &out, Coefficient const &src)
{
	out << src.repr();

	return (out);
}