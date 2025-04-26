# Smart Car Recolector de Objetos V1 (Manual)

![Descripción de la imagen](https://lh3.googleusercontent.com/d/1v_vK5Jsz6NdB6wrgMi-2Izepdv7-5_Q1=s220?authuser=0)

## 1. Introducción

**Propósito del manual:**
* **Objetivo:** Servir como guía para construir, programar, operar, mantener y reparar el Smart Car Recolector de Objetos.
* **Alcance:** Desde los fundamentos hasta detalles técnicos, para todos los niveles de experiencia.

**Público objetivo:**
Este manual está destinado a cualquier persona interesada en robótica, desde estudiantes y aficionados hasta ingenieros y educadores.

**Descripción general del Smart Car Recolector de Objetos:**
* **¿Qué es?:** El presente proyecto consiste en el diseño e implementación de un carro autónomo recolector de objetos pequeños, controlado por una placa ESP32. El robot utiliza sensores ultrasónicos para la detección de objetos, un sistema de recolección mediante un mecanismo de pinza, y motores DC para su desplazamiento. Su aplicación principal es la automatización de tareas de recolección en entornos controlados, como talleres o espacios educativos. Este proyecto se enfoca en el diseño e implementación de un robot recolector de objetos pequeños, una herramienta sociotecnológica que busca facilitar tareas de recolección en diversos entornos, como hogares, espacios públicos o industrias, contribuyendo así a la eficiencia y la inclusión social.
* **¿Cómo funciona?:** El prototipo demuestra que, con componentes de bajo costo y programación básica en C++, es posible crear un sistema autónomo para recolección de objetos, siendo escalable para aplicaciones más complejas. El Smart Car Recolector de Objetos opera en las siguientes etapas:
    * Exploración y detección: El robot se desplaza, y el sensor ultrasónico escanea continuamente en busca de objetos que cumplan con ciertas características (tamaño, distancia).
    * Acercamiento: Una vez detectado un objeto, el robot ajusta su trayectoria para acercarse a él.
    * Recolección: El robot se detiene a una distancia óptima y activa el mecanismo de la pinza.
    * Evitación de obstáculos: El robot utiliza un sensor de contacto (pulsador) para detectar colisiones. Al detectar un obstáculo, retrocede, gira y continúa su exploración.
    * Control y coordinación: Todas estas acciones son coordinadas por el microcontrolador ESP32, que ejecuta un programa en C++ diseñado para la tarea de recolección.

## 2. Advertencias de seguridad críticas

**Precauciones generales:**
* Leer este manual antes de operar el robot.
* Usar el robot en un área limpia, plana y uniforme.
* No permitir que niños operen el robot sin supervisión.

**Riesgos específicos del robot:**
* **Riesgos eléctricos (baterías, voltajes):**
    * No cortocircuitar las baterías.
    * No exponer las baterías al agua o al calor.
    * Usar un cargador adecuado para las baterías 18650.
* **Riesgos mecánicos (movimiento del brazo):**
    * Mantener las manos y otros objetos alejados del mecanismo en movimiento.
    * Apagar el robot antes de ajustar o reparar el mecanismo.
* **Advertencias de software (comportamiento inesperado):**
    * Asegurarse de que el código esté cargado y probado antes de operar el robot.
    * Estar preparado para detener el robot en caso de comportamiento inesperado.

**Protocolo de emergencia:**
* **Parada de emergencia:** Presionar el interruptor de apagado.
* **Desconexión segura:** Desconectar la alimentación desde el jack 3.5mm a la placa de alimentación.

**Sistema de carga con indicador LED:**
* **Bloqueo de alimentación:** Manual (apagar el switch principal). Si no se apaga el switch, se pueden dañar los componentes electrónicos.
* **Conmutación manual:** Apagar el switch principal y activar el switch de carga (proceso inverso al usar).
* **Indicador LED verde:** Indica que el cargador está conectado, no el estado de carga.
* **Tiempo de carga:** 2-3 horas con un cargador de 5V y 2-3A.

## 3. Especificaciones técnicas detalladas

**Componentes principales:**
* **ESP32 DevKit v1**
    * Sustituto: ESP32 WROOM
    * Características: Wi-Fi, Bluetooth, 38 pines GPIO, 520 KB SRAM, 4MB Flash.
    * Función: "Cerebro" del sistema, controla sensores, motores y toma decisiones de recolección y navegación.
* **Motores reductores DC**
    * Sustituto: Motores DC similares
    * Características: 3-6V, Relación 1:48.
    * Función: Proporcionan la fuerza y el control de velocidad necesarios para el movimiento del robot, permitiendo la tracción en diferentes superficies.
* **Servomotor SG90**
    * Uso en el robot: Movimiento del mecanismo.
    * Función: Gira en ángulos específicos el brazo, además de abrir/cerrar la pinza.
    * Sustituto: MG90S (mayor torque)
    * Características: 4.8-6V, Torque: 1.8-2.2 kg/cm, 0.1-0.12 s/60 grados.
    * Función: Permiten un movimiento preciso del mecanismo, facilitando la tarea de recolección.
* **Puente H L293N**
    * Sustituto: L298N (mayor corriente)
    * Características: 4.5-36V, 600mA por canal.
    * Función: Permite cambiar el sentido de giro y encender/apagar los motores.
* **Sensor ultrasónico HC-SR04**
    * Uso en el robot: "Ojos" del carrito.
    * Función: Detecta objetos para evitar choques o para recogerlos.
    * Sustituto: HC-SR04P (mayor precisión)
    * Características: 5V, Rango: 2cm - 400cm, Precisión: 3mm.
    * Función: Permite al robot "ver" el mundo que lo rodea.
* **Baterías 18650 (3.7V)**
    * Uso en el robot: Fuente de energía principal.
    * Función: Alimentan el ESP32, motores y otros módulos.
    * Sustituto: Baterías LiPo similares
    * Características: 3.7V.
    * Función: Garantizan el funcionamiento autónomo del robot.
* **Elevador de voltaje MT3608**
    * Uso en el robot: Para cargar las baterías del robot.
    * Función: Asegura energía suficiente para cargar las baterías.
    * Sustituto: Módulos elevadores similares
    * Características: 2V-24V a 5V-28V.
    * Función: Permite ajustar el voltaje del cargador hacia la batería..
* **Elevador de voltaje XL6009**
    * Uso en el robot: Similar al MT3608 pero con más potencia.
    * Función: Aumenta el voltaje para alimentar motores o servos más exigentes.
    * Sustituto: Módulos elevadores similares, pero con más potencia
    * Características: Similar al MT3608 pero con más potencia.
    * Función: Aumenta el voltaje para alimentar motores o servos más exigentes, garantizando un suministro de energía estable.
* **Fuente de alimentación HW-131**
    * Uso en el robot: Regulador para la protoboard.
    * Función: Entrega 3.3V o 5V estables desde las baterías.
    * Sustituto: Regulador similar
    * Características: Salida: 3.3V o 5V estables.
    * Función: Asegura un suministro de energía confiable para la protoboard y sus componentes.
* **Resistencia de 220 ohm**
    * Uso en el robot: Protección de componentes como LEDs o pulsadores.
    * Función: Limita la corriente para evitar daños.
    * Sustituto: Resistencia cercana (200-250 Ohm)
    * Características: 220 Ohm.
    * Función: Protege componentes como LEDs o pulsadores, limitando la corriente para evitar daños.
* **Pulsador**
    * Uso en el robot: Interfaz de usuario.
    * Función: Puede encender, detener o activar alguna función específica.
    * Sustituto: Pulsador similar
    * Características: Normalmente abierto (NO)
    * Función: Actúa como sensor de contacto para detectar colisiones o interacciones con el entorno.
* **Mini switch (o micro switch)**
    * Uso en el robot: Detector de fin de recorrido o contacto con objetos.
    * Función: Detecta si algo fue recogido o si una paleta llegó al tope.
    * Sustituto: Switch similar
    * Características: Micro Switch
    * Función: Permite encender, detener o activar alguna función específica
* **Pinza de paletas**
    * Uso en el robot: Mecanismo recolector.
    * Función: Recogen y empujan objetos hacia el interior del robot.
* **Kit Del Carrito**
    * Uso en el robot: Ensamblaje mecánico.
    * Función: Fijan piezas como motores, paletas, etc.
* **Tornillos Y Tuercas**
    * Uso en el robot: Ensamblaje mecánico.
    * Función: Fijan piezas como motores, paletas, etc.
* **Protoboard de 380 Puntos**
    * Uso en el robot: Facilita el montaje de todo el circuito sin soldadura.
    * Función: Facilita el montaje de todo el circuito sin soldadura.

**Características eléctricas:**
* Voltaje de operación: 5V (todos los componentes).
* Fuente de alimentación: XL6009 (batería a 9V, luego a 5V), MT3608 (cargador de 5V a 8.4V).

**Características mecánicas:**
* Dimensiones: 23cm de ancho, 42cm de largo, 19cm de alto, 2cm de altura mínima del suelo.
* Peso: 580 gramos (sin objetos).

**Software y programación:**
* Lenguaje: C++
* Librería: Servo.h

## 4. Diagrama Circuital Completo

**Diagrama esquemático:**

![Descripción de la imagen](https://lh3.googleusercontent.com/d/1F0z2lyRIHOcrWuVqWTqhrT0OmdSBy-gK=s220?authuser=0)


**Conexiones detalladas del ESP32:**

![Descripción de la imagen](https://lh3.googleusercontent.com/d/1M-0T6HMmLr5E9fIMdGeiJCA8YKBLsePS=s220?authuser=0)

* Pin 5: Trigger del sensor ultrasónico
* Pin 17: Echo del sensor ultrasónico
* Pin 23: Motor Izquierdo PWM
* Pin 21: Motor Izquierdo Dirección 1
* Pin 22: Motor Izquierdo Dirección 2
* Pin 15: Motor Derecho PWM
* Pin 18: Motor Derecho Dirección 1
* Pin 19: Motor Derecho Dirección 2
* Pin 2: Servo Base
* Pin 4: Servo Codo
* Pin 25: Servo Pinza
* Pin 14: Pulsador
* VIN (Alimentación): Conectado a la fuente de alimentación regulada de 5V proveniente de la HW-131.
* GND (Tierra): Conectado a la tierra común del circuito, que incluye la fuente de alimentación, las baterías y otros componentes.

**Distribución de la alimentación:**
La alimentación del Smart Car Recolector de Objetos se distribuye de la siguiente manera:
* Baterías 18650 (7.4V): Dos baterías 18650 en serie proporcionan 7.4V como fuente de energía principal.
* Elevador de Voltaje XL6009: Eleva el voltaje de las baterías a 9V para alimentar los componentes del robot.
* Fuente de Alimentación HW-131: Convierte el voltaje de entrada (9V) a 5V y 3.3V, que son utilizados por los componentes electrónicos.

**Alimentación a componentes:**
* 5V: Se utiliza para alimentar el ESP32, los servomotores, el sensor ultrasónico y los motores DC.
* Elevador de voltaje MT3608: Se utiliza para elevar el voltaje de 5V del cargador a 8.4V para cargar las baterías.

**Notas importantes sobre el cableado:**
* Utilice cables de calibre adecuado para evitar caídas de tensión.
* Asegúrese de que las conexiones estén bien aseguradas para evitar desconexiones accidentales.
* Siga el diagrama cuidadosamente para evitar errores de cableado.
* Utilice un multímetro para verificar la continuidad y los voltajes en puntos clave del circuito.

## 5. Montaje

**Preparación de componentes:**
* Reúna todos los componentes.
* Verifique que los componentes estén en buenas condiciones.
* Prepare las herramientas (destornillador, alicates, soldador, etc.).

**Montaje del chasis:**
* Use las paletas para construir el chasis.
* Asegúrese de que el chasis sea estable.

**Instalación de motores y ruedas:**
* Fije los motores al chasis.
* Conecte las ruedas a los motores.
* Asegúrese de que las ruedas giren libremente.

**Montaje del mecanismo:**
* Fije los servomotores a la base del mecanismo.
* Conecte las partes del mecanismo a los servomotores.
* Asegúrese de que el brazo se mueva suavemente.

**Conexión de componentes electrónicos:**
* Conecte los componentes según el diagrama circuital.
* Aísle las conexiones para evitar cortocircuitos.

**Verificación del montaje:**
* Revise todas las conexiones.
* Verifique que no haya cortocircuitos.
* Encienda el robot y verifique el funcionamiento.

## 6. Puesta en marcha y configuración inicial

* Cargue las baterías con el conector JST SM y el cargador USB (5V, 3A).
* Encienda el robot: Apague el switch de carga y active el switch principal (inverso para cargar).
* Conecte el ESP32 al ordenador y cargue el código con Arduino IDE.

## 7. Instrucciones de operación

* Coloque el robot en un área plana y uniforme con objetos adecuados.
* Encienda el robot.
* El robot explorará y recogerá objetos automáticamente.

## 8. Mantenimiento

**Cuidado de las baterías:**
* Cargue regularmente.
* Use el cargador correcto (5V).
* No exponer al calor.

**Limpieza:**
* Limpie con un paño suave y seco.

**Revisiones periódicas:**
* Verifique conexiones, motores, sensor y ruedas.

## 9. Guía de solución de problemas (Troubleshooting)

* **El robot no enciende:**
    * Causa: Baterías descargadas.
    * Solución: Cargue y verifique conexiones.
* **El brazo no se mueve:**
    * Causa: Servomotores defectuosos o conexiones incorrectas.
    * Solución: Verifique conexiones y reemplace servomotores.
* **El robot no detecta objetos:**
    * Causa: Sensor defectuoso o conexiones incorrectas.
    * Solución: Verifique conexiones y reemplace el sensor.
* **El robot no se mueve:**
    * Causa: Motores defectuosos o conexiones incorrectas.
    * Solución: Verifique conexiones y reemplace motores.

## 10. Software

**Lógica del programa:**
* Inicialización: Componentes (motores, servos, sensor).
* Detección de objetos: Sensor mide la distancia.
* Control del robot: Microcontrolador controla el movimiento y el mecanismo.

**Librerías utilizadas:**
* Servo.h: Control de servomotores.

## 11. Glosario

* ESP32: Microcontrolador con Wi-Fi y Bluetooth.
* PWM: Modulación por Ancho de Pulso (control de velocidad de motores).
* Servo: Servomotor (motor con control de posición).
* GPIO: Pines de entrada/salida.
* Protoboard: Placa de pruebas.
* SRAM: Memoria de acceso aleatorio estática.
* Flash: Memoria no volátil.
* JST SM: Tipo de conector.

## 12. Conclusión

El desarrollo del Smart Car Recolector de Objetos Pequeños evidencia que, mediante el uso de componentes de bajo costo y una programación básica en C++, es factible implementar un sistema autónomo capaz de realizar tareas de recolección de objetos en entornos controlados. El prototipo logra integrar sensores ultrasónicos, motores DC, mecanismos de recolección y controladores electrónicos, demostrando que la automatización de este tipo de tareas puede ser accesible, eficiente y escalable. Esta solución no solo es aplicable en el ámbito educativo y de laboratorio, sino que también puede adaptarse para aplicaciones más complejas en el hogar, la industria o espacios públicos, contribuyendo a la eficiencia, la innovación y la inclusión tecnológica en diferentes contextos.
