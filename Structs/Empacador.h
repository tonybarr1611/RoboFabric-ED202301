struct Empacador{
    bool encendido;
    queue<ListaCompleja*> * PorEmpacar;
    queue<ListaCompleja*> * PorFacturar;
    ListaCompleja * PedidoActual;

    Empacador(){
        encendido = true;
    }

    Empacador(bool _encendido, queue<ListaCompleja*> * _PorEmpacar, queue<ListaCompleja*>* _PorFacturar){
        encendido = _encendido;
        PorFacturar = _PorFacturar;
        PorEmpacar = _PorEmpacar;
    }

    void imprimir(){
        cout << "Empacador: " << endl;
        cout << "Encendido: " << encendido << endl;
    }

    void apagar(){
        encendido = false;
    }

    void encender(){
        encendido = true;
    }

    void Empacar(){
        // Solo llamar por medio de un hilo
        NodoComplejo * tmp = PedidoActual->primerNodo->siguiente->siguiente;
        ListaSimple* Bitacora = PedidoActual->Buscar("\t\tBitacora")->lista;
        Bitacora->agregar("A empaque:\t\t" + HoraSistema());
        Bitacora->imprimir();
        while (tmp != NULL && tmp->tipo != "Bitacora"){
            
            std::this_thread::sleep_for(std::chrono::seconds(1));
            tmp = tmp->siguiente;
        }
        PorFacturar->push(PedidoActual);
    }

    void continuarPedido(){
        // Funcion que debe ejecutarse en un thread constante
        if (!PorEmpacar->empty()){
            ListaCompleja * pedido = PorEmpacar->front();
            PorEmpacar->pop();
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