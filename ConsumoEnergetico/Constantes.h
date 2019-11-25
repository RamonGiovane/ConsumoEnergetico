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
const char TRECHO_BANDEIRA_AMARELA[] = "Band. Amarela - ";
const char LINHA_BANDEIRA_AMARELA[] = "Bandeira Amarela";
const char LINHA_BANDEIRA_VERMELHA[] = "Bandeira Vermelha";
const char LINHA_HISTORICO_CONSUMO[] = "Hist�rico de Consumo";
const char LINHA_ENERGIA[] = "Energia El�trica";
const char LINHA_ILUMINACAO[] = "Contrib Ilum Publica Municipal";
const char LINHA_HISTORICO[] = "Hist�rico ";

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
const char MSGE_HISTORICO_NAO_ENCONTRADO[] = "\nFALHA: Dados de hist�rico de consumo n�o encontrados. ";
const char MSGE_HISTORICO_INCONSISTENTE[] = "\nFALHA: Dados de hist�rico de consumo inconsistentes. ";
const char MSGE_NUMEROS_NAO_ENCONTRADOS[] = "\nFALHA: N�o foi poss�vel computar o n�mero do cliente e/ou da instala��o";
const char MSGE_DATA_E_VALOR_NAO_ENCONTRADO[] = "\nFALHA: Dados da fatura incompletos. Data de vencimento e valor a pagar n�o encontrados.\nProvavelmente o arquivo est� corrompido";
const char MSGE_SINTAXE_INVALIDA[] = "FALHA: Sintaxe inv�lida na linha ";
const char MSGE_VALORES_FATURADOS[] = "\nFALHA: N�o foi poss�vel computar os valores faturados.";
const char MSGE_ARQUIVO_ENTRADA[] = "FALHA: O arquivo de entrada n�o p�de ser lido pois est� corrompido ou vazio.";
const char MSGE_ARQUIVO_NAO_LIDO[] = "\nFALHA: O arquivo n�o p�de ser lido. Provavelmente n�o � um arquivo PDF ou n�o existe.";
const char MSGE_ARQUIVO_CORROMPIDO[] = "\nFALHA: O conte�do da fatura n�o p�de ser lido. Possivelmente o arquivo est� corrompido.";
const string MSGE_MISSING_XPDF = "\nDepend�ncia n�o encontrada:\n\t" 
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
const string VAZIO = "";
const char ESPACO = ' ';
const char BARRA = '/';
const char SEPARTOR[] = " | ";

//Casa com um m�s e ano referente no formato: "NOV/2019"
const char REGEX_MES_REFERENTE[] = "[A-Z]{3}[/]\\d{4}";

//Casa com as datas de leitura que estejam no formato: "MM/yy MM/yy MM/yy" que estejam precedidas ou n�o por espa�os em branco
const char REGEX_DATAS_LEITURA[] = "\\s*\\d{2}[/]\\d{2}\\s*\\d{2}[/]\\d{2}\\s*\\d{2}[/]\\d{2}";

//Casa com a data de vencimento e o valor a pagar que estejam no formato "22/12/2019 R$ 199,00"
const char REGEX_DATA_E_VALOR[] = "\\.*\\d{2}[/]\\d{2}[/]\\d{4}.*\\d{1,9}[,]\\d{2}";

//Casa com n�mero do cliente e da instala��o, cada um de 5 a 11 n�meros entre espa�o
const char REGEX_CLIENTE_INSTALACAO[] = "\\d{5,11}\\s*\\d{5,11}";

//Casa com um string que comece com uma letra mai�scula (correspondente a um nome) ou com um CEP
const char REGEX_CEP_E_NOMES[] = "(^[A-Z]+)|(^\\d{5}[-]\\d{3})";

//Casa com um m�s e ano do hist�rico de consumo no formato: "NOV/19";
const char REGEX_DATA_HISTORICO[] = "[A-Z]{3}[/]\\d{2}";



const int TAMANHO_HISTORICO = 13;


//Informa��es de do programa e ajuda
const string PROG_INFO = "CEE vers�o 0.1: Relat�rio de Consumo de Energia El�trica"  + SBARRA_N 
+ "2019 Ramon Giovane https://github.com/RamonGiovane"  + SBARRA_N 


+ "uso:\n1. Importando uma fatura ou v�rias faturas da CEMIG\n\tcee <fatura> | <diret�rio> "  + SBARRA_N  + SBARRA_N 
+ "2. Pesquisa de consumo\n\tcee <numeroCliente> [m�s e ano referente]\n\tExemplos:\n\t\tcee 8005243542\n\t\tcee 8005243542 set/2019"  + SBARRA_N  + SBARRA_N 
+ "3. Exibir hist�rico de consumo\n\tcee <numeroCliente> <mesAnoIncial> <mesAnoFinal>"  + SBARRA_N  + SBARRA_N 
+ "4. C�lculo de consumo de energia\n\tcee <numeroCliente> <mesAno> <arquivo>"  + SBARRA_N  + SBARRA_N 


+ "Mais informa��es em: https://github.com/RamonGiovane/ConsumoEnergetico"  + SBARRA_N ;

#endif // !CONSTANTES_H
