#include "./Coeff.hpp"


//CONSTRUCTORS
Coeff::Coeff()
{
    _sum = new map<Number, Number>;
}

Coeff::Coeff(Coeff const &src)
{
    _sum = new map<Number, Number>;
    *this = src;
}

Coeff::Coeff(Number nbr, Number x)
{
    _sum = new map<Number, Number>;

    (*_sum)[x] = nbr;
}


Coeff::~Coeff()
{
    delete _sum;
}

Coeff   &Coeff::operator=(Coeff const &rhs)
{
    *_sum = rhs.getSum();
    return (*this);
}


//GETTERS & SETTERS
map<Number, Number> &Coeff::getSum() const
{
    return (*_sum);
}

void            Coeff::setSum(map<Number, Number> sum)
{
    *_sum = sum;
}


//NUMBER OPERATOR OVERLOAD
Coeff   Coeff::operator+(Number const &rhs)
{
    Coeff ret = *this;
    
    ret.getSum()[0] += rhs;


    return (ret);
}
Coeff   Coeff::operator-(Number const &rhs)
{
    Coeff ret = *this;
    
    ret.getSum()[0] -= rhs;
    return (ret);
};
Coeff   Coeff::operator*(Number const &rhs)
{
    Coeff ret = *this;
    
    ret.getSum()[0] *= rhs;
    return (ret);
};
Coeff   Coeff::operator/(Number const &rhs)
{
    Coeff ret = *this;
    
    ret.getSum()[0] /= rhs;
    return (ret);
};

Coeff   &Coeff::operator+=(Number const &rhs)
{
    *this = *this + rhs;
    return (*this);
};
Coeff   &Coeff::operator-=(Number const &rhs)
{
    *this = *this + rhs;
    return (*this);
};
Coeff   &Coeff::operator*=(Number const &rhs)
{
    *this = *this + rhs;
    return (*this);
};
Coeff   &Coeff::operator/=(Number const &rhs)
{
    *this = *this + rhs;
    return (*this);
};



//COEFF OPERATOR OVERLOAD
Coeff   Coeff::operator+(Coeff const &rhs)
{
    Coeff ret = *this;

    for(map<Number, Number>::iterator it = rhs.getSum().begin(); it != rhs.getSum().end(); ++it)
        ret.getSum()[it->first] += it->second;
    return (ret);
}

Coeff   Coeff::operator-(Coeff const &rhs)
{
    Coeff ret = *this;

    for(map<Number, Number>::iterator it = rhs.getSum().begin(); it != rhs.getSum().end(); ++it)
        ret.getSum()[it->first] -= it->second;
    
    
    return (ret);
}

Coeff   Coeff::operator*(Coeff const &rhs)
{
    Coeff ret;

    if (!rhs.getSum().size())
        return (*this);
    if (!_sum->size())
        return (rhs);

    for (map<Number, Number>::iterator it = _sum->begin(); it != _sum->end(); ++it)
    {
        for(map<Number, Number>::iterator rhsit = rhs.getSum().begin(); rhsit != rhs.getSum().end(); ++rhsit)
        {
            ret.getSum()[it->first + rhsit->first] = it->second * rhsit->second;
        }
    }

    return (ret);
}

Coeff   Coeff::operator/(Coeff const &rhs)
{
    Coeff ret;

    if (!rhs.getSum().size())
        return (*this);
    if (!_sum->size())
        return (rhs);

    for (map<Number, Number>::iterator it = _sum->begin(); it != _sum->end(); ++it)
    {
        for(map<Number, Number>::iterator rhsit = rhs.getSum().begin(); rhsit != rhs.getSum().end(); ++rhsit)
        {
            if (rhsit->second)
                ret.getSum()[it->first - rhsit->first] = it->second / rhsit->second;
        }
    }

    return (ret);
}

Coeff::operator bool()
{
    for (map<Number, Number>::iterator it = _sum->begin(); it != _sum->end(); ++it)
        if (it->second)
            return (true);
    
    return (false);
} 

Coeff   Coeff::exponent(Coeff const &rhs)
{
    for(map<Number, Number>::iterator rhsit = rhs.getSum().begin(); rhsit != rhs.getSum().end(); ++rhsit)
    {
        if (rhsit->first && rhsit->second)
        {
            stringstream ss;
            ss << *this << "^(" << rhs << ") ... " << "Mdr t'as cru que je savais resoudre ca" ;
            throw runtime_error("Mdr t'as cru que je savais resoudre ca");
        }
    }

    
    return (*this);
};

ostream &operator<<(ostream &out, Coeff const &rhs)
{
    map<Number, Number>::iterator it = rhs.getSum().begin();
    
    if (it == rhs.getSum().end())
        out << 0;

    while (it != rhs.getSum().end())
    {
        out <<it->second << "x^" << it->first;
        ++it;
        if (it != rhs.getSum().end())
            out << " + ";
    }

    return (out);
}

