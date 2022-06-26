#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include "Number.hpp"

using namespace std;

#define INTEGER "INTEGER"
#define PLUS    "PLUS"
#define MINUS	"MINUS"
#define MUL    	"MUL"
#define DIV		"DIV"
#define EOL     "EOL"
#define ERR     "ERR"
#define	LPAREN	"LPAREN"
#define	RPAREN	"RPAREN"

class   Token
{
    private:
        string  _type;
        Number	_value;

    public:
        Token(): _type(), _value() {};
        Token(string type, Number value) : _type(type), _value(value)
        {};

        Token(Token const &src) { *this = src; };
        Token   &operator=(Token const &rhs)
        {
            this->_type = rhs.getType();
            this->_value = rhs.getValue();
            return (*this);
        }
        string	getType()   const { return (_type); };
        Number	getValue()  const { return (_value); };
        void    setType(const string type) { _type = type; };
        void    setValue(const Number value) { _value = value; };        
        
		~Token()
        {};
        
        string  str()
        {
           	stringstream ss;
		   
		   	ss << "Token(" << _type << ", '" << _value << "')";
			return (ss.str());
        };

        string repr()
        {
            return str();
        }
};

class Lexer
{
	private:
		string	*_text;
		int		_pos;
		char	_current_char;

    public:
		Lexer() : _text(NULL), _pos(0), _current_char(0) {};
        Lexer(string &text) : _text(&text), _pos(0), _current_char(_text->at(_pos))
        {};

		Lexer(Lexer const &src) { *this = src; };
		Lexer	&operator=(Lexer const &rhs)
		{
			this->_current_char = rhs.getCurrent_char();
			this->_pos = rhs.getPos();
			this->_text = &rhs.getText();
			return (*this);
		};
		string  &getText()         	const   { return (*_text); };
        int     getPos()          	const	{ return (_pos); };
		char	getCurrent_char()	const	{ return (_current_char); }
        void    setText(string &text)                   { _text = &text; };
        void    setPos(int pos)                         { _pos = pos; };
        void    setCurrent_char(int pos)                { _pos = pos; };

		~Lexer()
		{};

		void    error()
        {
            throw runtime_error("Error Lexer: Invalid character");
        };

		void	advance()
		{
			++_pos;
			if ((long unsigned int)_pos >= _text->length())
				_current_char = 0;
			else
				_current_char = _text->at(_pos);
		}

		void	skip_whitespace()
		{
			while (_current_char != 0 && isspace(_current_char))
				this->advance();
		}

		Number	integer()
		{
			string result;

			while (_current_char != 0 && isdigit(_current_char))
			{
				result += _current_char;
				this->advance();
			}
			return (result);
		}

        Token    get_next_token()
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
					return (Token(PLUS, 0));
				}
				if (_current_char == '-')
				{
					this->advance();
					return (Token(MINUS, 0));
				}
				if (_current_char == '*')
				{
					this->advance();
					return (Token(MUL, 0));
				}
				if (_current_char == '/')
				{
					this->advance();
					return (Token(DIV, 0));
				}
				if (_current_char == '(')
				{
					this->advance();
					return (Token(LPAREN, 0));
				}
				if (_current_char == ')')
				{
					this->advance();
					return (Token(RPAREN, 0));
				}

				this->error();
			}
			return (Token(EOL, 0));
        };
};

class Node
{
public:
	
	Node(Token value, Node *_left = NULL, Node *_right = NULL)
	: data(value), left(_left), right(_right)
	{};
	Node	&operator=(Node const &rhs)
	{
		if (this != &rhs)
		{
			this->data 	= rhs.data; 
			this->left 	= rhs.left;
			this->right	= rhs.right;
		}
		return (*this);
	};
	
	~Node(void)
	{};
	
	Token	data;
	Node	*left;
	Node	*right;
};

