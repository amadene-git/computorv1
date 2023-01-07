#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

template<class T>
string	to_str(T value)
{
	stringstream ss;
	ss << value;
	
	return (ss.str());
}

// template<class T>	__is_char

class Number
{
private:
	long int	integer;
	long int	decimal;

public:
	
//CONSTRUCTOR
	Number() : integer(0), decimal(0)
	{};
	Number(Number const &src)
	{
		*this = src;
	};
	~Number() {};

	Number(int number) 		: integer(number), decimal(0) {};
	Number(long int number) : integer(number), decimal(0) {};
	
	template <class T, class = typename enable_if<__is_char<T>::value, T>::type>
	Number(char number) 	: decimal(0) {
		if (!isdigit(number))
			throw invalid_argument("Number char constructor failed '" + to_str(number) + "' is not a number");
		integer = number - '0';
	};
	
	template <class T, class = typename enable_if<is_floating_point<T>::value, T>::type>
	Number(T number)	: integer(number)
	{
		number -= integer;
		while (to_str(number).back() != '0')
			number *= 10;
		number /= 10;		
		
		decimal = number;
		if (decimal % 10 != to_str(number).back() - '0')
		{
			decimal /= 10;
			decimal *= 10;
			decimal += to_str(number).back() - '0';
		}
	};
	
	Number(string number)
	{
		this->integer = atol(number.c_str());
		this->decimal = 0;
	};


//GETTER
	long int	getInteger()	const	{ return (integer); };
	long int	getDecimal()	const	{ return (decimal); };

	template <class T>
	void	setInteger(T number) { integer = Number(number).getInteger(); }

	template <class T>
	void	setDecimal(T number) { decimal = Number(number).getDecimal(); }


//OVERLOAD
	Number	&operator=(Number const &rhs)
	{
		this->integer = rhs.getInteger();
		this->decimal = rhs.getDecimal();
		return (*this);
	}

	Number	&operator=(string const &rhs)
	{
		this->integer = atol(rhs.c_str());
		return (*this);
	}

	Number	&operator+(Number const &rhs)
	{
		if (this->integer > 0 && rhs.getInteger() > 0 && this->integer + rhs.getInteger() < 0
		|| this->integer < 0 && rhs.getInteger() < 0 && this->integer + rhs.getInteger() > 0)
			throw overflow_error("Error: Overflow Number in operator+ overload");
		
		this->integer += rhs.getInteger();

		return (*this);

	};
	Number	&operator-(Number const &rhs)
	{
		if (this->integer > 0 && rhs.getInteger() < 0 && this->integer + rhs.getInteger() < 0
		|| this->integer < 0 && rhs.getInteger() > 0 && this->integer + rhs.getInteger() > 0)
			throw overflow_error("Error: Overflow Number in operator- overload");

		this->integer -= rhs.getInteger();
		return (*this);
	};
	// Number	&operator*(Number const &rhs);
	// Number	&operator/(Number const &rhs);

	Number	&operator+=(Number const &rhs)
	{
		this->integer = this->integer + rhs.getInteger();
		return (*this);
	};

	Number	&operator-=(Number const &rhs)
	{
		this->integer = this->integer - rhs.getInteger();
		return (*this);
	};

	Number	&operator+=(char const &rhs)
	{
		if (this->integer > 0 && this->integer * 10 < 0 
		||  this->integer < 0 && this->integer * 10 > 0)
			throw overflow_error("Error: Overflow Number in operator+= overload");
		this->integer *= 10;
		this->integer += rhs - '0';
		return (*this);
	};


};

ostream	&operator<<(ostream &out, Number const &src)
{
	out << src.getInteger();
	if (src.getDecimal())
		out << "." << src.getDecimal();

	return (out);
}