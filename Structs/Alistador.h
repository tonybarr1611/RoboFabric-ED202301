struct Alistador{
    int estado;
    int id; // 1-6
    ListaCompleja * listaProductos;
    queue<Alistador*> * Alistadores;
    queue<ListaCompleja*> * Alistados;
    ListaCompleja * pedido;
    string Accion;
    ListaSimple* HistorialAlistados;
    ListaSimple* Historial;

    Alistador(){
        estado = 1;
        id = 0;
        listaProductos = new ListaCompleja();
        Alistadores = new queue<Alistador*>;
        Alistados = new queue<ListaCompleja*>;
        Accion = "Esperando para alistar";
    }

    Alistador(int _encendido, int _id, ListaCompleja * _listaProductos, queue<Alistador*> * _Alistadores, queue<ListaCompleja*> * _Alistados){
        estado = _encendido;
        id = _id;
        listaProductos = _listaProductos;
        Alistadores = _Alistadores;
        Alistados = _Alistados;
        Accion = "Esperando para alistar";
        HistorialAlistados = new ListaSimple();
        Historial = new ListaSimple();
    }

    void imprimir(){
        cout << "Alistador: " << id << endl;
    }

    void apagar(){
        if (estado== 1){
            estado = 0;
            Accion = "Apagado";
        }
        else {
            estado= 1;
            Accion = "Esperando para alistar";
        }
    }


    int calcularTiempo(string ubicacion){
        int fila = ubicacion[0] - 'A';
        int columna = stoi(ubicacion.substr(1, ubicacion.length()));
        return fila + columna;
    }

    void Alistar(){
        NodoComplejo * tmp = pedido->primerNodo->siguiente->siguiente;
        ListaSimple* Bitacora = new ListaSimple();
        Bitacora->agregar("\t\tAlistando");
        string god = "Alistador " + to_string(id) + "\n";
        while (tmp != NULL && tmp->tipo != "Bitacora"){
            Producto * producto = new Producto(listaProductos->Buscar(tmp->lista->primerNodo->dato)->lista);
            Accion = "Alistando " + producto->codigo;
            int tiempo = calcularTiempo(producto->ubicacion);
            //cout << "Alistando " << producto->codigo << " en " << tiempo << " segundos" << endl;
            god += producto->codigo + "\t" + "Ubicacion: " + producto->ubicacion + "\t" + "Tiempo: " + to_string(tiempo) + "s\n";
            std::this_thread::sleep_for(std::chrono::seconds(tiempo));
            tmp = tmp->siguiente;
        }
        Accion = "Esperando para alistar";
        Bitacora->agregar(god);
        Bitacora->imprimir();
        pedido->agregar("Bitacora", Bitacora);
        Alistados->push(pedido);
        HistorialAlistados->agregar("Entra pedido: " + pedido->primerNodo->lista->primerNodo->dato + " - " + HoraSistema());
        Historial->agregar("Pedido: " + pedido->primerNodo->lista->primerNodo->dato + " - " + HoraSistema());   
        Alistadores->push(this);
    }
};