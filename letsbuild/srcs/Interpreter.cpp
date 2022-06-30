#include "./Interpreter.hpp"

//CONSTRUCTORS
Interpreter::Interpreter()
: _parser(NULL) {}

Interpreter::Interpreter(Parser &parser)
: _parser(&parser) {}

Interpreter::Interpreter(Parser const &src)
{
	*this = src;
}

Interpreter::~Interpreter() {}


//OVERLOADS
Interpreter	&Interpreter::operator=(Interpreter const &rhs)
{
	this->_parser = &rhs.getParser();
	return (*this);
};


//GETTERS
Parser	&Interpreter::getParser()	const
{
	return (*_parser);
}

//SETTERS
void	Interpreter::setParser(Parser &parser)
{
	_parser = &parser;
}


//METHODS
void	Interpreter::calcul(Node *node)
{
	if (node->left)
		calcul(node->left);
	if (node->right)
		calcul(node->right);
	
	if (node->data.getType() == PLUS)	
		node->data.setValue((node->left->data.getValue() + node->right->data.getValue()));
    else if (node->data.getType() == MINUS)	
		node->data.setValue((node->left->data.getValue() - node->right->data.getValue()));
    else if (node->data.getType() == MUL)	
		node->data.setValue((node->left->data.getValue() * node->right->data.getValue()));
    else if (node->data.getType() == DIV)	
		node->data.setValue((node->left->data.getValue() / node->right->data.getValue()));
}

Number	Interpreter::interpret()
{
	Node	*ast = _parser->parse();
	if (_parser->getCurrent_token().getType() != EOL)
		_parser->error();
	this->calcul(ast);
	Number	result = ast->data.getValue();
	cout << *ast << endl;
	clear_btree(ast);
	return (result);
}
