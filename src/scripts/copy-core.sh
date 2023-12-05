#!/bin/bash


omxplayer /home/pi/splash/copiado.mp4

# Verificar que se proporcionaron suficientes argumentos
if [ "$#" -ne 2 ]; then
    echo "Uso: $0 directorio_origen directorio_destino"
    exit 1
fi

# Directorio de origen
directorio_origen="$1"

# Directorio de destino
directorio_destino="$2"

# Verificar si el directorio de origen existe
if [ ! -d "$directorio_origen" ]; then
    echo "El directorio de origen no existe."
    exit 1
fi

# Verificar si el directorio de destino existe, si no, crearlo
if [ ! -d "$directorio_destino" ]; then
    mkdir -p "$directorio_destino"
fi

# Copiar archivos .zip de origen a destino y mostrar los nombres
for archivo_zip in "$directorio_origen"/*.zip; do
    nombre_archivo=$(basename "$archivo_zip")
    cp "$archivo_zip" "$directorio_destino"
    echo "Copiado: $nombre_archivo"
done

echo "Archivos .zip copiados correctamente de $directorio_origen a $directorio_destino."

