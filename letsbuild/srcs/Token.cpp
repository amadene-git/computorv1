#include "./Token.hpp"

//CONSTRUCTORs
Token::Token()
: _type(), _value() {}

Token::Token(string type, Coeff value)
: _type(type), _value(value) {}

Token::Token(Token const &src)
{
	*this = src;
}

Token::~Token() {}


//OVERLOADS
Token   &Token::operator=(Token const &rhs)
{
    this->_type		= rhs.getType();
    this->_value	= rhs.getValue();
    
	return (*this);
}


//GETTERS
string	Token::getType()	const
{
	return (_type); 
}
Coeff	Token::getValue()	const
{
	return (_value); 
}

//SETTERS
void	Token::setType(const string type)
{
	_type = type;
}
void	Token::setValue(const Coeff value)
{
	_value = value;
}        


//METHODS
string	Token::repr() const
{
	stringstream ss;

	ss << "Token(" << _type << ", '" << _value << "')";
	return (ss.str());
}


//OSTREAM
ostream	&operator<<(ostream &out, Token const &src)
{
	out << src.repr();

	return (out);
}
