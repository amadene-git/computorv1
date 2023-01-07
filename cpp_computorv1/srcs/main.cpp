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
#include "./Coeff.hpp"

#include "./Pint.hpp"

std::ostream	&operator<<(std::ostream &out, Number const &src)
{
	out << src.getInteger();

	return (out);
}
using namespace std;




int main()
{
	Pint nbr(-9223372036854775807L);
	std::cout << nbr << std::endl;
	
	nbr = nbr - 11;
	std::cout << nbr << std::endl;
	// std::cout << nbr << std::endl;
	// string input;
    // while (1)
    // {
    //     try
    //     {
    //         cout << "calc> ";
    //         if (getline(cin, input, '\n').eof())
	// 		{
	// 			return (0);
	// 		}
    //         if (!input.length())
    //             continue;
	// 		if (input == "quit" || input == "exit")
	// 			return (0);

	// 		Lexer		lexer(input);
    //         Parser 		parser(lexer);
	// 		Interpreter	interpreter(parser);
	// 		Coeff		result = interpreter.interpret();
			
	// 		cout << result << endl; 
    //     }
    //     catch(const std::exception& e)
    //     {
    //         std::cerr << e.what() << '\n';
    //     }
        
    // }

    // Coeff var(5, 3);

    // cout << var << endl;

    // var += 3;

    // Coeff var2(7, 3);
    // var2 += 8;

    // cout << "var :"<< var << endl;
    // cout << "var2 :"<< var2 << endl << endl;

    // var = var + var2;

    // cout << "var :"<< var << endl;
    // cout << "var2 :"<< var2 << endl << endl;

    // var = var * var2;

    // cout << "var :"<< var << endl;
    // cout << "var2 :"<< var2 << endl <<endl;

}