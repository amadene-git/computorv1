#include "./Parser.hpp"

//CONSTRUCTORS
Parser::Parser()
: _lexer(NULL), _current_token() {}

Parser::Parser(Lexer &lexer)
: _lexer(&lexer), _current_token(_lexer->get_next_token()) {}

Parser::Parser(const Parser &src)
{
	*this = src;
}

Parser::~Parser() {}


//OVERLOADS
Parser	&Parser::operator=(const Parser &rhs)
{
	_lexer 			= &rhs.getLexer();
	_current_token	= rhs.getCurrent_token();
	
	return (*this);
}


//GETTERS
Lexer	&Parser::getLexer()	const
{
	return (*_lexer);
}
Token	Parser::getCurrent_token()	const
{
	return (_current_token);
}

//SETTERS
void	Parser::setLexer(Lexer &lexer)
{
	_lexer = &lexer;
} 
void	Parser::setCurrent_token(Token current_token)
{
	_current_token = current_token;
} 


//METHODS
void	Parser::error()
{
	throw runtime_error("Error Parser: Invalid syntax");
}

void	Parser::eat(string token_type)
{
    if (_current_token.getType() == token_type)
        _current_token = _lexer->get_next_token();
    else
        this->error();
}

Node	*Parser::factor()
{
	Token	token = _current_token;

	if (token.getType() == INTEGER)
	{
		this->eat(INTEGER);
		return (new Node(token));
	}
	else if (_current_token.getType() == LPAREN)
	{
		this->eat(LPAREN);
		Node *node = this->expr();
		this->eat(RPAREN);
		return (node);
	}
	return (NULL);
}

Node	*Parser::term()
{
	Node *node = this->factor();

	while (	_current_token.getType() == MUL
	||		_current_token.getType() == DIV)
	{
		Token token = _current_token;
		if (_current_token.getType() == MUL)
		{
			this->eat(MUL);
		}
		else if (_current_token.getType() == DIV)
		{
			this->eat(DIV);
		}
		node = new Node(token, node, this->factor());
	}
	return (node);
}

Node	*Parser::expr()
{
	Node *node = this->term();

	while (	_current_token.getType() == PLUS
	||		_current_token.getType() == MINUS)
	{
		Token token = _current_token;
		if (_current_token.getType() == PLUS)
		{
			this->eat(PLUS);
		}
		else if (_current_token.getType() == MINUS)
		{
			this->eat(MINUS);
		}
		node = new Node(token, node, this->term());
	}
	return (node);		
}

Node	*Parser::parse()
{
	return this->expr();
}
