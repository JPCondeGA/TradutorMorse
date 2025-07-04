# Tradutor Morse
## Introdução 
Projeto realizada para a disciplina de Eletrônica para Computação no ICMC, USP São Carlos. O projeto consiste em um tradutor de Código Morse utilizando o Arduino Nano, equipado com push-buttons e display LCD. A ideia é mostrar no display o que é escrito pelo usuário, em Código Morse, com os botões, sendo um botão o ponto, outro barra e outro enter. O projeto, além de contribuir para o desenvolvimento dos integrantes do grupo, pode ser usado como base para um sistema de comunicação a distância por Código Morse, se utilizado algum equipamento emissor e receptor de sinais.

## Explicação dos Componentes e do Projeto 

### Arduino Nano 
Como as outras versões é um microcontrolador, equipado por um microprocessador, memória e pinos binário e PWM , isto é, pinos que entregam 5 ou 0 V e pinos que entregam entre 0 e 255 a depender da duração do ciclo da onda. Como o próprio nome diz, o Nano tem um tamanho menor, porém a mesma quantidade de pinos que o UNO (que foi utilizado no simulador TinkerCAD). Normalmente, ele é usado sendo encaixado na placa, por causa do seu tamanho, mas preferimos deixar ele fora, utilizando jumpers para conectar os componentes.

Além disso, é importante reassaltar que o arduino disponibiliza uma tensão de 5V e um ground, quando alimentado, geralmente pelo seu cabo USB. Essa tensão foi utilizada para ligar o display e outros componentes.

### Display LCD
Componente que é um tipo de tela capaz de mostrar caracteres literais e gráficos, por meio de uma tecnologia baseada em controle de criastal líquido por meio de campos magnéticos. Quando um campo elétrico é aplicado em um fio, o cristal se alinha, bloqueando a luz. Por meio dessa interrupção ou não de luz que o LCD forma os caracteres. Para controlar essa tecnologia, ele possui dentro de si um circuito controlador, quase como um microcontrolador. Ele possui diversos pinos, dentren os quais estão:

* VDD: onde se liga a fonte de tensão (o 5V do Arduino);
* VSS: onde se liga o terra;
* V0: controla o contraste do fundo com os caracteres impressos;
* RS: indica se o que ele está recebendo é um comando ou um dado;
* RW: controle se a operação a ser feita é leitura ou escrita (normalmente conectado ao terra, permitindo somente leitura);
* D0-D7: entrada para dados (conectado aos pinos do Arduino, o qual enviará os dados);
* E: quando tem valor lógico 1, faz com que os dados sejam lidos;
* A: VCC do LED (luz de fundo do display);
* K: terra do LED

OBS: no nosso circuito, utilizou-se somente do D4 a D7

Por ser um componente muito complexo, o Arduino possui diversas bibliotecas para trabalhar com ele. A mais comum, a qual utilizamos, foi a LiquidCrystal.h, que, ao conectar os pinos corretos no display, abstrai bastannte o uso dele por meio da classe lcd. Através de um objeto dessa classe, podemos executar o método print, por exemplo, que mostra algo no display, sem nos preocupar com a complexidade dessa operação.
Por fim, no nosso circuito, foi utilizado um de 2 linhas com 16 caracteres cada (16x2) e ele tem o papel de mostrar a mensagem escrita pelo usuário na primeira linha e o carctere que está sendo escrito, junto de seu Código Morse, na segunda linha.

### Potenciômetro
Componente que bifurca a corrente em dois caminhos, com um deles tendo resistência ajustável. No nosso circuito, tem a serventia de ajustar o contraste do LCD, estando então conectado ao VCC, terra e ao V0 do display.

### Push Button
Push-button é um tipo de botão que quando pressionado fecha uma chave que conecta dois fios. Normalmente, ele possui quatro pernas, sendo duas conectadas por um fio e outras duas conectadas por outro fio. Quando é pressionado, como chave, conecta-se esses fios. É importante então saber qual são as pernas que estão conectadas para conectá-lo ao circuito corretamente. Isso é possível ver pelo formato dessas pernas que são entortadas: as que apontam uma para outra são conectas por um fio. 

