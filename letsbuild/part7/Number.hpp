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
	long int	decimal;

public:
	
//CONSTRUCTOR
	Number() : integer(0), decimal(0)
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
	: integer(number), decimal(0) {};

	template <class T>
	Number(T number, T dec,
	typename enable_if<is_integer<T>::value, T>::type* = NULL)
	: integer(number), decimal(dec)
	{
		if (decimal < 0)
			throw invalid_argument("Error Number constructor: decimal can't be a negative value");
	};
	
	template <class LT, class RT>
	Number(LT number, RT dec,
	typename enable_if<is_integer<LT>::value, LT>::type* = NULL,
	typename enable_if<is_integer<RT>::value, RT>::type* = NULL)
	: integer(number), decimal(dec)
	{
		if (decimal < 0)
			throw invalid_argument("Error Number constructor: decimal can't be a negative value");

	};
	
//char
	template <class T>
	Number(T number, 
	typename enable_if<is_char<T>::value, T>::type* = NULL)
	: decimal(0) 
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
		
		decimal = number;
		if (decimal % 10 != to_str(number).back() - '0')
		{
			decimal /= 10;
			decimal *= 10;
			decimal += to_str(number).back() - '0';
		}

		cout << *this << endl;
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
		this->decimal = 0;
		return (*this);
	}

	Number	&operator+(Number const &rhs)
	{
		if (this->integer > 0 && rhs.getInteger() > 0 && this->integer + rhs.getInteger() < 0
		|| this->integer < 0 && rhs.getInteger() < 0 && this->integer + rhs.getInteger() > 0)
			throw overflow_error("Error: Overflow Number in operator+ overload");
		
		this->integer += rhs.getInteger();

		if (rhs.getDecimal())
		{
			long int rhs_dec1;
			long int rhs_dec2;
			long int lhs_dec1;
			long int lhs_dec2;

			rhs_dec1 = rhs.decimal;
			lhs_dec1 = this->decimal;

			while (to_str(lhs_dec1).length() < 18)
				lhs_dec1 *= 10;
			while (to_str(rhs_dec1).length() < 18)
				rhs_dec1 *= 10;
			
			rhs_dec2 = rhs_dec1; 
			lhs_dec2 = lhs_dec1; 

			for(int i = 0; i < 9; ++i)
			{
				lhs_dec1 /= 10;
				rhs_dec1 /= 10;
			}

			lhs_dec2 -= lhs_dec1 * 1000000000;// 10 ^ 9 
			rhs_dec2 -= rhs_dec1 * 1000000000;// 10 ^ 9


			int ret = 0;

			if (to_str(lhs_dec1).length() > to_str(rhs_dec1).length())
			{
				rhs_dec1 *= 10;
				rhs_dec1 += to_str(rhs_dec2)[0] - '0';
				rhs_dec2 -= (to_str(rhs_dec2)[0] - '0') * 100000000;
				rhs_dec2 *= 10;

				lhs_dec2 += rhs_dec2;
			}
			else
			{
				lhs_dec2 += rhs_dec2;

				if (to_str(lhs_dec2).length() > 9)
					ret = to_str(lhs_dec2)[0] - '0';
				lhs_dec2 %= 1000000000;// 10 ^ 9
			}
			if (to_str(lhs_dec1).length() == 9 
			&&	to_str(rhs_dec1).length() == 9)
			{
				lhs_dec1 += rhs_dec1 + ret;
				ret = 0;
				if (to_str(lhs_dec1).length() > 9)
					ret = to_str(lhs_dec1)[0] - '0';
				lhs_dec1 %= 1000000000;// 10 ^ 9
				this->decimal = lhs_dec1 * 1000000000 + lhs_dec2;//10 ^ 9
				if (this->integer > 0 && this->integer + ret < 0)
					throw overflow_error("Error: Overflow Number in operator+ overload");
				this->integer += ret;
			}
			else if (to_str(lhs_dec1).length() == 10 
			&&	to_str(rhs_dec1).length() == 10)
			{
				lhs_dec1 += rhs_dec1 + ret;
				ret = 0;
				if (to_str(lhs_dec1).length() > 10)
					ret = to_str(lhs_dec1)[0] - '0';
				lhs_dec1 %= 10000000000;// 10 ^ 10
				this->decimal = lhs_dec1 * 1000000000 + lhs_dec2;//10 ^ 9 

				if (this->integer > 0 && this->integer + ret < 0)
					throw overflow_error("Error: Overflow Number in operator+ overload");
				this->integer += ret;
			}



			while (to_str(this->decimal).back() == '0' && this->decimal != 0)
				this->decimal /= 10;


		}


		return (*this);

	};
	Number	&operator-(Number const &rhs)
	{
		if (this->integer > 0 && rhs.getInteger() < 0 && this->integer + rhs.getInteger() < 0
		|| this->integer < 0 && rhs.getInteger() > 0 && this->integer + rhs.getInteger() > 0)
			throw overflow_error("Error: Overflow Number in operator- overload");

		if (this->integer < 0 && rhs.getInteger() > 0)
		{
			*this = *this + Number(rhs.getInteger() * -1, rhs.getDecimal());
			return (*this);
		}
		if (this->integer > 0 && rhs.getInteger() < 0)
		{
			if (to_str(rhs.getInteger()) == "-9223372036854775808")
				throw overflow_error("Error: Overflow Number in operator- overload");
			
			*this = *this + Number(rhs.getInteger() * -1, rhs.getDecimal());
			return (*this);
		}

		
		this->integer -= rhs.getInteger();
		return (*this);
	};
	Number	&operator*(Number const &rhs)
	{
		if (this->integer > 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() < 0
		|| this->integer < 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() < 0
		|| this->integer > 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() > 0
		|| this->integer < 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() > 0)
			throw overflow_error("Error: Overflow Number in operator* overload");

		this->integer *= rhs.getInteger();
		return (*this);
	};
	Number	&operator/(Number const &rhs)
	{
		if (this->integer > 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() < 0
		|| this->integer < 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() < 0
		|| this->integer > 0 && rhs.getInteger() < 0 && this->integer * rhs.getInteger() > 0
		|| this->integer < 0 && rhs.getInteger() > 0 && this->integer * rhs.getInteger() > 0)
			throw overflow_error("Error: Overflow Number in operator/ overload");

		this->integer /= rhs.getInteger();
		return (*this);
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