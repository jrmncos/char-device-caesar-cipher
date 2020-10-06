# Trabajo práctico inicial de Sistemas Operativos y Redes II

El trabajo consiste en implementar un Driver que administre un char device alojado en /dev/UNGS. El driver encriptara los mensajes recibidos utilizando el cifrado de Cesar.

> Mas sobre Cifrado de Cesar:  [Explicación e implementación del algoritmo ](https://www.geeksforgeeks.org/caesar-cipher-in-cryptography/)
## Instalación

Asegurese de no tener ya cargado un driver con nombre 'miModulo'. Para esto, ejecute ***sudo lsmod | grep miModulo***. No se debería mostrar nada en la consola.

- Clone el repositorio ***git clone https://github.com/jrmncos/char-device-caesar-cipher.git***
- Moverse al directorio del proyecto ***cd char-device-caesar-cipher/*** 
- Leer el contenido del script ***cat scriptMountCharDev***
- Darle permisos de ejecución ***chmod u+x*** 
- Ejecutarlo ***./scriptMountCharDev.sh*** 
- Siga las instruccione del script.