#! /bin/bash
# Converti tout les images .pgm en .png dans le même dossier.
# Ensuite il supprime tout les images avec l'extension .pgm
# Pour compiler exécuter le programme 
#
#   ./convert.sh
#
for img in *.pgm; do 
    echo -e "$img\n"
    filename=${img%.*}
    convert "$filename.pgm" "$filename.png"
    rm "$img"
done
