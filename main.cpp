#include <iostream>
#include "string"
#include "vector"
#include "cmath"
using namespace std;

vector<char> letras = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int GenerarPrimos(int limiteInferior);
int NumeroCoprimo(int numero);
vector <int> Posiciones(string texto);
vector<int> Binario (int numero);
int ExponenciacionBinaria(int base, int exponente, int modulo);

int main() {

    string texto;
    cout << "Ingrese el texto que desea cifrar en RSA:";
    cin >> texto;

    int longitudTexto = texto.length(), p, q, n, indicadorEuler, e;
    p = GenerarPrimos(longitudTexto);
    q = GenerarPrimos(p);
    n = p*q;
    indicadorEuler = (p-1)*(q-1);
    e = NumeroCoprimo(indicadorEuler);

    //Operación para hallar el valor de d
    int cont=0;
    double d;
    do{
        cont++;
        d = (double)((indicadorEuler*cont)+1)/e;
    }
    while (d-((int)d)!=0);

    //Obtencion de los valores correspondientes a cada letra
    vector<int> valoresTexto = Posiciones(texto);

    //Cifrar mensaje
    cout << "Su mensaje cifrado es:" << endl;
    vector<int> mensajeCifrado;
    int exponenciacionBinaria;
    for (int valor : valoresTexto){
        exponenciacionBinaria = ExponenciacionBinaria(valor, e, n);
        mensajeCifrado.push_back(exponenciacionBinaria);
        cout << exponenciacionBinaria << " ";
    }

    //Descifrar mensaje
    cout << "\n" <<"Su mensaje descifrado es:" << endl;
    vector<int> mensajeDescifrado;
    for (int valor : mensajeCifrado){
        exponenciacionBinaria = ExponenciacionBinaria(valor, d, n);
        mensajeDescifrado.push_back(exponenciacionBinaria);
        cout << exponenciacionBinaria << " ";
    }

    //Imprimir mensaje
    cout << "\n" <<"Su mensaje textualmente es:" << endl;
    string mensaje = "";
    for (int letra : mensajeDescifrado){
        mensaje+= letras[letra];
    }
    cout << mensaje;

    return 0;
}

int GenerarPrimos(int limiteInferior){
    int cont = 2, numeroPrimo = 0;
    while (numeroPrimo<=limiteInferior){
        if (cont!=2 && cont!=3 && cont!=5 && cont!=7){
            if (cont%2!=0 && cont%3!=0 && cont%5!=0 && cont%7!=0){
                numeroPrimo = cont;
            }
        }
        else{
            numeroPrimo = cont;
        }
        cont++;
    }
    return numeroPrimo;
}

// Numero coprimo entre 3 y 𝜙(n)-2
int NumeroCoprimo(int indicadorDeEuler){
    int coprimo = 0;
    for (int i=3; i<indicadorDeEuler-2; i++){
        if (indicadorDeEuler%i!=0){
            coprimo = i;
            break;
        }
        else{
            continue;
        }
    }
    return coprimo;
}

vector <int> Posiciones(string texto){
    vector<int> valores;
    for (int i=0; i<texto.length(); i++){
        for (int j=0; j<letras.size(); j++){
            if (texto[i]==letras[j]){
                valores.push_back(j);
                break;
            }
        }
    }
    return valores;
}
vector<int> Binario (int numero){
    vector<int> binario;
    while (numero!=0){
        binario.insert(binario.begin(),numero % 2);
        numero /= 2;
    }
    return binario;
}
int ExponenciacionBinaria(int base, int exponente, int modulo){
    vector<int> exponenteABinario = Binario(exponente);
    int k = exponenteABinario.size(), x=1;
    for (int i=0; i<k; i++){
        if (exponenteABinario[i] == 1){
            x = (int)((pow(x,2))*base)%modulo;
        }
        else{
            x = (int)(pow(x,2))%modulo;
        }
    }
    return x;
}