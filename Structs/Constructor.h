struct Constructor{
    string Nombre; // Nombre ejemplo: Constructor 1
    int Estado; //Apagado = 0, Encendido = 1, En proceso = 2
    bool Disponibilidad; // Disponibilidad del constructor
    string tipoProducto; // D Seria que esta disponible para todos los productos

    //constructor
    Constructor(){
        Nombre = "";
        Estado = 0;
        Disponibilidad = true;
        tipoProducto = "D";
    }

    Constructor(string Nombre, int Estado, bool Disponibilidad, string tipoProducto){
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
        Disponibilidad = false;
        std::this_thread::sleep_for(std::chrono::seconds(TiempoTotal));
        cout << "El constructor" << Nombre << " ha terminado de elaborar" << Cantidad << "de productos" << Codigo << "\n";
        Disponibilidad = true;
}};