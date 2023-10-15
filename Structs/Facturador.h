struct Facturador {
    queue<ListaCompleja *> * PorFacturar;
    int Estado;
    string Accion;
    ListaSimple * HistorialPorfacturar;
    //Constructor
    Facturador() {
        Estado = 1;
        queue<ListaCompleja*> * PorFacturar = new queue<ListaCompleja*>;
        Accion = "Facturando cada segundo";
        HistorialPorfacturar = new ListaSimple();
    }
    Facturador(queue<ListaCompleja*> * _PorFacturar, ListaSimple * _HistorialPorfacturar) {
        Estado = 1;
        PorFacturar = _PorFacturar;
        Accion = "Facturando cada segundo";
        HistorialPorfacturar = _HistorialPorfacturar;
    }

    //Metodos
    void imprimir() {
        cout << "Facturador: " << endl;
        cout << "Estado: " << Estado << endl;
    }

    void apagar() {
        if (Estado== 1){
            Estado = 0;
            Accion = "Apagado";
        }
        else {
            Estado= 1;
            Accion = "Facturando cada segundo";
        }
    }

    void FacturaPedido(){
        // Solo llamar por medio de un hilo
        if (Estado == 0) return;

        if (PorFacturar->empty())
            return;
        ListaCompleja * pedido = PorFacturar->front();
        PorFacturar->pop();

        ListaSimple* Bitacora = pedido->Buscar("\t\tBitacora")->lista;
        Bitacora->agregar("Finalizado:\t\t" + HoraSistema());
        std::this_thread::sleep_for(std::chrono::seconds(1));
        //Creacion del archivo
        string hora = quitarEspacios(reemplazarCaracter(HoraSistema(), "/", "-"));
        hora = reemplazarCaracter(hora, ":", "-");
        string nombre = pedido->primerNodo->lista->primerNodo->dato + "_" + pedido->primerNodo->siguiente->lista->primerNodo->dato + "_" + hora;
        string nombreArchivo = "Pedidos/Completados/" + nombre + ".txt";
        std::ofstream archivo (nombreArchivo, std::ios::out);
        //Escritura en el archivo
        if (archivo.is_open()) {
        ListaSimple* Bitacora = pedido->Buscar("\t\tBitacora")->lista;
        ListaSimple* Bitacora_constructor = pedido->Buscar("\t\tRobots Fabrica")->lista;
        ListaSimple* Bitacora_Alisto = pedido->Buscar("\t\tAlistando")->lista;


        //Primera Bitacora
        NodoSimple* tmp = Bitacora->primerNodo;
        while (tmp != NULL){
            archivo << tmp->dato << endl;
            tmp = tmp->siguiente;     
        } 
        tmp = Bitacora_constructor->primerNodo;
        while (tmp != NULL){
            archivo << tmp->dato << endl;
            tmp = tmp->siguiente;
        }
        tmp = Bitacora_Alisto->primerNodo;
        while (tmp != NULL){
            archivo << tmp->dato << endl;
            tmp = tmp->siguiente;
        } 
        }  
        else
            std::cerr << "No se pudo abrir el archivo." << std::endl;
        

    }   

    void FacturarPedidoThread(bool * isRunning){
        while (isRunning){
            FacturaPedido();
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }
    }
};