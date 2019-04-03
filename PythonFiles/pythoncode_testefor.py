#!/usr/bin/env python3
# -*- coding: utf-8 -*-
a = 1
i = int(input("Digite o valor da variável i:"))
k = int(input("Digite o valor da variável k:"))
j = 10
while j>=1:
    if k==2:
        a = a*i-j
        k = 1
    elif k==1:
        a = a*i+j
        k = 0
    else:
        k = 2
        a = 0
    print("Valor da variável a :" + str(a))
    print("Valor da variável k :" + str(k))
    j = j-1
print(str(a<i))
