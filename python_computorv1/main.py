from srcs.utils import *
from srcs.Number import *
from srcs.BTree import *

NUMBERNULL = Number(0) # constant null
class Coeff(object):
    
    def __init__(self, dict_x):
        if not isinstance(dict_x, dict):
            raise Exception("Coeff error init")
        
        try:
            for i, j in dict_x.items():
                if j == 0:
                    dict_x.pop(i)
        except RuntimeError:
            dict_x = {NUMBERNULL : NUMBERNULL}
        
        self.dict_x = dict_x

    def __str__(self):
        ret = ""
        for i, j in self.dict_x.items():
            
            if len(ret) > 2 and j.num < 0:
                ret = ret[:-2]
                ret += "+ "
            if i == 0:
                ret += f"{j} + "
            else:
                if j == 1:
                    ret += "x"
                else:
                    ret += f"{j}x"
                if i != 1:
                    ret += f"^{i}"
                ret += " + "
                
        return ret[:-3]

    def __repr__(self):
        return self.__str__()

    def __add__(self, rhs):
        ret = {}

        for i in self.dict_x.keys():
            if i in rhs.dict_x.keys():
                ret[i] = self.dict_x[i] + rhs.dict_x[i]
            else:
                ret[i] = self.dict_x[i]
        for i in rhs.dict_x.keys():
            if i not in self.dict_x.keys():
                ret[i] = rhs.dict_x[i]

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
                ret[i] = rhs.dict_x[i] * Number(-1)

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

    def __pow__(self, rhs):
        if not isinstance(rhs, Coeff):
            raise Exception(f"Coeff.__pow__ error: unsupported operand type(s) for **: 'Coeff' and '{type(rhs)}'")
        
        # on verifie qu'i n'y a pas de x dans rhs
        if len(rhs.dict_x) != 1\
        or NUMBERNULL not in rhs.dict_x.keys():
            raise Exception("Coeff.__pow__ error: cannot solve a^x ... yet")

        # on verifie qu'il n'y a qu'un coeff dans self
        if len(self.dict_x) != 1:
            raise Exception("Coeff.__pow__ error: cannot solve (a + bx + cx^2 +...)^n ... yet")


        # cas a^b
        if NUMBERNULL in self.dict_x.keys():
            return Coeff({NUMBERNULL : self.dict_x[NUMBERNULL] ** rhs.dict_x[NUMBERNULL]})
        
        # cas (x^n)^k = x^(n + k)
        else:
            return Coeff({list(self.dict_x.keys())[0] * rhs.dict_x[NUMBERNULL] : list(self.dict_x.values())[0]})



class Token(object):
    def __init__(self, type, value):
        self.type = type
        self.value = value

    def __str__(self):
        return f'Token({self.type}, {repr(self.value)})'

    def __repr__(self):
        return self.__str__()

class Lexer(object):
    def __init__(self, text):
        self.text = text
        self.pos = 0
        self.current_char = text[self.pos]

    def error(self, msg = ""):
        raise Exception(f'Error Lexer : {msg}')

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
        return (Coeff({Number(0): Number(int(ret))}))

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
                return Token(X, Coeff({Number(1): Number(1)}))
            
            if self.current_char == '^':
                self.advance()
                return Token(POWER, '^')
        
            self.error(f"Bad character {self.current_char}")
        
        return Token(EOF, None)





class Parser(object):

    def __init__(self, lexer):
        self.lexer = lexer
        self.current_token = lexer.get_next_token()


    def error(self, msg = ""):
        raise Exception(f'Error Parser: {msg}')


    def eat(self, token_type):
        if self.current_token.type == token_type:
            self.current_token = self.lexer.get_next_token()
        else:
            self.error(f"Unexpected '{self.current_token.type}' token instead of '{token_type}' token ")

    def coeff(self):
        
        token = self.current_token
        if token.type == INTEGER:
            self.eat(INTEGER)
            if self.current_token.type == X:
                self.eat(X)
                token.value = Coeff({Number(1): token.value.dict_x[NUMBERNULL]})
            return Node(token)
        if token.type == X:
            self.eat(X)
            return Node(token)
        self.error(f"Unexpected token '{token.type}'")
        

    def factor(self):
        
        token = self.current_token
        
        if token.type == LPAR:
            self.eat(LPAR)
            node = self.expr()
            self.eat(RPAR)
            return node

        return self.coeff()

    def expo(self):
        node = self.factor()
        while self.current_token.type == POWER:
            token = self.current_token
            self.eat(POWER)
            node = Node(data = token, left = node, right = self.factor())	

        return node

    def term(self):
        
        node = self.expo()
        while self.current_token.type in (MUL, DIV):
            token = self.current_token
            if token.type == MUL:
                self.eat(MUL)
            if token.type == DIV:
                self.eat(DIV)
            node = Node(data = token, left = node, right = self.expo())

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
        ret = self.expr()
        if self.current_token.type != EOF:
            self.error(f"Unexpected token '{self.current_token.value}'")
        return ret


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
        elif root.data.type == POWER:
            root.data.value = root.left.data.value ** root.right.data.value
            

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
        if text == "print":
            if 'interpreter' in locals() and not interpreter.tree is None:
                print_btree(interpreter.tree)
            else:
                print("Sorry, sorry there are no trees to display")
        else:
            try:
                lexer = Lexer(text)
                parser = Parser(lexer)
                interpreter = Interpreter(parser)
                result = interpreter.interpret()
                print(result)
            except Exception as e:
                print(e)



if __name__ == '__main__':
    main()
