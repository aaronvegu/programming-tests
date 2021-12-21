#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

// Vector para almacenar posibles soluciones
vector<double> possibleRoots;

// Prototipo de funcion para evaluar polinomio a un valor asignado
bool isTheAnswer(double a, double b, double c, double d, double x);

// Prototipo de funcion para obtener los factores de n
void factorsOf(double n);

int main(int argc, char** argv) {
    // Manejo de errores
    bool isError = false;

    // Vector para almacenar las raices del resultado
    vector<double> results;

    // Declaramos variable de la raiz
    double x;
    
    // Verificamos haber recibido los cuatro valores requeridos para el polinomio
    if (argc != 5) {
        cout << "Error: No se ingresaron los 4 valores para las variables a, b, c y d. Se regresa vector vacio" << endl;
        return -1; 
    }

    // Declaramos y almacenamos valores de las variables para el polinomio
    double a = stod(argv[1]);
    double b = stod(argv[2]);
    double c = stod(argv[3]);
    double d = stod(argv[4]);

    // PRUEBA
    //cout << "a: " << a << ", b: " << b << ", c: " << c << ", d: " << d << endl;

    /**
     * 1ra Revision:
     * Checar que x = 1 sea una solucion para el polinomio
     */
    if (isTheAnswer(a, b, c, d, 1))
        results.push_back((double)1);

    /**
     * 2da Revision:
     * Checar que x = -1 sea una solucion para el polinomio
     * Usando la regla: si la suma de los coeficientes de terminos alternos son iguales,
     * entonces -1 es una solucion a la raiz.
     */
    if ((a + c) == (b + d))
        results.push_back((double)-1);

    /**
     * 3ra Revision:
     * Tomamos el primer y ultimo coeficiente, teniendo:
     * q = a, p = d. Donde a = ax^3 y d = dx^0
     * Para buscar los divisores o factores de P y Q, y almacenarlos
     * como posibles soluciones de raices
     */
    // Obtenemos factores de a
    factorsOf(a);
    // Obtenemos factores de d
    factorsOf(d);

    cout << "Possible factors:" << endl;
    for (auto i = possibleRoots.begin(); i != possibleRoots.end(); ++i)
        cout << *i << " ";


    // Validamos no contar con errores en el programa
    if (!isError) {
        // Imprimimos contenido del vector de resultados
        cout << "{ ";
        for (auto i = results.begin(); i != results.end(); ++i)
            cout << *i << " ";
        cout << "}";
        return EXIT_SUCCESS;
    }
}

// Funcion de evaluacion
bool isTheAnswer(double a, double b, double c, double d, double x) {
    double result = ((a * pow(x, 3)) + (b * pow(x, 2)) + (c * x) + d);
    //cout << result;
    if (result == 0) // MANEJAR PRECISION EN DECIMALES
        return true;

    return false;
}

// Funcion para obtener los factores de n
void factorsOf(double n) {
    for (int i = 0; i <= sqrt(n); i++)
    {
        if (fmod(n,(double)i) == 0) { // De ser divisibles (usando modulo)
            if (n / i == i) {// Si la division es entre mismos numeros, solo agregar uno
                if (find(possibleRoots.begin(), possibleRoots.end(), i) == possibleRoots.end())
                    possibleRoots.push_back(i); // de no existir en vector, agregarlo
            }
            else { // de lo contario, agregar ambos
                if (find(possibleRoots.begin(), possibleRoots.end(), i) == possibleRoots.end())
                    possibleRoots.push_back(i); // de no existir en vector, agregarlo
                if (find(possibleRoots.begin(), possibleRoots.end(), n/i) == possibleRoots.end())
                    possibleRoots.push_back(n/i); // de no existir en vector, agregarlo
            }      
        }
    }
}