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
        Token(): _type(string()), _value(char())
        {};
        Token(string type, Number value) : _type(type), _value(value)
        {};

        Token(Token const &src)
        {
            *this = src;
        };

        Token   &operator=(Token const &rhs)
        {
            this->_type = rhs.getType();
            this->_value = rhs.getValue();
            return (*this);
        }
        
        ~Token()
        {};
        
        string  str()
        {
           	stringstream ss;
		   	char op = (char)_value.getInteger(); 
		   
		   	ss << "Token(" << _type << ", '";
			
			if (_type == INTEGER)
				ss << _value;
			else
				ss << op; 
			
			ss << "')";
			return (ss.str());
        };

        string repr()
        {
            return str();
        }

        string	getType()   const { return (_type); };
        Number	getValue()  const { return (_value); };

        void    setType(const string type) { _type = type; };
        void    setValue(const Number value) { _value = value; };

};

class Lexer
{
	private:
		string	_text;
		int		_pos;
		char	_current_char;

    public:

		Lexer(Lexer const &src) { *this = src; };
		Lexer	&operator=(Lexer const &rhs)
		{
			this->_current_char = rhs._current_char;
			this->_pos = rhs._pos;
			this->_text = rhs._text;
			return (*this);
		};

        Lexer(string text) : _text(text), _pos(0), _current_char(_text[_pos])
        {};

		string  getText()           const   { return (_text); };
        int     getPos()            const   { return (_pos); };
        void    setText(string text)                    { _text = text; };
        void    setPos(int pos)                         { _pos = pos; };


		void    error()
        {
            throw runtime_error("Error Lexer: Invalid character");
        };

		void	advance()
		{
			++_pos;
			if (_pos >= _text.length())
				_current_char = 0;
			else
				_current_char = _text[_pos];
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
					return (Token(PLUS, '+'));
				}
				if (_current_char == '-')
				{
					this->advance();
					return (Token(MINUS, '-'));
				}
				if (_current_char == '*')
				{
					this->advance();
					return (Token(MUL, '*'));
				}
				if (_current_char == '/')
				{
					this->advance();
					return (Token(DIV, '/'));
				}
				if (_current_char == '(')
				{
					this->advance();
					return (Token(LPAREN, '('));
				}
				if (_current_char == ')')
				{
					this->advance();
					return (Token(RPAREN, ')'));
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

		Lexer	_lexer;
		Token	_current_token;
    
	public:

        Parser(Lexer lexer) : _lexer(lexer), _current_token(_lexer.get_next_token())
        {};

       void	error()
	   {
			throw runtime_error("Error Parser: Invalid syntax");
	   }


        void    eat(string token_type)
        {
            if (_current_token.getType() == token_type)
                _current_token = _lexer.get_next_token();
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

        Token   getCurrent_token()  const   { return (_current_token); };

        void    setCurrent_token(Token current_token)   { _current_token = current_token; }; 
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
			Node 		*tree = parser.parse();
            // if (interpreter.getCurrent_token().getType() != EOL)
			// 	interpreter.error();
			
			print_btree(tree);
			clear_btree(tree);
			tree = NULL;
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