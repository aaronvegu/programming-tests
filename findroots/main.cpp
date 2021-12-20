#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

// Prototipo de funcion para evaluar polinomio a un valor asignado
bool isTheAnswer(double a, double b, double c, double d, double x);

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