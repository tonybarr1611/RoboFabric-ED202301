struct Constructor{
    string Nombre; // Nombre ejemplo: Constructor 1
    int Estado; //Apagado = 0, Encendido = 1, En proceso = 2
    string Codigo; // Codigo del producto que esta elaborando

    //constructor
    Constructor(){
        Nombre = "";
        Estado = 0;
        Codigo = "";
    }

    Constructor(string Nombre, int Estado, string Codigo){
        this->Nombre = Nombre;
        this->Estado = Estado;
        this->Codigo = Codigo;
    }

    //Metodos

    void imprimir(){
        cout << "Constructor: " << Nombre << "\n";
        cout << "Estado: " << Estado << "\n";
        cout << "Codigo: " << Codigo << "\n";
    }

    void AgregarCantidadAlProducto(ListaCompleja * listaDeProductos){
        NodoComplejo* tmp = listaDeProductos->Buscar(Codigo);
        //Variables
        int cantidadAlmacenada= stoi(tmp -> lista -> primerNodo -> siguiente -> dato);
        int tiempoDeElboracion= stoi(tmp -> lista -> primerNodo -> siguiente -> siguiente -> dato);
        //Proceso
        cout << "El constructor" << Nombre << " esta elaborando el producto" << Codigo << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(tiempoDeElboracion));
        cout << "El producto" << Codigo << "ha sido elaborado" << "\n";
        cantidadAlmacenada++;
        tmp -> lista -> primerNodo -> siguiente -> dato = to_string(cantidadAlmacenada);
}};