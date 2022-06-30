#ifndef PARSER_HPP
# define PARSER_HPP

# include <stdexcept>

# include "./Node.hpp"
# include "./Token.hpp"
# include "./Lexer.hpp"

using namespace std;


class   Parser
{
private:
	Lexer	*_lexer;
	Token	_current_token;

public:
	Parser();
	Parser(Lexer &lexer);
	Parser(const Parser &src);
	~Parser();

	Parser	&operator=(const Parser &rhs);

	Lexer	&getLexer()	const;
	Token	getCurrent_token()	const;
	void	setLexer(Lexer &lexer); 
	void	setCurrent_token(Token current_token); 

	void	error();
	void	eat(string token_type);
	Node	*factor();
	Node	*exponent();
	Node	*term();
	Node	*expr();
	Node	*parse();
	Node	*equation();
};

#endif
