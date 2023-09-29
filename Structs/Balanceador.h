struct Balanceador {
    Constructor * ArrayConstructores [10]; //Iterar
    queue<ListaCompleja*> Altaprioridad;
    queue<ListaCompleja*> Bajaprioridad;
    queue<ListaCompleja*> PedidoInstantaneo;
    int Estado; // 0 = Apagado, 1 = Encendido, 2 = En proceso

    //constructor 
    Balanceador() {
    Estado = 0;
    for (int i = 0; i < 10; i++) {
        ArrayConstructores[i] = new Constructor();
    }
    // Inicializa las colas aquí, por ejemplo, si deseas que estén vacías:
    while (!Altaprioridad.empty()) Altaprioridad.pop();
    while (!Bajaprioridad.empty()) Bajaprioridad.pop();
    while (!PedidoInstantaneo.empty()) PedidoInstantaneo.pop();
    }

    Balanceador(queue<ListaCompleja*> Altaprioridad, queue<ListaCompleja*> Bajaprioridad, queue<ListaCompleja*> PedidoInstantaneo, int Estado){
        this->Altaprioridad = Altaprioridad;
        this->Bajaprioridad = Bajaprioridad;
        this->PedidoInstantaneo = PedidoInstantaneo;
        this->Estado = Estado;
    }

    //Metodos 

    void ComprobarPedido(ListaSimple * ListaPedidos, ListaCompleja * ListaClientes){
        //Esta Funcion Unicamente Comprueba un pedidos en ListaPedidos en caso da dar error los mueves al archivo de error
        NodoSimple  * tmp = ListaPedidos->primerNodo;
        ListaCompleja * PedidoActual= new ListaCompleja(); 
        while (tmp != NULL){
            PedidoActual = LeerArchivo(tmp , "Pedido");
        int Prioridad = RetornaPrioridad(ListaClientes, PedidoActual->primerNodo->siguiente->lista->primerNodo->dato);
        if (Prioridad == 10){
            Altaprioridad.push(PedidoActual);
        }
        if (Prioridad  < 10){
            Bajaprioridad.push(PedidoActual);
        }
        if (Prioridad == 11){
            PedidoInstantaneo.push(PedidoActual);
        }
        if (PedidoActual->primerNodo->siguiente->siguiente== NULL)
        //Codigo que mueve archivos a error, no es un pedido
        tmp = tmp -> siguiente;
        } 
        cout << "Se metieron todos los pedidos a las colas" << endl;
        return ;
}
    void IniciaPedido(){
        //Esta funcion inicia el pedido, si no hay pedidos en las colas, no hace nada
        if (Altaprioridad.empty() && Bajaprioridad.empty() && PedidoInstantaneo.empty()){
            cout << "No hay pedidos en las colas" << endl;
        }
        else{
            if (!Altaprioridad.empty()){
                ListaSimple * Bitacora = new ListaSimple();
                ListaCompleja * PedidoActual = Altaprioridad.front();
                cout << "El pedido:" << PedidoActual->primerNodo->lista->primerNodo->dato << "Esta siendo procesado" << endl;
                Altaprioridad.pop();
                NodoComplejo * tmp= PedidoActual->primerNodo->siguiente->siguiente;
                while (tmp != NULL){
                    string CodigoProducto = tmp -> primerNodo -> lista -> primerNodo -> dato 
                    int cantidad = tmp -> primerNodo -> lista -> primerNodo -> siguiente -> dato 
                };
            }
            else{
                if (!Bajaprioridad.empty()){
                  return ;  
                }
                else{
                    return ;
                }
            }
        }
    }

};