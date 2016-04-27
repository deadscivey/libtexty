type_map = {}


class CPPType(object):
    class_name = None

    def to_str(self):
        return str(self)

    def __str__(self):
        raise NotImplementedError



class CPPLiteral(CPPType):
    pass


class CPPStringLiteral(CPPLiteral):
    def __init__(self, val):
        self.val = val

    def __str__(self):
        return '"%s"' % str(self.val)


class CPPIntLiteral(CPPLiteral):
    def __init__(self, val):
        self.val = val

    def __str__(self):
        return '%s' % str(self.val)


class CPPDoubleLiteral(CPPLiteral):
    def __init__(self, val):
        self.val = val

    def __str__(self):
        return '%s' % str(self.val)

class CPPIdentifier(CPPType):
    def __init__(self, val):
        self.val = val

    def __str__(self):
        return str(self.val)


def make_literal(x):
    return {
        int: CPPIntLiteral,
        float: CPPDoubleLiteral,
        str: CPPStringLiteral,
        unicode: CPPStringLiteral
    }[type(x)](x)

def ident(x):
    if isinstance(x, CPPIdentifier):
        return x
    return CPPIdentifier(x)

class CPPTypeAnnotation(CPPType):
    def __init__(self, val):
        self.val = val

    def __str__(self):
        return str(self.val)


class CPPInitializerList(CPPLiteral):
    def __init__(self, *vals):
        if len(vals) > 0:
            if isinstance(vals[0], (list, tuple)):
                vals = vals[0]
            if len(vals) > 0:
                vals = map(make_literal, vals)
        self.vals = vals

    def __str__(self):
        return '{' + ', '.join(map(str, self.vals)) + '}'


class CPPDeclaration(CPPType):
    def __init__(self, type_name, var_name, value):
        self.type_name = type_name
        self.var_name = ident(var_name)
        self.value = value

    def __str__(self):
        val = ''
        if isinstance(self.value, CPPInitializerList):
            val = str(self.value)
        else:
            val = '{ %s }' % str(self.value)
        return '%s %s %s' % (self.type_name, self.var_name, val)


# def listy_to_vector(value_type, var_name, values):
#     yield 0, 'std::vector<%s> %s {' % (value_type, var_name)
#     for item in values:
#         yield 2, 
