#ifndef CONSTANTES_H
#define CONSTANTES_H
#include <string>
using namespace std;

//Meses abreviados
const string MESES_ABREVIADOS[] = {"", "jan", "fev", "mar", "abr", "mai", "jun", "jul", "ago", "set", "out", "nov", "dez" };
const string MESES_STR[] = {"", "Janeiro", "Fevereiro", "Mar�o", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro" };

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
const static char FILE_DIR_LIST[] = "files.tmp";
const string PONTO_BARRA = ".\\";
const char CEE_EXE[] = "cee.exe";
//Diret�rio
const char DIR_DATA[] = "data";
const char DIR_FATURAS[] = "faturas\\";

//Caminho de programa
const char PATH_XPDF[] = "pdftotext.exe";

//Trecho de linha do arquivo texto das faturas
const char STR_N_DO_CLIENTE[] = "N� DO CLIENTE";
const char LINHA_BANDEIRA_AMARELA[] = "Bandeira Amarela";
const char LINHA_BANDEIRA_VERMELHA[] = "Bandeira Vermelha";
const char LINHA_HISTORICO_CONSUMO[] = "Hist�rico de Consumo";
const char LINHA_ENERGIA[] = "Energia El�trica";
const char LINHA_ILUMINACAO[] = "Contrib Ilum Publica Municipal";
const char LINHA_HISTORICO[] = "Hist�rico ";

//Mensagem a ser exibidada ao usu�rio
const char MSG_DATA_INVALIDA[] ="\nPar�metro de data inv�lido.\n";
const char MSG_DADOS_NAO_ENCONTRADOS[] = "\nNenhum dado foi econtrado para os termos pesquisados.\n";
const char MSG_ARQUIVO_LIDO[] = " arquivo lido com sucesso.";
const char MSG_ARQUIVOS_LIDOS[] = " arquivos lidos com sucesso.";
const char MSG_ARQUIVO_IGNORADO[] = " arquivo com falha ignorado.";
const char MSG_ARQUIVOS_IGNORADOS[] = " arquivos com falha ignorados.";
const char MSG_CONVERTENDO_PDF[] = "\nConvertendo PDF... ";
const char MSG_LENDO_FATURA[] = "\nLendo a fatura digital em texto... ";
const char MSG_OBTENDO_INFO[] = "\nObtendo informa��es da fatura... ";
const char MSG_FIM_LEITURA[] = "\n\nA leitura terminou.\n";
const char MSG_LENDO[] = "\nLendo ";
const char MSG_IGNORANDO_ARQUIVO[] = "\nIgnorando arquivo...\n\n";
const char MSG_ARQUIVO_IMPORTADO[] = "\nArquivo lido e importado com sucesso...\n\n";
const char MSG_CLIENTE_NAO_LOCALIZADO[] = "\nCliente n�o localizado.\n";
const char MSG_FATURA_JA_EXISTE[] = "AVISO: Esta fatura j� foi importada anteriormente.";
const char MSG_ARQ_TEXTO_FALHOU[] = "\nAVISO: N�o foi poss�vel guardar uma c�pia do arquivo texto desta fatura.\nA convers�o do PDF para texto falhou.";
const char MSG_ARQ_TEXTO_SALVO[] = "\nA fatura foi salva como texto em\n\t";

//Mensagem de erro a ser exibidada ao usu�rio
const char MSGE_HISTORICO_NAO_ENCONTRADO[] = "\nFALHA: Dados de hist�rico de consumo n�o encontrados. ";
const char MSGE_HISTORICO_INCONSISTENTE[] = "\nFALHA: Dados de hist�rico de consumo inconsistentes. ";
const char MSGE_NUMEROS_NAO_ENCONTRADOS[] = "\nFALHA: N�o foi poss�vel computar o n�mero do cliente e/ou da instala��o";
const char MSGE_DATA_E_VALOR_NAO_ENCONTRADO[] = "\nFALHA: Dados da fatura incompletos. Data de vencimento e valor a pagar n�o encontrados.\nProvavelmente o arquivo est� corrompido";
const char MSGE_SINTAXE_INVALIDA[] = "FALHA: Sintaxe inv�lida na linha ";
const char MSGE_VALORES_FATURADOS[] = "\nFALHA: N�o foi poss�vel computar os valores faturados.";
const char MSGE_ARQUIVO_ENTRADA[] = "FALHA: O arquivo de entrada n�o p�de ser lido pois est� corrompido ou vazio.";
const char MSGE_ARQUIVO_NAO_LIDO[] = "\nFALHA: O arquivo n�o p�de ser lido nem guardado como texto. Provavelmente n�o � um arquivo PDF ou n�o existe.";
const char MSGE_ARQUIVO_CORROMPIDO[] = "Provavelmente o arquivo PDF est� corrompido.";
const char MSGE_FATURA_INVALIDA[] = "\nFALHA: O arquivo fornecido n�o corresponde a uma fatura CEMIG.";
const string MSGE_DADOS_INCOMPLETOS_CLIENTE = "\nFALHA: Dados do cliente inconsistentes." + string(MSGE_ARQUIVO_CORROMPIDO);
const char MSGE_DATAS_LEITURA[] = "FALHA:\n N�o foi poss�vel computar as datas de leitura";


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
const char SEM_DADOS_INPUT_FILE[] = "\nN�o h� dados de consumo deste cliente para o m�s/ano fornecidos no arquivo de entrada: ";
const char SEM_DADOS_INPUT_SINTAX[] = "\nN�o h� dados de consumo deste cliente para o m�s/ano fornecidos nos par�metros de entrada do programa: ";
const char STR_CONSUMO_MENSAL[] = "\n\t  Consumo mensal: ";
const char STR_CONSUMO_DIARIO[] = "\n\t  Consumo m�dio di�rio: ";
const char STR_VALOR_CONSUMO[] = "\n\t  Valor do consumo el�trico: ";
const char STR_NUMERO_DIAS[] = "\n\t  N�mero de dias: ";
const char STR_DADOS_FATURA_EM[] = "\n  >> Dados da fatura Cemig em ";
const char STR_DADOS_CALCULADOS[] = "\n  >> Dados calculados para ";
const char STR_SEM_DADOS[] = "\n\t--- Sem dados de faturas para exibir para esta instala��o neste m�s/ano ---\n";
const char STR_ARQUIVOS_FALHARAM[] = "\nOs seguintes arquivos falharam durante a leitura: ";
const char PRECO_ENERGIA_INDISPONIVEL[] = "Dados de pre�o de energia indispon�veis para este m�s/ano e instala��o.";
const char RS[] = "R$ ";

//Constantes de strings e chars utilit�rios
const char BARRA_N = '\n';
const string SBARRA_N = "\n";
const string BARRA_I = "/i";
const string VAZIO = "";
const string SNULL = "NULL";
const string HASH_TAG = "#";
const char ESPACO = ' ';
const char BARRA = '/';
const char SEPARTOR[] = " | ";
const char VIRGULA = ',';
const char PONTO = '.';
const char ARRAB = '\\';
const char TXT[] = ".txt";
const char ITEM_LINHA[] = "\n\t >>";
const char KWH[] = "kWh";
const char H[] = "h";
const char W[] = "w";
const char VIRGULA_ESPACO[] = { VIRGULA, ESPACO, '\0' };

//Comando do windows
const char REDIRECTOR[] = " > ";
const char NUL_REDIRECTOR[] = " >nul 2>nul";
const char COM_MKDIR[] = "mkdir ";
const char COM_DIR[] = "dir /b ";
const char COM_CP[] = "copy /y %s %s %s";
const char COM_PDF_TO_TXT[] = "%s%s -table \"%s\" \"%s\"%s";


//Par�metro para visualizar ajuda do programa
const char HELP_COM1[] = "/h";
const char HELP_COM2[] = "--help";

//Tipo de arquivo em que a fatura se encontra
const int TIPO_PDF = 0;
const int TIPO_TEXTO = 1;

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

//Casa com uma linha de consumo do hist�rico de consumo, podendo ter ou n�o o m�s e ano referentes.
const char REGEX_LINHA_HISTORICO[] = "([A-Z]{3}[/]\\d{2})?\\s+\\d{1,4}\\s+\\d{1,3}[,]\\d{2}\\s+\\d{1,2}";



const int TAMANHO_HISTORICO = 13;
const int SIZE_STR = 1200;


//Informa��es do programa e ajuda
const string NO_PARAM_INFO = "\nO programa foi iniciado sem par�metros. Logo, far� importa��es de faturas do diret�rio atual.\n" + string(ITEM_LINHA) +
" Pressione ENTER para aceitar ou CTRL+C para cancelar." +
"\n\nPara mais informa��es re-execute o programa utilizando o par�metro /h ou --help.\n";

const string PROG_INFO = "CEE vers�o 0.1: Relat�rio de Consumo de Energia El�trica"  + SBARRA_N 
+ "2019 Ramon Giovane https://github.com/RamonGiovane"  + SBARRA_N 


+ "uso:\n1. Importando uma fatura ou v�rias faturas da CEMIG\n\tcee <fatura> | <diret�rio> "  +
	"\n\tNo momento da importa��o, se o arquivo for um PDF v�lido, uma c�pia em TXT ser� guardada no\n\tdiret�rio \"faturas\" para outra tentativa de importa��o em caso de falha."
	+ "\n\tPara importar uma fatura de um arquivo texto, use o par�metro /i.\n\tEsse m�todo n�o suporta o uso de diret�rios." + SBARRA_N  + SBARRA_N 
+ "2. Pesquisa de consumo\n\tcee <numeroCliente> [m�s e ano referente]\n\tExemplos:\n\t\tcee 8005243542\n\t\tcee 8005243542 set/2019"  + SBARRA_N  + SBARRA_N 
+ "3. Exibir hist�rico de consumo\n\tcee <numeroCliente> <mesAnoIncial> <mesAnoFinal>"  + SBARRA_N  + SBARRA_N 
+ "4. C�lculo de consumo de energia\n\tcee <numeroCliente> <mesAno> <arquivo TXT com consumos>"  + SBARRA_N  + SBARRA_N 


+ "Mais informa��es em: https://github.com/RamonGiovane/ConsumoEnergetico"  + SBARRA_N ;

#endif // !CONSTANTES_H
