# Simulador de Mapeamento de Cache - UFGD

Este projeto é um simulador de parâmetros de memória cache, desenvolvido para a disciplina de **Arquitetura e Organização de Computadores** na **UFGD (Universidade Federal da Grande Dourados)**.

O simulador permite calcular diversos parâmetros de endereçamento de memória (w, r, s, d, tag) com base em entradas fornecidas manualmente pelo usuário via teclado.

## 🚀 Funcionalidades

O sistema suporta três tipos principais de mapeamento de cache:
1.  **Mapeamento Direto**
2.  **Mapeamento Totalmente Associativo**
3.  **Mapeamento Associativo por Conjunto**

A partir dos dados de entrada, o simulador calcula e exibe:
-   Tamanho da Memória Principal (em KB e bytes)
-   Tamanho do endereço da MP (bits)
-   Quantidade de palavras por bloco
-   Quantidade de blocos na MP
-   Quantidade de linhas da cache
-   Bits de **w** (palavra), **r/s/d** (dependendo do mapeamento) e **tag**.

## 🛠️ Como Executar

### Pré-requisitos
-   Compilador C++ (g++, clang ou similar).

### Passo a Passo
1.  Compile o arquivo fonte:
    ```bash
    g++ simulador_cache.cpp -o simulador_cache
    ```
2.  Execute o programa:
    ```bash
    ./simulador_cache
    ```
3.  No menu principal, escolha a **Opção 1** para informar os dados iniciais.
4.  Após informar os dados, escolha a **Opção 2** para visualizar os cálculos realizados.

## 📋 Exemplo de Uso

Ao iniciar o programa, informe os seguintes dados (exemplo):
-   Tamanho da MP: 64 (KB)
-   Palavras por bloco: 4
-   Tipo de mapeamento: 1 (Direto)
-   Tamanho da Cache: 2048 (bytes)
-   Tamanho da linha/bloco: 16 (bytes)

O sistema retornará detalhadamente a divisão dos bits do endereço.

## 👤 Autor
-   **Gabriel Henrique Jesus de Melo** - [GabrielHJM](https://github.com/GabrielHJM)
-   Instituição: UFGD - Sistemas de Informação

---
*Este projeto foi desenvolvido seguindo as diretrizes acadêmicas para fins de aprendizado sobre organização de computadores.*
