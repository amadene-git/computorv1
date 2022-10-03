#include "./Pint.hpp"

Pint::Pint() : integer(0)
{
	std::cout << "Pint constructor called" << std::endl;
}
Pint::Pint(const Pint &src)
{
	std::cout << "Pint copy constructor called" << std::endl;
	*this = src;
}
Pint::Pint(long int nb) : integer(nb)
{
	std::cout << "Pint long int constructor called" << std::endl;
} 

Pint::~Pint()
{
	std::cout << "Pint Destructor called" << std::endl;
}

Pint &Pint::operator=(const Pint &rhs)
{
	this->integer = rhs.getInteger();
	return (*this);	
}


long int 	Pint::getInteger() const
{
	return this->integer;
}
void		Pint::setInteger(long int nb)
{
	this->integer = nb;
}

Pint	Pint::operator+(Pint const &rhs) const
{
	std::cout << this->getInteger() << " + " << rhs.getInteger() << std::endl;
	if ((this->integer > 0 && rhs.getInteger() > 0 && this->integer + rhs.getInteger() < 0)
	|| (this->integer < 0 && rhs.getInteger() < 0 && this->integer + rhs.getInteger() > 0))
		throw std::overflow_error("Error: Overflow Pint in operator+ overload " + to_str(*this) + " + " + to_str(rhs));
	

	return (this->integer + rhs.getInteger());
}

Pint	Pint::operator-(Pint const &rhs) const
{
	std::cout << this->getInteger() << " - " << rhs.getInteger() << std::endl;
	
	try
	{
		*this + rhs.getInteger() * -1;
		std::cout << "operator - " << std::endl;
	
	}
	catch (std::overflow_error)
	{
		throw std::overflow_error("Error: Overflow Pint in operator- overload " + to_str(*this) + " - " + to_str(rhs));
	}

	return (this->integer - rhs.getInteger());
}

std::ostream &operator<<(std::ostream &out, const Pint &src)
{
	out << src.getInteger();
	return out; 
}
