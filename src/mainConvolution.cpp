/*
   Pour compiler le fichier
   g++ mainConvolution.cpp -o mainCon

   ./mainCon ../images/base/boat.pgm
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

    // Matrice Identité
    double identite[9] = {
        0.0,0.0,0.0,
        0.0,1.0,0.0,
        0.0,0.0,0.0
    };
    double M1[9] = {
        1.0/9,1.0/9,1.0/9,
        1.0/9,1.0/9,1.0/9,
        1.0/9,1.0/9,1.0/9
    };

    double M2[9] = {
        1.0/16,2.0/16,1.0/16,
        2.0/16,4.0/16,2.0/16,
        1.0/16,2.0/16,1.0/16
    };

    double M3[9] = {
        0.0,-1.0,0.0,
        -1.0,5.0,-1.0,
        0.0,-1.0,0.0
    };

    double M4[9] = {
        -1.0,-1.0,-1.0,
        -1.0,9.0,-1.0,
        -1.0,-1.0,-1.0
    };
    printf("Test pour la convolution avec les masques M1 et M2 \n");
    Image<double> matriceIdentite(3,3,identite);
    Image<double> MatriceM1(3,3,M1);
    Image<double> MatriceM2(3,3,M2);
    Image<double> MatriceM3(3,3,M3);
    Image<double> MatriceM4(3,3,M4);

    // Matrice Identité
    // Lecture de l'image
    Image<uint8_t> image = readPGM(imageEntre);

    Image<double> imageFinale = convolution(image,matriceIdentite);
    Image<double> imageFinaleM1 = convolution(image,MatriceM1);
    Image<double> imageFinaleM2 = convolution(image,MatriceM2);
    Image<double> imageFinaleM3 = convolution(image,MatriceM3);
    Image<double> imageFinaleM4 = convolution(image,MatriceM4);

    // Image avec gaussienMask
    Image<double> imageGaussSigma1 = gaussienMask(1.0);
    Image<double> imageGaussSigma2 = gaussienMask(2.0);
    Image<double> imageGaussSigma3 = gaussienMask(3.0);
    Image<double> imageGaussSigma4 = gaussienMask(4.0);
    Image<double> imageGaussSigma7 = gaussienMask(7.0);
    Image<double> imageGaussSigmaDemi = gaussienMask(0.5);

    printf("Sigma 1, 2, 3, 4, 7 & Demi \n" );

    imageGaussSigma1.print();
    imageGaussSigma2.print();
    imageGaussSigma3.print();
    imageGaussSigma4.print();
    imageGaussSigma7.print();
    imageGaussSigmaDemi.print();


    Image<double> imageFinaleGaussSigma1 = convolution(image,imageGaussSigma1);
    Image<double> imageFinaleGaussSigma2 = convolution(image,imageGaussSigma2);
    Image<double> imageFinaleGaussSigma3 = convolution(image,imageGaussSigma3);
    Image<double> imageFinaleGaussSigma4 = convolution(image,imageGaussSigma4);
    Image<double> imageFinaleGaussSigma7 = convolution(image,imageGaussSigma7);
    Image<double> imageFinaleGaussSigmaDemi = convolution(image,imageGaussSigmaDemi);

    // Convertion des Sigmas pour les filtres M3 & M4

    Image<uint8_t> imageFinaleGaussConvSigma2 = convertionImage(imageFinaleGaussSigma2);
    Image<uint8_t> imageFinaleGaussConvSigma3 = convertionImage(imageFinaleGaussSigma3);
    Image<uint8_t> imageFinaleGaussConvSigma7 = convertionImage(imageFinaleGaussSigma7);



    Image<double> imageGaussSigma2M3 = convolution(imageFinaleGaussConvSigma2,MatriceM3);
    Image<double> imageGaussSigma3M3 = convolution(imageFinaleGaussConvSigma3,MatriceM3);
    Image<double> imageGaussSigma7M3 = convolution(imageFinaleGaussConvSigma7,MatriceM3);
    Image<double> imageGaussSigma2M4 = convolution(imageFinaleGaussConvSigma2,MatriceM4);
    Image<double> imageGaussSigma3M4 = convolution(imageFinaleGaussConvSigma3,MatriceM4);
    Image<double> imageGaussSigma7M4 = convolution(imageFinaleGaussConvSigma7,MatriceM4);

    Image<uint8_t> imageFinaleConv = convertionImage(imageFinale);
    Image<uint8_t> imageFinaleConvM1 = convertionImage(imageFinaleM1);
    Image<uint8_t> imageFinaleConvM2 = convertionImage(imageFinaleM2);
    Image<uint8_t> imageFinaleConvM3 = convertionImageCond(imageFinaleM3);
    Image<uint8_t> imageFinaleConvM4 = convertionImageCond(imageFinaleM4);


    Image<uint8_t> imageGaussSigma2M3Conv = convertionImageCond(imageGaussSigma2M3);
    Image<uint8_t> imageGaussSigma3M3Conv = convertionImageCond(imageGaussSigma3M3);
    Image<uint8_t> imageGaussSigma7M3Conv = convertionImageCond(imageGaussSigma7M3);
    Image<uint8_t> imageGaussSigma2M4Conv = convertionImageCond(imageGaussSigma2M4);
    Image<uint8_t> imageGaussSigma3M4Conv = convertionImageCond(imageGaussSigma3M4);
    Image<uint8_t> imageGaussSigma7M4Conv = convertionImageCond(imageGaussSigma7M4);

    Image<uint8_t> imageFinaleConvSigma1 = convertionImage(imageFinaleGaussSigma1);
    Image<uint8_t> imageFinaleConvSigma2 = convertionImage(imageFinaleGaussSigma2);
    Image<uint8_t> imageFinaleConvSigma3 = convertionImage(imageFinaleGaussSigma3);
    Image<uint8_t> imageFinaleConvSigma4 = convertionImage(imageFinaleGaussSigma4);
    Image<uint8_t> imageFinaleConvSigma7 = convertionImage(imageFinaleGaussSigma7);
    Image<uint8_t> imageFinaleConvSigmaDemi = convertionImage(imageFinaleGaussSigmaDemi);


    writePGM(imageFinaleConv,"../images/boatMatrice.pgm");
    writePGM(imageFinaleConvM1,"../images/boatM1.pgm");
    writePGM(imageFinaleConvM2,"../images/boatM2.pgm");
    writePGM(imageFinaleConvM3,"../images/boatM3.pgm");
    writePGM(imageFinaleConvM4,"../images/boatM4.pgm");

    writePGM(imageFinaleConvSigma1,"../images/boatGaussSigma1.pgm");
    writePGM(imageFinaleConvSigma2,"../images/boatGaussSigma2.pgm");
    writePGM(imageFinaleConvSigma3,"../images/boatGaussSigma3.pgm");
    writePGM(imageFinaleConvSigma4,"../images/boatGaussSigma4.pgm");
    writePGM(imageFinaleConvSigma7,"../images/boatGaussSigma7.pgm");
    writePGM(imageFinaleConvSigmaDemi,"../images/boatGaussSigmaDemi.pgm");

    writePGM(imageGaussSigma2M3Conv,"../images/boatGaussSigma2M3.pgm");
    writePGM(imageGaussSigma3M3Conv,"../images/boatGaussSigma3M3.pgm");
    writePGM(imageGaussSigma7M3Conv,"../images/boatGaussSigma7M3.pgm");
    writePGM(imageGaussSigma2M4Conv,"../images/boatGaussSigma2M4.pgm");
    writePGM(imageGaussSigma3M4Conv,"../images/boatGaussSigma3M4.pgm");
    writePGM(imageGaussSigma7M4Conv,"../images/boatGaussSigma7M4.pgm");


    return 0;
}
