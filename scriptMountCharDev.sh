#!/bin/bash

echo 'Ejecutando programa de montaje de dispositivo de caracter.'
echo ''
#sudo -E make clean --silent & -E make --silent
sudo -E make clean
sudo -E make
sudo insmod miModulo.ko

echo '#!/bin/bash' > tmp.sh
sudo chmod 777 tmp.sh
sudo dmesg | cut -c16-99 | grep sudo >> tmp.sh
./tmp.sh
sudo -E make clean
sudo rm tmp.sh
clear
echo 'El CharDevice-CaesarCipher se cargó con exito, para encriptar ejecuta echo "mensaje" > /dev/UNGS '
echo 'Luego, proba con cat /dev/UNGS para verificarlo.'
echo 'Recorda desmontar el dispositivo con sudo rmmod miModulo.'

