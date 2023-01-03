from Token import Token


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
        return (int(ret))

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

            self.error()
        return Token(EOF, None)

