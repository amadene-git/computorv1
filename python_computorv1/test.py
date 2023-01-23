#!/bin/env python3

from main import *
from random import randint

class GenExpr(object):
    def __init__(self):
        self.text = ""
        self.count = 0

    def coeff(self):
        
        i = randint(0,1)
        
        if randint(0,1) == 1:
            self.text += " " + str(randint(-1000, 1000)) + " "
        else :
            self.text += " x"
            

    def factor(self):
        
        
        if randint(0, 1) == 1 and self.count < self.deep:
            self.text += " ("
            self.expr()
            self.text += ") "
        else:
            self.coeff()
    def expo(self):
        self.factor()
        if randint(0, 1) == 1:

            self.text += "^"
            self.text += " " + str(randint(-10, 10)) + " "

    def term(self):
        
        self.factor()
        i = randint(0, 2)
        while i > 0:
            if i == 1:
                self.text += " * "
            elif i == 2:
                self.text += " / "
            self.factor()
            i = randint(0, 2)

    def expr(self):

        self.count += 1
        self.term()

        i = randint(0, 2)
        while i > 0:
            if i == 1:
                self.text += " + "
            elif i == 2:
                self.text += " - "
            self.term()
            i = randint(0, 2)
    


    def generate(self, deep = 10):
        self.count = 0
        self.deep = deep
        self.expr()
        self.text += " = "
        self.expr()

        return self.text


    def simplegen2(self):
        self.text += str(randint(-100000, 100000))
        self.text += "x^2 + "
        self.text += str(randint(-100000, 100000))
        self.text += "x + "
        self.text += str(randint(-100000, 100000))
        
        self.text += " = "

        self.text += str(randint(-100000, 100000))
        self.text += "x^2 + "
        self.text += str(randint(-100000, 100000))
        self.text += "x + "
        self.text += str(randint(-100000, 100000))

        return self.text

    def simplegen1(self):
        self.text += str(randint(-100000, 100000))
        self.text += "x + "
        self.text += str(randint(-100000, 100000))
        
        self.text += " = "

        self.text += str(randint(-100000, 100000))
        self.text += "x + "
        self.text += str(randint(-100000, 100000))

        return self.text



if __name__ == "__main__":
    if len(sys.argv) == 1:
        print(GenExpr().generate())
    if len(sys.argv) == 2 and sys.argv[1] == "simplegen2":
        print(GenExpr().simplegen2())
    elif len(sys.argv) == 2 and sys.argv[1] == "simplegen1":
        print(GenExpr().simplegen1())
    elif len(sys.argv) == 2:
        print(GenExpr().generate(deep = int(sys.argv[1])))



    