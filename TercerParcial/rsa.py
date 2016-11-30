#!/usr/bin/env python
# -*- coding: utf-8 -*- 

import random

def mcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def inverso_multiplicativo(e, phi):
    d = 0
    x1 = 0
    x2 = 1
    y1 = 1
    temp_phi = phi

    while e > 0:
        temp1 = temp_phi/e
        temp2 = temp_phi - temp1 * e

        temp_phi = e
        e = temp2

        x = x2- temp1* x1
        y = d - temp1 * y1

        x2 = x1
        x1 = x

        d = y1
        y1 = y

    if temp_phi == 1:
        return d

def es_primo(numero):
    if numero == 2:
        return True
    if numero < 2 or numero % 2 == 0:
        return False
    for n in xrange(3, int(numero**0.5)+2, 2):
        if numero % n == 0:
            return False
    return True

def genera_e(p, q):
    if not (es_primo(p) and es_primo(q)):
        raise ValueError('Ambos numeros deben ser primos.')
    elif p == q:
        raise ValueError('p y q no pueden ser iguales')

    e = random.randrange(1, phi)

    maxdiv = mcd(e, phi)

    while maxdiv != 1:
        e = random.randrange(1, phi)
        maxdiv = mcd(e, phi)

    return e

print('Proyecto Final Matematicas Computacionales - RSA')

p = int(input('Introduce p: '))
q = int(input('Introduce q: '))

n = (p * q)
phi = (p-1) * (q-1)
e = genera_e(p, q)
d = inverso_multiplicativo(e, phi)

mensaje_a_cifrar = int(input('Introduce el mensaje a cifrar: '))

print('La llave pública es: {}, {}'.format(e, n))
print('La llave privada es: {}, {}'.format(d, n))

mensaje_cifrado = pow(mensaje_a_cifrar, e, n)

print('El mensaje cifrado es: {}'.format(mensaje_cifrado))

mensaje_decifrado = pow(mensaje_cifrado, d, n)

print('El mensaje decifrado es: {}'.format(mensaje_decifrado))
