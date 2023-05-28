import os

def leer_diccionario_invertido(ruta_diccionario):
    diccionario = {}
    with open(ruta_diccionario, 'r') as archivo:
        lineas = archivo.readlines()
        for linea in lineas:
            clave, valor = linea.strip().split(':')
            diccionario[clave] = valor
    return diccionario

def buscar_cadena(coordenadas, archivo):
    with open(archivo, 'r') as archivo:
        lineas = archivo.readlines()
        numeros = []
        for coordenada in coordenadas:
            fila, columna = map(int, coordenada.split(','))

            if fila < len(lineas) and columna < len(lineas[fila]):
                caracter = lineas[fila][columna]
                numeros.append(caracter)
        return numeros

def main():
    ruta_diccionario = 'https://raw.githubusercontent.com/ahiralesc/Hash/main/scripts/inverted_dictionary.txt'
    diccionario = leer_diccionario_invertido(ruta_diccionario)

    salida_numerica = input('Ingrese las coordenadas separadas por comas (fila,columna): ')
    coordenadas = salida_numerica.split(',')

    archivo = '.txt'  #ruta del archivo

    numeros = buscar_cadena(coordenadas, archivo)

    cadena_texto = ''
    for numero in numeros:
        if numero in diccionario:
            cadena_texto += diccionario[numero]
        else:
            cadena_texto += 'NO ENCONTRADO'

    print('La cadena de texto es:', cadena_texto)

main()