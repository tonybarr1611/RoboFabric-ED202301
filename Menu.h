// Implementacion de la lista de Productos 
    //TODO Implementar la opcion de agregar Productos desde interfaz
    //TODO Implementar validaciones a los productos si un archivo tiene cantidad menor que cero, o una categoría diferente que A,B,C; o bien artículos repetidos, no se podrá iniciar
    //la simulación y debe mostrar el error al usuario.

    ListaCompleja * listaDeProductos = LeerArchivo("Productos", "txt", "Producto");
    listaDeProductos->primerNodo->lista->primerNodo->imprimir();
    listaDeProductos->primerNodo->lista->Buscar("X09");

// Implementacion de la lista de clientes
    //TODO Implementar la opcion de agregar clientes desde interfaz
    ListaSimple *ListaClientesArchivo = LeerDirectorio("Clientes", "txt");
    NodoSimple *nodo = ListaClientesArchivo->primerNodo;
    ListaCompleja *ListaClientes = LeerArchivo(nodo, "Cliente");

// Implementacion de la lista de pedidos y balanceador
   //TODO Implementar la funcion que modifica constructores en el menu
    ListaSimple *ListaNombresDePedidos = LeerDirectorio("Pedidos//Pendientes", "txt"); // Por medio de esta lista simple podemos mandar los pedidos a balanceador
    //Colas del balanceador
    queue<ListaCompleja*> Altaprioridad;
    queue<ListaCompleja*> Bajaprioridad;
    queue<ListaCompleja*> PedidoInstantaneo;
    //Cuando se crea el balanceador este tiene todos sus constructores con categoria D 
    Balanceador * balanceador = new Balanceador(1, listaDeProductos, Altaprioridad, Bajaprioridad, PedidoInstantaneo);
    
// Funcionamiento del programa

    //Creacion de los threads
    std::thread LeePedidos(Funcion); //thread lector de pedidos, lee pedidos cada segundo, los mete a ListaNombresDePedidos.
    std::thread MetePedidoEncola(Funcion); // Funcionamiento con un segundo de delay en comparacion a leer pedidos mete de uno a uno los pedidos en colas
    std::thread IniciarPedido(Funcion) //El balanceador se pone la gorra cada segundo 
    //TODO Threads de la parte de Tony

    bool Isrunning = true;
    while (Isrunning == true){
    


    }