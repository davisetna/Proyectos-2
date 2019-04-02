# EC3882 - LABORATORIO DE PROYECTOS 2 

GRUPO 13

>Autores:
Etna Davis 14-10281
Hugo Troyani 14-11094

>Profesor:
Novel Certad

# OSCILOSCOPIO DIGITAL

Objetivo General: Realizar un osciloscopio digital haciendo uso de una tarjeta de desarrollo (DEMOQE128), crear un protocolo de comunicación entre el microprocesador de la tarjeta y la computadora, montar un circuito de protección para evitar quemar el microcontrolador, y crear una interfaz grafica para poder visualizar las señales. 

>Requirimientos Técnicos:

1. El proyecto debe hacer uso de un mínimo de dos canales analógicos más dos canales digitales
2. Las señales provenientes de los canales de adquisición deben ser procesadas por el microcontrolador, cuidando mantener el sincronismo y la concurrencia de procesos.
3. La conversión analógica digital debe hacerse a 12 bits.
4. La adquisición debe hacerse con un ancho de banda de 1kHz para cada canal.

>Etapas del proyecto:

1. Circuito de protección: Consta de un LM324 y un 7434 que permiten que las 4 señales con las que se alimentan el circuito no sobrepasen el voltaje que permite el micro MC9S08QE128
2. El protocolo de comunicacion entre el procesador de la tarjeta y la computadora: El micro recibe una señal analógica que debe muestrear y convertir un numero binario; para esto el ADC convierte una cantidad física contínua (generalmente voltaje) a un número digital que representan la amplitud de dicha cantidad. La conversión implica un cuantización de la entrada por lo que se produce un pequeño error al realizar la conversión. La salida del ADC,en decimal, es un numero del 0 al 4095

