-EL trabajo practico utiliza las librerias de math.h

-Para su compilacion solamente es necesario hacer un "make all", generando un binario llamado "ss"

-Para su ejecucion en modo distribucion
    ./ss –d –s secreto.bmp –m watermark.bmp –k 4 – n 8 –dir images/
 Creando un archivo llamado "RW.bmp"


-Para su ejecucion en modo de reucperacion
    ./ss –r –s secreto.bmp –m RW.bmp –k 4 –n 8 –dir images/
 Creando un archivo "secreto.bmp", por el argumento s y un archivo "watermark.bmp"