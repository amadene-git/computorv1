#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include <sstream>
# include <iostream>

# include "./Number.hpp"

using namespace std;

class   Token
{
private:
	string	_type;
	Number	_value;

public:
	Token();
	Token(string type, Number value);
	Token(Token const &src);
	~Token();

	Token	&operator=(Token const &rhs);

	string	getType()	const;
	Number	getValue()	const;
	void	setType(const string type);
	void	setValue(const Number value);        
        
	string repr()	const;
};

ostream	&operator<<(ostream &out, Token const &src);

#endif
