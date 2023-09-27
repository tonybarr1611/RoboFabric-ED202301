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

    Producto *producto = new Producto("101", 100 , 5 ,"A" ,"X10");
    producto->imprimir();
    ListaSimple * Lista = producto->ConvertirEnListaSimple();
    Lista->imprimir();
    cout << "----------------------------------------------------------------------------------" << endl;
    ListaCompleja * listaDeProductos = new ListaCompleja();
    listaDeProductos->agregar("Producto", Lista);
    listaDeProductos->imprimir();
    Constructor * constructor = new Constructor("C1", 0, "101");
    constructor->AgregarCantidadAlProducto(listaDeProductos);
    listaDeProductos->imprimir();
    cout << "----------------------------------------------------------------------------------" << endl;
    ListaSimple *ListaClientesArchivo = LeerDirectorio("Clientes", "txt");
    ListaClientesArchivo->imprimir();
    cout << "----------------------------------------------------------------------------------" << endl;
    NodoSimple *nodo = ListaClientesArchivo->primerNodo;
    while (nodo != NULL){
        cout << nodo->dato << endl;
        ListaCompleja *ListaClientes = LeerArchivo(nodo, "Cliente");
        ListaClientes->imprimir();
        nodo = nodo->siguiente;
        cout << "-----------------------------------" << endl;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
    ListaCompleja *ListaProductosArchivo = LeerArchivo("Clientes", "txt", "Cliente");
    ListaProductosArchivo->imprimir();
    return 0;
}