from srcs.utils import *
from srcs.Number import *
from srcs.BTree import *

import sys

NUMBERNULL = Number(0) # constant null
class Coeff(object):
    
    def __init__(self, dict_x):
        if not isinstance(dict_x, dict):
            raise Exception("Coeff error init")
        
        self.dict_x = {}
        for i, j in dict_x.items():
            if j != 0:
                self.dict_x[i] = j
        
        if len(self.dict_x) == 0:
            self.dict_x = {NUMBERNULL : NUMBERNULL}
        

    def __str__(self):
        ret = ""
        for i, j in self.dict_x.items():
            if len(ret) > 2 and j.num < 0:
                ret = ret[:-2]
                ret += "+ "
            if i == 0:
                ret += f"{j} + "
            else:
                if j == Number(1):
                    ret += "x"
                else:
                    ret += f"{j}x"
                if i != Number(1):
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
                    if i - k in ret.keys():
                        ret[i - k] += j / n
                    else:
                        ret[i - k] = j / n
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

        # on gere (a+b)² = a² + 2ab + b² -> a etendre au cas G avec le triangle de pascal
        if len(self.dict_x) == 2\
        and NUMBERNULL in rhs.dict_x.keys()\
        and rhs.dict_x[NUMBERNULL] == Number(2):
            
            a = Coeff({list(self.dict_x.keys())[0] : list(self.dict_x.values())[0]}) 
            b = Coeff({list(self.dict_x.keys())[1] : list(self.dict_x.values())[1]}) 
            two = Coeff({Number(0) : Number(2)})
            return (a ** two) + (two * a * b) + b ** two


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

            if self.current_char == '=':
                self.advance()
                return Token(EQUAL, '=')
        
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
        
        sign = 1

        if self.current_token.type in (PLUS, MINUS):
            if self.current_token.type == MINUS:
                self.eat(MINUS)
                sign = -1
            elif self.current_token.type == PLUS:
                self.eat(PLUS)

        token = self.current_token
        if token.type == INTEGER:
            self.eat(INTEGER)
            token.value.dict_x[NUMBERNULL] *= Number(sign)
            return Node(token)
        elif token.type == X:
            self.eat(X)
            token.value.dict_x[Number(1)] *= Number(sign)
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
        if self.current_token.type == EQUAL:
            self.eat(EQUAL)
            ret = Node(data = Token(EQUAL, EQUAL), left=ret, right=self.expr())        
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
        elif root.data.type == EQUAL:
            root.data.value = root.left.data.value - root.right.data.value

    def interpret(self):
        self.tree = self.parser.parse()
        self.calcul(self.tree)
        return self.tree


def my_sqrt(b):
    if b.num == Number(1) and b.denom == Number(1):
        return b
    a = Number(1)
    e = Number(1)
    while len(str(e.denom)) - len(str(e.num)) < 20:
        # print("lol")
        fa = b / a
        fa += a
        fa /= Number(2)
        if fa > a:
            e = fa - a
        else:
            e = a - fa
        a = fa
        # print(a)
    
    return a



