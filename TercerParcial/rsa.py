p = int(input('Introduce p: '))
q = int(input('Introduce q: '))
e = int(input('Introduce e: '))
d = int(input('Introduce d: '))
mensaje_a_cifrar = int(input('Introduce el mensaje a cifrar: '))

n = (p * q)

print('La llave pública es: {}, {}'.format(e, n))
# print('La llave privada es: {}, {}'.format(d, n))

mensaje_cifrado = pow(mensaje_a_cifrar, e, n)

print('El mensaje cifrado es: {}'.format(mensaje_cifrado))

mensaje_decifrado = pow(mensaje_cifrado, d, n)

print('El mensaje decifrado es: {}'.format(mensaje_decifrado))