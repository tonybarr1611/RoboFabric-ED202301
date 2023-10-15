struct Balanceador {
    Constructor * ArrayConstructores [10]; //Iterar
    queue<ListaCompleja*> Altaprioridad;
    queue<ListaCompleja*> Bajaprioridad;
    queue<ListaCompleja*> PedidoInstantaneo;
    queue<ListaCompleja*> * pedidosAlmacen;
    ListaCompleja * ListaProductos;
    ListaCompleja * ListaClientes;
    ListaSimple * ListaPedidos;
    string Accion; 
    ListaSimple * HistorialColasBalanceador;
    ListaSimple * HistorialColaAlmacen;
    int Estado = 1; // 0 = Apagado, 1 = Encendido

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
        ListaCompleja * ListaProductos = new ListaCompleja();
        ListaCompleja * ListaClientes = new ListaCompleja();
        ListaSimple * ListaPedidos = new ListaSimple();
        pedidosAlmacen = new queue<ListaCompleja*>();
        HistorialColasBalanceador = new ListaSimple();
        Accion = "Leyendo Pedidos de la cola";
        HistorialColaAlmacen = new ListaSimple();

    }

    Balanceador(int Estado, ListaCompleja * ListaProductos, queue<ListaCompleja*> Altaprioridad, queue<ListaCompleja*> Bajaprioridad, queue<ListaCompleja*> PedidoInstantaneo, queue<ListaCompleja*> * pedidosAlmacen, ListaCompleja * ListaClientes, ListaSimple * ListaPedidos, ListaSimple * _HistorialColaAlmacen) {
        this->Altaprioridad = Altaprioridad;
        this->Bajaprioridad = Bajaprioridad;
        this->PedidoInstantaneo = PedidoInstantaneo;
        this->ListaProductos = ListaProductos; 
        this->Estado = Estado;
        this->pedidosAlmacen = pedidosAlmacen;
        this->ListaClientes = ListaClientes;
        this->ListaPedidos = ListaPedidos;
        Accion = "Leyendo Pedidos de la cola";
        for (int i = 0; i < 10; i++) {
            ArrayConstructores[i] = new Constructor();
        }
        HistorialColasBalanceador = new ListaSimple();
        HistorialColaAlmacen = _HistorialColaAlmacen;
    }

    //Metodos
    void ModificaConstructorPrioridad(int Posicion, string Prioridad){
        //Esta funcion modifica la prioridad del constructor
        if (Prioridad == "S")
            ArrayConstructores[Posicion]->Prioridad = true;
        else
            ArrayConstructores[Posicion]->Prioridad = false;
        
    }   

    void ModificaConstructorTipo(int Posicion, string Tipo){
        //Esta funcion modifica el tipo de producto que puede construir el constructor
        ArrayConstructores[Posicion]->tipoProducto = Tipo;
    }	

    void ModificaConstructorEstado(int posicion){
        //Esta funcion modifica el estado del constructor
        if (Estado == 0)
            ArrayConstructores[posicion]->Estado = 1;
        else
            ArrayConstructores[posicion]->Estado = 0;
    }



    void ImprimeConstructores(){
        //Esta funcion imprime los constructores
        cout << endl;
        for (int i = 0; i < 10; i++){
            cout << "Posicion: " << i << endl;
            ArrayConstructores[i]->imprimir();
            cout << endl;
        }
    }

    void ImprimeNombreConstructores(){
        cout << endl;
        for (int i = 0; i < 10; i++){
            cout << "Posicion: " << i << endl;
            cout << ArrayConstructores[i]->Nombre << endl;
            if (ArrayConstructores[i]->Estado == 1)
                cout << "Prendido" << endl;
            else 
                cout << "Apagado" << endl;
            cout << endl;
        }
    }
    void CargaConstructores(ListaCompleja* ListaConstructores){
        //Esta funcion carga los constructores en el array de constructores
        NodoComplejo * tmp = ListaConstructores->primerNodo;
        int contador = 0;
        while (tmp != NULL){
            ArrayConstructores[contador] = new Constructor(tmp->lista->primerNodo->dato, stoi(tmp->lista->primerNodo->siguiente->dato), true, tmp->lista->primerNodo->siguiente->siguiente->dato, tmp->lista->primerNodo->siguiente->siguiente->siguiente->dato , ListaProductos);
            tmp = tmp->siguiente;
            contador++;
        }
    }
    string EncuentraErrorPedido(NodoSimple * Directorio){
        //Esta funcion encuentra el error en el pedido y lo retorna en un tipo string 
        ListaCompleja * PedidoActual = LeerArchivo(Directorio, "Pedido");
        if (ListaClientes->Buscar(PedidoActual->primerNodo->siguiente->lista->primerNodo->dato) == NULL ){
            return "Error: El cliente no existe";
        }else if (PedidoActual->primerNodo->siguiente->siguiente == NULL){
            return "Error: No hay productos en el pedido";
        }
        NodoComplejo * tmp = PedidoActual->primerNodo->siguiente->siguiente;
        while (tmp != NULL){
            if (ListaProductos->Buscar(tmp->lista->primerNodo->dato) == NULL)
                return "Error: El producto: " + tmp->lista->primerNodo->dato + " no existe";
        tmp = tmp->siguiente;
        }
        return "true";
    }
    
    ListaCompleja * ValidaArchivo(ListaSimple * Listapedidos ){
        //Esta funcion valida el archivo, si no hay error retorna el pedido y lo mueve a procesados, si hay error lo mueve a la carpeta de error
        if (Listapedidos->primerNodo == NULL){
            //cout << "No hay pedidos en la lista" << endl;
            return NULL;
        }
        string definer = EncuentraErrorPedido(Listapedidos->primerNodo);
        //cout << nombreArchivo(Listapedidos->primerNodo->dato) << endl;
        if (definer == "true"){
            MoverArchivotxt("Pedidos/Pendientes/" + nombreArchivo(Listapedidos->primerNodo->dato), "Pedidos/Procesados");
            ListaPedidos->primerNodo->dato = "Pedidos/Procesados/" + nombreArchivo(Listapedidos->primerNodo->dato);
            return LeerArchivo(Listapedidos->primerNodo, "Pedido");
        }else{
            string Archivo = "Pedidos//Pendientes//" + nombreArchivo(Listapedidos->primerNodo->dato);
            EscribirArchivo(Archivo, definer);
            MoverArchivotxt("Pedidos/Pendientes/" + nombreArchivo(Listapedidos->primerNodo->dato), "Pedidos/Errores");
        }
        return NULL;
    }

    void MetePedidoEncola(){
        //Esta Funcion Unicamente Comprueba un pedidos en ListaPedidos en caso da dar error los mueves al archivo de error
        //Valida el archivo
        ListaCompleja * PedidoActual = ValidaArchivo(ListaPedidos);
        if (PedidoActual == NULL)
            return;
        ListaPedidos->eliminarinicio();
        //Variables
        ListaSimple * Bitacora = new ListaSimple();
        int Prioridad = RetornaPrioridad(ListaClientes, PedidoActual->primerNodo->siguiente->lista->primerNodo->dato);

        //Funcionamiento
        Bitacora->agregar("\t\tBitacora");
        Bitacora->agregar("Pedido:\t\t" + PedidoActual->primerNodo->lista->primerNodo->dato);
        Bitacora->agregar("Cliente:\t\t" + PedidoActual->primerNodo->siguiente->lista->primerNodo->dato);
        PedidoActual->agregar("Bitacora", Bitacora);
        if (Prioridad == 10){
            // Recupera la hora del sistema y la agrega a la bitacora
            Bitacora->agregar("Cola:\t\t Alta Prioridad - " + HoraSistema());
            Altaprioridad.push(PedidoActual);
            HistorialColasBalanceador->agregar("Entra pedido: " + PedidoActual->primerNodo->lista->primerNodo->dato + " - " + HoraSistema() + " a la cola de alta prioridad");
        }else if (Prioridad  < 10){
            Bitacora->agregar("Cola:\t\t Baja Prioridad - " + HoraSistema());
            Bajaprioridad.push(PedidoActual);
            HistorialColasBalanceador->agregar("Entra pedido: " + PedidoActual->primerNodo->lista->primerNodo->dato + " - " + HoraSistema() + " a la cola de baja prioridad");
        }else if (Prioridad == 11){
            //cout << "Se metio a la cola de pedido instantaneo" << endl;
            Bitacora->agregar("Cola:\t\t Pedido Instantaneo - " + HoraSistema());
            PedidoInstantaneo.push(PedidoActual);
            HistorialColasBalanceador->agregar("Entra pedido: " + PedidoActual->primerNodo->lista->primerNodo->dato + " - " + HoraSistema() + " a la cola de pedido instantaneo");
        }
    }
    void MetePedidoEncolaThread(bool * isRunning){
        while (* isRunning){
            MetePedidoEncola();
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }
    }

    ListaCompleja * RetornaPedido(){
        //Esta funcion retorna el pedido que se va a procesar
        ListaCompleja * PedidoActual = NULL;
        if (!PedidoInstantaneo.empty()){
            PedidoActual = PedidoInstantaneo.front();
            PedidoInstantaneo.pop();
            HistorialColasBalanceador->agregar("Sale pedido: " + PedidoActual->primerNodo->lista->primerNodo->dato + " - " + HoraSistema() + " de la cola de pedido instantaneo");
        }else if (!Bajaprioridad.empty()){
            PedidoActual = Bajaprioridad.front();
            Bajaprioridad.pop();
            HistorialColasBalanceador->agregar("Sale pedido: " + PedidoActual->primerNodo->lista->primerNodo->dato + " - " + HoraSistema() + " de la cola de baja prioridad");
        }else if (!Altaprioridad.empty()){
            PedidoActual = Altaprioridad.front();
            Altaprioridad.pop();
            HistorialColasBalanceador->agregar("Sale pedido: " + PedidoActual->primerNodo->lista->primerNodo->dato + " - " + HoraSistema() + " de la cola de alta prioridad");
        }
        return PedidoActual;
    }

    Constructor * RetornaConstructorValido(string tipoProducto){
        //Esta funcion retorna el constructor que se va a usar
        //Comprueba la prioridad
        
        for (int i = 0; i < 10; i++){
            if (ArrayConstructores[i]->Prioridad == true && ArrayConstructores[i]->tipoProducto == tipoProducto && ArrayConstructores[i]->Disponibilidad == true && ArrayConstructores[i]->Estado == 1)
                return ArrayConstructores[i];
            else if (ArrayConstructores[i]->Prioridad == true && ArrayConstructores[i]->tipoProducto == "D" && ArrayConstructores[i]->Disponibilidad == true && ArrayConstructores[i]->Estado == 1)
                return ArrayConstructores[i];
        }
        
        for (int i = 0; i < 10; i++){
            if (ArrayConstructores[i]->tipoProducto == tipoProducto && ArrayConstructores[i]->Disponibilidad == true && ArrayConstructores[i]->Estado == 1)
                return ArrayConstructores[i];
            else if (ArrayConstructores[i]->tipoProducto == "D" && ArrayConstructores[i]->Disponibilidad == true && ArrayConstructores[i]->Estado == 1)
                return ArrayConstructores[i];
            }
        return NULL;
    }

    Constructor *  ConstruirProductos(int ProductosNecesitados, NodoComplejo * ProductoBuscado){
        string CodigoProducto = ProductoBuscado -> lista -> primerNodo -> dato;
        ProductoBuscado->lista->primerNodo->siguiente->dato = "0";
        Constructor * ConstructorValido = RetornaConstructorValido(ProductoBuscado->lista->primerNodo->siguiente->siguiente->dato);
        ConstructorValido->Disponibilidad = false;
        if (ConstructorValido == NULL){
            cout << "No hay constructores disponibles para el producto: " << CodigoProducto << endl;
            return NULL;
        }
        std::thread hilo(&Constructor::AgregarCantidadAlProducto, ConstructorValido, CodigoProducto, ProductosNecesitados);
        hilo.detach();
        return ConstructorValido;
    }

    void validarFinalPedido(queue<Constructor*> * ConstructoresUsados, ListaCompleja * PedidoActual){
        //Esta funcion valida si el pedido se completo, si no se completo, sigue loopeando hasta que lo este
        // Solo llamar por medio de thread
        //cout << "ESTADO COLA:  " << ConstructoresUsados->size() << endl;
        while (!ConstructoresUsados->empty()){
            if (ConstructoresUsados->front()->Disponibilidad == true){
                ConstructoresUsados->pop();
            }
        }
        if (ConstructoresUsados->empty()){

            //cout << "El pedido: " << PedidoActual->primerNodo->lista->primerNodo->dato << ". Ha sido procesado" << endl;
            ListaSimple* Bitacora = PedidoActual->Buscar("\t\tBitacora")->lista;
            Bitacora->agregar("A cola de alisto:\t\t" + HoraSistema());
            Bitacora->imprimir();
            HistorialColaAlmacen->agregar("Entra pedido: " + PedidoActual->primerNodo->lista->primerNodo->dato + " - " + HoraSistema());
            pedidosAlmacen->push(PedidoActual);
        }
    }

    void VerificaProductos(int cantidad, queue<Constructor*> * ConstructoresUsados, string CodigoProducto, ListaSimple* Bitacora, ListaSimple* ConstructorBitacora){
        //Verifica que hayan productos en el almacen si no pone los constructores a trabajar
        NodoComplejo * ProductoBuscado = ListaProductos->Buscar(CodigoProducto);
        if (cantidad < 0){
            //cout << "No hay suficientes productos: " << CodigoProducto << " por lo tanto se construiran" << endl;
            cantidad = -cantidad;
            int Tiempo = stoi(ProductoBuscado->lista->primerNodo->siguiente->siguiente->dato)*cantidad;
            Constructor * Constructor = ConstruirProductos(cantidad, ProductoBuscado);
            while (Constructor == NULL){
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "Buscando constructor para:" << CodigoProducto << endl;
                Constructor = ConstruirProductos(cantidad, ProductoBuscado);
            }
            ConstructorBitacora->agregar("ARTICULO " + CodigoProducto + "\n" + "Tiempo de fabricacion: " + to_string(Tiempo) + " segundos" + "\n" + "Hora de inicio: " + HoraSistema());
            ConstructorBitacora->imprimir();
            ConstructoresUsados->push(Constructor);
            Bitacora->agregar("A robot " + Constructor->Nombre + ":\t" + HoraSistema() + " Faltaban "  + to_string(cantidad) + " de " + CodigoProducto);
            Bitacora->imprimir();
        }else if (cantidad >= 0){
            ProductoBuscado->lista->primerNodo->siguiente->dato = to_string(cantidad);
        }
    }

    void IniciaPedido(){
        //Esta funcion inicia el pedido, si no hay pedidos en las colas, no hace nada
        ListaCompleja * PedidoActual = RetornaPedido();
        if (PedidoActual == NULL){
            //cout << "No hay pedidos en las colas" << endl;
            return; 
        }
        if (Estado == 0){
            //cout << "El balanceador esta apagado" << endl;
            return;
        }
        ListaSimple* Bitacora = PedidoActual->Buscar("\t\tBitacora")->lista;
        Bitacora->agregar("Balanceador:\t\t" + HoraSistema());
        Bitacora->imprimir();
        ListaSimple* ConstructorBitacora = new ListaSimple();
        ConstructorBitacora->agregar("\t\tRobots Fabrica");
        PedidoActual->agregar("Bitacora", ConstructorBitacora);
        queue<Constructor*> * ConstructoresUsados = new queue<Constructor*>();
        NodoComplejo * tmp= PedidoActual->primerNodo->siguiente->siguiente;
        //cout << "El pedido: " << PedidoActual->primerNodo->lista->primerNodo->dato << ". Esta siendo procesado" << endl;
        while (tmp != NULL && tmp -> tipo != "Bitacora"){
            //Variables
            NodoSimple * tmp2 = tmp -> lista -> primerNodo;
            string CodigoProducto = tmp2 -> dato;
            int CantidadNecesitada = stoi(tmp2-> siguiente -> dato);
            int CantidadAlmacenada = stoi(ListaProductos->Buscar(CodigoProducto)->lista->primerNodo->siguiente->dato);
            int Res = CantidadAlmacenada - CantidadNecesitada;
            VerificaProductos(Res, ConstructoresUsados, CodigoProducto, Bitacora, ConstructorBitacora);
            tmp = tmp -> siguiente;
        }
        std::thread hilo(&Balanceador::validarFinalPedido, this, ConstructoresUsados, PedidoActual);
        hilo.detach();
    }

    void IniciaPedidoThread(bool * isRunning){
        while (* isRunning){
            IniciaPedido();
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

    void ApagaBalanceador(){
        //Esta funcion apaga el balanceador
        if (Estado== 1){
            Estado = 0;
            Accion = "Apagado";
        }
        else {
            Estado= 1;
            Accion = "Leyendo Pedidos de la cola";
        }
    }


};