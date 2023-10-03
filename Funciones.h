//Funciones
string HoraSistema(){
    // Retorna la hora y fecha del sistema
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string hora = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min) + ":" + to_string(ltm->tm_sec);
    string fecha = to_string(ltm->tm_mday) + "/" + to_string(ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);
    return fecha + " " + hora;
}

ListaSimple* SepararStringsPorTabs(string linea) {
    ListaSimple *lista = new ListaSimple(); // Crear una instancia de ListaSimple
    string dato = "";

    for (int i = 0; i < linea.length(); i++) {
        if (linea[i] == '\t') {
            lista->agregar(dato); // Agregar el dato a la lista
            dato = "";
        } else {
            dato += linea[i];
        }
    }
    lista->agregar(dato); // Agregar el último dato
    return lista;
}

ListaCompleja *SepararStringsPorLineas(string linea, string tipo){
    // Toma un string y lo separa por saltos de línea, cada línea se convierte en una lista simple que se pasa por SepararStringsPorTabs
    ListaCompleja *listaCompleja = new ListaCompleja();
    listaCompleja->tipo = tipo;
    NodoComplejo *nodoActual = new NodoComplejo(tipo);
    string dato = "";

    for (int i = 0; i < linea.length(); i++) {
        if (linea[i] == '\n') {
            ListaSimple *listaSimple = SepararStringsPorTabs(dato);
            nodoActual->lista = listaSimple;
            listaCompleja->agregar(nodoActual);
            nodoActual = new NodoComplejo(tipo);
            dato = "";
        } else {
            dato += linea[i];
        }
    }

    ListaSimple *listaSimple = SepararStringsPorTabs(dato);
    nodoActual->lista = listaSimple;
    listaCompleja->agregar(nodoActual);

    return listaCompleja;
}

ListaSimple *LeerDirectorio(string directorio, string tipoArchivo){
    // Toma un directorio, direccion relativa, y devuelve una lista de todos los archivos que sean del tipo especificado
    ListaSimple *lista = new ListaSimple();
    tipoArchivo = "." + tipoArchivo;
    for (const auto & entry : fs::directory_iterator(directorio)){
        string path = entry.path().string();
        if(path.substr(path.length() - tipoArchivo.length(), path.length()) == tipoArchivo)
            lista->agregar(path);
    }
    return lista;
}

ListaCompleja *LeerArchivo(ListaSimple *listaArchivos, string tipoLista){
    // Toma una lista de archivos, lee cada archivo y devuelve una lista de listas con los datos del archivo
    ListaCompleja *listaCompleja = new ListaCompleja();
    listaCompleja->tipo = tipoLista;
    NodoSimple *tmp = listaArchivos->primerNodo;
    while(tmp != NULL){
        string path = tmp->dato;
        ifstream archivo(path);
        string linea;
        string contenido = "";
        while(getline(archivo, linea)){
            if (contenido == "")
                contenido += linea;
            else
                contenido += "\n" + linea;
        }
        ListaCompleja *lista = SepararStringsPorLineas(contenido, tipoLista);
        listaCompleja->agregar(lista);
        tmp = tmp->siguiente;
    }
    return listaCompleja;
}

ListaCompleja *LeerArchivo(string directorio, string tipoArchivo, string tipoLista){
    // Toma un directorio, direccion relativa, lee el archivo y devuelve una lista de listas con los datos del archivo
    ListaSimple *lista = LeerDirectorio(directorio, tipoArchivo);
    return LeerArchivo(lista, tipoLista);
}

ListaCompleja *LeerArchivo(NodoSimple *NodoArchivo, string tipoLista){
    // Toma un nodo de archivos, lee el archivo y devuelve una lista de listas con los datos del archivo
    ListaSimple *lista = new ListaSimple();
    lista->agregar(NodoArchivo->dato);
    return LeerArchivo(lista, tipoLista);
}


int RetornaPrioridad(ListaCompleja * ListaClientes, string codigo){
    //Retorna la prioridad del Cliente con su codigo 
    NodoComplejo * ClienteBuscado = ListaClientes->Buscar(codigo);
    if (ClienteBuscado != NULL){
        return stoi(ClienteBuscado->lista->ultimoNodo->dato);}
    else{ return -1;
    }
}

string nombreArchivo(string directorio){
    while (directorio.find("/") != string::npos && directorio.find("") != directorio.length() - 1)
        directorio = directorio.substr(directorio.find("/") + 1, directorio.length());
    if (directorio.find("Pendientes") != string::npos)
        directorio = directorio.substr(directorio.find("Pendientes") + 11, directorio.length());
    return directorio;
}

bool MoverArchivotxt(string Directorio, string Destino){
    //Mueve un archivo de un directorio a otro
    // MoverArchivotxt("Pedidos/Pendientes/pedido1", "Pedidos/Completados");
    string filename = Directorio;
    filename = nombreArchivo(filename);
    string path = Directorio;
    string pathDestino = Destino + "/" + filename;;
    if (fs::exists(path)){
        fs::rename(path, pathDestino);
        return true;
    }
    else
        return false;
}


void LeerPedidosThread(string Directorio, bool Isrunning, ListaSimple* ListaPedidos){
    //thread 
    while(Isrunning){
        std::this_thread::sleep_for(std::chrono::seconds(5));
        ListaSimple* tmp = LeerDirectorio(Directorio, "txt");
        NodoSimple* tmpNodo = tmp->primerNodo;
        while (tmpNodo != NULL){
            //TODO ver si se puede implementar semaforo 
            ListaPedidos->primerNodo = ListaPedidos->ultimoNodo = NULL;
            if (ListaPedidos->Buscar(tmpNodo->dato) == NULL)
                ListaPedidos->agregar(tmpNodo);
            tmpNodo = tmpNodo->siguiente;
        }
    }
}

