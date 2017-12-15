//https://fr.wikipedia.org/wiki/Filtre_de_Canny

#include <fstream>
#include <iostream>
#include "TP2/bas_niveau.hpp"
#include <cstdint>

int main(int argc,const char * argv[]){

    if (argc != 3){
        std::cout << "Vous devez appelez le programme " << argv[0] << " avec 2 arguments \n";
        std::cout<< "Par exemple : \n" << argv[0] << " boat.pgm imageSortie.pgm \n";
        system("pause");
        exit(EXIT_FAILURE);
    }

    std::string imageEntre = argv[2];
    std::string imageSortie= argv[3];

    printf("Nous allons utiliser une matrice identité 3X3 \n");

    // Matrice Identité
    double[9] identite = {
                            0,0,0,
                            0,1,0,
                            0,0,0
                        }
    double[9] lissage = {
                            1,1,1,
                            1,1,1,
                            1,1,1
                        }
                        }
    double[9] gaussien = {
                            1,2,1,
                            2,4,2,
                            1,2,1
                        }
    Image<double> matriceIdentite(3,3,identite);
    Image<double> matricelissage(3,3,lissage);
    Image<double> matricegaussien(3,3,gaussien);
    // Matrice Identité
    // Lecture de l'image
    Image<uint8_t> image = readPGM(imageEntre);

    // On fait le redimenssionnage
    Image<double> imageFinale = convolution(image,matriceIdentite);

    writePGM(imageFinale,imageSortie);

    return 0;
}
