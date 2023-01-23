from srcs.Number import *
from srcs.utils import *

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

        for i in sorted(self.dict_x):
            sign = 1
            if len(ret) > 2 and self.dict_x[i].num < 0:
                ret = ret[:-2]
                ret += "- "
                sign = -1
            if i == 0:
                ret += f"{self.dict_x[i] * Number(sign)} + "
            else:
                if self.dict_x[i] == -1 and i == sorted(self.dict_x)[0]:
                    ret += "-x"
                elif self.dict_x[i] == 1 or self.dict_x[i] == -1:
                    ret += "x"
                else:
                    ret += f"{self.dict_x[i] * Number(sign)}x"
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

