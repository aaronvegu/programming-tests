# Findroots

##### License: GNU General Public License v3.0

#

## Descripción

**Findroots** es un buscador de raices que calcula las raices reales de un polinomio de tercer grado de la forma _**ax^3 + bx^2 + cx + d**_, sobre la cual sus coeficientes son pasadas como parametros al momento de la ejecucion de forma descendiente.

**Findroots** ha sido construido mediante [CMAKE](https://cmake.org/) con la finalidad de que pueda ser ejecutado de manera independiente sin importar el entorno en el que se encuentre.

#

## Ejecución

El ejecutable del programa se encuentra dentro de la carpeta _/exe_ en este folder, el cual debe ser descargado para su ejecucion.

Una vez descargado el ejecutable en su equipo, se puede proceder a su ejecución de la siguiente manera:

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

## Funcionamiento del Algoritmo

De manera general, y para tener un acercamiento al funcionamiento del algoritmo, se explican los elementos y estructura general del codigo:

#

### Estructura del codigo

```
- Declaracion de Vectores y Banderas globales (variables de control)
- Declaracion de Prototipos de funciones
- Funcion principal del programa
- Desarrollo de funciones declaradas
```

Con esta estructura declarada, el codigo puede ser consultado para su evaluacion, sin embargo, en el presente archivo se busca explicar de manera concisa y clara cada elemento del algoritmo.

#

## Declaración de Vectores y Banderas

Se cuenta con dos vectores de double declarados de manera global, los cuales seran encargados de almacenar:

- _results._ Almacena las raices encontradas a lo largo de la ejecucion del codigo.
- _possibleRoots._ Almacena una serie de valores que indican una posible solucion de raices.

La variable booleana _isError_ funciona como una bandera que sera cambiada a true a lo largo del codigo si entra en un estado de error.

```cpp
vector<double> results;
vector<double> possibleRoots;

bool isError = false;
```

Explicadas las variables globales, la logica de las funciones internas del algoritmo son explicadas de manera individual despues de la explicacion de la funcion principal, en la seccion de **_Desarrollo de Funciones_**.

La funcion principal es explicada a continuacion:

#

## Funcion Principal (Main)

Debido a que son necesarios los cuatro argumentos para definir los coeficientes del polinomio, se revisa que contemos con los 4 parametros pasados:

Debido a que la ejecucion cuenta como el primer argumento, mas cuatro argumentos del polinomio, se revisa que nuestro contador de argumentos sea cinco.

```cpp
if (argc != 5) {
        cout << "Error: No se ingresaron los 4 valores para las variables a, b, c y d. Se regresa vector vacio" << endl;
        return -1;
    }
```

Se declaran y se toman las cuatro variables que contendran los coeficientes tomados del vector de argumentos, y que seran usados a lo largo del algoritmo:

```cpp
double a = stod(argv[1]);
double b = stod(argv[2]);
double c = stod(argv[3]);
double d = stod(argv[4]);
```

Nuestro primer paso en la busqueda de las raices sera evaluar que 1 sea una solucion para el algoritmo:

```cpp
if (isTheAnswer(a, b, c, d, 1)) {
    results.push_back((double)1);
    rootsCounters++;
}
```

utilizando la funcion isTheAnswer(), que devuelve un booleano que es evaluado, se revisa que el valor 1 retorne 0 con los coeficientes que son pasados como argumentos. De ser _true_, se agrega 1 al vector de resultados y se suma uno al contador de raices.

El contador de raices:

```cpp
int rootsCounters = 0;
```

es una variable encargada de llevar la cuenta de raices encontradas, ya que de encontrar 3 raices, el programa puede terminar y evitar utilizando recursos del progra. Esto ya que al ser una funcion cubica, su numero maximo de raices positivas y negativas es tres.

Nuestro segundo paso es revisar que -1 sea otro de las raices para el polinomio. Usando la regla: si la suma de los coeficientes de terminos alternos son iguales, entonces -1 es una solucion a la raiz, y de igual manera, de ser positivo, el valor es agregado al vector de resultados y se suma uno al contador de raices.

```cpp
if ((a + c) == (b + d)) {
    results.push_back((double)-1);
    rootsCounters++;
}
```

Una vez que se evaluó la posibilidad de que uno y uno negativo sean raices, se tomaran los coeficientes a la orilla de la ecuacion (coeficientes a y d) y se crearan dos vectores, uno que contendra todos los factores o divisores naturales de a y d. Para ello se utilizara la funcion interna _factorsOf()_ que es explicada a detalle en la sección de **_Desarrollo de funciones internas._**

```cpp
// Obtenemos factores de a
vector<double> p = factorsOf(d);
for (auto i = p.begin(); i != p.end(); ++i)
    cout << "P: " << *i << " ";
// Obtenemos factores de d
vector<double> q = factorsOf(a);
for (auto i = q.begin(); i != q.end(); ++i)
    cout << "Q: " << *i << " ";
```

Obtenidas las posibles raices de a y d, utilizamos la funcion interna getPossibleRoots() encargada de tomar los factores de a y d, realizar la division entre cada uno de esos factores y obtenerlos para contar con un vector de posibles raices que seran evaluadas mediante una division sintetica en el paso siguiente.

```cpp
getPossibleRoots(p, q);
```

Una vez obtenidos las posibles raices, procedemos a realizar una division sintetica con los valores de nuestra polinomio y cada posible raiz hasta obtener un remainder de 0, indicando haber logrado reducir nuestro polinomio a una ecuacion cuadratica.

```cpp
float value1, value2, value3, value4; // variables para nuevos valores
// Division sintetica por cada posible raiz
for (auto i = possibleRoots.begin(); i != possibleRoots.end(); ++i) {
    value1 = a;
    value2 = (*i * value1) + b;
    value3 = (*i * value2) + c;
    value4 = (*i * value3) + d;
```

Dentro de este mismo for evaluamos haber encontrado una nueva raiz de la ecuacion, y de no haber sido asi, seguimos iterando la division sintetica sobre cada valor en nuestro vector de raices posibles

Si nuestro value4 (d) es 0, se ha reducido la ecuacion y ya contamos con una ecuacion cuadratica que puede ser resuelto mediante la formula cuadratica:

```cpp
if (value4 == 0) { // Si el remainder es 0, encontramos la raiz
   results.push_back(*i);
   rootsCounters++;
if (rootsCounters < 3) { // Si quedan raices por encontrar
```

Agregamos la raiz al vector de resultados, sumamos el contador de raices y de no contar aun con las tres raices necesarias para cerrar el programa, continuamos con la realizacion de la formula cuadratica:

```cpp
// Obtenemos el discriminante de la formula
discriminant = ((value2 * value2) - (4 * value1 * value3));

// Si el discriminante es negativo, raiz no es real
if (discriminant < 0.0) break;

// Obtenemos su raiz cuadrada
squareDiscriminant = sqrt(discriminant);

// Calculamos las dos posibles raices
double root1 = ((-1 * value2) - (squareDiscriminant)) / (2 * value1);
double root2 = ((-1 * value2) + (squareDiscriminant)) / (2 * value1);

// Cargamos raices a vector de resultados
results.push_back(root1);
results.push_back(root2);

// Actualizamos nuestro contador de raices
rootsCounters += 2;
```

En la seccion de codigo superior, lo que hacemos es definir el discriminante de la formula, obtener su raiz cuadrada y calcular cada raiz siguiendo la formula, no sin antes verificar que la raiz sea positiva (mayor a 0), pues de ser negativa nos encontramos con una raiz no real y salimos del proceso.

Si para el final de la formula cuadratica se han alcanzado las tres raices necesarias y no se han activado errores, podemos imprimir nuestro vector de raices (mediante la funcion interna printResults() que se explica mas adelante) y terminar la funcion principal de manera exitosa.

```cpp
if (rootsCounters >= 3 && !isError) { // Si se llegó al limite de raices y no hay errores
    printResults();
    return EXIT_SUCCESS;
}
```

#

## Desarrollo de Funciones internas

Se explica el funcionamiento y logicas de las funciones desarrolladas para el algoritmo, con el proposito de encontrar las raices del polinomio sin recurrir a librerias externas mas que el calculo de las raices mediante _sqrt()_ de _math_.

#

### Funcion -> bool isTheAnswer()

```cpp
bool isTheAnswer(double a, double b, double c, double d, double value);
```

_isTheAnswer()_ recibe como parametro los cuatro coeficientes de la ecuacion y un quinto parametro llamado _value_ que representa la raiz que quiere ser probada para ser una solucion a la ecuacion. Regresando _true_ si la ecuacion equivale a 0 con _value_ y _false_ en caso de que no.

```cpp
bool isTheAnswer(double a, double b, double c, double d, double x) {
    double result = ((a * calculatePow(x, 3)) + (b * calculatePow(x, 2)) + (c * x) + d);
    if (result == 0)
        return true;

    return false;
}
```

La variable result recibe el resultado de la ecuacion, la cual es representada y es pasada con el valor de la raiz a probar.

Si result es 0, entonces sabemos que el valor pasado es una de las raices del polinomio y la funcion retorna _true_, caso contrario _false_.

#

### Funcion -> vector factorsOf()

```cpp
vector<double> factorsOf(double n)
```

Funcion encargada de retornar un vector con los factores o divisores del valor n pasado como parametro.

```cpp
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
```

De manera local se declara un vector temporal al que se le agregan los factores que van siendo calculados, y despues es retornado como resultado de la funcion.

Antes de evaluar los divisores de n, es importante pasar n a positivo en caso de ser negativo, esto para que sea posible obtener su raiz cuadrada, ya que es fundamental para obtener los divisores de n.

```cpp
// Si n es negativo, lo pasamos a positivo para poder calcular su raiz
if (n < 0.0) n = -n;
```

Se crea un for loop que inicia en cero y se recorre hasta la raiz de n, esto para eficientizar el algoritmo y no recorrer todos los valores de n desde cero, obteniendo un par de valores que son evaluados más adelante.

```cpp
for (int i = 0; i <= sqrt(n); i++)
```

Dentro del loop, se evalua que la division de n sobre i resulte en un remainder de 0 usando la funcion fmod() para el calculo de modulo en valores de tipo double, indicando que se encuentra con un divisor de n, agregandolo al vector temporal.

```cpp
if (fmod(n,(double)i) == 0)
```

Debido a que se obtienen los valores en pares donde -> (i, raiz de n) y se va avanzando su valor de uno en uno, el par es evaluado y de ser distintos numeros los contenidos en el par, se agregan ambos, de lo contrario, solo se agrega uno de los divisores.

```cpp
if (n / i == i) // Si la division es entre mismos numeros, solo agregar uno
    temp.push_back(i);
else { // de lo contario, agregar ambos
    temp.push_back(i);
    temp.push_back(n/i);
}
```

Ya que se han agregado los factores a nuestro vector, podemos proceder a devolver ese vector temporal para que sea manipulado en la funcion principal.

```cpp
return temp; // devolvemos vector con factores de n
```

#

### Funcion -> void getPossibleRoots()

```cpp
void getPossibleRoots(vector<double> p, vector<double> q);
```

La funcion _getPossibleRoots()_ recibe dos vectores, los cuales contienen los factores o divisores del primer y ultimo coeficiente (a y d), con los cuales se realiza una division entre los factores de ambos coeficientes y el resultado de cada division es una posible raiz que sera tratada en la resolucion del polinomio.

El siguiente loop dentro de la funcion itera los valores de P sobre Q, realizando la division de cada valor de P sobre cada valor de Q:

```cpp
for (auto i = p.begin(); i != p.end(); ++i) {
        for (auto t = q.begin(); t != q.end(); ++t) {
            // Si el resultado de la div no existe en el vector y es distinto de 1, agregarlo
            if (find(possibleRoots.begin(), possibleRoots.end(), *i / *t) == possibleRoots.end() && (*i / *t) != 1) {
                possibleRoots.push_back(*i / *t); // agregamos + y - de cada valor
                possibleRoots.push_back(-(*i / *t));
            }
        }
    }
```

Donde lo ultimo que queda es evaluar que el valor de la division no exista en el vector global de posibles raices, asi como el valor 1, ya que anteriormente a la funcion (en la funcion main del programa) se evalua que 1 sea una posible raiz.

#

## Funcion -> printResults()

```cpp
void printResults()
```

printResults() trata solo de una funcion utilitaria para mandar a imprimir el vector de resultados, a lo cual es llamada normalmente cuando se han encontrado todas las raices o se llega al final del algoritmo.

```cpp
cout << "{ ";
for (auto i = results.begin(); i != results.end(); ++i)
    cout << *i << " ";
cout << "}";
```

Arriba se muestra un for loop que itera sobre el vector utilizando las funciones begin() y end(), ingresando a la direccion de cada elemento en el vector e imprimiendolo en consola.

#

## Funcion -> calculatePow()

```cpp
double calculatePow(double base, int exponent)
```

La funcion recibe como parametros el numero base a exponenciar y el exponente al que sera elevada la base.

Debido a que un exponente trata de multiplicar la base el numero de veces al que corresponde su exponente, lo que hacemos es iterar de cero al exponente y en cada iteracion multiplicar la base sobre si misma y asignarlo a su valor previo en la variable result, que es retornada como resultado de la funcion.

```cpp
double calculatePow(double base, int exponent) {
    double result;
    for (int i = 0; i < exponent; ++i)
        result *= base;
    return result;
}
```

#

## Licencia

[GNU General Public License v3.0](https://choosealicense.com/licenses/gpl-3.0/)
