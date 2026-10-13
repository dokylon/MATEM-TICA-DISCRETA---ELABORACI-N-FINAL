#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <cctype>
#include <cstdlib>

using namespace std;

const int MAX_VERTICES = 20;
const double PI = 3.14159265358979323846;

string nombre_pieza = "";
string departamento = "";
string tipo_pieza = "";

double coordenada_x[MAX_VERTICES];
double coordenada_y[MAX_VERTICES];
int cantidad_vertices = 0;

bool pieza_registrada = false;
bool vertices_registrados = false;

bool texto_valido(string texto) {
    if (texto.length() == 0) {
        return false;
    }

    bool tiene_letra = false;

    for (int i = 0; i < texto.length(); i++) {
        if (isalpha((unsigned char)texto[i])) {
            tiene_letra = true;
        }
    }

    return tiene_letra;
}

bool entero_valido(string texto) {
    if (texto.length() == 0) {
        return false;
    }

    for (int i = 0; i < texto.length(); i++) {
        if (!isdigit((unsigned char)texto[i])) {
            return false;
        }
    }

    return true;
}

bool real_valido(string texto) {
    if (texto.length() == 0) {
        return false;
    }

    int puntos = 0;
    int inicio = 0;
    bool tiene_numero = false;

    if (texto[0] == '-' || texto[0] == '+') {
        inicio = 1;
    }

    if (inicio == texto.length()) {
        return false;
    }

    for (int i = inicio; i < texto.length(); i++) {
        if (isdigit((unsigned char)texto[i])) {
            tiene_numero = true;
        }
        else if (texto[i] == '.') {
            puntos++;

            if (puntos > 1) {
                return false;
            }
        }
        else {
            return false;
        }
    }

    return tiene_numero;
}

int leer_entero(string mensaje, int minimo, int maximo) {
    string dato;
    int numero;

    do {
        cout << mensaje;
        getline(cin, dato);

        if (!entero_valido(dato)) {
            cout << "ERROR: debe ingresar un numero entero.\n";
        }
        else {
            numero = atoi(dato.c_str());

            if (numero < minimo || numero > maximo) {
                cout << "ERROR: opcion fuera del rango permitido.\n";
            }
            else {
                return numero;
            }
        }

    } while (true);
}

double leer_real(string mensaje) {
    string dato;
    double numero;

    do {
        cout << mensaje;
        getline(cin, dato);

        if (!real_valido(dato)) {
            cout << "ERROR: debe ingresar un valor numerico.\n";
        }
        else {
            numero = atof(dato.c_str());
            return numero;
        }

    } while (true);
}

