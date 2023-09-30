struct Empacador{
    bool encendido;
    queue<ListaCompleja*> PorEmpacar;
    queue<ListaCompleja*> * PorFacturar;

    Empacador(){
        encendido = true;
    }

    Empacador(bool _encendido, queue<ListaCompleja*> * _PorFacturar){
        encendido = _encendido;
        PorFacturar = _PorFacturar;
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

    void Empacar(ListaCompleja * pedido){
        // Solo llamar por medio de un hilo
        NodoComplejo * tmp = pedido->primerNodo->siguiente->siguiente;
        while (tmp != NULL && tmp->tipo != "Bitacora"){
            cout << "Empacando " << tmp->lista->primerNodo->dato << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            tmp = tmp->siguiente;
        }
        PorFacturar->push(pedido);
    }

    void continuarPedido(){
        // Funcion que debe ejecutarse en un thread constante
        if (!PorEmpacar.empty()){
            ListaCompleja * pedido = PorEmpacar.front();
            PorEmpacar.pop();
            // std::thread hilo(&Empacador::Empacar, pedido);
            // hilo.detach();
        }else{
            return;
        }
    }
};