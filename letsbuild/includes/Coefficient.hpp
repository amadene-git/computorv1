#ifndef COEFFICIENT_HPP
# define COEFFICIENT_HPP

# include "Number.hpp"


class Coefficient
{
private:
	Number	_a;
	Number	_b;
	Number	_c;

public:
	Coefficient();
	Coefficient(Number a = 0, Number b = 0, Number c = 0);
	Coefficient(Coefficient const &src);
	~Coefficient();

	Coefficient	&operator=(Coefficient const &rhs);

	Number	getA()	const;
	Number	getB()	const;
	Number	getC()	const;

	void	setA(const Number value);        
	void	setB(const Number value);        
	void	setC(const Number value);        
        
	string repr()	const;
};

ostream	&operator<<(ostream &out, Coefficient const &src);


#endif

