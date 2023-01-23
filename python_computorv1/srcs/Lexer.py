from srcs.utils import *
from srcs.Coeff import *
from srcs.Number import *


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
        if self.current_char == POINT:
            ret2 = ""
            self.advance()
        while self.current_char is not None\
        and self.current_char.isdigit():
            ret2 += self.current_char
            self.advance()
        
        if 'ret2' in locals() and len(ret) == 0:
            self.error("invalid float")
        elif 'ret2' in locals():
            return Coeff({Number(0): Number(int(ret + ret2), Number.int_power(None, 10, len(ret2)).num)})



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
