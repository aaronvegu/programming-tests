#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

// Vector para almacenar las raices del resultado
vector<double> results;

// Vector para almacenar posibles soluciones
vector<double> possibleRoots;

// Manejo de errores
bool isError = false;

// Prototipo de funcion para evaluar polinomio a un valor asignado
bool isTheAnswer(double a, double b, double c, double d, double x);

// Prototipo de funcion para obtener los factores de n
vector<double> factorsOf(double n);

// Prototipo de funcion para obtener las posibles raices
void getPossibleRoots(vector<double> p, vector<double> q);

// Prototipo de funcion para imprimir resultados
void printResults();

int main(int argc, char** argv) {
    // Contador de raices
    // si raices > 3 = se encontraron todas las raices posibles
    int rootsCounters = 0;

    // Declaracion de discriminante y su raiz cuadrada
    double discriminant, squareDiscriminant;

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

    /**
     * 1ra Revision:
     * Checar que x = 1 sea una solucion para el polinomio
     */
    if (isTheAnswer(a, b, c, d, 1)) {
        results.push_back((double)1);
        rootsCounters++;
    }

    /**
     * 2da Revision:
     * Checar que x = -1 sea una solucion para el polinomio
     * Usando la regla: si la suma de los coeficientes de terminos alternos son iguales,
     * entonces -1 es una solucion a la raiz.
     */
    if ((a + c) == (b + d)) {
        results.push_back((double)-1);
        rootsCounters++;
    }

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
    for (auto i = p.begin(); i != p.end(); ++i)
        cout << "P: " << *i << " ";
    // Obtenemos factores de d
    vector<double> q = factorsOf(a);
    for (auto i = q.begin(); i != q.end(); ++i)
        cout << "Q: " << *i << " ";
    // Obtenemos posibles raices en base a p / q
    getPossibleRoots(p, q);

    cout << "Possible factors:" << endl;
    for (auto i = possibleRoots.begin(); i != possibleRoots.end(); ++i)
        cout << *i << " ";

    /**
     * Una vez obtenidos las posibles raices, procedemos a realizar una
     * division sintetica con los valores de nuestra polinomio y cada posible
     * raiz hasta obtener un remainder de 0, indicando haber logrado reducir nuestro
     * polinomio a una ecuacion cuadratica
     */
    float value1, value2, value3, value4; // variables para nuevos valores
    // Division sintetica por cada posible raiz
    for (auto i = possibleRoots.begin(); i != possibleRoots.end(); ++i) {
        value1 = a;
        value2 = (*i * value1) + b;
        value3 = (*i * value2) + c;
        value4 = (*i * value3) + d;
        if (value4 == 0) { // Si el remainder es 0, encontramos la raiz
            results.push_back(*i);
            rootsCounters++;
            if (rootsCounters < 3) { // Si quedan raices por encontrar
            // Aplicamos formula cuadratica con valores reducidos
            cout << "Values: a " << value1 << ", b " << value2 << ", c" << value3 << ", d" << value4 << endl;

            // Obtenemos el discriminante de la formula
            discriminant = ((value2 * value2) - (4 * value1 * value3));
            cout << "discriminante: " <<  discriminant << endl;

            // Si el discriminante es negativo, raiz no es real
            if (discriminant < 0.0) break;

            // Obtenemos su raiz cuadrada
            squareDiscriminant = sqrt(discriminant);
            cout << "raiz de discriminante: " <<  squareDiscriminant << endl;

            // Calculamos las dos posibles raices
            double root1 = ((-1 * value2) - (squareDiscriminant)) / (2 * value1);
            double root2 = ((-1 * value2) + (squareDiscriminant)) / (2 * value1);

            cout << "root1: " << root1 << endl;
            cout << "root2: " << root2 << endl;

            // Cargamos raices a vector de resultados
            results.push_back(root1);
            results.push_back(root2);

            // Actualizamos nuestro contador de raices
            rootsCounters += 2;
            }
            if (rootsCounters >= 3 && !isError) { // Si se llegó al limite de raices y no hay errores
                printResults();
                return EXIT_SUCCESS;
            }
        }
    }
    

    // Validamos no contar con errores en el programa
    if (!isError) {
        printResults();
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

    // Si n es negativo, lo pasamos a positivo para poder calcular su raiz
    if (n < 0.0) n = -n;

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
            if (find(possibleRoots.begin(), possibleRoots.end(), *i / *t) == possibleRoots.end() && (*i / *t) != 1) {
                possibleRoots.push_back(*i / *t); // agregamos + y - de cada valor
                possibleRoots.push_back(-(*i / *t));
            }
        }
    }
}

// Funcion para imprimir vector con raices
void printResults() {
        // Imprimimos contenido del vector de resultados
        cout << "{ ";
        for (auto i = results.begin(); i != results.end(); ++i)
            cout << *i << " ";
        cout << "}";
}