![image](https://github.com/user-attachments/assets/90e00807-b3ca-41b0-a1f4-3fd3aed35171)

Um problema comum com esse tipo de botão é o da flutuação. Imagine o seguinte caso: um botão está conectado a um pino de entrada do arduino e ao terra (nos fios separados); ao apertamos conectamos o terra ao pino e ele recebe o valor lógico 0, porém quando pararmos de pressionar, o pino será desconectado do terra e não conectado a nenhuma outra fonte, ou seja, o pino não tem uma tensão exata: não é 0 V que viria do terra e nem 5 V que viria da fonte. Desse modo, é necessário fazer um circuito chamado de pull-up, o qual tem a função de fazer o botão ter nível lógico 1 sempre que não estiver pressionado. Esse circuito é simples e é construído colocando um resistor que conecta uma fonte de tensão e a entrada (como abaixo). 

![image](https://github.com/user-attachments/assets/e0df0783-d650-4b69-b470-2790b84f0d59)

Fonte: _https://blog.eletrogate.com/entendendo-os-resistores-de-pull-up-e-pull-down/_

Porém, o Arduino tem um circuito interno de pull-up para cada pino e para utilizá-lo, declaramos o pino do botão como entrada com pull-up (button é uma variável inteira que guarda o valor do pino em que estpa conectado o botão):

    PIN_MODE(button, INPUT_PULLUP)

No projeto, foi utilizado o pull-up interno para tratar esse erro e foi utilzado três desses componentes para as funções: o da esquerda para "." e  o do meio para "_" (caracteres do Código Morse), além do mais a direita para o enter. O enter tem a função que quando a código está correto, junta o caractere escrito em código a mensagem maior no display. Além disso, quando o enter é pressionado por mais tempo, ele tem a função de dar um espaço na mensagem maior do display. Se pressionado por mais tempo ainda, limpará o display.

### LED RGB
LED RGB é um componente composto por três diodo capaz de emitir luz, ou seja, três LED. Cada um dos LED's que os compõe possuem cores diferentes: um vermelho, um verde e um azul. Pelas entradas PWM, conseguimos controlar a intensidades dos LED's. Através da mistura das cores, podemos obter quase qualquer cor visível. Por causa disso, o LED RGB possui quatro pernas: uma corresponde ao LED azul, outra ao LED vermelho, outra ao LED verde e outra para o cátodo comum (terra comum) ou o ânodo comum (alimentação comum). O LED RGB que foi colocado no circuito real é o que possui o ânodo comum como quarta perna.

![image](https://github.com/user-attachments/assets/617cdddf-a7bc-4b91-b898-5d9593f28cb3)

Fonte: _https://www.squids.com.br/arduino/software/dicas-de-software/372-led-rgb-anodo-comum-ou-o-led-rgb-catodo-comum-como-identificar-e-usar-com-arduino-cirucito-e-programacao_

O componente no sistema, inicialmente desligado, foi utilizado como indicador do tempo de pressão no botão enter: se o botão de enter foi pressionado o bastante para dar espaço, ele acende na cor verde; se já foi o bastante para limpar o display, desliga novamente.

### Resistores
Componentes capazes de segurar uma parte da tensão no circuito. No nosso projeto, foi utilizado dois resistores para diminuirem a corrente que passa pelo LED RGB e pelo LED do display LCD. O valor deles foi o necessário para que os LED's não tivessem perigo de queimar, o que acontece quando passa cerca de 20 mA por ele. Desse modo, cada um tem 820 Ohms e sendo 5 V a tensão do circuito por causa do Arduino, temos:

     I = 5/820 ~ 0,006 = 6 mA

## Tabela de Preços
|Componente|Quantidade|Preço|
|----------|----------|-----|
|Display LCD 16x2| 1 | R$ 16,06|
|Potenciômetro| 1 | R$ 7,00|
|Push-Button| 3 | R$ 0,14 * 3 = R$ 0,42| 
|LED RGB| 1 | R$ 4,20|
|Resistores 820R| 2 | R$ 0,07 * 2 = R$ 0,14|
|Protoboard 2 Barras| 1 | R$ 39,10|

## Projeto no Simulador TinkerCAD

![image](https://github.com/user-attachments/assets/ef566b66-fe91-4bcc-ada6-772350ca9a9c)

Link: https://www.tinkercad.com/things/90cZz3m95gR-tradutor-de-codigo-morse?sharecode=CViDSfkRNpLXkHRXYo7c-WaEDS6KajbH5TMtToBj50I

## Fotos do Projeto

![image](https://github.com/user-attachments/assets/60d32ecf-7dce-454b-9904-04ece526d313)

![image](https://github.com/user-attachments/assets/8fbb5770-b85d-48cb-8787-edba4a285c43)


## Grupo

* Antonio Carlos Madalozzo Gonzaga
* Danilo de Oliveira Lopes
* Joao Pedro Conde Gomes Alves
* Eduardo Benedini Bueno
