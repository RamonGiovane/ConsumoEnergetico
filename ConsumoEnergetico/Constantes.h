#ifndef CONSTANTES_H
#define CONSTANTES_H
#include <string>
#include <sstream>
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

//Diretório
const char DIR_DATA[] = "data";

//Caminho de programa
const char PATH_XPDF[] = "xpdf\\pdftotext.exe";

//Trecho de linha do arquivo texto das faturas
const char TRECHO_BANDEIRA_AMARELA[] = "Band. Amarela - ";
const char LINHA_BANDEIRA_AMARELA[] = "Bandeira Amarela";
const char LINHA_BANDEIRA_VERMELHA[] = "Bandeira Vermelha";
const char LINHA_HISTORICO_CONSUMO[] = "Histórico de Consumo";
const char LINHA_ENERGIA[] = "Energia Elétrica";
const char LINHA_ILUMINACAO[] = "Contrib Ilum Publica Municipal";
const char LINHA_HISTORICO[] = "Histórico ";

//Mensagem a ser exibidada ao usuário
const char MSG_DATA_INVALIDA[] ="\nParâmetro de data inválido.\n";
const char MSG_DADOS_NAO_ENCONTRADOS[] = "\nNenhum dado de consumo foi encontrado para os termos pesquisados.\n";
const char MSG_ARQUIVO_LIDO[] = " arquivo lido com sucesso.";
const char MSG_ARQUIVOS_LIDOS[] = " arquivos lidos com sucesso.";
const char MSG_ARQUIVO_IGNORADO[] = " arquivo com falha ignorado.";
const char MSG_ARQUIVOS_IGNORADOS[] = " arquivos com falha ignorados.";
const char MSG_CONVERTENDO_PDF[] = "\nConvertendo PDF... ";
const char MSG_LENDO_FATURA[] = "\nLendo a fatura digital... ";
const char MSG_OBTENDO_INFO[] = "\nObtendo informações da fatura... ";
const char MSG_FIM_LEITURA[] = "\n\nA leitura terminou.\n";
const char MSG_LENDO[] = "\nLendo ";
const char MSG_IGNORANDO_ARQUIVO[] = "\nIgnorando arquivo...\n\n";
const char MSG_ARQUIVO_IMPORTADO[] = "\nArquivo lido e importado com sucesso...\n\n";
const char MSG_CLIENTE_NAO_LOCALIZADO[] = "\nCliente não localizado.\n";
const char MSG_FATURA_JA_EXISTE[] = "AVISO: Esta fatura já foi importada anteriormente.";

//Mensagem de erro a ser exibidada ao usuário
const char MSGE_HISTORICO_NAO_ENCONTRADO[] = "\nFALHA: Dados de histórico de consumo não encontrados. ";
const char MSGE_HISTORICO_INCONSISTENTE[] = "\nFALHA: Dados de histórico de consumo inconsistentes. ";
const char MSGE_NUMEROS_NAO_ENCONTRADOS[] = "\nFALHA: Não foi possível computar o número do cliente e/ou da instalação";
const char MSGE_DATA_E_VALOR_NAO_ENCONTRADO[] = "\nFALHA: Dados da fatura incompletos. Data de vencimento e valor a pagar não encontrados.\nProvavelmente o arquivo está corrompido";
const char MSGE_SINTAXE_INVALIDA[] = "FALHA: Sintaxe inválida na linha ";
const char MSGE_VALORES_FATURADOS[] = "\nFALHA: Não foi possível computar os valores faturados.";
const char MSGE_ARQUIVO_ENTRADA[] = "FALHA: O arquivo de entrada não pôde ser lido pois está corrompido ou vazio.";
const char MSGE_ARQUIVO_NAO_LIDO[] = "\nFALHA: O arquivo não pôde ser lido. Provavelmente não é um arquivo PDF ou não existe.";
const char MSGE_ARQUIVO_CORROMPIDO[] = "\nFALHA: O conteúdo da fatura não pôde ser lido. Possivelmente o arquivo está corrompido.";
const string MSGE_MISSING_XPDF = "\nDependência não encontrada:\n\t" 
										"> O arquivo " + string(PATH_XPDF) + " não pôde ser localizado.\n\nO programa não pode prosseguir.\n";

