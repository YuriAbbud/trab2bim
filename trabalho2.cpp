#include <iostream>
#include <fstream>
using namespace std;

char transformarEscalaCinza(int valor) {
    char escalaCinza[] = {'$', '@', 'B', '%', '8', '&', 'W', 'M', '#', '*', 'o', 'a', 'h', 'b', 'k', 'd', 'p', 'q', 'w', 'm', 'Z', 'O', '0', 'Q', 'L', 'C', 'J', 'U', 'Y', 'X', 'z', 'c', 'v', 'u', 'n', 'x', 'r', 'j', 'f', 't', '/', '|', '(', ')', '{', '}', '[', ']', '?', '-', '_', '+', '~', '<', '>', 'i', '!', 'l', 'I', ';', ':', ',', '"', '^', '`', '.'};
    int i = valor * 7 / 255;
    return escalaCinza[i];
}

int main() {

    ifstream arqfoo("img.foo", ios::binary);
    if (!arqfoo) {
        cerr << "Erro ao abrir arquivo .foo" << endl;
        return 1;
    }

    ofstream arqfoo2("img.foo2");
    if (!arqfoo2) {
        cerr << "Erro ao criar arquivo .foo2" << endl;
        return 1;
    }

    int linha, coluna;
    arqfoo >> coluna >> linha;
    arqfoo.ignore();
    cout << linha << ' ' << coluna << endl;

    char* valores = new char[linha * coluna];

    for (int i = 0; i < linha * coluna; i++) {
        char binario;
        arqfoo.read(reinterpret_cast<char*>(&binario), sizeof(char));
        valores[i] = binario;
    }
    
    int contador = 0;
    for (int i = 0; i < linha * coluna; i++) {
        int valor = valores[i];
        char simbolo = transformarEscalaCinza(abs(valor));
        arqfoo2 << simbolo;
        if (contador == coluna) {
            arqfoo2 << '\n';
            contador = 0;
        }
        contador++;
    }
    
    delete[] valores;
    arqfoo.close();
    arqfoo2.close();

    return 0;
}