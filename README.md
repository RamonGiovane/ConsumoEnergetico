# ConsumoEnergetico
Programa que realiza o cálculo de gastos de energia elétrica e exibe históricos e dados de consumos a partir do PDF de  faturas digitais da CEMIG

CEE versão 0.1: Relatório de Consumo de Energia Elétrica
2019 Ramon Giovane 
uso:
1. Importando uma fatura ou várias faturas da CEMIG
        cee <fatura> | <diretório>
        No momento da importação, se o arquivo for um PDF válido, uma cópia em TXT será guardada no
        diretório "faturas" para outra tentativa de importação em caso de falha.
        Para importar uma fatura de um arquivo texto, use o parâmetro /i.
        Esse método não suporta o uso de diretórios.

2. Pesquisa de consumo
        cee <numeroCliente> [mês e ano referente]
        Exemplos:
                cee 8005243542
                cee 8005243542 set/2019

3. Exibir histórico de consumo
        cee <numeroCliente> <mesAnoIncial> <mesAnoFinal>

4. Cálculo de consumo de energia
        cee <numeroCliente> <mesAno> <arquivo TXT com consumos>
        Esta função permite que o usuário forneça a potência elétrica e as horas de funcionamento
        diário ou o consumo mensal de quilowatt-hora de qualquer aparelho elétrico, via um arquivo
        texto, e calcula o consumo de energia elétrica total em um mês para verificar se esse consumo é
        semelhante ao informado na fatura da Cemig. O arquivo texto deve listar em cada linha os valores
        para cada aparelho. Veja o exemplo abaixo, observe que para dois aparelhos (ar-condicionado e
        geladeira) foi fornecido apenas o consumo mensal e para o chuveiro a potência elétrica em watts
        e o número de horas de utilização no mês. A quantidade de aparelhos é definido pelo usuário. A
        primeira linha do arquivo deve ser um comentário iniciado com o caractere # seguido pelas
        palavras Consumo de mmm/aaaa, onde mmm/aaaa informa o mês e ano dos dados de consumo de
        cada aparelho.

        # Consumo de jul/2019
        Chuveiro 5500 w 15 h
        Ar-condicionado 186 kWh
        Geladeira 67,4 kWh
        
