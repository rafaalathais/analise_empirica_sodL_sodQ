#include <iostream>
using namespace std;

class Cliente{
public:
    string nome;
    int cpf;
};

int main(){
    int chave;
    int i;

    int hash(){
        return chave % 20;
    }
    i = hash(chave);

}