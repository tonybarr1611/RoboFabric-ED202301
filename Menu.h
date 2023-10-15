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
    //Colas
    queue<ListaCompleja*> Altaprioridad;
    queue<ListaCompleja*> Bajaprioridad;
    queue<ListaCompleja*> PedidoInstantaneo;
    queue<ListaCompleja*> * pedidosAlmacen;
    queue<ListaCompleja*> * paraAlisto = new queue<ListaCompleja*>;
    queue<Alistador*> * Alistadores = new queue<Alistador*>;
    queue<ListaCompleja*> * Alistados = new queue<ListaCompleja*>;
    queue<ListaCompleja*> * PorFacturar = new queue<ListaCompleja*>;
    ListaSimple * HistorialColaAlmacen = new ListaSimple();
    Alistador* ArrayAlistadores[6];
    Almacen * almacen = new Almacen(listaDeProductos, paraAlisto, HistorialColaAlmacen);
    pedidosAlmacen = &(almacen->pedidos);
    ListaCompleja* listaConstructores = LeerArchivo("Constructores", "txt", "Constructor");
    Balanceador * balanceador = new Balanceador(1, listaDeProductos, Altaprioridad, Bajaprioridad, PedidoInstantaneo, pedidosAlmacen, ListaClientes, ListaNombresPedidos, HistorialColaAlmacen);
    balanceador->CargaConstructores(listaConstructores);
    Bodega * bodega = new Bodega(listaDeProductos, paraAlisto, Alistadores, ArrayAlistadores, almacen->HistorialColaAlisto);
    
    for (int i = 0; i < 6; i++){
        Alistador * alistador = new Alistador(1, i+1, listaDeProductos, Alistadores, Alistados);
        ArrayAlistadores[i] = alistador;
        Alistadores->push(alistador);
    }

    Empacador * empacador = new Empacador(1, Alistados, PorFacturar, ArrayAlistadores[0]->HistorialAlistados);
    Facturador * facturador = new Facturador(PorFacturar, empacador->HistorialPorFacturar);
    Alistados = (empacador->PorEmpacar);
    //Lista de Acciones

    string* AccionesArray = new string[19];
    for (int i = 0; i < 9; i++){
        AccionesArray[i] = balanceador->ArrayConstructores[i]->Accion;
    }
    AccionesArray[10]= balanceador->Accion;
    for (int i = 0 ; i < 6; i++){
        AccionesArray[i+11] = ArrayAlistadores[i]->Accion;
    }

    AccionesArray[17] = empacador->Accion;
    AccionesArray[18] = facturador->Accion;

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

    std::thread FacturarPedido(&Facturador::FacturarPedidoThread, facturador, std::ref(isRunning));
    FacturarPedido.detach();

    string opcion;
    while (opcion != "6"){
        cout << endl;
        cout << "           Bienvenido a la fabrica" << endl;
        cout << "Desde aqui podra modificar el funcionamiento de la fabrica" << endl;
        cout << "1. Pedido Directo" << endl;
        cout << "2. Modificar constructores " << endl; 
        cout << "3. Ver historial de colas o alistadores" << endl;
        cout << "4. Ver acciones de la fabrica en tiempo real" << endl;
        cout << "5. Apagar/Prender elemento de la fabrica" << endl;
        cout << "6. Apagar fabrica" << endl;
        cout << "Ingrese la opcion que desea realizar:";
        cout << endl;
        getline(cin, opcion);
        cout << endl;
        if (opcion == "1"){
            //Pedido Instantaneo
            ListaCompleja * pedido = new ListaCompleja();
            ListaSimple * producto = new ListaSimple();
            pedido->agregar("Producto", "Pedido Directo");
            pedido->agregar("Producto", "Terminal");
            ListaSimple * Bitacora = new ListaSimple();
            Bitacora->agregar("\t\tBitacora");
            Bitacora->agregar("Pedido:\t\t" + pedido->primerNodo->lista->primerNodo->dato);
            Bitacora->agregar("Cliente:\t\t" + pedido->primerNodo->siguiente->lista->primerNodo->dato);
            string respuesta = "s";
            while (respuesta == "s"){
                cout << "Ingrese el codigo del producto:";
                string codigoProducto;
                getline(cin, codigoProducto);
                cout << endl; 
                if (listaDeProductos->Buscar(codigoProducto) == NULL){
                    cout << "Producto no encontrado" << endl;
                    continue;
                }
                cout << "Ingrese la cantidad del producto:";
                string cantidadProducto;
                getline(cin, cantidadProducto);
                cout << endl;
                char cantidad = cantidadProducto[0];
                if (!isdigit(cantidad)){
                    cout << "Cantidad invalida" << endl;
                    continue;
                }
                // Añadir como lista simple cada producto
                producto->agregar(codigoProducto);
                producto->agregar(cantidadProducto);
                pedido->agregar("Producto", producto);
                producto = new ListaSimple();
                cout << "Desea agregar otro producto? (s/n):";
                getline(cin, respuesta);
                cout << endl;
            }
            pedido->agregar("Bitacora", Bitacora);
            balanceador->PedidoInstantaneo.push(pedido);
        }

        else if (opcion == "2"){
            //Modificar constructores
            balanceador->ImprimeConstructores();
            cout << "Ingrese la posicion del constructor que desea modificar: ";
            string posicion;
            getline(cin, posicion);
            cout << endl;
            int pos = stoi(posicion);
            cout << "¿Que desea modificar del constructor?" << pos << endl;
            cout << "1. Cambiar Tipo , 2. Cambiar Prioridad" << endl;
            string subopcion;
            getline(cin, subopcion);
            cout << endl;
            if (subopcion == "1"){
                cout << "Ingrese el nuevo tipo del constructor" << endl;
                cout <<  "    Este debe ser A,B,C o D" << endl;
                string tipo;
                getline(cin, tipo);
                cout << endl;
                char NuevoTipo = toupper(tipo[0]);
                if (NuevoTipo != 'A' && NuevoTipo != 'B' && NuevoTipo != 'C' && NuevoTipo != 'D'){
                    cout << "Tipo invalido" << endl;
                    continue;
                }
                balanceador->ModificaConstructorTipo(pos, tipo);
                cout << "Tipo modificado" << endl;
                balanceador->ArrayConstructores[pos]->imprimir();
            }
            else if (subopcion == "2"){
                string Respuesta;
                if (balanceador->ArrayConstructores[pos]->Prioridad){
                    cout << "El constructor ya tiene prioridad, ¿Desea quitaserla?" << endl;
                    getline(cin, Respuesta);
                    cout << endl;
                    if (Respuesta == "s"){
                        balanceador->ModificaConstructorPrioridad(pos, "N");
                    }
                    else{
                        continue;
                    }
                }
                else{
                    cout << "El constructor no tiene prioridad, ¿Desea darsela?" << endl;
                    getline(cin, Respuesta);
                    cout << endl;
                    if (Respuesta == "s"){
                        balanceador->ModificaConstructorPrioridad(pos, "S");
                    }
                    else{
                        continue;
                    }
                }
            }
            else{
                cout << "Opcion invalida" << endl;
                continue;
            }
        }

        else if (opcion == "3"){
            //Ver Historial de colas
            cout << "¿Que cola desea ver?" << endl;
            cout << "1. Cola de pedidos" << endl;
            cout << "2. Cola de almacen" << endl;
            cout << "3. Cola de alistadores" << endl;
            cout << "4. Cola de alistados" << endl;
            cout << "5. Cola de empacados" << endl;
            cout << "6. Historial de alistadores" << endl;
            string subopcion;
            getline(cin, subopcion);
            cout << endl;
            if (subopcion == "1"){
                cout << "Cola de pedidos" << endl;
                balanceador->HistorialColasBalanceador->imprimir();
            }
            else if (subopcion == "2"){
                cout << "Cola de almacen" << endl;
                balanceador->HistorialColaAlmacen->imprimir();
            }
            else if (subopcion == "3"){
                cout << "Cola de alistadores" << endl;
                bodega->HistorialAlisto->imprimir();
            }
            else if (subopcion == "4"){
                cout << "Cola de alistados" << endl;
                ArrayAlistadores[0]->HistorialAlistados->imprimir();
            }
            else if (subopcion == "5"){
                cout << "Cola de empacados" << endl;
                empacador->HistorialPorFacturar->imprimir();
            }
            else if (subopcion == "6"){
                cout << "Historial de alistadores" << endl;
                for (int i = 0; i < 6; i++){
                    cout << "Alistador " << i+1 << endl;
                    ArrayAlistadores[i]->Historial->imprimir();
                }
            }
            else{
                cout << "Opcion invalida" << endl;
                continue;
            }
        }

        else if (opcion == "4"){
            //Ver acciones de la fabrica en tiempo real
            cout << "Acciones de la fabrica en tiempo real" << endl;
            cout << "1. Balanceador" << endl;
            cout << "2. Constructores" << endl;
            cout << "3. Alistadores" << endl;
            cout << "4. Empacador" << endl;
            cout << "5. Facturador" << endl;
            cout << "6. Ver bodega" << endl;
            string subopcion;
            getline(cin, subopcion);
            cout << endl;
            if (subopcion == "1"){
                cout << "Balanceador" << endl;
                cout << balanceador->Accion << endl;
            }
            else if (subopcion == "2"){
                cout << "Constructores" << endl;
                for (int i = 0; i < 9; i++){
                    cout << "Constructor " << i+1 << endl;
                    cout << balanceador->ArrayConstructores[i]->Accion << endl;
                }
            }
            else if (subopcion == "3"){
                cout << "Alistadores" << endl;
                for (int i = 0; i < 6; i++){
                    cout << "Alistador " << i+1 << endl;
                    cout << ArrayAlistadores[i]->Accion << endl;
                }
            }
            else if (subopcion == "4"){
                cout << "Empacador" << endl;
                cout << empacador->Accion << endl;
            }
            else if (subopcion == "5"){
                cout << "Facturador" << endl;
                cout << facturador->Accion << endl;
            }
            else if(subopcion== "6"){

            }
            else{
                cout << "Opcion invalida" << endl;
                continue;
            }
        }

        else if (opcion == "5"){
            //Apagar elemento de la fabrica
            cout << "¿Que elemento desea apagar/prender?" << endl;
            cout << "1. Balanceador" << endl;
            cout << "2. Constructores" << endl;
            cout << "3. Alistadores" << endl;
            cout << "4. Empacador" << endl;
            cout << "5. Facturador" << endl;
            string subopcion;
            getline(cin, subopcion);
            cout << endl;
            if (subopcion == "1"){
                balanceador->ApagaBalanceador();
                if (balanceador->Estado== 0)
                    cout << "El balanceador fue apagado" << endl;
                else
                    cout << "El balanceador fue prendido" << endl;
            }
            else if (subopcion == "2"){
                balanceador->ImprimeNombreConstructores();
                cout << "Ingrese la posicion del constructor que desea apagar/prender: ";
                string posicion;
                getline(cin, posicion);
                cout << endl;
                int pos = stoi(posicion);
                balanceador->ArrayConstructores[pos]->ApagaConstructor();
                balanceador->ArrayConstructores[pos]->imprimir(); 
            }
            else if (subopcion == "3"){
                bodega->imprimiralistadores();
                cout << "Ingrese la posicion del alistador que desea apagar: ";
                string posicion;
                getline(cin, posicion);
                cout << endl;
                int pos = stoi(posicion);
                ArrayAlistadores[pos]->apagar();
                bodega->imprimiralistadores();
            }
            else if (subopcion == "4"){
                cout << "Empacador" << endl;
                empacador->apagar();
                if (empacador->estado == 1)
                    cout << "El empacador fue prendido" << endl;
                else
                    cout << "El empacador fue apagado" << endl; 
            }
            else if (subopcion == "5"){
                cout << "Facturador" << endl;
                facturador->apagar();
                if (facturador->Estado == 1)
                    cout << "El facturador fue prendido"<< endl;    
                else
                    cout << "El facturador fue apagado" << endl;
            }
            else{
                cout << "Opcion invalida" << endl;
                continue;
            }
        }
        else{
            cout << "Opcion invalida" << endl;
        }

    }
    while (*isRunning){
        
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}