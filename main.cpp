#include <iostream>
#include "string"
#include "vector"
#include "cmath"
using namespace std;

int GenerarPrimos(int limiteInferior);
int NumeroCoprimo(int indicadorDeEuler);
vector <int> Posiciones(string texto);
vector <int> Binario (int numero);
int ExponenciacionBinaria(int base, int exponente, int modulo);

int main() {
  
    string texto = "";
    cout << "Ingrese el texto que desea cifrar en RSA: ";
    getline(cin, texto);

    int longitudTexto = texto.length(), p, q, n, indicadorEuler, e;
    p = GenerarPrimos(longitudTexto);
    q = GenerarPrimos(p);
    n = p*q;
    indicadorEuler = (p - 1) * (q - 1);
    e = NumeroCoprimo(indicadorEuler);
    
    //Operación para hallar el valor de d
    int cont = 0;
    double d;
    do{
        cont++;
        d = (double) ( (indicadorEuler * cont) + 1) / e;
    }
    while (d - ( (int) d) != 0);

    /*Impresion de prueba
    cout << "\nImpresión de las variables de prueba: " << endl;
    cout << "Longitud del texto: " << longitudTexto << endl;
    cout << "Valor de p: " << p << endl;
    cout << "Valor de q: " << q << endl;
    cout << "Valor de n: " << n << endl;
    cout << "Valor del indicadorEuler: " << indicadorEuler << endl;
    cout << "Valor de e: " << e << "\n" << endl;
    cout << "Valor de d: " << d << "\n" << endl;
    */
    
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
    cout << "\nSu mensaje descifrado es:" << endl;
    vector<int> mensajeDescifrado;
    for (int valor : mensajeCifrado){
        exponenciacionBinaria = ExponenciacionBinaria(valor, d, n);
        mensajeDescifrado.push_back(exponenciacionBinaria);
        cout << exponenciacionBinaria << " ";
    }

    //Imprimir mensaje
    cout << "\nSu mensaje textualmente es:" << endl;
    string mensaje = "";
    for (int letra : valoresTexto){
        mensaje += (char)letra;
    }
    cout << mensaje << endl;

    return 0;
}

int GenerarPrimos(int limiteInferior){
    int cont = limiteInferior, numeroPrimo = 0;
    while (numeroPrimo<=limiteInferior){
        if (cont != 2 && cont != 3 && cont != 5 && cont != 7){
            if (cont % 2 != 0 && cont % 3 != 0 && cont % 5 != 0 && cont % 7 != 0 && cont != 1){
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
    int limiteInferior = 3, limiteSuperior = indicadorDeEuler - 2, resultado = limiteSuperior % limiteInferior;
    while (resultado != 0){
        limiteSuperior = limiteInferior;
        limiteInferior = resultado;
        resultado = limiteSuperior % limiteInferior;
    }
    return limiteInferior;
}

vector <int> Posiciones(string texto){
    vector<int> valores;
    for (int i = 0; i < texto.length(); i++){
        valores.push_back( (int) texto[i]);
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
    int k = exponenteABinario.size(), x = 1;
    for (int i = 0; i < k; i++){
        if (exponenteABinario[i] == 1){
            x = (int)((pow(x,2))*base) % modulo;
        }
        else{
            x = (int)(pow(x,2)) % modulo;
        }
    }
    return x;
}
