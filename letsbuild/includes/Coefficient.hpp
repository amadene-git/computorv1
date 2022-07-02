#ifndef COEFFICIENT_HPP
# define COEFFICIENT_HPP

# include "Number.hpp"


class Coefficient;
ostream	&operator<<(ostream &out, Coefficient const &src);


class Coefficient
{
private:
	Number	_a;
	Number	_b;
	Number	_c;

public:
	Coefficient();
	Coefficient(Number a, Number b, Number c);
	Coefficient(Coefficient const &src);
	~Coefficient();

	Coefficient	&operator=(Coefficient const &rhs);

	Number	getA()	const;
	Number	getB()	const;
	Number	getC()	const;

	void	setA(const Number value);
	void	setB(const Number value);
	void	setC(const Number value);

Coefficient	operator+(Coefficient const &rhs)
{

	return (Coefficient(_a + rhs.getA(),\
						_b + rhs.getB(),\
						_c + rhs.getC()));
};
Coefficient	operator-(Coefficient const &rhs)
{
	return (Coefficient(_a - rhs.getA(),\
						_b - rhs.getB(),\
						_c - rhs.getC()));
};
Coefficient	operator*(Coefficient const &rhs)
{
	if ((_a && rhs.getA()) || (_a && rhs.getB()) || (_b && rhs.getA()))
		throw runtime_error("Not second degree equation");
	
	Number a = (_a * rhs.getC()) + (_c * rhs.getA()) + (_b * rhs.getB());
	Number b = (_b * rhs.getC()) + (_c * rhs.getB());
	Number c = (_c * rhs.getC());


	return (Coefficient( a, b, c));

};
Coefficient	operator/(Coefficient const &rhs)
{
	Number a = (_a / rhs.getC()) + (_c / rhs.getA()) + (_b / rhs.getB());
	Number b = (_b / rhs.getB()) + (_b / rhs.getC()) + (_c / rhs.getB());
	Number c = (_c / rhs.getC());


	return (Coefficient( a, b, c));
};

Coefficient	operator+(Number const &rhs)
{
	return (Coefficient(_a,\
						_b,\
						_c + rhs));
};
Coefficient	operator-(Number const &rhs)
{
	return (Coefficient(_a,\
						_b,\
						_c - rhs));
};
Coefficient	operator*(Number const &rhs)
{
	return (Coefficient(_a * rhs,\
						_b * rhs,\
						_c * rhs));
};
Coefficient	operator/(Number const &rhs)
{
	return (Coefficient(_a / rhs,\
						_b / rhs,\
						_c / rhs));
};



	string repr()	const;
};

ostream	&operator<<(ostream &out, Coefficient const &src);


#endif