bool confirmar(string mensaje) {
    cout << mensaje << endl;
    cout << "1. Si\n";
    cout << "2. No\n";

    int opcion = leer_entero("Seleccione una opcion: ", 1, 2);

    if (opcion == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool vertice_repetido(double x, double y, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        if (coordenada_x[i] == x && coordenada_y[i] == y) {
            return true;
        }
    }

    return false;
}

bool verificar_vertices() {
    if (!pieza_registrada) {
        cout << "\nERROR: primero debe registrar una pieza arqueologica.\n";
        return false;
    }

    if (!vertices_registrados) {
        cout << "\nERROR: primero debe ingresar los vertices de la pieza.\n";
        return false;
    }

    return true;
}

void registrar_pieza() {
    cout << "\n========== REGISTRO DE PIEZA ARQUEOLOGICA ==========\n";

    do {
        cout << "Nombre de la pieza: ";
        getline(cin, nombre_pieza);

        if (!texto_valido(nombre_pieza)) {
            cout << "ERROR: ingrese un nombre valido.\n";
        }

    } while (!texto_valido(nombre_pieza));

    string departamentos[25] = {
        "Amazonas", "Ancash", "Apurimac", "Arequipa", "Ayacucho",
        "Cajamarca", "Callao", "Cusco", "Huancavelica", "Huanuco",
        "Ica", "Junin", "La Libertad", "Lambayeque", "Lima",
        "Loreto", "Madre de Dios", "Moquegua", "Pasco", "Piura",
        "Puno", "San Martin", "Tacna", "Tumbes", "Ucayali"
    };

    cout << "\nDepartamento de procedencia:\n";

    for (int i = 0; i < 25; i++) {
        cout << i + 1 << ". " << departamentos[i] << endl;
    }

    int opcion_departamento =
        leer_entero("Seleccione una opcion: ", 1, 25);

    departamento = departamentos[opcion_departamento - 1];

    string tipos[6] = {
        "Ceramica",
        "Escultura",
        "Fragmento arquitectonico",
        "Textil",
        "Orfebreria",
        "Otro"
    };

    cout << "\nTipo de pieza arqueologica:\n";

    for (int i = 0; i < 6; i++) {
        cout << i + 1 << ". " << tipos[i] << endl;
    }

    int opcion_tipo =
        leer_entero("Seleccione una opcion: ", 1, 6);

    tipo_pieza = tipos[opcion_tipo - 1];

    pieza_registrada = true;
    vertices_registrados = false;
    cantidad_vertices = 0;

    cout << "\nPieza registrada correctamente.\n";
}

void ingresar_vertices() {
    if (!pieza_registrada) {
        cout << "\nERROR: primero debe registrar una pieza arqueologica.\n";
        return;
    }

    cout << "\n========== INGRESO DE VERTICES ==========\n";
    cout << "Para representar una figura se requieren de 3 a "
         << MAX_VERTICES << " vertices.\n";

    cantidad_vertices =
        leer_entero("Cantidad de vertices: ", 3, MAX_VERTICES);

    for (int i = 0; i < cantidad_vertices; i++) {
        bool valido;

        do {
            cout << "\nVertice " << i + 1 << endl;

            double x = leer_real("Coordenada X: ");
            double y = leer_real("Coordenada Y: ");

            if (vertice_repetido(x, y, i)) {
                cout << "ERROR: este vertice ya fue registrado.\n";
                valido = false;
            }
            else {
                coordenada_x[i] = x;
                coordenada_y[i] = y;
                valido = true;
            }

        } while (!valido);
    }

    cout << fixed << setprecision(2);
    cout << "\nVertices ingresados:\n";

    for (int i = 0; i < cantidad_vertices; i++) {
        cout << "P" << i + 1 << " = ("
             << coordenada_x[i] << ", "
             << coordenada_y[i] << ")\n";
    }

    if (confirmar("\nDesea guardar los vertices ingresados?")) {
        vertices_registrados = true;
        cout << "\nVertices registrados correctamente.\n";
    }
    else {
        cantidad_vertices = 0;
        vertices_registrados = false;
        cout << "\nRegistro de vertices cancelado.\n";
    }
}

void mostrar_pieza() {
    if (!pieza_registrada) {
        cout << "\nERROR: todavia no existe una pieza registrada.\n";
        return;
    }

    cout << "\n========== DATOS DE LA PIEZA ==========\n";
    cout << "Nombre       : " << nombre_pieza << endl;
    cout << "Procedencia  : " << departamento << ", Peru\n";
    cout << "Tipo         : " << tipo_pieza << endl;

    if (!vertices_registrados) {
        cout << "Vertices     : aun no registrados\n";
        return;
    }

    cout << "N. vertices  : " << cantidad_vertices << endl;

    cout << fixed << setprecision(2);

    for (int i = 0; i < cantidad_vertices; i++) {
        cout << "P" << i + 1 << " = ("
             << coordenada_x[i] << ", "
             << coordenada_y[i] << ")\n";
    }
}

void mostrar_resultados(double x_nuevo[],
                        double y_nuevo[]) {
    cout << fixed << setprecision(2);

    cout << "\nCoordenadas originales y transformadas:\n";

    for (int i = 0; i < cantidad_vertices; i++) {
        cout << "P" << i + 1
             << ": (" << coordenada_x[i] << ", "
             << coordenada_y[i] << ")"
             << " -> (" << x_nuevo[i] << ", "
             << y_nuevo[i] << ")\n";
    }
}

void rotar_pieza() {
    if (!verificar_vertices()) {
        return;
    }

    cout << "\n========== ROTACION DE LA PIEZA ==========\n";

    double angulo;

    do {
        angulo =
            leer_real("Ingrese el angulo en grados (0 a 360): ");

        if (angulo < 0 || angulo > 360) {
            cout << "ERROR: el angulo debe estar entre 0 y 360 grados.\n";
        }

    } while (angulo < 0 || angulo > 360);

    cout << "\nSentido de rotacion:\n";
    cout << "1. Horario\n";
    cout << "2. Antihorario\n";

    int sentido =
        leer_entero("Seleccione una opcion: ", 1, 2);

    cout << "\nAngulo: " << angulo << " grados\n";

    if (sentido == 1) {
        cout << "Sentido: Horario\n";
    }
    else {
        cout << "Sentido: Antihorario\n";
    }

    if (!confirmar("\nDesea aplicar la rotacion?")) {
        cout << "\nRotacion cancelada.\n";
        return;
    }

    double angulo_usado = angulo;

    if (sentido == 1) {
        angulo_usado = -angulo;
    }

    double radianes =
        angulo_usado * PI / 180.0;

    double x_nuevo[MAX_VERTICES];
    double y_nuevo[MAX_VERTICES];

    for (int i = 0; i < cantidad_vertices; i++) {
        x_nuevo[i] =
            coordenada_x[i] * cos(radianes)
            - coordenada_y[i] * sin(radianes);

        y_nuevo[i] =
            coordenada_x[i] * sin(radianes)
            + coordenada_y[i] * cos(radianes);

        if (fabs(x_nuevo[i]) < 0.000001) {
            x_nuevo[i] = 0;
        }

        if (fabs(y_nuevo[i]) < 0.000001) {
            y_nuevo[i] = 0;
        }
    }

    mostrar_resultados(x_nuevo, y_nuevo);

    cout << "\nRotacion realizada correctamente.\n";
}

void reflejar_pieza() {
    if (!verificar_vertices()) {
        return;
    }

    cout << "\n========== REFLEXION DE LA PIEZA ==========\n";
    cout << "1. Reflexion respecto al eje X\n";
    cout << "2. Reflexion respecto al eje Y\n";
    cout << "3. Reflexion respecto al origen\n";

    int opcion =
        leer_entero("Seleccione una opcion: ", 1, 3);

    if (opcion == 1) {
        cout << "\nRegla: (x, y) -> (x, -y)\n";
    }
    else if (opcion == 2) {
        cout << "\nRegla: (x, y) -> (-x, y)\n";
    }
    else {
        cout << "\nRegla: (x, y) -> (-x, -y)\n";
    }

    if (!confirmar("\nDesea aplicar la reflexion?")) {
        cout << "\nReflexion cancelada.\n";
        return;
    }

    double x_nuevo[MAX_VERTICES];
    double y_nuevo[MAX_VERTICES];

    for (int i = 0; i < cantidad_vertices; i++) {
        if (opcion == 1) {
            x_nuevo[i] = coordenada_x[i];
            y_nuevo[i] = -coordenada_y[i];
        }
        else if (opcion == 2) {
            x_nuevo[i] = -coordenada_x[i];
            y_nuevo[i] = coordenada_y[i];
        }
        else {
            x_nuevo[i] = -coordenada_x[i];
            y_nuevo[i] = -coordenada_y[i];
        }
    }

    mostrar_resultados(x_nuevo, y_nuevo);

    cout << "\nReflexion realizada correctamente.\n";
}

void aplicar_homotecia() {
    if (!verificar_vertices()) {
        return;
    }

    cout << "\n========== HOMOTECIA DE LA PIEZA ==========\n";

    double factor =
        leer_real("Ingrese el factor de escala k: ");

    cout << "\nRegla: (x, y) -> (k*x, k*y)\n";
    cout << "Factor k = " << factor << endl;

    if (!confirmar("\nDesea aplicar la homotecia?")) {
        cout << "\nHomotecia cancelada.\n";
        return;
    }

    double x_nuevo[MAX_VERTICES];
    double y_nuevo[MAX_VERTICES];

    for (int i = 0; i < cantidad_vertices; i++) {
        x_nuevo[i] =
            factor * coordenada_x[i];

        y_nuevo[i] =
            factor * coordenada_y[i];

        if (fabs(x_nuevo[i]) < 0.000001) {
            x_nuevo[i] = 0;
        }

        if (fabs(y_nuevo[i]) < 0.000001) {
            y_nuevo[i] = 0;
        }
    }

    mostrar_resultados(x_nuevo, y_nuevo);

    cout << "\nHomotecia realizada correctamente.\n";
}

bool extension_valida(string nombre_archivo) {
    int longitud = nombre_archivo.length();

    if (longitud >= 4) {
        string extension =
            nombre_archivo.substr(longitud - 4, 4);

        for (int i = 0; i < extension.length(); i++) {
            extension[i] =
                tolower((unsigned char)extension[i]);
        }

        if (extension == ".txt" ||
            extension == ".csv") {
            return true;
        }
    }

    return false;
}

void cargar_archivo() {
    if (!pieza_registrada) {
        cout << "\nERROR: primero debe registrar una pieza arqueologica.\n";
        return;
    }

    cout << "\n========== CARGAR ARCHIVO ==========\n";
    cout << "Formatos permitidos: .txt y .csv\n";
    cout << "Ejemplo de datos:\n";
    cout << "2,1\n";
    cout << "6,1\n";
    cout << "5,4\n";

    string nombre_archivo;

    cout << "\nIngrese el nombre o ruta del archivo: ";
    getline(cin, nombre_archivo);

    if (!extension_valida(nombre_archivo)) {
        cout << "\nERROR: el archivo debe ser .txt o .csv.\n";
        return;
    }

    ifstream archivo(nombre_archivo.c_str());

    if (!archivo.is_open()) {
        cout << "\nERROR: no se pudo abrir el archivo.\n";
        return;
    }

    double x_temporal[MAX_VERTICES];
    double y_temporal[MAX_VERTICES];

    int cantidad_temporal = 0;
    string linea;
    bool archivo_valido = true;

    while (getline(archivo, linea) &&
           cantidad_temporal < MAX_VERTICES) {

        if (linea.length() == 0) {
            continue;
        }

        for (int i = 0; i < linea.length(); i++) {
            if (linea[i] == ',' ||
                linea[i] == ';') {
                linea[i] = ' ';
            }
        }

        int posicion_espacio = -1;

        for (int i = 0; i < linea.length(); i++) {
            if (linea[i] == ' ') {
                posicion_espacio = i;
                break;
            }
        }

        if (posicion_espacio == -1) {
            archivo_valido = false;
            break;
        }

        string dato_x = linea.substr(0, posicion_espacio);
        string dato_y = linea.substr(posicion_espacio + 1);

        while (dato_y.length() > 0 && dato_y[0] == ' ') {
            dato_y.erase(0, 1);
        }

        if (!real_valido(dato_x) || !real_valido(dato_y)) {
            archivo_valido = false;
            break;
        }

        double x = atof(dato_x.c_str());
        double y = atof(dato_y.c_str());

        bool repetido = false;

        for (int i = 0; i < cantidad_temporal; i++) {
            if (x_temporal[i] == x &&
                y_temporal[i] == y) {
                repetido = true;
            }
        }

        if (repetido) {
            archivo_valido = false;
            break;
        }

        x_temporal[cantidad_temporal] = x;
        y_temporal[cantidad_temporal] = y;

        cantidad_temporal++;
    }

    archivo.close();

    if (!archivo_valido) {
        cout << "\nERROR: el archivo contiene datos invalidos.\n";
        return;
    }

    if (cantidad_temporal < 3) {
        cout << "\nERROR: el archivo debe contener al menos 3 vertices.\n";
        return;
    }

    cout << fixed << setprecision(2);
    cout << "\nVertices encontrados:\n";

    for (int i = 0; i < cantidad_temporal; i++) {
        cout << "P" << i + 1 << " = ("
             << x_temporal[i] << ", "
             << y_temporal[i] << ")\n";
    }

    if (!confirmar("\nDesea cargar estos vertices?")) {
        cout << "\nCarga cancelada.\n";
        return;
    }

    cantidad_vertices = cantidad_temporal;

    for (int i = 0; i < cantidad_vertices; i++) {
        coordenada_x[i] = x_temporal[i];
        coordenada_y[i] = y_temporal[i];
    }

    vertices_registrados = true;

    cout << "\nArchivo cargado correctamente.\n";
}

void mostrar_menu() {
    cout << "\n=================================================\n";
    cout << "   RECONSTRUCCION DE PATRIMONIO ARQUEOLOGICO\n";
    cout << "                  DEL PERU\n";
    cout << "=================================================\n";
    cout << "1. Registrar pieza arqueologica\n";
    cout << "2. Ingresar vertices\n";
    cout << "3. Mostrar datos de la pieza\n";
    cout << "4. Aplicar rotacion\n";
    cout << "5. Aplicar reflexion\n";
    cout << "6. Aplicar homotecia\n";
    cout << "7. Cargar archivo (.txt / .csv)\n";
    cout << "8. Salir\n";
    cout << "=================================================\n";
}

int main() {
    int opcion;

    do {
        mostrar_menu();

        opcion =
            leer_entero("Seleccione una opcion: ", 1, 8);

        switch (opcion) {
            case 1:
                registrar_pieza();
                break;

            case 2:
                ingresar_vertices();
                break;

            case 3:
                mostrar_pieza();
                break;

            case 4:
                rotar_pieza();
                break;

            case 5:
                reflejar_pieza();
                break;

            case 6:
                aplicar_homotecia();
                break;

            case 7:
                cargar_archivo();
                break;

            case 8:
                cout << "\nPrograma finalizado.\n";
                break;

            default:
                cout << "\nOpcion no valida.\n";
        }

    } while (opcion != 8);

    return 0;
}
