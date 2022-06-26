#ifndef INTERPRETER_HPP
# define INTERPRETER_HPP

# include "./Node.hpp"
# include "./Number.hpp"
# include "./Parser.hpp"

class	Interpreter
{
private:
	Parser	*_parser;
	
public:
	Interpreter();
	Interpreter(Parser &parser);
	Interpreter(Parser const &src);
	~Interpreter();

	Interpreter	&operator=(Interpreter const &rhs);
	
	Parser	&getParser()	const;
	void	setParser(Parser &parser);

	void	calcul(Node *node);
	Number	interpret();
};

#endif
