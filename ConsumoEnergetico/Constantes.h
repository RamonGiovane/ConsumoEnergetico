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

//Diret�rio
const char DIR_DATA[] = "data";

//Caminho de programa
const char PATH_XPDF[] = "xpdf\\pdftotext.exe";

//Trecho de linha do arquivo texto das faturas
const char LINHA_BANDEIRA_AMARELA[] = "Band. Amarela - ";
const char LINHA_HISTORICO_CONSUMO[] = "Hist�rico de Consumo";

//Mensagem a ser exibidada ao usu�rio
const char MSG_DATA_INVALIDA[] ="\nPar�metro de data inv�lido.\n";
const char MSG_DADOS_NAO_ENCONTRADOS[] = "\nNenhum dado de consumo foi encontrado para os termos pesquisados.\n";
const char MSG_ARQUIVO_LIDO[] = " arquivo lido com sucesso.";
const char MSG_ARQUIVOS_LIDOS[] = " arquivos lidos com sucesso.";
const char MSG_ARQUIVO_IGNORADO[] = " arquivo com falha ignorado.";
const char MSG_ARQUIVOS_IGNORADOS[] = " arquivos com falha ignorados.";
const char MSG_CONVERTENDO_PDF[] = "\nConvertendo PDF... ";
const char MSG_LENDO_FATURA[] = "\nLendo a fatura digital... ";
const char MSG_OBTENDO_INFO[] = "\nObtendo informa��es da fatura... ";
const char MSG_FIM_LEITURA[] = "\n\nA leitura terminou.\n";
const char MSG_LENDO[] = "\nLendo ";
const char MSG_IGNORANDO_ARQUIVO[] = "\nIgnorando arquivo...\n\n";
const char MSG_ARQUIVO_IMPORTADO[] = "\nArquivo lido e importado com sucesso...\n\n";
const char MSG_CLIENTE_NAO_LOCALIZADO[] = "\nCliente n�o localizado.\n";
const char MSG_FATURA_JA_EXISTE[] = "AVISO: Esta fatura j� foi importada anteriormente.";

//Mensagem de erro a ser exibidada ao usu�rio
const char MSG_SINTAXE_INVALIDA[] = "FALHA: Sintaxe inv�lida na linha ";
const char MSG_ERRO_ARQUIVO_ENTRADA[] = "FALHA: O arquivo de entrada n�o p�de ser lido pois est� corrompido ou vazio.";
const char MSG_ERRO_ARQUIVO_NAO_LIDO[] = "\nFALHA: O arquivo n�o p�de ser lido. Provavelmente n�o � um arquivo PDF ou n�o existe.";
const char MSG_ERRO_ARQUIVO_CORROMPIDO[] = "\nFALHA: O conte�do da fatura n�o p�de ser lido. Possivelmente o arquivo est� corrompido.";
const string MSG_ERRO_MISSING_XPDF = "\nDepend�ncia n�o encontrada:\n\t" 
										"> O arquivo " + string(PATH_XPDF) + " n�o p�de ser localizado.\n\nO programa n�o pode prosseguir.\n";

//Peda�os de string necess�rios para construir uma mensagem ao usu�rio
const char TITLE_HISTORICO[] = "\n|| Hist�rico de consumo de ";
const char TITLE_PESQUISANDO_CLIENTE[] = "|| Pesquisando dados do cliente:";
const char STR_A[] = " a ";
const char STR_D_PERIOD[] = ": ";
const char STR_KWH[] = " kWh";
const char SUBTITLE_HISTORICO[] = " M�S/ANO  CONSUMO  \tM�DIA DI�RIA\n";
const char SUBTITLE_INSTALACAO[] = "\n\n| Instala��o N� ";
const char STR_CONSUMO_INSTALACAO[] = "Consumo da Instala��o N� ";
const char STR_VALOR_A_PAGAR[] = "Valor a pagar: R$ ";
const char STR_DATA_VENC[] = " Data de Vencimento: ";
const char STR_REFERENTE[] = "Referente a: ";
const char STR_DE[] = " de ";

//Constantes de strings e chars utilit�rios
const char BARRA_N = '\n';
const string SBARRA_N = "\n";
const char ESPACO = ' ';
const char SEPARTOR[] = " | ";

const string PROG_INFO = "CEE vers�o 0.1: Relat�rio de Consumo de Energia El�trica"  + SBARRA_N 
+ "2019 Ramon Giovane https://github.com/RamonGiovane"  + SBARRA_N 


+ "uso:\n1. Importando uma fatura ou v�rias faturas da CEMIG\n\tcee <fatura> | <diret�rio> "  + SBARRA_N  + SBARRA_N 
+ "2. Pesquisa de consumo\n\tcee <numeroCliente> [m�s e ano referente]\n\tExemplos:\n\t\tcee 8005243542\n\t\tcee 8005243542 set/2019"  + SBARRA_N  + SBARRA_N 
+ "3. Exibir hist�rico de consumo\n\tcee <numeroCliente> <mesAnoIncial> <mesAnoFinal>"  + SBARRA_N  + SBARRA_N 
+ "4. C�lculo de consumo de energia\n\tcee <numeroCliente> <mesAno> <arquivo>"  + SBARRA_N  + SBARRA_N 


+ "Mais informa��es em: https://github.com/RamonGiovane/ConsumoEnergetico"  + SBARRA_N ;

#endif // !CONSTANTES_H
