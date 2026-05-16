/*
 * Nome: Gabriel Henrique Jesus de Melo
 * Instituição: UFGD - Sistemas de Informação
 * Finalidade: Simulador de parâmetros de memória cache baseado em entrada manual
 */

#include <cmath>
#include <iostream>
#include <string>

using namespace std;

// Estrutura para armazenar os dados informados pelo usuario
struct DadosMemoria {
  int mp_kb;
  int palavras_por_bloco;
  int tipo_mapeamento; // 1: Direto, 2: Totalmente Associativo, 3: Associativo
                       // por Conj.
  int cache_bytes;
  int linha_bytes;
  int num_conjuntos;
};

/*
 * Finalidade: Exibe o menu principal do programa.
 * Retorno: Não possui retorno. Apenas imprime as opções na tela.
 */
void exibirMenu() {
  cout << "\n=======================================\n";
  cout << "   SIMULADOR DE MAPEAMENTO DE CACHE    \n";
  cout << "=======================================\n";
  cout << "1. Informar dados iniciais\n";
  cout << "2. Apresentar informacoes calculadas\n";
  cout << "3. Sair do programa\n";
  cout << "Escolha uma opcao: ";
}

/*
 * Finalidade: Solicita os parâmetros de configuração via teclado.
 * Parâmetros:
 * - dados: Referência para a estrutura onde os valores serão armazenados.
 * Retorno: true após a leitura dos dados.
 */
bool informarDados(DadosMemoria &dados) {
  cout << "\n--- ENTRADA DE DADOS ---\n";
  cout << "Tamanho da Memória Principal (KB): ";
  cin >> dados.mp_kb;
  cout << "Quantidade de palavras por bloco: ";
  cin >> dados.palavras_por_bloco;
  cout << "Tipo de mapeamento (1:Direto, 2:Totalmente Associativo, 3:Associativo "
          "por Conjunto): ";
  cin >> dados.tipo_mapeamento;
  cout << "Tamanho da Cache (bytes): ";
  cin >> dados.cache_bytes;
  cout << "Tamanho da linha/bloco (bytes): ";
  cin >> dados.linha_bytes;

  if (dados.tipo_mapeamento == 3) {
    cout << "Quantidade de conjuntos: ";
    cin >> dados.num_conjuntos;
  } else {
    dados.num_conjuntos = 0;
  }

  cout << "Dados informados com sucesso!\n";
  return true;
}

/*
 * Finalidade: Processa e exibe os resultados para o Mapeamento Direto.
 */
void processarDireto(const DadosMemoria &dados, long long mp_bytes, int tam_end,
                     int w, int num_linhas) {
  cout << "Tipo do mapeamento: Direto\n";
  cout << "Quantidade de linhas da cache: " << num_linhas << "\n";

  int r = log2(num_linhas);
  int tag = tam_end - r - w;

  cout << "\nValores calculados (em bits):\n";
  cout << "- w (palavra): " << w << "\n";
  cout << "- r (linha): " << r << "\n";
  cout << "- tag: " << tag << "\n";
}

/*
 * Finalidade: Processa e exibe os resultados para o Mapeamento Totalmente
 * Associativo.
 */
void processarTotalmente(const DadosMemoria &dados, long long mp_bytes,
                         int tam_end, int w, int num_linhas) {
  cout << "Tipo do mapeamento: Totalmente Associativo\n";
  cout << "Quantidade de linhas da cache: " << num_linhas << "\n";

  int s = tam_end - w;
  int tag = s; // No totalmente associativo, a tag é o próprio bloco (s)

  cout << "\nValores calculados (em bits):\n";
  cout << "- w (palavra): " << w << "\n";
  cout << "- s (bloco): " << s << "\n";
  cout << "- tag: " << tag << "\n";
}

/*
 * Finalidade: Processa e exibe os resultados para o Mapeamento Associativo por
 * Conjunto.
 */
