#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

#include "utils.hpp"

using namespace std;



class Number;


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

	Number	operator+(Number const &rhs) const;
	Number	operator-(Number const &rhs) const;
	Number	operator*(Number const &rhs) const;
	Number	operator/(Number const &rhs) const;
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

	operator bool();
	operator bool() const;

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