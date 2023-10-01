struct Constructor{
    string Nombre; // Nombre ejemplo: Constructor 1
    int Estado; //Apagado = 0, Encendido = 1, En proceso = 2
    bool Disponibilidad; // Disponibilidad del constructor
    int tipoProducto; // 0 = A, 1 = B, 2 = C, 3 <= TODAS

    //constructor
    Constructor(){
        Nombre = "";
        Estado = 0;
        Disponibilidad = true;
        tipoProducto = 3;
    }

    Constructor(string Nombre, int Estado, bool Disponibilidad, int tipoProducto){
        this->Nombre = Nombre;
        this->Estado = Estado;
        this->tipoProducto = tipoProducto;
        this->Disponibilidad = Disponibilidad;
    }

    //Metodos

    void imprimir(){
        cout << "Constructor: " << Nombre << "\n";
        cout << "Estado: " << Estado << "\n";
        cout << "Tipo de Producto: " << tipoProducto << "\n";
        cout << "Disponibilidad: " << Disponibilidad << "\n";
    }

    void AgregarCantidadAlProducto(ListaCompleja * listaDeProductos, string Codigo, int Cantidad){
        //Variables
        NodoComplejo* tmp = listaDeProductos->Buscar(Codigo);
        int tiempoDeElboracion= stoi(tmp -> lista -> primerNodo -> siguiente -> siguiente -> dato);
        int TiempoTotal = tiempoDeElboracion * Cantidad;

        //Proceso
        cout << "El constructor" << Nombre << " esta elaborando" << Cantidad << "de productos" << Codigo << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(TiempoTotal));
        cout << "El constructor" << Nombre << " ha terminado de elaborar" << Cantidad << "de productos" << Codigo << "\n";
}};