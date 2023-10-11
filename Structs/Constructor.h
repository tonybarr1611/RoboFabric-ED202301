struct Constructor{
    ListaCompleja * ListaProductos;
    string Nombre; // Nombre ejemplo: Constructor 1
    int Estado; //Apagado = 0, Encendido = 1, En proceso = 2
    bool Disponibilidad; // Disponibilidad del constructor
    string tipoProducto; // D Seria que esta disponible para todos los productos
    bool Prioridad = false; // Prioridad del constructor
    string* Accion; // Accion que esta realizando el constructor
    //constructor
    Constructor(){
        Nombre = "";
        Estado = 0;
        Disponibilidad = true;
        tipoProducto = "D";
        ListaProductos = new ListaCompleja();
        Accion = new string("Inactivo");
    }    
    Constructor(string Nombre, int Estado, bool Disponibilidad, string tipoProducto, string prioridad, ListaCompleja* ListaProductos){
        this->ListaProductos = ListaProductos;
        this->Nombre = Nombre;
        this->Estado = Estado;
        this->tipoProducto = tipoProducto;
        this->Disponibilidad = Disponibilidad;
        if (prioridad == "S"){
            Prioridad = true;
        }
        Accion = new string("Inactivo");
    }

    //Metodos

    void imprimir(){
        cout << Nombre << "\n";
        cout << "Estado: " << Estado << "\n";
        cout << "Tipo de Producto: " << tipoProducto << "\n";
        cout << "Disponibilidad: " << Disponibilidad << "\n";
        if (Prioridad)
            cout << "Prioridad: Si" << "\n";
        else
            cout << "Prioridad: No" << "\n";
    }

    void AgregarCantidadAlProducto(string Codigo, int Cantidad){
        // Solo llamar por medio de thread
        //Variables
        NodoComplejo* tmp = ListaProductos->Buscar(Codigo);
        int tiempoDeElboracion= stoi(tmp -> lista -> primerNodo -> siguiente -> siguiente -> dato);
        int TiempoTotal = tiempoDeElboracion * Cantidad;

        //Proceso
        //cout << Nombre << " esta elaborando " << Cantidad << " de productos" << Codigo << "\n";
        *Accion = "Elaborando " + to_string(Cantidad) + " de productos " + Codigo;
        Disponibilidad = false;
        std::this_thread::sleep_for(std::chrono::seconds(TiempoTotal));
        //cout << Nombre << " ha terminado de elaborar " << Cantidad << " de productos" << Codigo << "\n";
        *Accion = "Inactivo, recientemente Ha terminado de elaborar " + to_string(Cantidad) + " de productos " + Codigo;
        Disponibilidad = true;
}};