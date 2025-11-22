Global Solution 2025 — Edge Computing
Monitoramento Cardíaco IoT com ESP32, MQTT e Node-RED

Integrantes

Bruna Sadi Duarte – RM 561870

Bernardo Moreira – RM 564103

Sara Marangon – RM 563807

LINK WOKWI:  https://wokwi.com/projects/448181298319875073

->Introdução
Este projeto foi desenvolvido para a Global Solution 2025 sobre Edge Computing. As tecnologias emergentes como IoT, automação, sensores inteligentes e Edge Computing influenciam diretamente o futuro do trabalho. A proposta da atividade é construir uma solução tecnológica que contribua com a saúde, produtividade e segurança de profissionais.

->Problema
Profissionais em ambientes corporativos, remotos ou híbridos estão expostos a estresse, fadiga e picos de batimentos cardíacos devido a longas jornadas e pressões constantes. Sem monitoramento, riscos podem passar despercebidos, prejudicando a saúde e o desempenho.

->Solução
O projeto consiste em um sistema IoT que monitora a frequência cardíaca em tempo real usando um ESP32, LEDs de alerta, comunicação MQTT e um dashboard no Node-RED.
A solução realiza:

-> Explicação
O sistema funciona realizando a leitura contínua do potenciômetro, que simula os batimentos cardíacos. O ESP32 processa essas informações localmente utilizando Edge Computing, classificando o valor recebido como batimento baixo, normal ou alto. Com base nessa classificação, LEDs são acionados imediatamente para indicar o estado atual. Paralelamente, o ESP32 envia os dados pela internet usando o protocolo MQTT, comunicando-se com o broker test.mosquitto.org por meio do tópico skillink/batimentos. A cada segundo, um JSON contendo os valores de “batimentos” e “status” é publicado. O Node-RED recebe essas mensagens, interpreta os dados e exibe tudo em tempo real em um dashboard web, permitindo o monitoramento contínuo e visual do comportamento cardíaco simulado.



->Componentes Utilizados

ESP32 DevKit V1

Potenciômetro

LED verde

LED amarelo

LED vermelho

Resistores 220 ohms

Protoboard e jumpers

Node-RED

Broker Mosquitto

Simulador WokWi

-> Dependências:
As bibliotecas utilizadas no projeto foram essenciais para garantir a comunicação e o funcionamento correto do sistema IoT. A biblioteca WiFi.h foi responsável por permitir que o ESP32 se conectasse à rede sem fio, possibilitando o envio de dados para a internet. Já a PubSubClient.h foi utilizada para implementar o protocolo MQTT, permitindo que o ESP32 publicasse mensagens no broker test.mosquitto.org, mantendo uma comunicação contínua e confiável com o Node-RED. Essas duas bibliotecas formam a base da conectividade do projeto, permitindo o envio periódico dos batimentos cardíacos simulados e garantindo a integração entre hardware e dashboard web.


->Instruções de Uso

Executando no WokWi

Abrir o link do projeto no WokWi

Clicar em executar

Verificar no monitor serial a conexão Wi-Fi e MQTT

Girar o potenciômetro para simular diferentes batimentos

LEDs mudam de acordo com o status

ESP32 envia batimentos para o tópico skillink/batimentos

Configurando o Node-RED

Abrir o Node-RED pelo navegador

Criar fluxo com: mqtt in, json, change, gauge, debug

Configurar mqtt in para:

server: test.mosquitto.org

port: 1883

topic: skillink/batimentos

 

 
 