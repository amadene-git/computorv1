from srcs.utils import *
from srcs.BTree import *

class Interpreter(object):
    def __init__(self, parser):
        self.parser = parser
        self.tree = None
        self.steps = ""
    
    def calcul(self, root):
        if root.left is not None:
            self.calcul(root.left)
        if root.right is not None:
            self.calcul(root.right)
        


        if root.data.type == PLUS:
            root.data.value = root.left.data.value + root.right.data.value
        elif root.data.type == MINUS:
            root.data.value = root.left.data.value - root.right.data.value
        elif root.data.type == MUL:
            root.data.value = root.left.data.value * root.right.data.value
        elif root.data.type == DIV:
            root.data.value = root.left.data.value / root.right.data.value
        elif root.data.type == POWER:
            root.data.value = root.left.data.value ** root.right.data.value
        elif root.data.type == EQUAL:
            self.steps += f"-> {root.left.data.value} - ({root.right.data.value}) = 0\n"
            self.steps += f"-> {root.left.data.value - root.right.data.value} = 0\n"
            root.data.value = root.left.data.value - root.right.data.value
        else:
            return
        if root.data.type != EQUAL:
            self.steps += f"-> {str_expr(self.tree)}\n"
        

    def interpret(self):
        self.tree = self.parser.parse()
        self.steps += f"-> {str_expr(self.tree)}\n"
        self.calcul(self.tree)
        return self.tree
