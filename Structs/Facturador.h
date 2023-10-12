struct Facturador {
    queue<ListaCompleja *> * PorFacturar;
    bool Estado;

    //Constructor
    Facturador() {
        Estado = true;
        queue<ListaCompleja*> * PorFacturar = new queue<ListaCompleja*>;
    }
    Facturador(queue<ListaCompleja*> * _PorFacturar) {
        Estado = true;
        PorFacturar = _PorFacturar;
    }

    //Metodos
    void imprimir() {
        cout << "Facturador: " << endl;
        cout << "Estado: " << Estado << endl;
    }

    void FacturaPedido(){
        // Solo llamar por medio de un hilo
        ListaCompleja * pedido = PorFacturar->front();
        PorFacturar->pop();
        ListaSimple* Bitacora = pedido->Buscar("\t\tBitacora")->lista;
        Bitacora->agregar("Finalizado:\t\t" + HoraSistema());
        Bitacora->imprimir();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    void FacturarPedidoThread(bool * isRunning){
        while (isRunning){
            FacturaPedido();
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }
    }
};