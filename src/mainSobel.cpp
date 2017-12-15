/*
    SOBEl Filters

    Pour compiler le fichier
    g++ mainSobel.cpp -o mainSobel

    ./mainSobel ../images/base/boat.pgm

    Voici sur comment j'ai appris à faire le Sobel
    https://blog.saush.com/2011/04/20/edge-detection-with-the-sobel-operator-in-ruby/
    http://stackoverflow.com/questions/17815687/image-processing-implementing-sobel-filter
*/
#include <fstream>
#include <iostream>
#include "bas_niveau.hpp"
#include <cstdint>


int main(int argc,const char * argv[]){

    if (argc != 2){
        std::cout << "Vous devez appelez le programme " << argv[0] << " avec 2 arguments \n";
        std::cout<< "Par exemple : \n" << argv[0] << " boat.pgm \n";
        system("pause");
        exit(EXIT_FAILURE);
    }

    std::string imageEntre = argv[1];

    printf("Nous allons utiliser une matrice identité 3X3 \n");

    // Sobel Vertical
    double matrixSobelX[9] = {
                            -1,0,1,
                            -2,0,2,
                            -1,0,1
                        };
    // Sobel Horizontal
    double matrixSobelY[9] = {
                            -1,-2,-1,
                            0,0,0,
                            1,2,1
                        };

    Image<double> imageSobelX(3,3,matrixSobelX);
    Image<double> imageSobelY(3,3,matrixSobelY);
    // Matrice Identité
    // Lecture de l'image
    Image<uint8_t> image = readPGM(imageEntre);

    Image<double> imageFiltreSobelX = convolution(image,imageSobelX);
    Image<double> imageFiltreSobelY = convolution(image,imageSobelY);

    Image<uint8_t> imageFiltreConvSobelX = convertionImageCond(imageFiltreSobelX);
    Image<uint8_t> imageFiltreConvSobelY = convertionImageCond(imageFiltreSobelY);

    Image<uint8_t> imageFiltreConvAbsSobelX = sobelOperatorAbsolue(imageFiltreConvSobelX);
    Image<uint8_t> imageFiltreConvAbsSobelY = sobelOperatorAbsolue(imageFiltreConvSobelY);

    Image<uint8_t> imageSobel = sobelOperatorNorme(imageFiltreConvAbsSobelX,imageFiltreConvAbsSobelY);

    writePGM(imageFiltreConvSobelX,"../images/boatSobelX.pgm");
    writePGM(imageFiltreConvSobelX,"../images/boatSobelY.pgm");
    writePGM(imageSobel,"../images/boatSobelYX.pgm");

    return 0;
}
