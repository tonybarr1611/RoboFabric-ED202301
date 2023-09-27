struct Producto{
    string codigo;
    int cantidadAlmacenada;
    int tiempoDeElboracion;
    string categoria;
    string ubicacion;

    //constructores
    Producto(){
        codigo = "";
        cantidadAlmacenada = 0;
        tiempoDeElboracion = 0;
        categoria = "";
        ubicacion = "";}
    
    Producto(string codigo, int cantidadAlmacenada, int tiempoDeElboracion, string categoria, string ubicacion){
        this->codigo = codigo;
        this->cantidadAlmacenada = cantidadAlmacenada;
        this->tiempoDeElboracion = tiempoDeElboracion;
        this->categoria = categoria;
        this->ubicacion = ubicacion;
    }

    Producto(ListaSimple * listaProducto){
        codigo = listaProducto->primerNodo->dato;
        cantidadAlmacenada = stoi(listaProducto->primerNodo->siguiente->dato);
        tiempoDeElboracion = stoi(listaProducto->primerNodo->siguiente->siguiente->dato);
        categoria = listaProducto->primerNodo->siguiente->siguiente->siguiente->dato;
        ubicacion = listaProducto->primerNodo->siguiente->siguiente->siguiente->siguiente->dato;
    }
        
    void imprimir(){
        cout << "Codigo: " << codigo << "\n";
        cout << "Cantidad Almacenada: " << cantidadAlmacenada << "\n";
        cout << "Tiempo de Elaboracion: " << tiempoDeElboracion << "\n";
        cout << "Categoria: " << categoria << "\n";
        cout << "Ubicacion: " << ubicacion << "\n";

    }

    ListaSimple* ConvertirEnListaSimple(){
        ListaSimple *lista = new ListaSimple();
        lista->agregar(codigo);
        lista->agregar(to_string(cantidadAlmacenada));
        lista->agregar(to_string(tiempoDeElboracion));
        lista->agregar(categoria);
        lista->agregar(ubicacion);
        return lista;}

    int DaColumnas(){
        int columna = stoi(ubicacion.substr(1,ubicacion.length()))-1;
        return columna;
    }
    
    int DaFilas(){
        int fila = ubicacion[0] - 'A';
        return fila;
    }
};