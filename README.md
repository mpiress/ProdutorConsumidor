# Produtor vs Consumidor


<div style="display: inline-block;">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Maintained%3F-yes-green.svg"/> 
<img align="center" height="20px" width="60px" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/> 
<img align="center" height="20px" width="80px" src="https://img.shields.io/badge/Made%20for-VSCode-1f425f.svg"/> 
<a href="https://github.com/mpiress/midpy/issues">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat"/>
<img align="center" height="20px" width="80px" src="https://badgen.net/badge/license/MIT/green"/>
</a> 
</div>

<p> </p>
<p> </p>

<p align="justify">
Tratamos neste repositório um problema classico em sistemas operacionais, a <b>exclusão mútua</b>. Segundo a <i>lei de Amdahl</i>, muitos problemas, embora se apresentem possíveis de paralelismo, há partes de um problema computacional que devem ser executados de forma sequêncial. Este é o caso que se enquadra o conceito de <i>exclusão mútua</i>, um problema que reporta como regra que duas ou mais threads não devem acessar uma região importânte ao mesmo tempo, essa região é chamada de <b>região crítica</b>. Em caso de acesso mútuo na <i>região crítica</i> por múltiplas threads, resultados inesperados vão ocorrer, invalidando a execução correta do problema abordado. Para detalhar os problemas por traz desses conceitos, utilizamos como exemplo um modelo didático conhecido como Produtor vs Consumidor. Nesse modelo, considera-se um espaço de buffer compartilhado entre as múltiplas threads em execução em que threads produtoras têm por objetivo introduzir items e incrementar um contador de itens produzidos e consumidores os subtraem do buffer e decrementam a variável de controle para posicionamento do índice da próxima posição vaga, tudo isso em um ciclo infinito de execução, i.e., <b> while(TRUE)</b>.   
</p>

<p align="justify">
Primeiro, consideramos um universo perfeito, em que dois produtores e dois consumidores são executados por quatro threads. Consideramos, que se inicializamos os produtores primeiro tudo deverá funcionar corretamente, uma vez que, ao posicionar os consumidores no buffer, esse já terá itens consumíveis e a variável de controle já estará incrementada algumas vezes. Observe para isso o exemplo 1, pasta <b>prodcom1</b>. Nela, inicializamos no main as múltiplas threads, parte para tratar a função produtor outras para lidar com o consumo. Nesse exemplo, as funções são diretas, passamos para as threads a área compartilhada, ou seja, buffer e variável de índice para controle. Logo, todas atuam diretamente nesse espaço para produção e consumo. Note que ao executar, nem sempre os produtores são inicializados primeiro, por quê?. Além disso, o ciclo de produção e consumo é totalmente desordenado, virando um caos ao decorrer das interações entre buffer e variável de indexação. 
</p>

<p align="justify">
O exemplo produzido na pasta <b>prodcom1</b>, detalha exatamente o problema que enfrentamos quando múltiplas threads ou processos precisam de um recurso em particular e esse é limitado em relação ao número de requerentes. Logo, ao executar o programa há uma ação de todos os processos e threads, chamado <b>condição de corrida</b>. Resumidamente, a condição de corrida nos diz que quem chega na frente atua sob os dados e isso para o controle de <i>região crítica</i> não é interessante. Fato que nos conduz a primeira tentativa de correção, a solução apresentada na pasta <b>prodcom2</b>. 
</p>

<p align="justify">
Como o problema acima apresentado é gerado pela condição de corrida sob uma regição crítica, espera-se que ao tratar essa região o problema desapareça. Então, no exemplo 2 (i.e., prodcom2) é implementado um conceito popular em sistemas operacionais, chamado Mutex (i.e., Mutual Exclusion). A idéia por traz do Mutex é prover uma TAD que consiga <i>"travar"</i> as threads, controlando o acesso da região crítica permitindo que apenas uma de cada vez tenha esse acesso. Para isso, pense em uma variável booleana em que true significa caminho livre e false espere por liberação. Nesse conceito, espera-se que a thread que receber primeiro o acesso irá faze-lo e logo em seguida vai liberar a trava para que outra consiga utilizar a região dada como crítica. Utilizando a biblioteca <b>pthreads.h</b>, é possível introduzir o Mutex, criando-se uma variável do tipo <b>pthread_mutex_t</b>. Essa, por sua vez, deve ser coordenada nas chamadas de função <b>pthread_mutex_lock</b> e <b>pthread_mutex_unlock</b>, ambas disponíveis como parte da <i>pthread.h</i>. Observe o exemplo 2 para melhor compreensão.  
</p>

<p align="justify">
Uma vez controlada a região crítica, tudo deve funcionar, não é. Porêm ao executar a aplicação exemplos é possível notar que há erros de realização de buffer ainda, por quê?.
</p>

<p align="justify">
Embora a exclusão mútua tenha sido de fato resolvida, a falta de sincronismo entre as threads ainda afeta o resultado, uma vez que, ambas ainda operam sob um contexto ilimitado de produção e consumo. Para resolver esse problema e manter uma consistência de execução, é introduzido no exemplo 3 (i.e., prodcom3) um conceito chamado <b>semáforo</b>. Os semáforos têm por objetivo prover sincronismo entre as múltipas threads. Para isso, variáveis de controle de máximo e mínimo permitido são implementadas e essas controladas por uma biblioteca chamada <b>semaphore.h</b>. Adotando o problema do Produtor e Consumidor como alvo, criamos duas novas variáveis dentro da <i>struct</i> compartilhada, ambas do tipo <b>sem_t</b>. Essas, por sua vez, são coordenadas pelas chamadas de função <b>sem_wait</b> e <b>sem_post</b>. A função <b>sem_wait</b> tem o objetivo de parar as threads de uma dada variável quando essa chegar em um dado limite pré-definido, o qual é inicializado pela função <b>sem_init</b>. Logo, assim que uma ou mais threads atingem esse limiar, essas ficam em estado de bloqueadas até que algo modifique a variável, o que as tira do estado atual e as insere como prontas novamente. Já em <b>sem_post</b>, a ação de subtrair é realizada, tornando o controle da variável alvo baseada em regras, por exemplo, de cheio e vazio. Então, se o buffer encher, os produtores param de produzir. Pelo contrário, se o buffer se encontrar vazio, os consumidores é que param de consumir. Ambos ficam parados até que uma thread contrária a sua ação execute uma operação que modifique tal valor e acorde as threads do tipo oposto.   
</p>

# Compilação e Execução

Os exemplos disponibilizados possuem um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |


# Contatos

<div style="display: inline-block;">
<a href="https://t.me/michelpires369">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
</a>

<a href="https://www.linkedin.com/in/michelpiressilva/">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"/>
</a>

</div>

<p> </p>


<a style="color:black" href="mailto:michel@cefetmg.br?subject=[GitHub]%20Source%20Dynamic%20Lists">
✉️ <i>michel@cefetmg.br</i>
</a>


