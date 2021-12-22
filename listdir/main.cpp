#include<iostream>
#include<string>
#include<filesystem>
#include<fstream>

namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    // Verificar que se obtuvo un argumento
    if (argc != 2)
    {
        std::cout << "Error: Se esperaba un parametro que no fue ingresado." << std::endl;
        return -1;
    }

    // Leemos la ruta de los argumentos del programa
    std::string path = argv[1];

    // Creamos el archivo al que se le escribira el contenido del directorio
    std::fstream file("dir.json", std::ios::out);

    // Escribimos el inicio del JSON
    file << "{ \"files\": [" << std::endl;

    // For loop que usa el iterador de directorios propio de Filesystem (antes Boost) 
    // declaramos la variable entry, la cual se le asigna un tipo constante para evitar cambiar
    // su ubicacion en memoria, llamndo su valor mediante referencia e inicializando su contenido 
    // a traves de los archivos que va iterando directory_iterator en la ruta especificada en su argumento
    // que es tomada de la lista de parametros del programa
    for (const auto & entry : fs::directory_iterator(path)) {
        // leemos el tipo de archivo que se encuentra almacenado en symlink_status, encargado de recoger los 
        // atributos del objeto de archivo en que se encuentra la iteracion del directorio:
        // pasando la condicion solo si el tipo de archivo es distinto de directorio, ignorando directorios
        if (entry.symlink_status().type() != fs::file_type::directory) { // si NO es directorio:
            file << "\t{\"name\":" << entry.path().filename() << ",\"size\":" // Obtenemos su nombre y peso
            << fs::file_size(entry.path()) << "}," << std::endl; // imprimiendolo en el archivo con el formato JSON establecido
        }
    }

    // Se cierra el formato JSON en el archivo, una vez terminada la iteracion
    file << "\t]\n}" << std::endl;

    // Cerramos el flujo del archivo
    file.close();

    return 0;
}