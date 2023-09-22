#include "Estructuras.h"

int main(int argc, char** argv) {
    cout << "RoboFabric 2023/01" << endl;
    string linea = "Hola\tMundo\tCruel";
    ListaSimple lista = SepararStringsPorTabs(linea);
    lista.imprimir();
}