#ifndef CONSTANTES_H
#define CONSTANTES_H
#include <string>
using namespace std;

//Meses abreviados
const string MESES_ABREVIADOS[] = {"", "jan", "fev", "mar", "abr", "mai", "jun", "jul", "ago", "set", "out", "nov", "dez" };
const string MESES_STR[] = {"", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro" };

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
//Diretório
const char DIR_DATA[] = "data";
const char DIR_FATURAS[] = "faturas\\";

//Caminho de programa
const char PATH_XPDF[] = "pdftotext.exe";

//Trecho de linha do arquivo texto das faturas
const char STR_N_DO_CLIENTE[] = "Nº DO CLIENTE";
const char LINHA_BANDEIRA_AMARELA[] = "Bandeira Amarela";
const char LINHA_BANDEIRA_VERMELHA[] = "Bandeira Vermelha";
const char LINHA_HISTORICO_CONSUMO[] = "Histórico de Consumo";
const char LINHA_ENERGIA[] = "Energia Elétrica";
const char LINHA_ILUMINACAO[] = "Contrib Ilum Publica Municipal";
const char LINHA_HISTORICO[] = "Histórico ";

//Mensagem a ser exibidada ao usuário
const char MSG_DATA_INVALIDA[] ="\nParâmetro de data inválido.\n";
const char MSG_DADOS_NAO_ENCONTRADOS[] = "\nNenhum dado foi econtrado para os termos pesquisados.\n";
const char MSG_ARQUIVO_LIDO[] = " arquivo lido com sucesso.";
const char MSG_ARQUIVOS_LIDOS[] = " arquivos lidos com sucesso.";
const char MSG_ARQUIVO_IGNORADO[] = " arquivo com falha ignorado.";
const char MSG_ARQUIVOS_IGNORADOS[] = " arquivos com falha ignorados.";
const char MSG_CONVERTENDO_PDF[] = "\nConvertendo PDF... ";
const char MSG_LENDO_FATURA[] = "\nLendo a fatura digital em texto... ";
const char MSG_OBTENDO_INFO[] = "\nObtendo informações da fatura... ";
const char MSG_FIM_LEITURA[] = "\n\nA leitura terminou.\n";
const char MSG_LENDO[] = "\nLendo ";
const char MSG_IGNORANDO_ARQUIVO[] = "\nIgnorando arquivo...\n\n";
const char MSG_ARQUIVO_IMPORTADO[] = "\nArquivo lido e importado com sucesso...\n\n";
const char MSG_CLIENTE_NAO_LOCALIZADO[] = "\nCliente não localizado.\n";
const char MSG_FATURA_JA_EXISTE[] = "AVISO: Esta fatura já foi importada anteriormente.";
const char MSG_ARQ_TEXTO_FALHOU[] = "\nAVISO: Não foi possível guardar uma cópia do arquivo texto desta fatura.\nA conversão do PDF para texto falhou.";
const char MSG_ARQ_TEXTO_SALVO[] = "\nA fatura foi salva como texto em\n\t";

//Mensagem de erro a ser exibidada ao usuário
const char MSGE_HISTORICO_NAO_ENCONTRADO[] = "\nFALHA: Dados de histórico de consumo não encontrados. ";
const char MSGE_HISTORICO_INCONSISTENTE[] = "\nFALHA: Dados de histórico de consumo inconsistentes. ";
const char MSGE_NUMEROS_NAO_ENCONTRADOS[] = "\nFALHA: Não foi possível computar o número do cliente e/ou da instalação";
const char MSGE_DATA_E_VALOR_NAO_ENCONTRADO[] = "\nFALHA: Dados da fatura incompletos. Data de vencimento e valor a pagar não encontrados.\nProvavelmente o arquivo está corrompido";
const char MSGE_SINTAXE_INVALIDA[] = "FALHA: Sintaxe inválida na linha ";
const char MSGE_VALORES_FATURADOS[] = "\nFALHA: Não foi possível computar os valores faturados.";
const char MSGE_ARQUIVO_ENTRADA[] = "FALHA: O arquivo de entrada não pôde ser lido pois está corrompido ou vazio.";
const char MSGE_ARQUIVO_NAO_LIDO[] = "\nFALHA: O arquivo não pôde ser lido nem guardado como texto. Provavelmente não é um arquivo PDF ou não existe.";
const char MSGE_ARQUIVO_CORROMPIDO[] = "Provavelmente o arquivo PDF está corrompido.";
const char MSGE_FATURA_INVALIDA[] = "\nFALHA: O arquivo fornecido não corresponde a uma fatura CEMIG.";
const string MSGE_DADOS_INCOMPLETOS_CLIENTE = "\nFALHA: Dados do cliente inconsistentes." + string(MSGE_ARQUIVO_CORROMPIDO);
const char MSGE_DATAS_LEITURA[] = "FALHA:\n Não foi possível computar as datas de leitura";


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
const char SEM_DADOS_INPUT_FILE[] = "\nNão há dados de consumo deste cliente para o mês/ano fornecidos no arquivo de entrada: ";
const char SEM_DADOS_INPUT_SINTAX[] = "\nNão há dados de consumo deste cliente para o mês/ano fornecidos nos parâmetros de entrada do programa: ";
const char STR_CONSUMO_MENSAL[] = "\n\t  Consumo mensal: ";
const char STR_CONSUMO_DIARIO[] = "\n\t  Consumo médio diário: ";
const char STR_VALOR_CONSUMO[] = "\n\t  Valor do consumo elétrico: ";
const char STR_NUMERO_DIAS[] = "\n\t  Número de dias: ";
const char STR_DADOS_FATURA_EM[] = "\n  >> Dados da fatura Cemig em ";
const char STR_DADOS_CALCULADOS[] = "\n  >> Dados calculados para ";
const char STR_SEM_DADOS[] = "\n\t--- Sem dados de faturas para exibir para esta instalação neste mês/ano ---\n";
const char STR_ARQUIVOS_FALHARAM[] = "\nOs seguintes arquivos falharam durante a leitura: ";
const char PRECO_ENERGIA_INDISPONIVEL[] = "Dados de preço de energia indisponíveis para este mês/ano e instalação.";
const char RS[] = "R$ ";

//Constantes de strings e chars utilitários
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


//Parâmetro para visualizar ajuda do programa
const char HELP_COM1[] = "/h";
const char HELP_COM2[] = "--help";

//Tipo de arquivo em que a fatura se encontra
const int TIPO_PDF = 0;
const int TIPO_TEXTO = 1;

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

//Casa com uma linha de consumo do histórico de consumo, podendo ter ou não o mês e ano referentes.
const char REGEX_LINHA_HISTORICO[] = "([A-Z]{3}[/]\\d{2})?\\s+\\d{1,4}\\s+\\d{1,3}[,]\\d{2}\\s+\\d{1,2}";



const int TAMANHO_HISTORICO = 13;
const int SIZE_STR = 1200;


//Informações do programa e ajuda
const string NO_PARAM_INFO = "\nO programa foi iniciado sem parâmetros. Logo, fará importações de faturas do diretório atual.\n" + string(ITEM_LINHA) +
" Pressione ENTER para aceitar ou CTRL+C para cancelar." +
"\n\nPara mais informações re-execute o programa utilizando o parâmetro /h ou --help.\n";

const string PROG_INFO = "CEE versão 0.1: Relatório de Consumo de Energia Elétrica"  + SBARRA_N 
+ "2019 Ramon Giovane https://github.com/RamonGiovane"  + SBARRA_N 


+ "uso:\n1. Importando uma fatura ou várias faturas da CEMIG\n\tcee <fatura> | <diretório> "  +
	"\n\tNo momento da importação, se o arquivo for um PDF válido, uma cópia em TXT será guardada no\n\tdiretório \"faturas\" para outra tentativa de importação em caso de falha."
	+ "\n\tPara importar uma fatura de um arquivo texto, use o parâmetro /i.\n\tEsse método não suporta o uso de diretórios." + SBARRA_N  + SBARRA_N 
+ "2. Pesquisa de consumo\n\tcee <numeroCliente> [mês e ano referente]\n\tExemplos:\n\t\tcee 8005243542\n\t\tcee 8005243542 set/2019"  + SBARRA_N  + SBARRA_N 
+ "3. Exibir histórico de consumo\n\tcee <numeroCliente> <mesAnoIncial> <mesAnoFinal>"  + SBARRA_N  + SBARRA_N 
+ "4. Cálculo de consumo de energia\n\tcee <numeroCliente> <mesAno> <arquivo TXT com consumos>"  + SBARRA_N  + SBARRA_N 


+ "Mais informações em: https://github.com/RamonGiovane/ConsumoEnergetico"  + SBARRA_N ;

#endif // !CONSTANTES_H
