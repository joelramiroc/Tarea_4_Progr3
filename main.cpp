// queue::push/pop
#include "Mascota.h"
#include "Evaluador.h"
#include <iostream>
#include <list>
#include <fstream>
using namespace std;

//Escribe los datos del objeto mascota dado en un archivo binario con el nombre dado en la posicion dada
//Nota: Se deben poder agregar varias mascotas en un solo archivo
int TAMANO_REGISTRO=14;
void escribir(string nombre_archivo, Mascota*mascota, int posicion)
{
    ofstream out(nombre_archivo.c_str(),ios::in|ios::out);

    if(!out.is_open())
    {
        out.open(nombre_archivo.c_str());
    }

    out.seekp(posicion * TAMANO_REGISTRO);
    out.write((char*)&mascota->edad,4);
    out.write(mascota->nombre.c_str(),10);
    out.close();
}

//Devuelve una mascota previamente escrita (con la funcion escribir()) en un archivo binario con nombre dado en la posicion dada
//Nota: Se deben poder leer varias mascotas de un solo archivo
Mascota* leer(string nombre_archivo, int posicion)
{

    int edad;
    char nombre[10];
    ifstream in(nombre_archivo.c_str());
    in.seekg(posicion *TAMANO_REGISTRO);
    in.read((char*)&edad,4);
    in.read(nombre,10);
    Mascota *m = new Mascota(edad,nombre);
    return m;
}

//Devuelve un vector que contenga todas las mascotas previamente escritas (con la funcion escribir()) en un archivo binario con nombre dado
//Nota: El vector debe contener las mascotas ordenadas de acuerdo a la posicion en la que se escribieron
vector<Mascota*> leerTodos(string nombre_archivo)
{

    vector<Mascota*>respuesta;
    Mascota* nueva;
    ifstream in(nombre_archivo.c_str());
    in.seekg(0,ios::end);
    int cantidad_bytes = in.tellg();
    double cantidad_registros= cantidad_bytes / TAMANO_REGISTRO;
    int edad;
    char nombre[10];
    for(int i=0;i<cantidad_registros;i++)
    {
    in.seekg(i *TAMANO_REGISTRO);
    in.read((char*)&edad,4);
    in.read(nombre,10);
    nueva= new Mascota(edad,nombre);
    respuesta.push_back(nueva);
    }
    in.close();
    return respuesta;
}

int main ()
{
    //Funcion evaluadora
    evaluar();
    return 0;
}
