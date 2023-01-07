#ifndef UTILS_HPP 
# define UTILS_HPP
 
# include <string>
# include <sstream>

using namespace std;

template<class T> 	struct is_char 			: false_type {};
template<>			struct is_char<char>	: true_type {};

template<class T> 	struct is_integer 			: false_type {};
template<>			struct is_integer<int>		: true_type {};
template<>			struct is_integer<long int>	: true_type {};

template<class T> 	struct is_float 				: false_type {};
template<>			struct is_float<float>			: true_type {};
template<>			struct is_float<double>			: true_type {};
template<>			struct is_float<long double>	: true_type {};

template<class T>
string	to_str(T value)
{
	stringstream ss;
	ss << value;
	
	return (ss.str());
}



#endif