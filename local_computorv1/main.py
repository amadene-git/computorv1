INTEGER = 'INTEGER'
PLUS    = 'PLUS'
MINUS   = 'MINUS'
MUL     = 'MUL'
DIV     = 'DIV'
EOF     = 'EOF'
LPAR    = '('
RPAR    = ')'
X       = 'X'
EXPO	= '^'

# import argparse
# import textwrap
import os

# from spi import PLUS, MINUS, MUL, DIV, INTEGER, LPAREN, RPAREN, Lexer

class Number(object):
    def __init__(self, num = 0, denom = 1):
        self.num = num
        self.denom = denom
    
    def __add__(self, rhs):
        if not isinstance(rhs, Number):
            raise Exception("Number add error")
        return Number(self.num * rhs.denom + self.denom * rhs.num, self.denom * rhs.denom)

    def __sub__(self, rhs):
        if not isinstance(rhs, Number):
            raise Exception("Number sub error")
        return Number(self.num * rhs.denom - self.denom * rhs.num, self.denom * rhs.denom)

    def __mul__(self, rhs):
        if not isinstance(rhs, Number):
            raise Exception("Number mul error")
        return Number(self.num * rhs.num, self.denom * rhs.denom)

    def __truediv__(self, rhs):
        if not isinstance(rhs, Number):
            raise Exception("Number div error")
        return Number(self.num * rhs.denom, self.denom * rhs.num)


    def __str__(self):
        ret = f"{self.num}"
        if self.denom != 1:
            ret += f"/{self.denom}"
        return ret

    def __repr__(self):
        return self.__str__()



class Coeff(object):
    def __init__(self, dict_x):
        if not isinstance(dict_x, dict):
            print(type(dict_x))
            raise Exception("Coeff error init")
        self.dict_x = dict_x

    def __str__(self):
        ret = ""
        for i, j in self.dict_x.items():
            ret += f"{j}x^{i} + "
        return ret[:-3]

    def __repr__(self):
        return self.__str__()

    def __add__(self, rhs):
        ret = {}

        for i in self.dict_x.keys():
            if i in rhs.dict_x.keys():
                print(f"ret: [{i}]{rhs.dict_x[i]}")
                ret[i] = self.dict_x[i] + rhs.dict_x[i]
            else:
                ret[i] = self.dict_x[i]
        for i in rhs.dict_x.keys():
            if i not in self.dict_x.keys():
                print(f"rhs: [{i}]{rhs.dict_x[i]}")
                ret[i] = rhs.dict_x[i]
        print(ret)

        return Coeff(ret)

    def __sub__(self, rhs):
        ret = {}

        for i in self.dict_x.keys():
            if i in rhs.dict_x.keys():
                ret[i] = self.dict_x[i] - rhs.dict_x[i]
            else:
                ret[i] = self.dict_x[i]
        for i in rhs.dict_x.keys():
            if i not in self.dict_x.keys():
                ret[i] = rhs.dict_x[i]

        return Coeff(ret)

    def __mul__(self, rhs):
        ret = {}

        for i, j in self.dict_x.items():
            for k, n in rhs.dict_x.items():
                if i + k in ret.keys():
                    ret[i + k] += j * n
                else:
                    ret[i + k] = j * n
        return Coeff(ret)


    def __truediv__(self, rhs):
        ret = {}

        for i, j in self.dict_x.items():
            for k, n in rhs.dict_x.items():
                if i + k in ret.keys():
                    ret[i - k] += j / n
                else:
                    ret[i - k] = j / n
        return Coeff(ret)


# from Token import Token
class Token(object):
    def __init__(self, type, value):
        self.type = type
        self.value = value

    def __str__(self):
        return f'Token({self.type}, {repr(self.value)})'

    def __repr__(self):
        return self.__str__()

