#include <iostream>

using namespace std;

//Estructuras 
struct Nodo {
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

