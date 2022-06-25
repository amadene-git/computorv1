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
		   
		   ss << "Token(" << _type << ", '" << _value << "')";
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
				
				
				this->error();
			}
			return (Token(EOL, 0));
        };


};

class   Interpreter
{
    private:

		Lexer	_lexer;
		Token	_current_token;
    
	public:

        Interpreter(Lexer lexer) : _lexer(lexer), _current_token(_lexer.get_next_token())
        {};

       void	error()
	   {
			throw runtime_error("Error Interpreter: Invalid syntax");
	   }


        void    eat(string token_type)
        {
            if (_current_token.getType() == token_type)
                _current_token = _lexer.get_next_token();
            else
                this->error();
        }

		Number	factor()
		{
			Token	token = _current_token;

			this->eat(INTEGER);
			return (token.getValue());
		}

        Number	term()
        {
			Number result = this->factor();

			while (	_current_token.getType() == MUL
			||		_current_token.getType() == DIV)
			{
				if (_current_token.getType() == MUL)
				{
					this->eat(MUL);
					result *= this->factor();
				}
				else if (_current_token.getType() == DIV)
				{
					this->eat(DIV);
					result /= this->factor();
				}
			}
			return (result);
        }

		Number	expr()
		{
			Number result = this->term();

			while (	_current_token.getType() == PLUS
			||		_current_token.getType() == MINUS)
			{
				if (_current_token.getType() == PLUS)
				{
					this->eat(PLUS);
					result += this->term();
				}
				else if (_current_token.getType() == MINUS)
				{
					this->eat(MINUS);
					result -= this->term();
				}
			}
			return (result);
			
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
				return 0;
			}
            if (!input.length())
                continue;

			Lexer		lexer(input);
            Interpreter interpreter(lexer);
            Number 		result = interpreter.expr();
            cout << result << endl;  
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }


}