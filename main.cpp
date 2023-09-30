#include "Estructuras.h"

int main(int argc, char** argv) {
    cout << "RoboFabric 2023/01" << endl;
    

    cout << "--------------------------------------------------------------------" << endl; 
    cout << "Beta de la implementacion de la lista de Productos" << endl;
    ListaCompleja * listaDeProductos = LeerArchivo("Productos", "txt", "Producto");
    //listaDeProductos->imprimir();
    listaDeProductos->primerNodo->lista->primerNodo->imprimir();
    listaDeProductos->primerNodo->lista->Buscar("X09");
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "Beta de la implementacion de la lista de Clientes" << endl;
    ListaSimple *ListaClientesArchivo = LeerDirectorio("Clientes", "txt");
    ListaClientesArchivo->imprimir();
    NodoSimple *nodo = ListaClientesArchivo->primerNodo;
    ListaCompleja *ListaClientes = LeerArchivo(nodo, "Cliente");
    ListaClientes->imprimir();
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "Beta de la implementacion de pedidos" << endl;
    
    ListaSimple *ListaNombresDePedidos = LeerDirectorio("Pedidos//Pendientes", "txt");
    ListaNombresDePedidos->imprimir();
    queue<ListaCompleja*> Altaprioridad;
    queue<ListaCompleja*> Bajaprioridad;
    queue<ListaCompleja*> PedidoInstantaneo;

    Balanceador * balanceador = new Balanceador(1, listaDeProductos, Altaprioridad, Bajaprioridad, PedidoInstantaneo);
    ListaCompleja * PedidoActual = LeerArchivo(ListaNombresDePedidos->primerNodo , "Pedido");
    balanceador->MetePedidoEncola(ListaNombresDePedidos, ListaClientes);
    bool aja = balanceador->Altaprioridad.empty();
    cout << aja << endl;
    balanceador->PedidoInstantaneo.front()->imprimir();
    
    cout << "----------------------------------------------------------------------------------" << endl;

    return 0;
}