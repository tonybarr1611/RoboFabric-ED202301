struct Almacen{
    ListaCompleja *listaDeProductos;
    queue<ListaCompleja*> pedidos;
    queue<ListaCompleja*> * paraAlisto;

    Almacen() {
        listaDeProductos = new ListaCompleja();
        while (!pedidos.empty()) pedidos.pop();
        while (!paraAlisto->empty()) paraAlisto->pop();
    }

    Almacen(ListaCompleja* _listaDeProductos, queue<ListaCompleja*> * _paraAlisto){
        listaDeProductos = _listaDeProductos;
        paraAlisto = _paraAlisto;
        while (!pedidos.empty()) pedidos.pop();
        while (!paraAlisto->empty()) paraAlisto->pop();

    }

    void imprimir(){
        NodoComplejo * tmp = listaDeProductos->primerNodo;
        while (tmp != NULL){
            tmp->imprimir();
            tmp = tmp->siguiente;
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

    void InsertaProductoEnAlmacen(Producto * producto){
        if (buscarProducto(producto->codigo) == NULL){
            listaDeProductos->agregar("Producto", producto->ConvertirEnListaSimple());
        }else{
            return;
        }      
    }

    void InsertaProductoEnAlmacen(ListaSimple * lista){
        if (buscarProducto(lista->primerNodo->dato) == NULL){
            listaDeProductos->agregar("Producto", lista);
        }else{
            return;
        }
    }

    void continuarPedido(){
        // Funcion que debe ejecutarse en un thread constante
        if (!pedidos.empty()){
            ListaCompleja * pedido = pedidos.front();
            pedido->imprimir();
            paraAlisto->push(pedido);
            pedidos.pop();
        }else{
            return;
        }
    }

    void continuarPedidoThread(bool * isRunning){
        while (*isRunning){
            continuarPedido();
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }
    }
};