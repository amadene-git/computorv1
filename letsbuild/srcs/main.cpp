#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cctype>

#include "./Token_type.hpp"
#include "./Number.hpp"
#include "./Node.hpp"
#include "./Token.hpp"
#include "./Lexer.hpp"
#include "./Parser.hpp"
#include "./Interpreter.hpp"



std::ostream	&operator<<(std::ostream &out, Number const &src)
{
	out << src.getInteger();

	return (out);
}
using namespace std;




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
			Coefficient		result = interpreter.interpret();
			
			cout << result << endl; 
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

}