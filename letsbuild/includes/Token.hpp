#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <sstream>
# include <iostream>

# include "./Coefficient.hpp"

using namespace std;


class   Token
{
private:
	string	_type;
	Coefficient	_value;

public:
	Token();
	Token(string type, Coefficient value);
	Token(Token const &src);
	~Token();

	Token	&operator=(Token const &rhs);

	string	getType()	const;
	Coefficient	getValue()	const;
	void	setType(const string type);
	void	setValue(const Coefficient value);        
        
	string repr()	const;
};

ostream	&operator<<(ostream &out, Token const &src);

#endif
