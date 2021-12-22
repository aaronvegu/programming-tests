# Listdir

##### License: GNU General Public License v3.0

#

## Descripción

_**Listdir**_ es un programa que usa la libreria [Filesystem](https://en.cppreference.com/w/cpp/filesystem) nativa del lenguaje C++ para la lectura de los archivos en un directorio, listando los archivos con nombre y peso en bytes, y escribiendolo la informacion en un archivo JSON que genera en el mismo directorio donde se ha ejecutado el programa.

La ruta del directorio a listar se debe especificar como parametro en el momento de su ejecucion.

**Listdir** ha sido construido mediante [CMAKE](https://cmake.org/) con la finalidad de que pueda ser ejecutado de manera independiente sin importar el entorno en el que se encuentre.

#

## Ejecución

El ejecutable del programa se encuentra dentro de la carpeta _/exe_ en este folder, el cual debe ser descargado para su ejecucion.

Una vez descargado el ejecutable en su equipo, se puede proceder a su ejecución de la siguiente manera:

```bash
./listdir path/to/list
```

Donde _path/to/list_ representa la ruta al directorio que se desea listar, por ejemplo, en un sistema MacOS la ruta para listar el directorio de descargas quedaria de la siguiente:

```bash
./listdir /Users/user/Downloads
```

#

## Funcionamiento del Algoritmo

Las funcionalidades de manipulacion de archivos del sistema se obtienen de la libreria Filesystem propia del lenguaje C++ en versión C++17 y posteriores.

Por esta razon se incluyen las siguientes librerias al codigo del programa:

```cpp
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
```

Asi como _fstream_ para la creacion y manipulación del archivo JSON que es listado como salida del programa.

Seguido de la declaracion del ambito y el namespace _**fs**_ para el conjunto de utilidades de la libreria Filesystem proveniente de la libreria Standard.

```cpp
namespace fs = std::filesystem;
```

#

## Función Principal (Main)

El primer paso en nuestra funcion principal es verificar que se haya recibido un segundo argumento (ademas del programa) en el vector de argumentos a la hora de su ejecucion:

```cpp
if (argc != 2)
    {
        std::cout << "Error: Se esperaba un parametro que no fue ingresado." << std::endl;
        return -1;
    }
```

De lo contrario damos por terminado el programa y hacemos indicacion del error en consola.

```cpp
std::string path = argv[1];
```

Comprobado el argumento, asignamos la cadena otorgada por el usuario en la variable _path_ que se encargara de almacenar la ruta sobre la que trabajaremos la iteracion del directorio.

Mediante _fstream_ abrimos un flujo bidireccional (I/O) en un archivo que llamaremos **"dir.json"**, y este lo asignamos a la variable llamada _file_.

```cpp
std::fstream file("dir.json", std::ios::out);
```

Una vez que contamos con la ruta a listar y el archivo sobre el que escribiremos, podemos proceder a iniciar el formato JSON en que iremos listando cada archivo del directorio

```cpp
file << "{ \"files\": [" << std::endl;
```

escribiendolo sobre nuestro archivo _dir.json_ en _file_.

A continuacion se presenta el nucleo central de nuestro programa,

```cpp
for (const auto & entry : fs::directory_iterator(path)) {
  /** Iteracion sobre los archivos del directorio **/
}
```

que se trata de un for loop que usa el iterador de directorios ([directory_iterator](https://en.cppreference.com/w/cpp/filesystem/directory_iterator)) propio de Filesystem (antes Boost) como objeto de iteración sobre el directorio.

Declaramos la variable entry:

```cpp
// dentro del for loop
const auto & entry : fs::directory_iterator(path)
```

a la cual se le asigna de tipo constante para evitar cambiar su ubicacion en memoria, llamando su valor mediante referencia e inicializando su contenido a traves de los archivos que va iterando **_directory_iterator_** en la ruta especificada en el argumento del programa.

El objetivo de llamar el valor de una constante (_entry_) mediante referencia es modificar su valor en cada iteración sin alterar su ubicación en memoria, y a la vez definir esta constante como _auto_ para obtener el soporte de trabajar objetos complejos.

De esta manera dentro de nuestro ciclo la variable _entry_ representa cada archivo del directorio conforme se encuentra en cada estado de la iteración, haciendo posible obtener el tipo de archivo con que contamos en esa instancia, y solo pasar a listar tal archivo si este NO es un directorio:

```cpp
if (entry.symlink_status().type() != fs::file_type::directory)
```

Esto se logra con la lectura de las propiedades que se encuentran almacenadas en el metodo _**symlink_status**_ de nuestra variable entry que las obtiene a traves del iterador de archivos, que a su vez presenta una enumeracion de distintos tipos de archivos llamada _type()_, entre ellas _"directory"_ que es evaluada en la condicion.

De NO ser un directorio, obtenemos su nombre y peso y estos datos los imprimimos en el archivo dir.json a traves de nuestro flujo **_fstream_** declarado.

```cpp
file << "\t{\"name\":" << entry.path().filename() << ",\"size\":" << fs::file_size(entry.path()) << "}," << std::endl;
```

Siguiendo el formato JSON especificado en forma de objeto para cada archivo del directorio.

Concluida la iteracion (no recursiva) sobre el directorio, nuestros pasos finales son cerrar el formato de objeto JSON en nuestro archivo y cerrar el flujo del archivo.

```cpp
// Se cierra el formato JSON en el archivo, una vez terminada la iteracion
file << "\t]\n}" << std::endl;

// Cerramos el flujo del archivo
file.close();

return 0;
```

Terminando asi la ejecucion del programa principal, que ha dado como resultado un archivo _"dir.json"_ en la ruta de su ejecucion sobre el directorio pasado como argumento.

#

## Licencia

[GNU General Public License v3.0](https://choosealicense.com/licenses/gpl-3.0/)
