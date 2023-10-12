struct Bodega {
    ListaCompleja *listaDeProductos;
    queue<ListaCompleja*> * paraAlisto;
    queue<Alistador*> * Alistadores;
    std::vector<std::vector<string>> matriz;

    // Constructores
    Bodega() {
        listaDeProductos = new ListaCompleja();
        matriz = std::vector<std::vector<string>>(10, std::vector<string>(25));
    }

    Bodega(ListaCompleja* _listaDeProductos, queue<ListaCompleja*> * _paraAlisto, queue<Alistador*> * _Alistadores) {
        listaDeProductos = _listaDeProductos;
        paraAlisto = _paraAlisto;
        Alistadores = _Alistadores;
        matriz = std::vector<std::vector<string>>(10, std::vector<string>(25));
    }

    // Método para imprimir la matriz
    void imprimir() {
        cout << "Almacen: \n";
        for (int i = 0; i < matriz.size(); i++) {
            for (int j = 0; j < matriz[i].size(); j++) {
                cout <<"[" << matriz[i][j] << "]";
            }
            cout << endl;
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

    void continuarPedido(){
        // Funcion que debe ejecutarse en un thread constante
        if (!paraAlisto->empty() && !Alistadores->empty()){
            ListaCompleja * pedido = paraAlisto->front();
            paraAlisto->pop();
            Alistador * alistador = Alistadores->front();
            Alistadores->pop();
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