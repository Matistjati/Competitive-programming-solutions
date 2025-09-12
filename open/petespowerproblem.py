from decimal import Decimal, getcontext
getcontext().prec = 2000

a,b=input().split()

print(format(Decimal(a)**int(b), 'f'))
