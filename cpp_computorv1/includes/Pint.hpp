#ifndef PINT_HPP
# define PINT_HPP

# include <iostream>
# include <stdexcept>

# include "utils.hpp"

class Pint
{
	private:
		long int integer;

	public:
	Pint();
	Pint(const Pint &src);
	Pint(long int nb);
	~Pint();

	Pint &operator=(const Pint &rhs);


	long int 	getInteger() const;
	void		setInteger(long int nb);

	Pint	operator+(Pint const &rhs) const;
	Pint	operator-(Pint const &rhs) const;



};

std::ostream &operator<<(std::ostream &out, const Pint &src);

#endif