//Pedaços de string necessários para construir uma mensagem ao usuário
const char TITLE_HISTORICO[] = "\n|| Histórico de consumo de ";
const char TITLE_PESQUISANDO_CLIENTE[] = "|| Pesquisando dados do cliente:";
const char STR_A[] = " a ";
const char STR_D_PERIOD[] = ": ";
const char STR_KWH[] = " kWh";
const char SUBTITLE_HISTORICO[] = " MÊS/ANO  CONSUMO  \tMÉDIA DIÁRIA\n";
const char SUBTITLE_INSTALACAO[] = "\n\n| Instalação Nº ";
const char STR_CONSUMO_INSTALACAO[] = "Consumo da Instalação Nº ";
const char STR_VALOR_A_PAGAR[] = "Valor a pagar: R$ ";
const char STR_DATA_VENC[] = " Data de Vencimento: ";
const char STR_REFERENTE[] = "Referente a: ";
const char STR_DE[] = " de ";

//Constantes de strings e chars utilitários
const char BARRA_N = '\n';
const string SBARRA_N = "\n";
const string VAZIO = "";
const char ESPACO = ' ';
const char BARRA = '/';
const char SEPARTOR[] = " | ";

//Casa com um mês e ano referente no formato: "NOV/2019"
const char REGEX_MES_REFERENTE[] = "[A-Z]{3}[/]\\d{4}";

//Casa com as datas de leitura que estejam no formato: "MM/yy MM/yy MM/yy" que estejam precedidas ou não por espaços em branco
const char REGEX_DATAS_LEITURA[] = "\\s*\\d{2}[/]\\d{2}\\s*\\d{2}[/]\\d{2}\\s*\\d{2}[/]\\d{2}";

//Casa com a data de vencimento e o valor a pagar que estejam no formato "22/12/2019 R$ 199,00"
const char REGEX_DATA_E_VALOR[] = "\\.*\\d{2}[/]\\d{2}[/]\\d{4}.*\\d{1,9}[,]\\d{2}";

//Casa com número do cliente e da instalação, cada um de 5 a 11 números entre espaço
const char REGEX_CLIENTE_INSTALACAO[] = "\\d{5,11}\\s*\\d{5,11}";

//Casa com um string que comece com uma letra maiúscula (correspondente a um nome) ou com um CEP
const char REGEX_CEP_E_NOMES[] = "(^[A-Z]+)|(^\\d{5}[-]\\d{3})";

//Casa com um mês e ano do histórico de consumo no formato: "NOV/19";
const char REGEX_DATA_HISTORICO[] = "[A-Z]{3}[/]\\d{2}";



const int TAMANHO_HISTORICO = 13;


//Informações de do programa e ajuda
const string PROG_INFO = "CEE versão 0.1: Relatório de Consumo de Energia Elétrica"  + SBARRA_N 
+ "2019 Ramon Giovane https://github.com/RamonGiovane"  + SBARRA_N 


+ "uso:\n1. Importando uma fatura ou várias faturas da CEMIG\n\tcee <fatura> | <diretório> "  + SBARRA_N  + SBARRA_N 
+ "2. Pesquisa de consumo\n\tcee <numeroCliente> [mês e ano referente]\n\tExemplos:\n\t\tcee 8005243542\n\t\tcee 8005243542 set/2019"  + SBARRA_N  + SBARRA_N 
+ "3. Exibir histórico de consumo\n\tcee <numeroCliente> <mesAnoIncial> <mesAnoFinal>"  + SBARRA_N  + SBARRA_N 
+ "4. Cálculo de consumo de energia\n\tcee <numeroCliente> <mesAno> <arquivo>"  + SBARRA_N  + SBARRA_N 


+ "Mais informações em: https://github.com/RamonGiovane/ConsumoEnergetico"  + SBARRA_N ;

#endif // !CONSTANTES_H
