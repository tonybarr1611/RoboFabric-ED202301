struct Almacen {
    ListaCompleja *listaDeProductos;
    std::vector<std::vector<string>> matriz;

    // Constructores
    Almacen() {
        listaDeProductos = new ListaCompleja();
        matriz = std::vector<std::vector<string>>(10, std::vector<string>(25));
    }

    Almacen(ListaCompleja* _listaDeProductos){
        listaDeProductos = _listaDeProductos;
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
};