void processarConjunto(const DadosMemoria &dados, long long mp_bytes,
                       int tam_end, int w, int num_linhas) {
  cout << "Tipo do mapeamento: Associativo por Conjunto\n";

  int num_conjuntos = dados.num_conjuntos;
  if (num_conjuntos <= 0) {
    cout << "Erro: Quantidade de conjuntos invalida para este mapeamento.\n";
    return;
  }

  int linhas_por_conjunto = num_linhas / num_conjuntos;
  cout << "Quantidade de linhas da cache: " << num_linhas << "\n";
  cout << "Quantidade de conjuntos (calculado): " << num_conjuntos << "\n";
  cout << "Quantidade de linhas por conjunto: " << linhas_por_conjunto << "\n";

  int d = log2(num_conjuntos);
  int tag = tam_end - d - w;

  cout << "\nValores calculados (em bits):\n";
  cout << "- w (palavra): " << w << "\n";
  cout << "- d (conjunto): " << d << "\n";
  cout << "- tag: " << tag << "\n";
}

/*
 * Finalidade: Calcula informações gerais e direciona para o mapeamento correto.
 */
void calcularEApresentar(const DadosMemoria &dados) {
  // Validação básica para evitar erros de execução (divisão por zero, log de 0)
  if (dados.linha_bytes <= 0 || dados.mp_kb <= 0 || dados.cache_bytes <= 0) {
    cout << "Erro: Dados invalidos (valores devem ser positivos).\n";
    return;
  }

  cout << "\n--- RESULTADOS DOS CALCULOS ---\n";

  // Cálculos Gerais (conforme requisitos do professor)
  long long mp_bytes = dados.mp_kb * 1024LL;
  int tam_end = log2(mp_bytes);
  long long num_blocos_mp = mp_bytes / dados.linha_bytes;
  int num_linhas = dados.cache_bytes / dados.linha_bytes;
  int w = log2(dados.linha_bytes);

  // Exibição dos Dados Obrigatórios
  cout << "Tamanho da MP: " << dados.mp_kb << " KB (" << mp_bytes
       << " bytes)\n";
  cout << "Tamanho da Cache: " << dados.cache_bytes << " bytes\n";
  cout << "Tamanho do endereco da MP: " << tam_end << " bits\n";
  cout << "Quantidade de palavras por bloco: " << dados.palavras_por_bloco
       << "\n";
  cout << "Quantidade de blocos na MP: " << num_blocos_mp << "\n";

  cout << "\n--- DETALHES ESPECIFICOS ---\n";
  switch (dados.tipo_mapeamento) {
  case 1:
    processarDireto(dados, mp_bytes, tam_end, w, num_linhas);
    break;
  case 2:
    processarTotalmente(dados, mp_bytes, tam_end, w, num_linhas);
    break;
  case 3:
    processarConjunto(dados, mp_bytes, tam_end, w, num_linhas);
    break;
  default:
    cout << "Erro: Tipo de mapeamento (" << dados.tipo_mapeamento
         << ") desconhecido.\n";
  }
  cout << "-------------------------------\n";
}

/*
 * Finalidade: Gerencia o menu principal e o fluxo do programa.
 */
int main() {
  DadosMemoria dados = {0};
  bool dadosCarregados = false;
  int opcao = 0;

  while (opcao != 3) {
    exibirMenu();
    if (!(cin >> opcao)) {
      cin.clear();
      cin.ignore(10000, '\n');
      cout << "Entrada invalida. Por favor, digite um numero.\n";
      continue;
    }

    switch (opcao) {
    case 1:
      dadosCarregados = informarDados(dados);
      break;
    case 2:
      if (dadosCarregados) {
        calcularEApresentar(dados);
      } else {
        cout << "Por favor, primeiro informe os dados iniciais (Opcao 1).\n";
      }
      break;
    case 3:
      cout << "Encerrando o simulador... Sucesso no trabalho!\n";
      break;
    default:
      cout << "Opcao invalida. Tente novamente.\n";
    }
  }

  return 0;
}
