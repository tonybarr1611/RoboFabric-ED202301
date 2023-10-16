struct Bodega {
    ListaCompleja *listaDeProductos;
    queue<ListaCompleja*> * paraAlisto;
    queue<Alistador*> * Alistadores;
    Alistador* ArrayAlistadores[6];
    std::vector<std::vector<string>> matriz;
    ListaSimple * HistorialAlisto;

    // Constructores
    Bodega() {
        listaDeProductos = new ListaCompleja();
        matriz = std::vector<std::vector<string>>(10, std::vector<string>(25));
    }

    Bodega(ListaCompleja* _listaDeProductos, queue<ListaCompleja*> * _paraAlisto, queue<Alistador*> * _Alistadores, Alistador* _ArrayAlistadores[6], ListaSimple * _HistorialAlisto) {
        listaDeProductos = _listaDeProductos;
        paraAlisto = _paraAlisto;
        Alistadores = _Alistadores;
        matriz = std::vector<std::vector<string>>(10, std::vector<string>(25));
        for (int i = 0; i < 6; i++){
            ArrayAlistadores[i] = _ArrayAlistadores[i];
        }
        HistorialAlisto = _HistorialAlisto;
    }

    // Método para imprimir la matriz
    void imprimir() {
        cout << "Bodega: \n";
        for (int i = 0; i < matriz.size(); i++) {
            for (int j = 0; j < matriz[i].size(); j++) {
                cout <<"[" << matriz[i][j] << "]";
            }
            cout << endl;
        }
    }

    void imprimiralistadores(){
        for (int i =0; i>6; i++){
        cout << "Posicion: " << i << endl;
        cout<< "Alistador: " << ArrayAlistadores[i]->id << endl;
        if (ArrayAlistadores[i]->estado== 1)
            cout << "Prendido" << endl;
        else
            cout << "Apagado" << endl;
        }
    }

    NodoComplejo * buscarProducto(string codigo){
        NodoComplejo * tmp = listaDeProductos->primerNodo;
        while (tmp != NULL){
            if (tmp->lista->primerNodo->dato == codigo)
                return tmp;
            tmp = tmp->siguiente;
        }
        return NULL;
    }

    void InsertaProductosEnAlmacen(){
        NodoComplejo *tmp = listaDeProductos->primerNodo;
        while (tmp != NULL){
            Producto * producto = new Producto(tmp->lista);
            int fila = producto->DaFilas();
            int columna = producto->DaColumnas();
            matriz[columna][fila] = producto->codigo;
            tmp = tmp->siguiente;
        }
    }

    void InsertaProductoEnAlmacen(Producto * producto){
        if (buscarProducto(producto->codigo) == NULL){
            listaDeProductos->agregar("Producto", producto->ConvertirEnListaSimple());
            int fila = producto->DaFilas();
            int columna = producto->DaColumnas();
            matriz[columna][fila] = producto->codigo;
        }else{
            return;
        }      
    }

    void InsertaProductoEnAlmacen(ListaSimple * lista){
        if (buscarProducto(lista->primerNodo->dato) == NULL){
            listaDeProductos->agregar("Producto", lista);
            Producto * producto = new Producto(lista);
            InsertaProductoEnAlmacen(producto);
        }else{
            return;
        }
    }    

    Alistador * RetornaAlistadorValido(){
        //con la cola
        int Contador = 0;
        while (Contador < 6){
            Alistador * alistador = Alistadores->front();
            if (alistador->estado == 1){
                Alistadores->pop();
                return alistador;
            }else{
                Alistadores->pop();
                Alistadores->push(alistador);
                Contador++;
            }
        }
        return NULL;
    }

    void continuarPedido(){
        // Funcion que debe ejecutarse en un thread constante
        if (!paraAlisto->empty() && !Alistadores->empty()){
            ListaCompleja * pedido = paraAlisto->front();
            HistorialAlisto->agregar("Sale pedido:\t"+ pedido->primerNodo->lista->primerNodo->dato + "-" + HoraSistema());
            paraAlisto->pop();
            Alistador * alistador = RetornaAlistadorValido();
            if (alistador == NULL) {
                cout << "No hay alistadores disponibles" << endl;    
                return;
            }
            
            // Revisar hilo
            alistador->pedido = pedido;
            
            std::thread hilo(&Alistador::Alistar, alistador);
            hilo.detach();
        }else{
            return;
        }
    }

    void AlistarPedidosThread(bool * isRunning){
        while (*isRunning){
            this->continuarPedido();
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }
    }
};