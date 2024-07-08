# Cálculo de Pi usando Threads
- Instituto Federal de Alagoas - Campus Arapiraca
- Sistemas de Informação, 3º Período.

## Equipe
- Jhully Walkyria
- Joellen Silva
- Josenilton Galdino
- Matheus Ferreira
  
## Relatório de Desempenho: Cálculo de Pi com Diferentes Números de Threads
### Tabela de Resultados:

<img width="709" alt="Captura de Tela 2024-07-08 às 19 30 19" src="https://github.com/joellensilva/calculo-pi/assets/99025532/d80bb3d8-9ec4-4993-92c1-3f9c95f6da9f">

## Análise dos Resultados
### Valor Aproximado de Pi:

Em todas as configurações de threads, o valor aproximado de pi calculado é muito próximo de 3.14159265359, 
indicando que o cálculo é preciso independentemente do número de threads utilizado.

### Tempo Médio de Execução:

O tempo médio de execução diminui significativamente à medida que o número de threads aumenta. Isso é esperado, pois mais threads permitem 
que o trabalho seja distribuído entre múltiplos núcleos de CPU, aumentando a paralelização e, portanto, a eficiência do cálculo.
O tempo médio de execução com 1 thread é aproximadamente 13.864500 segundos, enquanto com 32 threads é reduzido para cerca de 0.546474 segundos,
demonstrando uma melhoria substancial no tempo de execução.

### Desvio Padrão:

O desvio padrão dos tempos de execução é relativamente baixo em todas as configurações, indicando que os tempos de execução 
são consistentes entre os experimentos repetidos.
O desvio padrão varia de 0.204278 segundos com 1 thread a 0.009289 segundos
com 32 threads.

### Coeficiente de Variação:

O coeficiente de variação (CV) é uma medida da dispersão relativa dos tempos de execução em relação à média.
Um CV mais baixo indica menor variabilidade.
Os CVs estão todos abaixo de 2%, com valores variando de 1.45% a 2.01%. Isso mostra que o tempo de execução 
é bastante estável para todas as configurações de threads.

## Diferenças Observadas

### Eficiência de Paralelização:

A eficiência de paralelização melhora significativamente à medida que o número de threads aumenta, evidenciado
pela redução substancial no tempo de execução.
Com 32 threads, o tempo de execução é aproximadamente 25 vezes menor do que com 1 thread, o que reflete a eficiência
da utilização de múltiplos núcleos de CPU.

### Consistência:

A consistência dos tempos de execução é alta em todas as configurações de threads, como indicado pelos baixos desvios padrões 
e coeficientes de variação.Isso sugere que o sistema é eficiente em gerenciar a execução paralela de threads sem introduzir 
grandes variabilidades no tempo de execução.

### Limitações de Paralelização:

Embora o aumento do número de threads reduza significativamente o tempo de execução, há uma diminuição nos ganhos marginais à 
medida que o número de threads se aproxima do número máximo de núcleos de CPU disponíveis.Isso se deve à sobrecarga de gerenciamento 
de threads e à contenção de recursos, que se tornam mais pronunciadas com um maior número de threads.

### Conclusão

O experimento demonstra claramente os benefícios da paralelização no cálculo de pi utilizando a série de Leibniz-Gregory. O uso de
múltiplas threads permite uma redução significativa no tempo de execução, especialmente ao utilizar até 32 threads. No entanto, é 
importante considerar as limitações e a sobrecarga associada ao gerenciamento de um grande número de threads.

