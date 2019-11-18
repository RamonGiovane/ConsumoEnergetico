#ifndef CONSTANTES_H
#define CONSTANTES_H
#include <string>
using namespace std;

//Tamanho de string
const int TAMANHO_NOMES = 75;
const int TAMANHO_CODIGOS = 20;

//Nome de arquivo
const char FILE_FATURA_DAT[] = "data\\Fatura.dat";
const char FILE_FATURA_TMP[] = "data\\Fatura.tmp";
const char FILE_CLIENTE_DAT[] = "data\\Cliente.dat";
const char FILE_CLIENTE_TMP[] = "data\\Cliente.tmp";
const char FILE_HISTORICO_DAT[] = "data\\Historico.dat";
const char FILE_HISTORICO_TMP[] = "data\\Historico.tmp";
const char FILE_SAIDA_TMP[] = "saida.tmp";

//Caminho de programa
const char PATH_XPDF[] = "xpdf\\pdftotext.exe";

//Trecho de linha do arquivo texto das faturas
const char LINHA_BANDEIRA_AMARELA[] = "Band. Amarela - ";
const char LINHA_HISTORICO_CONSUMO[] = "Histórico de Consumo";

//Mensagem a ser exibidada ao usuário
const char MSG_DATA_INVALIDA[] ="\nParâmetro de data inválido.\n";
const char MSG_DADOS_NAO_ENCONTRADOS[] = "\nNenhum dado de consumo foi encontrado para os termos pesquisados.\n";
const char MSG_SINTAXE_INVALIDA[] = "FALHA: Sintaxe inválida na linha ";
const char MSG_ERRO_ARQUIVO_ENTRADA[] = "FALHA: O arquivo de entrada não pôde ser lido pois está corrompido ou vazio.";

#endif // !CONSTANTES_H
