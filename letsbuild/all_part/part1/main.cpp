#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>

using namespace std;

#define INTEGER "INTEGER"
#define PLUS    "PLUS"
#define EOL     "EOL"
#define ERR     "ERR"

class   Token
{
    private:
        
        
        string  _type;
        char    _value;

    public:
        Token(): _type(string()), _value(char())
        {};
        Token(string type, char value) : _type(type), _value(value)
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
            return (_type + ", '" + _value + "'");
        };

        string repr()
        {
            return str();
        }

        string  getType()   const { return (_type); };
        char    getValue()  const { return (_value); };

        void    setType(const string type) { _type = type; };
        void    setValue(const char value) { _value = value; };

};

class   Interpreter
{
    private:
        Interpreter()
        {};

        string  _text;
        int     _pos;
        Token   _current_token;

    public:

        Interpreter(string text) : _text(text), _pos(0)
        {};

        void    error()
        {
            throw runtime_error("Error parsing input");
        };

        Token    get_next_token()
        {
            if (_pos >= _text.length())
                return (Token(EOL, 0));

            char current_char = _text[_pos];
            // std::cout << current_char << " char: " << int(current_char) << "  pos: " << _pos << "  "<< text.length() << std::endl;

            if (isdigit(current_char))
            {
               
                ++_pos;
                return (Token(INTEGER, current_char));
            }
            else if (current_char == '+')
            {
                ++_pos;
                return (Token(PLUS, current_char));
            }
            else
            {
                this->error();
                return (Token(ERR, 0));
            }
        };

        void    eat(string token_type)
        {
            if (_current_token.getType() == token_type)
                _current_token = this->get_next_token();
            else
                this->error();
        }

        int     expr()
        {
            _current_token = this->get_next_token();

            Token left = _current_token;
            this->eat(INTEGER);

            Token op = _current_token;
            this->eat(PLUS);

            Token right = _current_token;
            this->eat(INTEGER);

            int result = int((left.getValue() - '0') + (right.getValue() - '0'));

            return (result);
        }


        string  getText()           const   { return (_text); };
        int     getPos()            const   { return (_pos); };
        Token   getCurrent_token()  const   { return (_current_token); };

        void    setText(string text)                    { _text = text; };
        void    setPos(int pos)                         { _pos = pos; };
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
            cin >> input;

            if (!input.length())
                continue;

            Interpreter interpreter(input);
            int result = interpreter.expr();
            cout << result << endl;  
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

}