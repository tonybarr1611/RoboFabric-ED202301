#include "Estructuras.h"

int main(int argc, char** argv) {
    cout << "RoboFabric 2023/01" << endl;
    string linea = "Hola\tMundo\tCruel\tAdios\tMundo\tCruel";
    ListaSimple *lista = SepararStringsPorTabs(linea);
    cout << "\nLista de strings:" << endl;
    lista->imprimir();

    linea = "Hola\tMundo\tCruel\nAdios\tMundo\tCruel";
    cout << "\nLista de strings compleja:" << endl;
    ListaCompleja *lista2 = SepararStringsPorLineas(linea, "Cliente");
    lista2->imprimir();
}