# Programming Tests

#### Developed by Aaron Vegu

#

## Descripción

_Programming tests_ es un repositorio que consiste en un par de programas desarrollados en C++ y construidos mediante [CMAKE](https://cmake.org/) con la finalidad de poder ser ejecutados de manera independiente sin importar el entorno en el que se encuentre.

Los dos programas en cuestión son:

- **Findroots.** Un Buscador de raices que calcula las raices reales de un polinomio de tercer grado de la forma _**ax^3 + bx^2 + cx + d**_.
- **Listdir.** Programa que lista los archivos existentes un directorio, mostrando su nombre y tamaño en bytes en un formato JSON, haciendo uso de la libreria nativa _Filesystem_, disponible en versiones posteriores a C++17.

La ejecución de cada programa, paso de parametros y funcionamiento detallado de su codigo se encuentran descritos en la subcarpeta de cada programa dentro de este repositorio.

#

## Ejecución

La ejecución de cada programa se logra mediante su ejecutable que se encuentra en el folder _/exe_ dentro de la subcarpeta de cada programa en este repositorio.

Una vez descargado cada ejecutable en su equipo, se puede proceder a su ejecución de la siguiente manera:

### Findroots

```bash
./findroots a b c d
```

Donde a, b, c y d representan los coeficientes de la ecuación de forma descendiente, que deben ser ingresados respectivamente en valores enteros.

Siendo asi, si tenemos la siguiente ecuacion:

- x^3 - 3x^2 - 53x - 65

El paso al programa para su ejecucion quedaria:

```bash
./findroots 1 -3 -53 -65
```

donde _a = 1x^3, b = -3x^2, c = -53x y d = -65_

#

### Listdir

```bash
./listdir path/to/list
```

Donde _path/to/list_ representa la ruta al directorio que se desea listar, por ejemplo, en un sistema MacOS la ruta para listar el directorio de descargas quedaria de la siguiente:

```bash
./listdir /Users/user/Downloads
```

#

##

#

## Licencia

[GNU General Public License v3.0](https://choosealicense.com/licenses/gpl-3.0/)
