struct Empacador{
    int estado;
    queue<ListaCompleja*> * PorEmpacar;
    queue<ListaCompleja*> * PorFacturar;
    ListaCompleja * PedidoActual;
    string Accion;
    ListaSimple* HistorialPorempacar;
    ListaSimple* HistorialPorFacturar;
    Empacador(){
        estado = 1;
        PorEmpacar = new queue<ListaCompleja*>;
        PorFacturar = new queue<ListaCompleja*>;
        Accion = "Esperando para empacar";
        HistorialPorempacar = new ListaSimple();
        HistorialPorFacturar = new ListaSimple();
    }

    Empacador(int _encendido, queue<ListaCompleja*> * _PorEmpacar, queue<ListaCompleja*>* _PorFacturar, ListaSimple * _HistorialPorEmpacar, ListaSimple* _HistorialPorFacturar){
        estado = _encendido;
        PorFacturar = _PorFacturar;
        PorEmpacar = _PorEmpacar;
        Accion = "Esperando para empacar";
        HistorialPorempacar = _HistorialPorEmpacar;
        HistorialPorFacturar = _HistorialPorFacturar;
    }

    void imprimir(){
        cout << "Empacador: " << endl;
    }

    void apagar(){
        if (estado== 1){
            estado = 0;
            Accion = "Apagado";
        }
        else {
            estado= 1;
            Accion = "Esperando para empacar";
        }
    }

    void Empacar(){
        // Solo llamar por medio de un hilo
        NodoComplejo * tmp = PedidoActual->primerNodo->siguiente->siguiente;
        ListaSimple* Bitacora = PedidoActual->Buscar("\t\tBitacora")->lista;
        Bitacora->agregar("A empaque:\t\t" + HoraSistema());
        while (tmp != NULL && tmp->tipo != "Bitacora"){
            Accion = "Empacando " + tmp->lista->primerNodo->dato;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            tmp = tmp->siguiente;
        }
        PorFacturar->push(PedidoActual);
        HistorialPorFacturar->agregar("Entra pedido:\t"+ PedidoActual->primerNodo->lista->primerNodo->dato + "-" + HoraSistema());
    }

    void continuarPedido(){
        // Funcion que debe ejecutarse en un thread constante
        if (estado == 0) return;
        if (!PorEmpacar->empty()){
            ListaCompleja * pedido = PorEmpacar->front();
            PorEmpacar->pop();
            HistorialPorempacar->agregar("Sale pedido:\t"+ pedido->primerNodo->lista->primerNodo->dato + "-" + HoraSistema());
            PedidoActual = pedido;
            std::thread hilo(Empacador::Empacar, this);
            hilo.detach();
        }else{
            return;
        }
    }

    void EmpacarPedidosThread(bool * isRunning){
        while (isRunning){
            continuarPedido();
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }
    }
};