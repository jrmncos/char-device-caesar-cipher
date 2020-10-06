#!/bin/bash

echo 'Ejecutando programa de montaje de dispositivo de caracter.'
echo ''
make clean --silent & make --silent
insmod chardev.ko

echo '#!/bin/bash' > tmp.sh
chmod 777 tmp.sh
dmesg | cut -c16-99 | grep sudo >> tmp.sh
./tmp.sh

echo 'Hola! Soy CharDev y me ejecute con exito.' > /dev/UNGS
echo 'Proba con cat /dev/UNGS para verificarlo.'
echo 'Recorda desmontar el dispositivo con rmmod chardev.'

