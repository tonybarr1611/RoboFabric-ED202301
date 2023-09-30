#include <iostream>
#include <filesystem>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <queue>

using namespace std;
namespace fs = std::filesystem;

// Declaraciones de Estructuras
struct NodoSimple;
struct NodoComplejo;
struct ListaSimple;
struct ListaCompleja;
struct Cola;
struct Producto;
struct Constructor;
struct Almacen;
struct Balanceador;

// Declaraciones de Funciones
string HoraSistema();
ListaSimple *SepararStringsPorTabs(string linea);
ListaCompleja *SepararStringsPorLineas(string linea, string tipo);
ListaSimple *LeerDirectorio(string, string);
ListaCompleja *LeerArchivo(string, string, string); // Directorio, tipo de archivo, tipo de lista
ListaCompleja *LeerArchivo(ListaSimple*, string); // Lista de archivos, tipo de lista
ListaCompleja *LeerArchivo(NodoSimple*, string); // Nodo de archivos, tipo de lista
int RetornaPrioridad(ListaCompleja *, string);


// Estructuras 
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

    void agregar(NodoSimple *nuevo){
        if(primerNodo == NULL){
            primerNodo = nuevo;
            ultimoNodo = nuevo;
        }else{
            ultimoNodo -> siguiente = nuevo;
            ultimoNodo = nuevo;
        }
    }

    void agregar(string dato){
        NodoSimple * nuevo = new NodoSimple(dato);
        agregar(nuevo);
    }

    NodoSimple * Buscar(string dato){
        NodoSimple * tmp = primerNodo;
        while(tmp != NULL){
            if(tmp->dato == dato){
                return tmp;
            }
            tmp = tmp -> siguiente;
        }
        return NULL;
    }

    int lenLista(){
        NodoSimple * tmp = primerNodo;
        int i = 0;
        while(tmp != NULL){
            tmp = tmp -> siguiente;
            i++;
        }
        return i;
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
            cout << "Nodo " << i << "\n";
            tmp -> imprimir();
            tmp = tmp -> siguiente;
            i++;
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

    void agregar(string tipo, ListaSimple * lista){
        agregar(new NodoComplejo(tipo, lista));
    }

    void agregar(ListaCompleja * lista){
        while (lista->primerNodo != NULL){
            agregar(lista->primerNodo);
            lista->primerNodo = lista->primerNodo->siguiente;
        }
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

    int lenLista(){
        NodoComplejo * tmp = primerNodo;
        int i = 0;
        while(tmp != NULL){
            tmp = tmp -> siguiente;
            i++;
        }
        return i;
    }

    NodoComplejo* Buscar(string dato){
        //Busca el dato en alguna de la listas, retorna la lista que lo contiene o NULL si no lo encuentra
        //Se puede usar para los clientes y productos al tener un unico nombre indicativo de la lista
        NodoComplejo * tmp = primerNodo;
        while(tmp != NULL){
            if(tmp->lista->Buscar(dato) != NULL){
                return tmp;
            }
            tmp = tmp -> siguiente;
        }
        cout << "No se encontro el dato" << "\n";
        return NULL;
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

#include "Structs/Producto.h"

#include "Structs/Constructor.h"

#include "Structs/Almacen.h"

#include "Structs/Balanceador.h"

#include "Funciones.h"