#include <iostream>

using namespace std;

struct NodoSimple;
struct NodoComplejo;
struct ListaSimple;
struct ListaCompleja;
struct Cola;

ListaSimple *SepararStringsPorTabs(string linea);
ListaCompleja *SepararStringsPorLineas(string linea, string tipo);

//Estructuras 
struct NodoSimple {
    // NodoSimple es un nodo de ListaSimple
    string dato;
    NodoSimple *siguiente = NULL;

    NodoSimple() {
        dato = "";
        siguiente = NULL;
    }

    NodoSimple(int _dato) {
        dato = _dato;
        siguiente = NULL;
    }

    NodoSimple(string _dato) {
        dato = _dato;
        siguiente = NULL;
    }

    void imprimir() {
        cout << dato << "\n";
    }

};

struct ListaSimple{
    // ListaSimple consiste de una lista de strings
    NodoSimple * primerNodo = NULL;
    NodoSimple * ultimoNodo = NULL;

    ListaSimple(){
        primerNodo = NULL;
        ultimoNodo = NULL;
    }

    void imprimir(){
        NodoSimple * tmp = primerNodo;
        while(tmp != NULL){
            tmp -> imprimir();
            tmp = tmp -> siguiente;
        }
    }

    void agregar(string dato){
        NodoSimple * nuevo = new NodoSimple(dato);
        if(primerNodo == NULL){
            primerNodo = nuevo;
            ultimoNodo = nuevo;
        }else{
            ultimoNodo -> siguiente = nuevo;
            ultimoNodo = nuevo;
        }
    }
};

struct NodoComplejo{
    // NodoComplejo es un nodo de ListaCompleja que contiene una lista simple
    string tipo;
    ListaSimple * lista;
    NodoComplejo * siguiente;
    NodoComplejo * anterior;

    NodoComplejo(){
        tipo = "";
        lista = new ListaSimple();
        siguiente = NULL;
        anterior = NULL;
    }

    NodoComplejo(string _tipo){
        tipo = _tipo;
        lista = new ListaSimple();
        siguiente = NULL;
        anterior = NULL;
    }

    NodoComplejo(string _tipo, ListaSimple * _lista){
        tipo = _tipo;
        lista = _lista;
        siguiente = NULL;
        anterior = NULL;
    }

    NodoComplejo(ListaSimple * _lista){
        tipo = "";
        lista = _lista;
        siguiente = NULL;
        anterior = NULL;
    }

    void imprimir(){
        cout << "Lista tipo: " << tipo << "\n";
        lista -> imprimir();
    }

    void agregar(string dato){
        lista -> agregar(dato);
    }
};

struct ListaCompleja{
    // ListaCompleja consiste de una lista de listas, cada nodo contiene una lista simple
    // El string tipo es para identificar el tipo de dato que contiene la lista simple
    string tipo;
    NodoComplejo * primerNodo;
    NodoComplejo * ultimoNodo;

    ListaCompleja(){
        tipo = "";
        primerNodo = NULL;
        ultimoNodo = NULL;
    }

    ListaCompleja(string _tipo){
        tipo = _tipo;
        primerNodo = NULL;
        ultimoNodo = NULL;
    }

    void imprimir(){
        NodoComplejo * tmp = primerNodo;
        int i = 0;
        while(tmp != NULL){
            tmp -> imprimir();
            tmp = tmp -> siguiente;
        }
    }

    void agregar(NodoComplejo * nuevo){
        if(primerNodo == NULL){
            primerNodo = nuevo;
            ultimoNodo = nuevo;
        }else{
            ultimoNodo -> siguiente = nuevo;
            nuevo -> anterior = ultimoNodo;
            ultimoNodo = nuevo;
        }
    }

    void agregar(ListaSimple * dato){
        agregar(new NodoComplejo(dato));
    }

    void agregar(string dato, ListaSimple * lista){
        agregar(new NodoComplejo(dato, lista));
    }

    NodoComplejo * eliminar(NodoComplejo * nodo){
        if(nodo == primerNodo){
            primerNodo = primerNodo -> siguiente;
            primerNodo -> anterior = NULL;
        }else if(nodo == ultimoNodo){
            ultimoNodo = ultimoNodo -> anterior;
            ultimoNodo -> siguiente = NULL;
        }else{
            nodo -> anterior -> siguiente = nodo -> siguiente;
            nodo -> siguiente -> anterior = nodo -> anterior;
        }
        return nodo;
    }
};

struct Cola{
    // TODO verificar si usa NodoSimple o NodoComplejo
    NodoSimple *primerNodo;
    NodoSimple *ultimoNodo;

    Cola(){
        primerNodo = NULL;
    }

    void imprimir(){
        NodoSimple *tmp = primerNodo;
        while(tmp != NULL){
            tmp->imprimir();
            tmp = tmp -> siguiente;
        }
    }

    void encolar(NodoSimple *nuevo){
        if(primerNodo == NULL)
            primerNodo = nuevo;
        else
            ultimoNodo -> siguiente = nuevo;
        ultimoNodo = nuevo;
    }

    NodoSimple *desencolar(){
        NodoSimple *tmp = primerNodo;
        primerNodo = primerNodo -> siguiente;
        return tmp;
    }

    NodoSimple *peek(){
        return primerNodo;
    }
};

//Funciones

ListaSimple *SepararStringsPorTabs(string linea) {
    ListaSimple *lista = new ListaSimple(); // Crear una instancia de ListaSimple
    string dato = "";

    for (int i = 0; i < linea.length(); i++) {
        if (linea[i] == '\t') {
            lista->agregar(dato); // Agregar el dato a la lista
            dato = "";
        } else {
            dato += linea[i];
        }
    }
    lista->agregar(dato); // Agregar el último dato
    return lista;
}

ListaCompleja *SepararStringsPorLineas(string linea, string tipo){
    // Toma un string y lo separa por saltos de línea, cada línea se convierte en una lista simple que se pasa por SepararStringsPorTabs
    ListaCompleja *listaCompleja = new ListaCompleja();
    listaCompleja->tipo = tipo;
    NodoComplejo *nodoActual = new NodoComplejo(tipo);
    string dato = "";

    for (int i = 0; i < linea.length(); i++) {
        if (linea[i] == '\n') {
            ListaSimple *listaSimple = SepararStringsPorTabs(dato);
            nodoActual->lista = listaSimple;
            listaCompleja->agregar(nodoActual);
            nodoActual = new NodoComplejo(tipo);
            dato = "";
        } else {
            dato += linea[i];
        }
    }

    ListaSimple *listaSimple = SepararStringsPorTabs(dato);
    nodoActual->lista = listaSimple;
    listaCompleja->agregar(nodoActual);

    return listaCompleja;
}