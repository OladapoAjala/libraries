# Biblioteca MotoMamaLib
Biblioteca para el manejo del **L298N H-Bridge Motor Driver Shield (MotoMama)** de [itead studio](https://www.itead.cc/wiki/MotoMama).

## Autor
Jorge Villalobos Carvajal - Abril.2018

## Uso
Se declara una variable con el tipo de la biblioteca y se inicializa por medio del método **begin** en el **setup** del sketch.

#### Ejemplo
```
#include <MotoMamaLib.h>

MotoMamaLib Robot;

void setup() {
  Robot.begin();             // Se realiza la inicialización de la placa
}  // setup

void loop() {
  robot.setSpeed(175, 175);  // Se establece una velocidad de 175 (0-255)
  robot.forward(500);        // Se avanza hacia adelante por medio segundo
  robot.left(500);           // Se gira a la izquierda por medio segundo
  robot.right(500);          // Se gira a la derecha por medio segundo
  robot.backward(500);       // Se retrocede por medio segundo
}
```

## Métodos de la biblioteca

Método | Descripción
------ | -----------
**begin()** | Inicializa los puertos del controlador (usar en el setup del sketch)
**forward()** | Se desplaza hacia adelante
**forward(int ms)** | Se desplaza hacia adelante por **_ms_** milisegundos y se detiene
**backward()** | Se desplaza hacia atrás
**backward(int ms)** | Se desplaza hacia atrás por **_ms_** milisegundos y se detiene
**left()** | Gira hacia la izquierda
**left(int ms)** | Gira hacia la izquierda por **_ms_** milisegundos y se detiene
**right()** | Gira hacia la derecha
**right(int ms)** | Gira hacia la derecha por **_ms_** milisegundos y se detiene
**stop()** | Detiene ambos motores, estableciendo su velocidad en 0.
**setMotors(bool leftVal, bool rightVal)** | Establece la dirección de los motores
**setSpeed(int leftVal, int rightVal)** | Establece la velocidad de los motores (valores entre 0 y 255)

## Recomendaciones
- Si va a utilizar el header Xbee para comunicaciones (por ejemplo: Bluetooth Bee HC-06), recuerde **quitar el dispositivo que tenga conectado antes de cargar el sketch**.  De otra forma, obtendrá un error de comunicación.

![Bluetooth Bee](/images/BTBee.jpg)

- Recuerde que si va a utilizar dos baterías: una para el Arduino y otra para la placa, los negativos deben de estar interconectados.

## Hardware utilizado

* Arduino UNO R3
* Chasis con 2 motores DC
* Conector para batería de 9V
* Batería de 9V
* L298N H-Bridge Motor Driver Shield (MotoMama)
* Bluetooth Bee HC-06   

## Instrucciones para la conexión

![Chasis armado](/images/ChasisArmado.jpg)

[JorgeMVC - Empezando con el MotoMama H-Bridge de Itead](https://www.instructables.com/id/Empezando-Con-El-MotoMama-H-Bridge-De-Itead/)

## Ejemplos incluídos
* **MMSimpleTest:** muestra simple de uso de la biblioteca
* **MMBluetoothTest:** muestra simple de uso de la biblioteca con el Bluetooth Bee

## APP utilizada
* [Bluetooth Controller](https://play.google.com/store/apps/details?id=com.lafabricadeandroides.lfdabluetoothcontroller)

Puede se alguna otra, en ese caso se utilizan los siguientes comandos:
- Comando **s** para detener el carro
- Comando **u** para ir hacia adelante
- Comando **b** para ir hacia atrás
- Comando **l** para girar a la izquierda
- Comando **r** para girar a la derecha
- Comandos del **1 al 0** corresponden a los valores del 1 al 10 para la velocidad (1 detenido y 10 la máxima velocidad).

## Licencia
Este proyecto ha sido liberado bajo la licencia: **MIT License**
