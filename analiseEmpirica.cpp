#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <iomanip> // Necessário para formatar as casas decimais no cout

using namespace std;

// Estrutura simples para cada espaço da tabela
struct Elemento {
    int chave;
    string valor;
    bool ocupado = false;
};

// --- TABELA 1: SONDAGEM LINEAR ---
class TabelaLinear {
public:
    int tamanho;
    int colisoes = 0;
    long long sondagens =0;
    int inseridos=0;
    vector<Elemento> tabela;

    // Construtor que inicializa o vector com o tamanho correto
    TabelaLinear(int size) : tamanho(size), tabela(size) {}

    void inserir(int chave, string valor) {
        int hash_base = chave % tamanho;

        for (int i = 0; i < tamanho; i++) {
            // Sondagem Linear: anda de 1 em 1
            int indice = (hash_base + i) % tamanho;
            sondagens++;

            if (!tabela[indice].ocupado) {
                tabela[indice].chave = chave;
                tabela[indice].valor = valor;
                tabela[indice].ocupado = true;
                inseridos++;
                return;
            }
            colisoes++;
        }
    }
};

// --- TABELA 2: SONDAGEM QUADRÁTICA ---
class TabelaQuadratica {
public:
    int tamanho;
    int colisoes = 0;
    long long sondagens =0;
    int inseridos = 0;
    vector<Elemento> tabela;

    TabelaQuadratica(int size) : tamanho(size), tabela(size) {}

    void inserir(int chave, string valor) {
        int hash_base = chave % tamanho;

        for (int i = 0; i < tamanho; i++) {
            // Sondagem Quadrática: anda em saltos de i * i
            int indice = (hash_base + (i * i)) % tamanho;
            sondagens++;
            
            if (!tabela[indice].ocupado) {
                tabela[indice].chave = chave;
                tabela[indice].valor = valor;
                tabela[indice].ocupado = true;
                inseridos++;
                return;
            }
            
            colisoes++;
        }
    }
};

int main() {
    // Configurações do teste
    const int TAB_SIZE = 10000;        // Tamanho da tabela 
    const int NUM_ELEMENTS = 7500;     // Fator de carga 
    cout << "--- Configuração do Teste (C++) ---" << endl;
    cout << "Tamanho da Tabela: " << TAB_SIZE << endl;
    cout << "Elementos a inserir: " << NUM_ELEMENTS << " (Fator de Carga: " 
         << fixed << setprecision(2) << (double)NUM_ELEMENTS / TAB_SIZE << ")\n" << endl;

    // Criando o vetor com as chaves de teste
    vector<int> chaves_teste;

    srand(42); 
    for (int i = 0; i < NUM_ELEMENTS; i++) {
            chaves_teste.push_back(rand());
    }

    // --- TESTE 1: SONDAGEM LINEAR ---
    TabelaLinear ht_linear(TAB_SIZE);
    
    // Marca o tempo de início de alta precisão
    auto start = chrono::high_resolution_clock::now();
    
    for (int chave : chaves_teste) {
        ht_linear.inserir(chave, "Dados");
    }
    
    // Marca o tempo de fim
    auto end = chrono::high_resolution_clock::now();
    
    // Calcula a diferença em milissegundos (ms)
    chrono::duration<double, milli> tempo_linear = end - start;


    // --- TESTE 2: SONDAGEM QUADRÁTICA ---
    TabelaQuadratica ht_quad(TAB_SIZE);

    start = chrono::high_resolution_clock::now();
    
    for (int chave : chaves_teste) {
        ht_quad.inserir(chave, "Dados");
    }
    
    end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tempo_quad = end - start;
    
    
    double media_linear = (double) ht_linear.sondagens / NUM_ELEMENTS ;
    double media_quad = (double) ht_quad.sondagens / NUM_ELEMENTS ;

    // --- EXIBIÇÃO DOS RESULTADOS (Visual do primeiro código) ---
    cout << "=== RESULTADOS DA ANÁLISE EMPÍRICA ===" << endl;
    cout << "Sondagem Linear:" << endl;
    cout << "  - Total de colisões: " << ht_linear.colisoes << endl;
     cout << "  - Total de sondagens: " << ht_linear.sondagens << endl;
     cout << "  - Média de sondagens: " << media_linear << endl;
    cout << "  - Tempo de execução: " << tempo_linear.count() << " ms" << endl;
    cout << "  - Elementos inseridos: " << ht_linear.inseridos << endl;
    cout << endl;
    cout << "Sondagem Quadrática:" << endl;
    cout << "  - Total de colisões: " << ht_quad.colisoes << endl;
     cout << "  - Média de sondagens: " << media_quad << endl;
    cout << "  - Tempo de execução: " << tempo_quad.count() << " ms" << endl;
    cout << "  - Total de sondagens: " << ht_quad.sondagens << endl;
    cout << "  -Elementos inseridos: " << ht_quad.inseridos << endl;
    cout << "\n--------------------------------------" << endl;
    
    double ganho_colisoes = ((double)(ht_linear.colisoes - ht_quad.colisoes) / ht_linear.colisoes) * 100;
    cout << "Resultado: A Sondagem Quadrática evitou " << ganho_colisoes << "% de sondagens extras em comparação à Linear." << endl;

    return 0;
}