void	print_btree(Node *root = NULL, int a = 0, int lvl = 0, int max = -1)
{
	if (!root)
	{
		cerr << "error root null" << std::endl;
		return;
	}
	if (root->right && (lvl <= max || max == -1))
		print_btree(root->right, 0, lvl + 1, max);
	for (int k = 1	; k < lvl; k++)
		for (int i = 0; i < 20; i++)
			cout << " ";
	if (lvl)
	{
		for (int i = 0; i < 20 - 5; i++)
			cout << " ";
		if (a)
			cout << "\\";
		else
			cout << "/";
	}
	cout << "---<" << lvl << ">";
	cout << "[" << root->data.repr() << "]";
	if (root->right && root->left)
		cout << " <";
	else
	{
		if (root->right)
			cout << " /";
		if (root->left)
			cout << " \\";
	}
	cout << std::endl;
	if (root->left && (lvl <= max || max == -1))
		print_btree(root->left, 1, lvl + 1, max);
}

void	clear_btree(Node *root)
{
	if (root->left)
		clear_btree(root->left);
	if (root->right)
		clear_btree(root->right);
	delete root;
}

class   Parser
{
    private:
		Lexer	*_lexer;
		Token	_current_token;

	public:
		Parser() : _lexer(NULL), _current_token(){};
        Parser(Lexer &lexer) : _lexer(&lexer), _current_token(_lexer->get_next_token())
        {};
		
		Parser(const Parser &src) { *this = src; };
		Parser	&operator=(const Parser &rhs)
		{
			_lexer 			= &rhs.getLexer();
			_current_token	= rhs.getCurrent_token();
			return (*this);
		};
		Lexer	&getLexer()			const	{ return (*_lexer); };
		Token   getCurrent_token()	const   { return (_current_token); };
        void    setLexer(Lexer &lexer)					{ _lexer = &lexer; }; 
        void    setCurrent_token(Token current_token)   { _current_token = current_token; }; 

		~Parser()
		{};

		void	error()
		{
			throw runtime_error("Error Parser: Invalid syntax");
		}

        void    eat(string token_type)
        {
            if (_current_token.getType() == token_type)
                _current_token = _lexer->get_next_token();
            else
                this->error();
        }

		Node	*factor()
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

        Node	*term()
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

		Node	*expr()
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

		Node	*parse()
		{
			return this->expr();
		}
};


class	Interpreter
{
	private:
		Parser	*_parser;
	
	public:
	Interpreter() : _parser(NULL) {};
	Interpreter(Parser &parser) : _parser(&parser){};

	Interpreter(Parser const &src) { *this = src; };
	Interpreter	&operator=(Interpreter const &rhs)
	{
		this->_parser = &rhs.getParser();
		return (*this);
	};
	Parser	&getParser()	const	{ return (*_parser); };
	void	setParser(Parser &parser)	{ _parser = &parser; };

	~Interpreter() 
	{};

 	void	error()
	{
		throw runtime_error("Error Interpreter: Invalid syntax");
	}

	void	calcul(Node *node)
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

	};

	Number	interpret()
	{
		Node	*ast = _parser->parse();
		if (_parser->getCurrent_token().getType() != EOL)
			_parser->error();

		this->calcul(ast);

		Number	result = ast->data.getValue();

		clear_btree(ast);
		return (result);
	}
};

int main()
{
    string input;
    while (1)
    {
        try
        {
            cout << "calc> ";
            if (getline(cin, input, '\n').eof())
			{
				return (0);
			}
            if (!input.length())
                continue;
			if (input == "quit" || input == "exit")
				return (0);

			Lexer		lexer(input);
            Parser 		parser(lexer);
			Interpreter	interpreter(parser);
			Number		result = interpreter.interpret();
			
			cout << result << endl; 
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

	// Number nbr1(-45, 78);
	// Number nbr2(-12, 89);
	// cout << "nbr1: " << nbr1 << endl;
	// cout << "nbr2: " << nbr2 << endl;



	// nbr1 += nbr2;
	// cout << nbr1 << endl;

}