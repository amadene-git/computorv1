import os
from srcs.utils import *



class Node(object):
    def __init__(self, data = None, left=None, right=None):
        self.data = data
        self.left = left
        self.right = right

    def __str__(self):
        return f'Node({self.data})'

    def __repr__(self):
        return self.__str__()



class BTree(object):
    def __init__(self, begin):
        if not isinstance(begin, Node):
            raise Exception('BTree error: must initialize with Node')
        self.begin = begin
        self.ncount = 0
        self.dotf = ''
        self.expr = ''

    def gendot(self, root = None, id = 0):

        if root is None:
            root = self.begin
        
        self.dotf += f'  node{id} [label="{root.data}"]\n'


        if root.left is not None:
            self.ncount += 1
            self.dotf += f"  node{id} -> node{self.ncount}\n"
            self.gendot(root.left, self.ncount)
        if root.right is not None:
            self.ncount += 1
            self.dotf += f"  node{id} -> node{self.ncount}\n"
            self.gendot(root.right, self.ncount)

    def print_btree(self):
        self.dotf = 'digraph astgraph {\n\
  node [shape=none, fontsize=12, fontname="Courier", height=.1];\n\
  ranksep=.5;\n\
  edge [arrowsize=.5]\n\n'

        self.gendot()

        self.dotf += "\n\n}"
        os.system(f"echo '{self.dotf}' > tmp.dot")
        os.system(f'rm -rf tree.png;')
        os.system(f"dot -Tpng -o tree.png tmp.dot")
        os.system(f'rm -rf tmp.dot')
        os.system(f'xdg-open tree.png 2> /dev/null')


    def print_expr(self, root = None):
        if root is None:
            root = self.begin
        
        if root.data.type != INTEGER and not isinstance(root.data.value, str):
            self.expr += f"{root.data.value} "
            return

        if not root.left is None:
            self.print_expr(root.left)
        
        self.expr += f"{root.data.value} "
        
        if not root.right is None:
            self.print_expr(root.right)



def print_btree(root):
    BTree(root).print_btree()


def str_expr(root):
    tree = BTree(root)
    tree.print_expr()
    return tree.expr