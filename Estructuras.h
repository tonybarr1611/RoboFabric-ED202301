#include <iostream>

using namespace std;

struct Nodo;
struct ListaSimple;
struct Cola;

ListaSimple SepararStringsPorTabs(string);

//Estructuras 

struct Cola{
    Nodo *primerNodo;
    Nodo *ultimoNodo;

    Cola(){
        primerNodo = NULL;
    }

    void imprimir(){
        Nodo *tmp = primerNodo;
        while(tmp != NULL){
            tmp->imprimir();
            tmp = tmp -> siguiente;
        }
    }

    void encolar(Nodo *nuevo){
        if(primerNodo == NULL)
            primerNodo = nuevo;
        else
            ultimoNodo -> siguiente = nuevo;
        ultimoNodo = nuevo;
    }

    Nodo *desencolar(){
        Nodo *tmp = primerNodo;
        primerNodo = primerNodo -> siguiente;
        return tmp;
    }

    Nodo *peek(){
        return primerNodo;
    }
};

struct Nodo {
    // TODO Verificar tipo de dato que se va a guardar
    string dato;
    Nodo *siguiente;

    Nodo(int _dato) {
        dato = _dato;
        siguiente = NULL;
    }

    Nodo(string _dato) {
        dato = _dato;
        siguiente = NULL;
    }

    void imprimir() {
        cout << dato << "\t";
    }

};

struct ListaSimple{
    Nodo * primerNodo;
    Nodo * ultimoNodo;

    ListaSimple(){
        primerNodo = NULL;
    }

    void imprimir(){
        Nodo * tmp = primerNodo;
        while(tmp != NULL){
            cout <<tmp -> dato<< "\t";
            tmp = tmp -> siguiente;
        }
    }

    void agregar(string dato){
        Nodo * nuevo = new Nodo(dato);
        if(primerNodo == NULL){
            primerNodo = nuevo;
            ultimoNodo = nuevo;
        }else{
            ultimoNodo -> siguiente = nuevo;
            ultimoNodo = nuevo;
        }
    }
};



//Funciones

ListaSimple SepararStringsPorTabs(string linea) {
    ListaSimple lista; // Crear una instancia de ListaSimple
    string dato = "";

    for (int i = 0; i < linea.length(); i++) {
        if (linea[i] == '\t') {
            lista.agregar(dato); // Agregar el dato a la lista
            dato = "";
        } else {
            dato += linea[i];
        }
    }

    lista.agregar(dato); // Agregar el último dato
    return lista;
}

