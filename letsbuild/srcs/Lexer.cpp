#include "./Lexer.hpp"
#include "./Coeff.hpp"

//CONSTRUCTORS
Lexer::Lexer()
: _text(NULL), _pos(0), _current_char(0) {}

Lexer::Lexer(string &text)
: _text(&text), _pos(0), _current_char(_text->at(_pos)) {}

Lexer::Lexer(Lexer const &src)
{
	*this = src;
}

Lexer::~Lexer() {}


//OVERLOADS
Lexer	&Lexer::operator=(Lexer const &rhs)
{
	this->_current_char	= rhs.getCurrent_char();
	this->_pos			= rhs.getPos();
	this->_text			= &rhs.getText();
	
	return (*this);
}


//GETTERS
string	&Lexer::getText()	const
{
	return (*_text);
}
int		Lexer::getPos()	const
{
	return (_pos);
}
char	Lexer::getCurrent_char()	const
{
	return (_current_char);
}

//SETTERS
void	Lexer::setText(string &text)
{
	_text = &text;
}
void	Lexer::setPos(int pos)
{
	_pos = pos;
}
void	Lexer::setCurrent_char(int pos)
{
	_pos = pos;
}


//METHODS
void    Lexer::error()
{
	throw runtime_error("Error Lexer: Invalid character");
}

void	Lexer::advance()
{
	++_pos;
	if ((long unsigned int)_pos >= _text->length())
		_current_char = 0;
	else
		_current_char = _text->at(_pos);
}

void	Lexer::skip_whitespace()
{
	while (_current_char != 0 && isspace(_current_char))
		this->advance();
}

Coeff	Lexer::integer()
{
	string result;

	while (_current_char != 0 && isdigit(_current_char))
	{
		result += _current_char;
		this->advance();
	}
	return (Coeff(result, 0));
}

Token	Lexer::get_next_token()
{
	while (_current_char)
	{
		// cout << "char: '" <<  _current_char << "' ; pos: " << _pos << endl; 
		if (isspace(_current_char))
		{
			this->skip_whitespace();
			continue;
		}
		if (isdigit(_current_char))
		{
			return (Token(INTEGER, this->integer()));
		}
		if (_current_char == '+')
		{
			this->advance();
			return (Token(PLUS, Coeff()));
		}
		if (_current_char == '-')
		{
			this->advance();
			return (Token(MINUS, Coeff()));
		}
		if (_current_char == '*')
		{
			this->advance();
			return (Token(MUL, Coeff()));
		}
		if (_current_char == '/')
		{
			this->advance();
			return (Token(DIV, Coeff()));
		}
		if (_current_char == '(')
		{
			this->advance();
			return (Token(LPAREN, Coeff()));
		}
		if (_current_char == ')')
		{
			this->advance();
			return (Token(RPAREN, Coeff()));
		}
		if (_current_char == '=')
		{
			this->advance();
			return (Token(EQUAL, Coeff()));
		}
		if (_current_char == '^')
		{
			this->advance();
			return (Token(EXPO, Coeff()));
		}
		if (_current_char == 'x')
		{
			this->advance();
			// cout << Coeff(0, 1, 0) << endl;
			return (Token(X, Coeff(1, 1)));
		}



		this->error();
	}
	return (Token(EOL, Coeff()));
}
