#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

template<class T> 	struct is_char 			: false_type {};
template<>			struct is_char<char>	: true_type {};

template<class T> 	struct is_integer 			: false_type {};
template<>			struct is_integer<int>		: true_type {};
template<>			struct is_integer<long int>	: true_type {};

template<class T> 	struct is_float 				: false_type {};
template<>			struct is_float<float>			: true_type {};
template<>			struct is_float<double>			: true_type {};
template<>			struct is_float<long double>	: true_type {};


class Number;

template<class T>
string	to_str(T value)
{
	stringstream ss;
	ss << value;
	
	return (ss.str());
}

ostream	&operator<<(ostream &out, Number const &src);


class Number
{
private:
	long int	integer;

public:
	
//CONSTRUCTOR
	Number() : integer(0)
	{};
	Number(Number const &src)
	{
		*this = src;
	};
	Number(string const &number)
	{
		*this = number;
	};

	~Number() {};

//integer
	template <class T>
	Number(T number,
	typename enable_if<is_integer<T>::value, T>::type* = NULL)
	: integer(number) 
	{
		// cout << "number construct -> " << integer << " : " << defined << endl;
	};

	
//char
	template <class T>
	Number(T number, 
	typename enable_if<is_char<T>::value, T>::type* = NULL) 
	{
		if (!isdigit(number))
		{
			// throw invalid_argument("Number char constructor failed '" + to_str(number) + "' is not a number");
			integer = number;	
		}
		else
			integer = number - '0';

	};

//float
	template <class T>
	Number(T number, 
	typename enable_if<is_float<T>::value, T>::type* = NULL)
	: integer(number)
	{
		cout << "float constructor called" << endl;
		number -= integer;
		while (to_str(number).back() != '0')
			number *= 10;
		number /= 10;


		cout << *this << endl;
	};
	


//GETTER
	long int	getInteger()	const	{ return (integer); };

	template <class T>
	void	setInteger(T number) { integer = Number(number).getInteger(); }



//OVERLOAD
	Number	&operator=(Number const &rhs)
	{
		this->integer = rhs.getInteger();
		return (*this);
	}

	Number	&operator=(string const &rhs)
	{
		this->integer = atol(rhs.c_str());
		return (*this);
	}

	Number	operator+(Number const &rhs)
	{
		// cout << this->getInteger() << " + " << rhs.getInteger() << endl;
		if ((this->integer > 0 && rhs.getInteger() > 0 && this->integer + rhs.getInteger() < 0)
		|| (this->integer < 0 && rhs.getInteger() < 0 && this->integer + rhs.getInteger() > 0))
			throw overflow_error("Error: Overflow Number in operator+ overload " + to_str(*this) + " + " + to_str(rhs));
		
	
		return (this->integer + rhs.getInteger());

	};
	Number	operator-(Number const &rhs)
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
	};
	Number	operator*(Number const &rhs)
	{
		// cout << this->getInteger() << " * " << rhs.getInteger() << " = ";
		if ((this->integer > 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() < 0)
		|| (this->integer < 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() < 0)
		|| (this->integer > 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() > 0)
		|| (this->integer < 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() > 0))
			throw overflow_error("Error: Overflow Number in operator* overload " + to_str(*this) + " * " + to_str(rhs));

		return (this->integer * rhs.getInteger());
	};
	Number	operator/(Number const &rhs)
	{
		// cout << this->getInteger() << " / " << rhs.getInteger() << endl;
		if ((this->integer > 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() < 0)
		|| (this->integer < 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() < 0)
		|| (this->integer > 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() > 0)
		|| (this->integer < 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() > 0))
			throw overflow_error("Error: Overflow Number in operator/ overload " + to_str(*this) + " / " + to_str(rhs));

		return (this->integer / rhs.getInteger());
	};

	Number	&operator+=(Number const &rhs)
	{
		*this = *this + rhs;
		return (*this);
	};

	Number	&operator-=(Number const &rhs)
	{
		*this = *this - rhs;
		return (*this);
	};

	Number	&operator*=(Number const &rhs)
	{
		*this = *this * rhs;
		return (*this);
	};

	Number	&operator/=(Number const &rhs)
	{
		*this = *this / rhs;
		return (*this);
	};

	operator bool()
	{
		return (integer);
	}

	Number	exponent(Number const &src)
	{
		if (src.getInteger() <= 0)
			return (1);
		
		int i = 1;
		Number ret = *this;

		while (i < src.getInteger())
		{
			cout << i << " < " << src.getInteger() << "   -> "<< *this << endl;
			*this *= ret;
			++i;
		}
		return (*this);
	};
};

#endif