# include "Number.hpp"


Number	Number::operator+(Number const &rhs) const
{
	// cout << this->getInteger() << " + " << rhs.getInteger() << endl;
	if ((this->integer > 0 && rhs.getInteger() > 0 && this->integer + rhs.getInteger() < 0)
	|| (this->integer < 0 && rhs.getInteger() < 0 && this->integer + rhs.getInteger() > 0))
		throw overflow_error("Error: Overflow Number in operator+ overload " + to_str(*this) + " + " + to_str(rhs));
	

	return (this->integer + rhs.getInteger());
}

Number	Number::operator-(Number const &rhs) const
{
	// cout << this->getInteger() << " - " << rhs.getInteger() << endl;
	if ((this->integer > 0 && rhs.getInteger() < 0 && this->integer - rhs.getInteger() < 0)
	|| (this->integer < 0 && rhs.getInteger() > 0 && this->integer - rhs.getInteger() > 0))
		throw overflow_error("Error: Overflow Number in operator- overload " + to_str(*this) + " - " + to_str(rhs));
	if (this->integer < 0 && rhs.getInteger() > 0)
	{
		return (*this + Number(rhs.getInteger() * -1));
	}
	if (this->integer > 0 && rhs.getInteger() < 0)
	{
		if (to_str(rhs.getInteger()) == "-9223372036854775808")
			throw overflow_error("Error: Overflow Number in operator- overload " + to_str(*this) + " - " + to_str(rhs));
		
		return (*this + Number(rhs.getInteger() * -1));
	}
	return (this->integer - rhs.getInteger());
}

Number	Number::operator*(Number const &rhs) const
{
	// cout << this->getInteger() << " * " << rhs.getInteger() << " = ";
	if ((this->integer > 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() < 0)
	|| (this->integer < 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() < 0)
	|| (this->integer > 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() > 0)
	|| (this->integer < 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() > 0))
		throw overflow_error("Error: Overflow Number in operator* overload " + to_str(*this) + " * " + to_str(rhs));
	return (this->integer * rhs.getInteger());
}

Number	Number::operator/(Number const &rhs) const
{
	// cout << this->getInteger() << " / " << rhs.getInteger() << endl;
	if ((this->integer > 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() < 0)
	|| (this->integer < 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() < 0)
	|| (this->integer > 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() > 0)
	|| (this->integer < 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() > 0))
		throw overflow_error("Error: Overflow Number in operator/ overload " + to_str(*this) + " / " + to_str(rhs));
	if (!rhs.getInteger())
        throw logic_error("Number Error: Divide by zero");

    return (this->integer / rhs.getInteger());
};


bool	operator==(const Number& lhs, const Number& rhs)
{
	return (lhs.getInteger() == rhs.getInteger());
}
bool	operator!=(const Number& lhs, const Number& rhs)
{
	return (!(lhs == rhs));
}
bool	operator<(const Number& lhs, const Number& rhs)
{
	return (lhs.getInteger() < rhs.getInteger());
}
bool	operator<=(const Number& lhs, const Number& rhs)
{
	return (!(rhs < lhs));
}
bool	operator>(const Number& lhs, const Number& rhs)
{
	return (rhs < lhs);
}
bool	operator>=(const Number& lhs, const Number& rhs)
{
	return (!(rhs > lhs));
}

Number::operator bool()
{
	return (integer);
}

Number::operator bool() const
{
	return (integer);
}
