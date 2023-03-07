class Number(object):
    def __init__(self, num = 0, denom = 1): # ne gere pas les float
        if denom == 0:
            raise Exception(f"Number.__init__ error: divide by zero'")
            
        self.num = num
        self.denom = denom
        
        # algo d'Euclide pour reduire la fraction au pgcd
        while denom != 0:
            t = denom
            denom = num % denom
            num = t
        self.num //= num
        self.denom //= num
        
        if self.denom < 0:
            self.denom *= -1
            self.num *= -1



    def __eq__(self, rhs):

        if isinstance(rhs, int):
            return self.num == float(rhs)
        
        if not isinstance(rhs, Number):
            raise Exception(f"Number.__eq__ error: unsupported operand type(s) for ==: 'Number' and '{type(rhs)}'")

        if self.num == rhs.num and self.denom == rhs.denom:
            return True
        else:
            return False

    def __ne__(self, rhs):
        return not self == rhs

    def __gt__(self, rhs):
        return self.num * rhs.denom > rhs.num * self.denom
    
    def __le__(self, rhs):
        return self.num * rhs.denom <= rhs.num * self.denom
    
    def __ge__(self, rhs):
        return self.num * rhs.denom >= rhs.num * self.denom
    

    def __lt__(self, rhs):
        return self.num * rhs.denom < rhs.num * self.denom

    def __hash__(self):
        return self.__str__().__hash__()
	
    def __add__(self, rhs):
        if not isinstance(rhs, Number):
            raise Exception(f"Number.__add__ error: unsupported operand type(s) for +: 'Number' and '{type(rhs)}'")
        return Number(self.num * rhs.denom + self.denom * rhs.num, self.denom * rhs.denom)

    def __sub__(self, rhs):
        if not isinstance(rhs, Number):
            raise Exception(f"Number.__sub__ error: unsupported operand type(s) for -: 'Number' and '{type(rhs)}'")
        return Number(self.num * rhs.denom - self.denom * rhs.num, self.denom * rhs.denom)

    def __mul__(self, rhs):
        if not isinstance(rhs, Number):
            raise Exception(f"Number.__mul__ error: unsupported operand type(s) for *: 'Number' and '{type(rhs)}'")
        return Number(self.num * rhs.num, self.denom * rhs.denom)

    def __truediv__(self, rhs):
        if not isinstance(rhs, Number):
            raise Exception(f"Number.__div__ error: unsupported operand type(s) for /: 'Number' and '{type(rhs)}'")
        return Number(self.num * rhs.denom, self.denom * rhs.num)

    def int_power(self, a, b): 
        if not isinstance(a, int)\
        or not isinstance(b, int):
            raise Exception("Number.int_power error: int arg is required")

        ret = 1
        if b > 0:
            while b > 0:
                ret *= a
                b -= 1
            return Number(ret)
        else:
            while b < 0:
                ret *= a
                b += 1
            return Number(1, ret)


#   (a/b)^(c/d) = (a^(c/d) / b^(c/d))   <- essayer de gerer ca 
#   a^(b/c) = sqrt[c]{a^b}

#   (a/b)^c = a^c / b^c                 <- au lieu de ca
    def __pow__(self, rhs):
        if not isinstance(rhs, Number):
            raise Exception(f"Number.__pow__ error: unsupported operand type(s) for **: 'Number' and '{type(rhs)}({rhs})'")
        if rhs.denom != 1:
            raise Exception("Number.__pow__ error: cannot solve a^(b/c) ... yet")

        if rhs.num == 0:
            return Number(1)
        if self.num == 0:
            return Number(0)


        return self.int_power(self.num, rhs.num) / self.int_power(self.denom, rhs.num)


    def __str__(self):
        ret = f"{self.num}"
        if self.denom != 1:
            ret += f"/{self.denom}"
        return ret

    def __repr__(self):
        return self.__str__()
