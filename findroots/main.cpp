#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

// Vector para almacenar posibles soluciones
vector<double> possibleRoots;

// Prototipo de funcion para evaluar polinomio a un valor asignado
bool isTheAnswer(double a, double b, double c, double d, double x);

// Prototipo de funcion para obtener los factores de n
vector<double> factorsOf(double n);

// Prototipo de funcion para obtener las posibles raices
void getPossibleRoots(vector<double> p, vector<double> q);

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
     * como posibles soluciones de raices, a traves de las divisiones posibles
     * entre p y q, incluyendo positivos y negativos
     */
    // Obtenemos factores de a
    vector<double> p = factorsOf(d);
    // Obtenemos factores de d
    vector<double> q = factorsOf(a);
    // Obtenemos posibles raices en base a p / q
    getPossibleRoots(p, q);

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
vector<double> factorsOf(double n) {
    // vector temporal a devolver
    vector<double> temp;

    for (int i = 0; i <= sqrt(n); i++) // Todos los divisores vienen en pares
    {
        if (fmod(n,(double)i) == 0) { // De ser divisibles (usando modulo)
            if (n / i == i) // Si la division es entre mismos numeros, solo agregar uno
                temp.push_back(i); 
            else { // de lo contario, agregar ambos
                temp.push_back(i); 
                temp.push_back(n/i); 
            }      
        }
    }

    return temp; // devolvemos vector con factores de n
}

// Funcion para obtener vector con posibles raices en base a la division de p / q
void getPossibleRoots(vector<double> p, vector<double> q) {
    for (auto i = p.begin(); i != p.end(); ++i) {
        for (auto t = q.begin(); t != q.end(); ++t) {
            // Si el resultado de la div no existe en el vector y es distinto de 1, agregarlo
            if (find(possibleRoots.begin(), possibleRoots.end(), *i / *t) == possibleRoots.end() && (*i / *t) != 1)
                possibleRoots.push_back(*i / *t);
        }
    }
}