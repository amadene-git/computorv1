#ifndef LEXER_HPP
# define LEXER_HPP

# include <string>
# include <stdexcept>

# include "./Token.hpp"
# include "./Token_type.hpp"

using namespace std;

class Lexer
{
private:
	string	*_text;
	int		_pos;
	char	_current_char;

public:
	Lexer();
	Lexer(string &text);
	Lexer(Lexer const &src);
	~Lexer();

	Lexer	&operator=(Lexer const &rhs);

	string	&getText()	const;
	int		getPos()	const;
	char	getCurrent_char()	const;
	void	setText(string &text);
	void	setPos(int pos);
	void	setCurrent_char(int pos);

	void	error();
	void	advance();
	void	skip_whitespace();
	Number	integer();
	Token	get_next_token();
};

#endif
