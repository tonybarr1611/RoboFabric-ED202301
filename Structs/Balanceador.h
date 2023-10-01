struct Balanceador {
    Constructor * ArrayConstructores [10]; //Iterar
    queue<ListaCompleja*> Altaprioridad;
    queue<ListaCompleja*> Bajaprioridad;
    queue<ListaCompleja*> PedidoInstantaneo;
    ListaCompleja * ListaProductos;
    int Estado; // 0 = Apagado, 1 = Encendido, 2 = En proceso

    //constructor 
    Balanceador() {
        Estado = 0;
        for (int i = 0; i < 10; i++) {
            ArrayConstructores[i] = new Constructor();
        }
        ListaProductos = new ListaCompleja();
        // Inicializa las colas aquí, por ejemplo, si deseas que estén vacías:
        while (!Altaprioridad.empty()) Altaprioridad.pop();
        while (!Bajaprioridad.empty()) Bajaprioridad.pop();
        while (!PedidoInstantaneo.empty()) PedidoInstantaneo.pop();
    }

    Balanceador(int Estado, ListaCompleja * ListaProductos, queue<ListaCompleja*> Altaprioridad, queue<ListaCompleja*> Bajaprioridad, queue<ListaCompleja*> PedidoInstantaneo) {
        this->Altaprioridad = Altaprioridad;
        this->Bajaprioridad = Bajaprioridad;
        this->PedidoInstantaneo = PedidoInstantaneo;
        this->ListaProductos = ListaProductos; 
        this->Estado = Estado;
        for (int i = 0; i < 10; i++) {
            ArrayConstructores[i] = new Constructor("Constructor " + to_string(i), 1, true, "D");
        }
    }

    //Metodos
    void MetePedidoEncola(ListaSimple * ListaPedidos, ListaCompleja * ListaClientes){
        //Esta Funcion Unicamente Comprueba un pedidos en ListaPedidos en caso da dar error los mueves al archivo de error
        ListaCompleja * PedidoActual= LeerArchivo(ListaPedidos->primerNodo , "Pedido");
        ListaSimple * Bitacora = new ListaSimple();
        int Prioridad = RetornaPrioridad(ListaClientes, PedidoActual->primerNodo->siguiente->lista->primerNodo->dato);

        cout << "Se esta procesando el pedido: " << PedidoActual->primerNodo->lista->primerNodo->dato << endl;
        Bitacora->agregar("Pedido:\t\t" + PedidoActual->primerNodo->lista->primerNodo->dato);
        Bitacora->agregar("Cliente:\t\t" + PedidoActual->primerNodo->siguiente->lista->primerNodo->dato);
        PedidoActual->agregar("Bitacora", Bitacora);
        if (Prioridad == 10){
            // Recupera la hora del sistema y la agrega a la bitacora
            Bitacora->agregar("Cola:\t\t Alta Prioridad - " + HoraSistema());
            Altaprioridad.push(PedidoActual);
        }else if (Prioridad  < 10){
            Bitacora->agregar("Cola:\t\t Baja Prioridad - " + HoraSistema());
            Bajaprioridad.push(PedidoActual);
        }else if (Prioridad == 11){
            cout << "Se metio a la cola de pedido instantaneo" << endl;
            Bitacora->agregar("Cola:\t\t Pedido Instantaneo - " + HoraSistema());
            PedidoInstantaneo.push(PedidoActual);
        }else if (PedidoActual->primerNodo->siguiente->siguiente == NULL)
        // TODO Codigo que mueve archivos a error, no es un pedido
        cout << "Se metio el pedido a la cola" << endl;
    }
    ListaCompleja * RetornaPedido(){
        //Esta funcion retorna el pedido que se va a procesar
        ListaCompleja * PedidoActual = NULL;
        if (!Altaprioridad.empty()){
            PedidoActual = Altaprioridad.front();
            Altaprioridad.pop();
        }else if (!Bajaprioridad.empty()){
            PedidoActual = Bajaprioridad.front();
            Bajaprioridad.pop();
        }else if (!PedidoInstantaneo.empty()){
            PedidoActual = PedidoInstantaneo.front();
            PedidoInstantaneo.pop();
        }
        return PedidoActual;
    }

    Constructor * RetornaConstructorValido(string tipoProducto){
        //Esta funcion retorna el constructor que se va a usar
        for (int i = 0; i < 10; i++){
            if (ArrayConstructores[i]->tipoProducto == tipoProducto && ArrayConstructores[i]->Disponibilidad == true){
                return ArrayConstructores[i];
            }else if (ArrayConstructores[i]->tipoProducto == "D" && ArrayConstructores[i]->Disponibilidad == true){
                return ArrayConstructores[i];
            }
        }
        return NULL;
    }

    void ConstruirProductos(int ProductosNecesitados, listaCompleja * ProductoBuscado){
        ProductoBuscado->lista->primerNodo->siguiente->dato = "0";
        cout << "No hay suficiente productos: " << CodigoProducto << "por lo tanto se construiran" << endl;
        Constructor * ConstructorValido = RetornaConstructorValido(ProductoBuscado->lista->primerNodo->siguiente->siguiente->dato);
        ConstructorValido->AgregarCantidadAlProducto(ListaProductos, CodigoProducto, Res);

        while (ConstructorValido->Disponibilidad == false ){
            cout << "Construyendo" << endl;
        }
    }
    
    void IniciaPedido(){
        //Esta funcion inicia el pedido, si no hay pedidos en las colas, no hace nada
        ListaCompleja * PedidoActual = RetornaPedido();
        if (PedidoActual == NULL){
            cout << "No hay pedidos en las colas" << endl;
            return; 
        }
        NodoComplejo * tmp= PedidoActual->primerNodo->siguiente->siguiente;
        cout << "El pedido: " << PedidoActual->primerNodo->lista->primerNodo->dato << ". Esta siendo procesado" << endl;
        while (tmp != NULL && tmp -> tipo != "Bitacora"){
            string CodigoProducto = tmp -> lista -> primerNodo -> dato;
            int CantidadNecesitada = stoi(tmp -> lista -> primerNodo -> siguiente -> dato);
            NodoComplejo * ProductoBuscado = ListaProductos->Buscar(CodigoProducto);
            int CantidadAlmacenada = stoi(ProductoBuscado->lista->primerNodo->siguiente->dato);
            int Res = CantidadAlmacenada - CantidadNecesitada;
            if (Res < 0){
                Res = CantidadNecesitada - CantidadAlmacenada;
                ConstruirProductos(Res, ProductoBuscado);

            }else if (Res >= 0){
                cout << "Se esta procesando el producto: " << CodigoProducto << endl;
                ProductoBuscado->lista->primerNodo->siguiente->dato = to_string(Res);
            }
            tmp = tmp -> siguiente;
        }
        cout << "El pedido: " << PedidoActual->primerNodo->lista->primerNodo->dato << ". Ha sido procesado" << endl;
        //TODO Enviar a cola de almacen 
    }
};