/******************************************************************************

Welcome to GDB Online.

KARLA MILAGROS DOMINGUEZ DOPORTO 

06 DE AGOSTO DE 2025         09:27PM 

LENGUAJE DE PROGRAMACION 1 (Actividad #3 Calculo de RFC)

ESTE PROGRAMA ESTA DISEÑADO CON LA INTENCION DE AUTOMATIZAR EL PROCESO DE CALCULO DE RFC 
ESTO LLEVANDO ACABO INSTRUCCIONES PRECISAS QUE FUERON DADOS EN EL DOCUMENTO TALES COMO 
LAS PRIMERAS LETRAS DEL APELLIDO PARTERNO Y LA PRIMERA DEL APELLIDO MATERNO ECT. 

NOTA: En este se ha añadido la validacion de palabrabas prohibidas para que no permita seguir hasta que se elimine 
y que se muestre un mensaje 
"GROSERIA PALABRA PROHIBIDA"
*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <limits>
using namespace std;

class Empleado {
public:
    string nombre;
    string apellidoP;
    string apellidoM;
    int dia, mes, año;
    
    vector<string> palabrabasProhibidas={
        "popo","mierda","inutil","puto","pendejo","ladron","idiota","basura","verga","guey"
    };
    
    string aMinusculas(string texto){
        transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
        return texto;
    }
    
    bool contienePalabraProhibida(string campo) {
        string campoMin = aMinusculas(campo);
        for (string palabra : palabrabasProhibidas) {
            if (campoMin.find(palabra) !=string::npos){
                return true;
            }
        }
        return false;
    }
    
    void capturarDatos() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        do{
            cout<<"INGRESE EL NOMBRE";
            getline(cin, nombre);
            if (contienePalabraProhibida(nombre)){
                cout<<"ADVERTENCIA: GROCERIA:PALABRA PROHIBIDA en el nombre.Intente nuevamente.\n";
            }
        }while (contienePalabraProhibida(nombre));
        
        do{
            cout<<"INGRESE EL APELLIDO PATERNO:";
            getline(cin, apellidoP);
            if(contienePalabraProhibida(apellidoP)){
                cout<<"ADVERTENCIA:GROCERIA:PALABRA PROHIBIDA en el apellido paterno.Intente nuevamente.\n";
            }
        }while (contienePalabraProhibida(apellidoP));
        
        do {
            cout<<"INGRESE EL APELLIDO MATERNO(en caso de no contar con uno, escriba X):";
            getline(cin,apellidoM);
            if(contienePalabraProhibida(apellidoM)){
                cout<<"ADVERTENCIA:GROCERIA:PALABRA PROHIBIDA en el apellido materno.Intente nuevamente.\n";
            }
        }while (contienePalabraProhibida(apellidoM));
        
        cout<<"INGRESE DIA DE NACIMIENTO(2 DIGITOS):";
        cin>>dia;
        cout<<"INGRESE MES DE NACIMIENTO(2 DIGITOS):";
        cin>>mes;
        cout<<"INGRESE AÑO DE NACIMIENTO(4 DIGITOS):";
        cin>>año;
    }
    
    string obtenerRFC(){
        string rfc = "";
        
        rfc+= toupper(apellidoP[0]);
        for(size_t i=1;i < apellidoP.length();i++){
            char c = toupper(apellidoP[i]);
            if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
                rfc +=c;
                break;
            }
    }
    
    if(aMinusculas(apellidoM) == "X"|| apellidoM.empty()) {
        rfc += 'X';
        }else{
            rfc += toupper(apellidoM[0]);
        }
        
        rfc += toupper(nombre[0]);
        
        string rfc4 = aMinusculas(rfc.substr(0,4));
        
    for (string palabra : palabrabasProhibidas) {
        if (rfc4 == palabra) {
            rfc[3] = 'X';
            break;
        }
        
    }
    
    rfc += to_string(año).substr(2,2);
    
    if (mes<10) rfc += "0";
    rfc += to_string(mes);
    
    if (dia<10) rfc += "0";
    rfc+= to_string(dia);
    
    return rfc;
    }
    
};

int main() {
    Empleado emp;
    emp.capturarDatos();
    string rfc = emp.obtenerRFC();
    cout<<"\nEXITO: RFC GENERADO (sin homoclave): " <<rfc<<"XXXX" <<endl;
    return 0;
}