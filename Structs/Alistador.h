struct Alistador{
    bool encendido;
    int id; // 1-6
    ListaCompleja * listaProductos;
    queue<ListaCompleja*> * Alistados;

    Alistador(){
        encendido = true;
        id = 0;
    }

    Alistador(bool _encendido, int _id, ListaCompleja * _listaProductos){
        encendido = _encendido;
        id = _id;
        listaProductos = _listaProductos;
    }

    void imprimir(){
        cout << "Alistador: " << id << endl;
        cout << "Encendido: " << encendido << endl;
    }

    void apagar(){
        encendido = false;
    }

    void encender(){
        encendido = true;
    }

    int calcularTiempo(string ubicacion){
        int fila = ubicacion[0] - 'A';
        int columna = stoi(ubicacion.substr(1, ubicacion.length()));
        return fila + columna;
    }

    void Alistar(ListaCompleja * pedido){
        // Solo llamar por medio de un hilo
        NodoComplejo * tmp = pedido->primerNodo->siguiente->siguiente;
        while (tmp != NULL && tmp->tipo != "Bitacora"){
            Producto * producto = new Producto(listaProductos->Buscar(tmp->lista->primerNodo->dato)->lista);
            int tiempo = calcularTiempo(producto->ubicacion);
            cout << "Alistando " << producto->codigo << " en " << tiempo << " segundos" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(tiempo));
            tmp = tmp->siguiente;
        }
        Alistados->push(pedido);
    }
};