struct Balanceador {
    Constructor * ArrayConstructores [10]; //Iterar
    queue<ListaCompleja*> Altaprioridad;
    queue<ListaCompleja*> Bajaprioridad;
    queue<ListaCompleja*> PedidoInstantaneo;
    queue<ListaCompleja*> * pedidosAlmacen;
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

    Balanceador(int Estado, ListaCompleja * ListaProductos, queue<ListaCompleja*> Altaprioridad, queue<ListaCompleja*> Bajaprioridad, queue<ListaCompleja*> PedidoInstantaneo, queue<ListaCompleja*> * pedidosAlmacen) {
        this->Altaprioridad = Altaprioridad;
        this->Bajaprioridad = Bajaprioridad;
        this->PedidoInstantaneo = PedidoInstantaneo;
        this->ListaProductos = ListaProductos; 
        this->Estado = Estado;
        this->pedidosAlmacen = pedidosAlmacen;
        for (int i = 0; i < 10; i++) {
            ArrayConstructores[i] = new Constructor("Constructor " + to_string(i), 1, true, "D", ListaProductos);
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

    Constructor *  ConstruirProductos(int ProductosNecesitados, NodoComplejo * ProductoBuscado){
        string CodigoProducto = ProductoBuscado -> lista -> primerNodo -> dato;
        ProductoBuscado->lista->primerNodo->siguiente->dato = "0";
        Constructor * ConstructorValido = RetornaConstructorValido(ProductoBuscado->lista->primerNodo->siguiente->siguiente->dato);
        // TODO llamar por medio de thread
        ConstructorValido->AgregarCantidadAlProducto(CodigoProducto, ProductosNecesitados);
        return ConstructorValido;
    }

    void validarFinalPedido(queue<Constructor*> ConstructoresUsados, ListaCompleja * PedidoActual){
        //Esta funcion valida si el pedido se completo, si no se completo, sigue loopeando hasta que lo este
        // Solo llamar por medio de thread
        while (!ConstructoresUsados.empty()){
            if (ConstructoresUsados.front()->Disponibilidad == true){
                ConstructoresUsados.pop();
            }
        }
        if (ConstructoresUsados.empty()){
            cout << "El pedido: " << PedidoActual->primerNodo->lista->primerNodo->dato << ". Ha sido procesado" << endl;
            pedidosAlmacen->push(PedidoActual);
        }
    }

    void VerificaProductos(int cantidad, queue<Constructor*> ConstructoresUsados, string CodigoProducto){
        //Verifica que hayan productos en el almacen si no pone los constructores a trabajar
        NodoComplejo * ProductoBuscado = ListaProductos->Buscar(CodigoProducto);
        if (cantidad < 0){
            cout << "No hay suficientes productos: " << CodigoProducto << " por lo tanto se construiran" << endl;
            cantidad = -cantidad;
            ConstructoresUsados.push(ConstruirProductos(cantidad, ProductoBuscado));

        }else if (cantidad >= 0){
            cout << "Se esta procesando el producto: " << CodigoProducto << endl;
            ProductoBuscado->lista->primerNodo->siguiente->dato = to_string(cantidad);
            }
    }

    void IniciaPedido(){
        //Esta funcion inicia el pedido, si no hay pedidos en las colas, no hace nada
        ListaCompleja * PedidoActual = RetornaPedido();
        queue<Constructor*> ConstructoresUsados;
        if (PedidoActual == NULL){
            cout << "No hay pedidos en las colas" << endl;
            return; 
        }
        NodoComplejo * tmp= PedidoActual->primerNodo->siguiente->siguiente;
        cout << "El pedido: " << PedidoActual->primerNodo->lista->primerNodo->dato << ". Esta siendo procesado" << endl;
        while (tmp != NULL && tmp -> tipo != "Bitacora"){
            //Variables
            NodoSimple * tmp2 = tmp -> lista -> primerNodo;
            string CodigoProducto = tmp2 -> dato;
            int CantidadNecesitada = stoi(tmp2-> siguiente -> dato);
            int CantidadAlmacenada = stoi(ListaProductos->Buscar(CodigoProducto)->lista->primerNodo->siguiente->dato);
            int Res = CantidadAlmacenada - CantidadNecesitada;
            VerificaProductos(Res, ConstructoresUsados, CodigoProducto);
            tmp = tmp -> siguiente;
        }
        // TODO llamar por medio de thread
        validarFinalPedido(ConstructoresUsados, PedidoActual);
    }
};