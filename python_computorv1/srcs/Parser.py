from srcs.Lexer import *
from srcs.BTree import *

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
            ret = Node(data = Token(EQUAL, '='), left=ret, right=self.expr())        
        if self.current_token.type != EOF:
            self.error(f"Unexpected token '{self.current_token.type}'")
        return ret
