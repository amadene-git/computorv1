#ifndef NODE_HPP
# define NODE_HPP

# include <iostream>

# include "./Token.hpp"

class Node
{
public:
	Token	data;
	Node	*left;
	Node	*right;
	
	Node(Token value, Node *_left = NULL, Node *_right = NULL);
	Node(Node const &src);
	~Node();

	Node	&operator=(Node const &rhs);
};

ostream	&operator<<(ostream &out, Node const &src);


void	print_btree(ostream &out, Node const *root = NULL, int a = 0, int lvl = 0, int max = -1);
void	clear_btree(Node *root);

#endif
