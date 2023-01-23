#!/bin/env python3

import sys

from srcs.utils import *
from srcs.Number import *
from srcs.BTree import *
from srcs.Coeff import *
from srcs.Lexer import *
from srcs.Parser import *
from srcs.Interpreter import *


def print_result(root):

    result = root.data.value.dict_x

    degree = list(result.keys())[0]
    for i in result.keys():
        if i.denom != 1 or i.num < 0:
            degree = None
            break
        if i > degree and i != NUMBERNULL:
            degree = i
    
    # cas d'une expresssion
    if root.data.type != EQUAL:
        # print("Expression :")
        if degree == 0:
            print(f"\nresult: {root.data.value}")
            if result[NUMBERNULL].denom != 1:
                print(f"      ≈ {result[NUMBERNULL].num / result[NUMBERNULL].denom}")
        else:
            print(f"\nReduced form: {root.data.value}")
            print(f"Polynomial degree: {degree}")
        
    # cas d'une equation
    else:
        # print("Equation :")
        print(f'\nReduced form: {root.left.data.value} = {root.right.data.value}')
        
        # equation non polynomiale 
        if degree is None or degree > Number(2):
            print(f"              {root.data.value} = 0\n")
            print(f"Polynomial degree: {degree}\n")
            
            print(f"Cannot solve this equation, sorry...")
            
        # equation de la forme a = b
        elif degree == 0:

            
            print(f"\nPolynomial degree: {degree}\n")
            
            
            # ax^n = bx^n avec n != 0
            if not NUMBERNULL in root.left.data.value.dict_x.keys():
                print("The expression is always true, x can be all reals") 
            elif result[NUMBERNULL] != NUMBERNULL:
                print(f"The expression is false")
            else:
                print("The expression is true")

        # equation de la forme ax + b
        elif degree == 1\
        and len(result.keys()) == 2:
            
            print(f"              {root.data.value} = 0")
            print(f"              x = {result[NUMBERNULL] * Number(-1)} / {result[Number(1)]}")
            print(f"\nPolynomial degree: {degree}\n")
            
            solution = result[NUMBERNULL] / result[Number(1)] * Number(-1)
            
            print(f"The solution is: {solution}")
            if solution.denom != 1:
                print(f" ≈ {solution.num / solution.denom}")
        
        # equation premier degre invalid
        elif degree == 1:
            print(f"              {root.data.value} = 0\n")
            
            
            print(f"Polynomial degree: {degree}\n")
            print("The solution is zero")
        
        #eqution second degre
        elif degree == 2:
                
            # calcul de delta
            delta_dict = {}
            if Number(0) in result.keys():
                delta_dict[0] = result[Number(0)]
            else:
                delta_dict[0] = NUMBERNULL

            if Number(1) in result.keys():
                delta_dict[1] = result[Number(1)]
            else:
                delta_dict[1] = NUMBERNULL

            if Number(2) in result.keys():
                delta_dict[2] = result[Number(2)]
            else:
                delta_dict[2] = NUMBERNULL
            
            delta = delta_dict[1] ** Number(2) - Number(4) * delta_dict[2] * delta_dict[0]


            print(f"              {root.data.value} = 0")
            print(f"\nPolynomial degree: {degree}")
            print(f"\nDelta = {delta}")
            
            if delta.num < 0:
                print(f"There are no solutions in this equation in the reals set")
            elif delta == 0:
                solution = delta_dict[1] * Number(-1)
                solution /= delta_dict[2] * Number(2)
                print(f"The solution is : {solution}")
            
            
            elif delta.num > 0:

                i = 0
                with timeout(5):    
                    sqrt_delta = my_sqrt(delta)
                    i = 1
                if i == 0:
                    print(f"\nError : Cannot calulate √{delta}")

                print(f"The 2 solutions are :")
                print("\t"*3 + f"x1 = ({Number(-1) *  delta_dict[1]} -  √({delta})) / ({Number(2) * delta_dict[2]})")
                print("\t"*3 + f"x2 = ({Number(-1) *  delta_dict[1]} +  √({delta})) / ({Number(2) * delta_dict[2]})\n")


                if i == 1:
                    x1 = Number(-1) * delta_dict[1] - sqrt_delta
                    x1 /= Number(2) * delta_dict[2]    
                    x2 = Number(-1) * delta_dict[1] + sqrt_delta
                    x2 /= Number(2) * delta_dict[2]
                    print("\t"*3 + f"x1 = ({Number(-1) *  delta_dict[1]} -  {sqrt_delta.num / sqrt_delta.denom}) / ({Number(2) * delta_dict[2]})")
                    print("\t"*3 + f"x2 = ({Number(-1) *  delta_dict[1]} +  {sqrt_delta.num / sqrt_delta.denom}) / ({Number(2) * delta_dict[2]})\n")
 
                    if x1.denom != 1 or x2.denom != 1:
                        print("\t"*3 + f"x1 = {x1.num / x1.denom}")
                        print("\t"*3 + f"x2 = {x2.num / x2.denom}")


def launch(text):
    try:
        with timeout(20):
            i = 0
            lexer = Lexer(text)
            parser = Parser(lexer)
            interpreter = Interpreter(parser)
            result = interpreter.interpret()
            print_result(result)
            i = 1
            return interpreter
        if i == 0:
            print("Error : timeout")
    except Exception as e:
        print(e)
        return None
    



def main(text = None):
    
    if not text is None:
        launch(preparse(text))
    else:
        while True:
            try:
                text = input('Computor > ')
            except (EOFError, KeyboardInterrupt):
                break
            if not text or text.isspace():
                continue
            if not text.isascii():
                print("Error: invalid character")
                text = None
                interpreter = None
                continue
            if text in ("print_btree", "print_steps"):
                if 'interpreter' in locals() and not interpreter is None:
                    if text == "print_btree":
                        print_btree(interpreter.tree)
                    elif text == "print_steps": 
                        print(f'\n{interpreter.steps}', end="")
                else:
                    print("Sorry, there are no trees to display")
            elif text in ("exit", "quit"):
                break
            
            else:
                interpreter = launch(preparse(text))

            print("_________________________________________\n")
        print("\nGoodbye !")
        os.system(f'rm -rf tree.png;')



if __name__ == '__main__':
    if len(sys.argv) == 1:
        main()
    elif len(sys.argv) == 2:
        print("Computor >", sys.argv[1], "\n")
        main(sys.argv[1])
    else:
        a = my_sqrt(Number(123))
        print(a)
        print(a.num / a.denom)
