class NoInheritanceMeta(type):
    raise_exception = True
    def __new__(cls, name, bases, attrs):
        if bases:
            if cls.raise_exception:
                raise RuntimeError("Inheritance Forbidden")
            else:
                print(Warning("Inheritance Warning"))
        return super().__new__(cls, name, bases, attrs)


class WarningInheritanceMeta(NoInheritanceMeta):
    raise_exception = False

class A(metaclass=NoInheritanceMeta):
    pass


class C(A, metaclass=WarningInheritanceMeta):
    pass


class B(C, A):
    pass


class D(A):
    pass
