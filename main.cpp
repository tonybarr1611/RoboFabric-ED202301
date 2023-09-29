#include "Estructuras.h"

int main(int argc, char** argv) {
    cout << "RoboFabric 2023/01" << endl;
    

    cout << "--------------------------------------------------------------------" << endl; 
    cout << "Beta de la implementacion de la lista de Productos" << endl;
    ListaCompleja * listaDeProductos = LeerArchivo("Productos", "txt", "Producto");
    listaDeProductos->primerNodo->imprimir();
    listaDeProductos->imprimir();

    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "Beta de la implementacion de la lista de Clientes" << endl;
    ListaSimple *ListaClientesArchivo = LeerDirectorio("Clientes", "txt");
    ListaClientesArchivo->imprimir();
    NodoSimple *nodo = ListaClientesArchivo->primerNodo;
    while (nodo != NULL){
        cout << nodo->dato << endl;
        ListaCompleja *ListaClientes = LeerArchivo(nodo, "Cliente");
        ListaClientes->imprimir();
        nodo = nodo->siguiente;
        cout << "-----------------------------------" << endl;
    }
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "Beta de la implementacion de pedidos" << endl;
    ListaSimple *ListaPedidos = LeerDirectorio("Pedidos//Pendientes", "txt");
    ListaPedidos->imprimir();
    NodoSimple * tmp = ListaPedidos->primerNodo;
    ListaCompleja * ListaPedidosCompleja;
    while(tmp != NULL){
        ListaPedidosCompleja = LeerArchivo(tmp, "Pedido");
        tmp = tmp->siguiente;
    }

    ListaPedidosCompleja->imprimir();
    
    
    cout << "----------------------------------------------------------------------------------" << endl;

    return 0;
}