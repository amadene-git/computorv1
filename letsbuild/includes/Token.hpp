#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <sstream>
# include <iostream>

# include "./Coeff.hpp"

using namespace std;


class   Token
{
private:
	string	_type;
	Coeff	_value;

public:
	Token();
	Token(string type, Coeff value);
	Token(Token const &src);
	~Token();

	Token	&operator=(Token const &rhs);

	string	getType()	const;
	Coeff	getValue()	const;
	void	setType(const string type);
	void	setValue(const Coeff value);        
        
	string repr()	const;
};

ostream	&operator<<(ostream &out, Token const &src);

#endif
