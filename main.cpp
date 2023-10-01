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
    queue<ListaCompleja*> * pedidosAlmacen = new queue<ListaCompleja*>;

    Balanceador * balanceador = new Balanceador(1, listaDeProductos, Altaprioridad, Bajaprioridad, PedidoInstantaneo, pedidosAlmacen);
    ListaCompleja * PedidoActual = LeerArchivo(ListaNombresDePedidos->primerNodo , "Pedido");
    balanceador->ArrayConstructores[2]->imprimir();
    balanceador->MetePedidoEncola(ListaNombresDePedidos, ListaClientes);
    balanceador->IniciaPedido();
    pedidosAlmacen->front()->imprimir();
    
    
    cout << "----------------------------------------------------------------------------------" << endl;

    cout << "Beta de la implementacion de la lista de Alistadores" << endl;
    Alistador * alistador = new Alistador(true, 1, listaDeProductos);
    alistador->imprimir();
    PedidoActual->primerNodo->siguiente->siguiente->imprimir();
    // alistador->Alistar(PedidoActual);


    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "Beta de la implementacion de la lista de Empacadores" << endl;
    queue<ListaCompleja*> * PorFacturar = new queue<ListaCompleja*>;
    Empacador * empacador = new Empacador(true, PorFacturar);
    
    empacador->Empacar(PedidoActual);
    return 0;
}