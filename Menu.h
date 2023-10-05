void Menu(){
    bool temp = true;
    bool * isRunning = &temp;
// Implementacion de la lista de Productos 
    //TODO Implementar la opcion de agregar Productos desde interfaz
    //TODO Implementar validaciones a los productos si un archivo tiene cantidad menor que cero, o una categoría diferente que A,B,C; o bien artículos repetidos, no se podrá iniciar
    //la simulación y debe mostrar el error al usuario.
    ListaCompleja * listaDeProductos = LeerArchivo("Productos", "txt", "Producto");

// Implementacion de la lista de clientes
    //TODO Implementar la opcion de agregar clientes desde interfaz
    ListaSimple *ListaClientesArchivo = LeerDirectorio("Clientes", "txt");
    NodoSimple *nodo = ListaClientesArchivo->primerNodo;
    ListaCompleja *ListaClientes = LeerArchivo(nodo, "Cliente");

// Implementacion balanceador y creacion de la lista de pedidos
   //TODO Implementar la funcion que modifica constructores en el menu
    ListaSimple *ListaNombresPedidos = LeerDirectorio("Pedidos//Pendientes", "txt"); // Por medio de esta lista simple podemos mandar los pedidos a balanceador
    //Colas del balanceador
    queue<ListaCompleja*> Altaprioridad;
    queue<ListaCompleja*> Bajaprioridad;
    queue<ListaCompleja*> PedidoInstantaneo;
    queue<ListaCompleja*> * pedidosAlmacen;
    queue<ListaCompleja*> * paraAlisto = new queue<ListaCompleja*>;
    queue<Alistador*> * Alistadores = new queue<Alistador*>;
    queue<ListaCompleja*> * Alistados = new queue<ListaCompleja*>;
    queue<ListaCompleja*> * Empacados = new queue<ListaCompleja*>;

    //Cuando se crea el balanceador este tiene todos sus constructores con categoria D 
    Almacen * almacen = new Almacen(listaDeProductos, paraAlisto);
    pedidosAlmacen = &(almacen->pedidos);
    Balanceador * balanceador = new Balanceador(1, listaDeProductos, Altaprioridad, Bajaprioridad, PedidoInstantaneo, pedidosAlmacen, ListaClientes, ListaNombresPedidos);
    Bodega * bodega = new Bodega(listaDeProductos, paraAlisto, Alistadores);
    Empacador * empacador = new Empacador(true, Empacados);
    Alistados = &(empacador->PorEmpacar);
    for (int i = 0; i < 6; i++){
        Alistador * alistador = new Alistador(true, i+1, listaDeProductos, Alistadores, Alistados);
        Alistadores->push(alistador);
    }

    std::thread LeePedidos(LeerPedidosThread, "Pedidos/Pendientes", std::ref(isRunning), std::ref(ListaNombresPedidos));
    LeePedidos.detach();

    std::thread IniciarPedido(&Balanceador::IniciaPedidoThread, balanceador, std::ref(isRunning));
    IniciarPedido.detach();

    std::thread SeguirPedido(&Almacen::continuarPedidoThread, almacen, std::ref(isRunning));
    SeguirPedido.detach();

    std::thread EncolarPedidos(&Balanceador::MetePedidoEncolaThread, balanceador, std::ref(isRunning));
    EncolarPedidos.detach();

    std::thread AlistarPedido(&Bodega::AlistarPedidosThread, bodega, std::ref(isRunning));
    AlistarPedido.detach();

    std::thread EmpacarPedido(&Empacador::EmpacarPedidosThread, empacador, std::ref(isRunning));
    EmpacarPedido.detach();


    while (*isRunning){
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
// Funcionamiento del programa

    //Creacion de los threads
     //thread lector de pedidos, lee pedidos cada segundo, los mete a ListaNombresDePedidos.
    //std::thread MetePedidoEncola(Funcion); // Funcionamiento con un segundo de delay en comparacion a leer pedidos mete de uno a uno los pedidos en colas
    //std::thread IniciarPedido(Funcion); //El balanceador se pone la gorra cada segundo 
    //TODO Threads de la parte de Tony
    
    // cout << "test" << endl;
    // ListaNombresPedidos = LeerDirectorio("Pedidos//Pendientes", "txt");
    
    // balanceador->MetePedidoEncola(ListaNombresPedidos);
    // PedidoInstantaneo.front()->imprimir();
    // NodoSimple * tmp = ListaNombresPedidos->primerNodo;
    // ListaNombresPedidos->primerNodo = tmp->siguiente;
    // balanceador->MetePedidoEncola(ListaNombresPedidos);
    // Bajaprioridad.front()->imprimir();
    
    // bool Isrunning = true;
    // while (Isrunning == true){
    
    //     bool Isrunning = true;
    //     std::thread LeePedidos(LeerPedidosThread, "Pedidos//Pendientes", Isrunning, ListaNombresPedidos);
    //     LeePedidos.detach();
    //     while (Isrunning == true){
    //         ListaNombresPedidos->imprimir();
    //         std::this_thread::sleep_for(std::chrono::seconds(5));
    //     }
    // }
}