def print_result(root):
    
    

    n = list(root.data.value.dict_x.keys())[0]
    for i in root.data.value.dict_x.keys():
        if i > n and i != NUMBERNULL:
            n = i

    
    # cas d'une expresssion
    if root.data.type != EQUAL:
        # print("Expression :")
        print(f"Reduced form: {root.data.value}")
        print(f"Polynomial degree: {n}")
    # cas d'une equation
    else:
        # print("Equation :")
        
        # equation de la forme a = b
        if n == Number(0)\
        and len(root.data.value.dict_x.keys()) == 1:
            print(f"Reduced form: {root.data.value} = 0")
            print(f"Polynomial degree: {n}")
            if root.data.value.dict_x[NUMBERNULL] != NUMBERNULL:
                print(f"There are no solutions in this equation, the calcul will be always false")
            else:
                print("Each real number is a solution, the calcul will be always true") 
       
       
        # equation de la forme ax + b
        elif n == Number(1)\
        and len(root.data.value.dict_x.keys()) == 2\
        and Number(0) in root.data.value.dict_x.keys():
            print(f"Reduced form: {root.data.value.dict_x[Number(1)]}x = {root.data.value.dict_x[NUMBERNULL] * Number(-1)}")
            print(f"Polynomial degree: {n}")
            solution = root.data.value.dict_x[NUMBERNULL] / root.data.value.dict_x[Number(1)] * Number(-1)
            print(f"The solution is: {solution}")
            
            if solution.denom != 1:
                print(f" ≈ {solution.num / solution.denom}")
        # equation premier degre invalid, ou avec des x ^ (< 1)
        elif n == Number(1):
            # print(list(root.data.value.dict_x)[0])
            if list(root.data.value.dict_x)[0] == NUMBERNULL:
                # print(f"Value root: {root.data.value}")
                print(f"Reduced form: {root.left.data.value} = {root.right.data.value}")
                print("Each real number is a solution")
            else:
            
                print(f"Reduced form: {root.data.value} = 0")
                print("The solution is zero")
        
        elif n == Number(2)\
        and len(root.data.value.dict_x.keys()) <= 3:
            

            # on check si il n'y a pas des degres different de 0, 1 ou 2
            for i in root.data.value.dict_x.keys():
                if not i in (Number(0), Number(1), Number(2)):
                    print("second degre other case: ")
                    print(f"real Reduced form: {root.left.data.value} = {root.right.data.value}")
                    print(f"Reduced form: {root.data.value} = 0")
                    print(f"Polynomial degree: {n}")
            
            # on rempli les degres manquant avec 0
            delta_dict = {}
            if Number(0) in root.data.value.dict_x.keys():
                delta_dict[0] = root.data.value.dict_x[Number(0)]
            else:
                delta_dict[0] = NUMBERNULL

            if Number(1) in root.data.value.dict_x.keys():
                delta_dict[1] = root.data.value.dict_x[Number(1)]
            else:
                delta_dict[1] = NUMBERNULL

            if Number(2) in root.data.value.dict_x.keys():
                delta_dict[2] = root.data.value.dict_x[Number(2)]
            else:
                delta_dict[2] = NUMBERNULL
            
            delta = delta_dict[1] ** Number(2) - Number(4) * delta_dict[2] * delta_dict[0]


            print(f"Reduced form: {root.data.value} = 0")
            print(f"Polynomial degree: {n}")
            print(f"Delta = {delta}")
            
            if delta.num < 0:
                print(f"There are no solutions in this equation in the reals set")
            if delta == 0:
                solution = delta_dict[1] * Number(-1)
                solution /= delta_dict[2] * Number(2)
                print(f"The solution is : {solution}")
            if delta.num > 0:
                
                with timeout(2):
                    i = 0
                    x1 = Number(-1) * delta_dict[1] - my_sqrt(delta)
                    x1 /= Number(2) * delta_dict[2]    

                    x2 = Number(-1) * delta_dict[1] + my_sqrt(delta)
                    x2 /= Number(2) * delta_dict[2]

                    print(f"The 2 solutions are : x1 = {x1} ; x2 = {x2}")
                    print(f"The 2 solutions are : x1 = {x1.num / x1.denom} ; x2 = {x2.num / x2.denom}")

                    i = 1
                if i == 0:
                    print(f"The 2 solutions are : x1 = {Number(-1) *  delta_dict[1]} -  √{delta} / {Number(2) * delta_dict[2]}")
                    print(f"                      x2 = {Number(-1) *  delta_dict[1]} +  √{delta} / {Number(2) * delta_dict[2]}")

        else:
            print("other case: ")
            print(f"real Reduced form: {root.left.data.value} = {root.right.data.value}")
            
            print(f"Reduced form: {root.data.value} = 0")
            print(f"Polynomial degree: ?")



def launch(text):
    # try:
        with timeout(20):
            i = 0
            lexer = Lexer(text)
            parser = Parser(lexer)
            interpreter = Interpreter(parser)
            result = interpreter.interpret()
            print_result(result)
            i = 1
            return interpreter.tree
        if i == 0:
            print("Error : timeout")
    # except Exception as e:
    #             print(e)
    

def preparse(text):
    i = 0
    n = len(text)

    while i < n:
        if text[i] in ('x', 'X'):
            if i != 0 and text[i - 1].isdigit():
                text = text[:i] + " * x" + text[i+1:]
        n = len(text)
        i += 1
    return text



def main(text = None):
    
    if not text is None:
        launch(preparse(text))
    else:

        while True:
            try:
                text = input('Computor > ')
            except EOFError:
                break
            if not text:
                continue
            if text == "print":
                if 'tree' in locals() and not tree is None:
                    print_btree(tree)
                else:
                    print("Sorry, sorry there are no trees to display")
            elif text in ("exit", "quit"):
                print ("Goodbye !")
                break
            
            else:
                tree = launch(preparse(text))



if __name__ == '__main__':
    if len(sys.argv) == 1:
        main()
    elif len(sys.argv) == 2:
        print("Computor >", sys.argv[1], "\n\n\n")
        main(sys.argv[1])
    else:
        a = my_sqrt(Number(123))
        print(a)
        print(a.num / a.denom)