# from Lexer import Lexer
class Lexer(object):
    def __init__(self, text):
        self.text = text
        self.pos = 0
        self.current_char = text[self.pos]

    def error(self):
        raise Exception('Error Lexer')

    def advance(self):
        self.pos += 1

        if self.pos >= len(self.text):
            self.current_char = None
        else:
            self.current_char = self.text[self.pos]


    def skip_whitespace(self):
        while self.current_char is not None\
        and self.current_char.isspace():
            self.advance()


    def integer(self):
        ret = ""
        
        while self.current_char is not None\
        and self.current_char.isdigit():
            ret += self.current_char
            self.advance()
        return (Coeff({0: Number(int(ret))}))

    def get_next_token(self):
        while self.current_char is not None:
            
            if self.current_char.isspace():
                self.skip_whitespace()
                continue

            if self.current_char.isdigit():
                return Token(INTEGER, self.integer())

            if self.current_char == '+':
                self.advance()
                return Token(PLUS, '+')

            if self.current_char == '-':
                self.advance()
                return Token(MINUS, '-')
            
            if self.current_char == '*':
                self.advance()
                return Token(MUL, '*')
            
            if self.current_char == '/':
                self.advance()
                return Token(DIV, '/')

            if self.current_char == '(':
                self.advance()
                return Token(LPAR, '(')

            if self.current_char == ')':
                self.advance()
                return Token(RPAR, ')')
            
            if self.current_char == 'X' or self.current_char == 'x':
                self.advance()
                return Token(X, Coeff({1: Number(1)}))
            
            if self.current_char == '^':
                self.advance()
                return Token(EXPO, '^')
            self.error()
        return Token(EOF, None)



# from BTree import Node, print_btree
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
        os.system(f"dot -Tpng -o tree.png tmp.dot")
        os.system(f"open tree.png")
        os.system(f"rm -rf tmp.dot")

def print_btree(root):
    BTree(root).print_btree()

class Parser(object):

    def __init__(self, lexer):
        self.lexer = lexer
        self.current_token = lexer.get_next_token()


    def error(self):
        raise Exception('Error Interpreter')


    def eat(self, token_type):
        # print(f"EAT {self.current_token} -> {token_type}")
        if self.current_token.type == token_type:
            self.current_token = self.lexer.get_next_token()
        else:
            self.error()

    def coeff(self):
        
        token = self.current_token
        if token.type == INTEGER:
            self.eat(INTEGER)
            if self.current_token.type == X:
                self.eat(X)
                token.value = Coeff({1: token.value.dict_x[0]})
            return Node(token)
        if token.type == X:
            self.eat(X)
            return Node(token)
        self.error()

    # def expo(self):
    #     node = self.coeff()
    #     while self.current_token.type == EXPO:
    #         node = Node(data = self.current_token, left = node, right = self.integer())	
    def factor(self):
        
        token = self.current_token
        
        if token.type == LPAR:
            self.eat(LPAR)
            node = self.expr()
            self.eat(RPAR)
            return node

        return self.coeff()

    def term(self):
        
        node = self.factor()
        while self.current_token.type in (MUL, DIV):
            token = self.current_token
            if token.type == MUL:
                self.eat(MUL)
            if token.type == DIV:
                self.eat(DIV)
            node = Node(data = token, left = node, right = self.factor())

        return node

    def expr(self):

        node = self.term()
        while self.current_token.type in (PLUS, MINUS):
            token = self.current_token
            if token.type == PLUS:
                self.eat(PLUS)
            elif token.type == MINUS:
                self.eat(MINUS)
            node = Node(data = token, left = node, right = self.term())

        return node

    def parse(self):
        return self.expr()


class Interpreter(object):
    def __init__(self, parser):
        self.parser = parser
        self.tree = None
    
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


    def interpret(self):
        self.tree = self.parser.parse()
        self.calcul(self.tree)
        return self.tree.data.value



def main():
    while True:
        try:
            text = input('calc> ')
        except EOFError:
            break
        if not text:
            continue
        lexer = Lexer(text)
        parser = Parser(lexer)
        interpreter = Interpreter(parser)
        result = interpreter.interpret()
        print_btree(interpreter.tree)
        print(result)



if __name__ == '__main__':
    main()
