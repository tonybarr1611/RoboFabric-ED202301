void Menu(){
    bool temp = true;
    bool * isRunning = &temp;

// Implementacion de la lista de Productos 
    ListaCompleja * listaDeProductos = LeerArchivo("Productos", "txt", "Producto");

// Implementacion de la lista de clientes
    ListaSimple *ListaClientesArchivo = LeerDirectorio("Clientes", "txt");
    NodoSimple *nodo = ListaClientesArchivo->primerNodo;
    ListaCompleja *ListaClientes = LeerArchivo(nodo, "Cliente");

// Implementacion balanceador y creacion de la lista de pedidos
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

    //Cuando se crea el balanceador tiene todos sus constructores con categoria D 
    ListaCompleja* listaConstructores = LeerArchivo("Constructores", "txt", "Constructor");
    
    Almacen * almacen = new Almacen(listaDeProductos, paraAlisto);
    pedidosAlmacen = &(almacen->pedidos);
    Balanceador * balanceador = new Balanceador(1, listaDeProductos, Altaprioridad, Bajaprioridad, PedidoInstantaneo, pedidosAlmacen, ListaClientes, ListaNombresPedidos);
    balanceador->CargaConstructores(listaConstructores);
    balanceador->ImprimeConstructores();
    Bodega * bodega = new Bodega(listaDeProductos, paraAlisto, Alistadores);
    Empacador * empacador = new Empacador(true, Empacados);
    Alistados = &(empacador->PorEmpacar);
    for (int i = 0; i < 6; i++){
        Alistador * alistador = new Alistador(true, i+1, listaDeProductos, Alistadores, Alistados);
        Alistadores->push(alistador);
    }

    // std::thread LeePedidos(LeerPedidosThread, "Pedidos/Pendientes", std::ref(isRunning), std::ref(ListaNombresPedidos));
    // LeePedidos.detach();

    // std::thread IniciarPedido(&Balanceador::IniciaPedidoThread, balanceador, std::ref(isRunning));
    // IniciarPedido.detach();

    // std::thread SeguirPedido(&Almacen::continuarPedidoThread, almacen, std::ref(isRunning));
    // SeguirPedido.detach();

    // std::thread EncolarPedidos(&Balanceador::MetePedidoEncolaThread, balanceador, std::ref(isRunning));
    // EncolarPedidos.detach();

    // std::thread AlistarPedido(&Bodega::AlistarPedidosThread, bodega, std::ref(isRunning));
    // AlistarPedido.detach();

    // std::thread EmpacarPedido(&Empacador::EmpacarPedidosThread, empacador, std::ref(isRunning));
    // EmpacarPedido.detach();

    cout << "           Bienvenido a la fabrica" << endl;
    cout << "Desde aqui podra modificar el funcionamiento de la fabrica" << endl;
    cout << "1. Pedido Directo" << endl;
    cout << "2. Modificar constructores " << endl; 
    cout << "3. Apagar elemento de la fabrica" << endl;
    cout << "4. Apagar fabrica " << endl;
    string opcion;
    while (opcion != "4"){
        cout << "Ingrese la opcion que desea realizar:";
        getline(cin, opcion);
        if (opcion == "1"){
            ListaCompleja * pedido = new ListaCompleja();
            ListaSimple * producto = new ListaSimple();
            pedido->agregar("Producto", "Pedido Directo");
            pedido->agregar("Producto", "Terminal");
            string respuesta = "s";
            while (respuesta == "s"){
                cout << "Ingrese el codigo del producto:";
                string codigoProducto;
                getline(cin, codigoProducto);

                cout << "Ingrese la cantidad del producto:";
                string cantidadProducto;
                getline(cin, cantidadProducto);
                // Añadir como lista simple cada producto
                producto->agregar(codigoProducto);
                producto->agregar(cantidadProducto);
                pedido->agregar("Producto", producto);
                producto = new ListaSimple();
                cout << "Desea agregar otro producto? (s/n):";
                getline(cin, respuesta);
            }
            pedido->imprimir();
            balanceador->PedidoInstantaneo.push(pedido);}}
    //     }
    //     else if (opcion == "2"){
    //         cout << "Ingrese el nombre del constructor que desea modificar: ";
    //         string nombreConstructor;
    //         cin >> nombreConstructor;
    //         cout << "Ingrese la categoria que desea asignarle: ";
    //         string categoria;
    //         cin >> categoria;
    //         balanceador->ModificarConstructor(nombreConstructor, categoria);
    //     }
    //     else if (opcion == "3"){
    //         cout << "Ingrese el nombre del elemento que desea apagar: ";
    //         string nombreElemento;
    //         cin >> nombreElemento;
    //         balanceador->ApagarElemento(nombreElemento);
    //     }
    //     else if (opcion == "4"){
    //         cout << "Apagando fabrica" << endl;
    //         *isRunning = false;
    //     }
    //     else{
    //         cout << "Opcion invalida" << endl;
    //     }
    // }

    while (*isRunning){
        
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}