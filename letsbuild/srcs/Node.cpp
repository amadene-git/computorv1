#include "./Node.hpp"

//CONSTRUCTORS
Node::Node(Token value, Node *_left, Node *_right)
: data(value), left(_left), right(_right) {}

Node::Node(Node const &src)
{
	*this = src;
}

Node::~Node() {}


//OVERLOADS
Node	&Node::operator=(Node const &rhs)
{
	if (this != &rhs)
	{
		this->data	= rhs.data; 
		this->left	= rhs.left;
		this->right	= rhs.right;
	}
	return (*this);
}


//OSTREAM
ostream	&operator<<(ostream &out, Node const &src)
{
	print_btree(out, &src);
	return (out);
}


//EXTERNAL FUNCTIONS
void	print_btree(ostream &out, Node const *root, int a, int lvl, int max)
{
	if (!root)
	{
		cerr << "error root null" << endl;
		return;
	}
	if (root->right && (lvl <= max || max == -1))
		print_btree(out, root->right, 0, lvl + 1, max);
	for (int k = 1	; k < lvl; k++)
		for (int i = 0; i < 20; i++)
			out << " ";
	if (lvl)
	{
		for (int i = 0; i < 20 - 5; i++)
			out << " ";
		if (a)
			out << "\\";
		else
			out << "/";
	}
	out << "---<" << lvl << ">";
	out << "[" << root->data << "]";
	if (root->right && root->left)
		out << " <";
	else
	{
		if (root->right)
			out << " /";
		if (root->left)
			out << " \\";
	}
	out << endl;
	if (root->left && (lvl <= max || max == -1))
		print_btree(out, root->left, 1, lvl + 1, max);
}

void	clear_btree(Node *root)
{
	if (root->left)
		clear_btree(root->left);
	if (root->right)
		clear_btree(root->right);
	delete root;
}
