#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include "image.h"

//////////////////////////////
/*

   Déclaration des fonctions pour l'interpréteur

*/
//////////////////////////////
Image<uint8_t> quantize(Image<uint8_t> &imageSource,uint8_t puissance);
Image<uint8_t> readPGM(const std::string &inputFile);
int writePGM(const Image<uint8_t> &image, const std::string &outputFile);
int writePGMDouble(const Image<double> &image, const std::string &outputFile);
Image<uint8_t> resampleNN(Image<uint8_t> &imageEntre,double r);
Image<uint8_t> resampleBilinearInterpolation(Image<uint8_t>& imageEntre, double r);
Image<double> convolution(Image<uint8_t>& imageEntre,Image<double>& masque );
Image<uint8_t> convertionImage(Image<double>& imageEntree);
Image<uint8_t> sobelOperatorAbsolue(Image<uint8_t>& imageSobel);
Image<uint8_t> sobelOperatorNorme(Image<uint8_t>& imageSobelAbsolue1,Image<uint8_t>& imageSobelAbsolue2);
//////////////////////////////

/*

   Corps des fonctions

*/
//////////////////////////////

Image<uint8_t> quantize(Image<uint8_t> &imageSource, uint8_t puissance){

    Image<uint8_t> imageRetour(imageSource.getDx(),imageSource.getDy());
    // Formule pour obtenir les segments selon la puissance
    double segment = ( 255 / ((1 << (8-puissance)) - 1) );
    // On itère sur tout les pixels de l'image et on l'assigne dans le bon segment
    for (int y = 0;y<imageSource.getDy();y++){
        for(int x = 0; x<imageSource.getDy();x++){
            float ensemble = imageSource(x,y) >> puissance;
            imageRetour(x,y) = (int)(ensemble*segment);
        }
    }
    return imageRetour;
}
Image <uint8_t> readPGM(const std::string &inputFile)
{
    Image <uint8_t> result;
    std::ifstream file(inputFile);
    if(file.is_open()) {
        std::string line;
        std::getline(file,line);
        // only binary, greyscale PGM
        if(line=="P5") {
            int dx,dy,maxValue;
            std::getline(file,line);
            // remove comments beginning by '#'
            while(line[0]=='#')
                std::getline(file,line);
            std::stringstream ss(line);
            ss >> dx >> dy;
            std::getline(file,line);
            ss.clear();
            ss.str(line);
            ss>>maxValue;
            std::cout << "Reading header.\nFile "<<inputFile<< "\ndx : "  << dx << "\ndy : " <<dy << "\nmaxValue : " << maxValue << "\n";
            int size=dx*dy;
            uint8_t *buffer=new uint8_t[size];
            file.read((char *)buffer,size);
            Image <uint8_t> result(dx,dy,buffer);
            delete[] buffer;
            return result;

        }
        file.close();
    }

    return result;
}

int writePGM(const Image<uint8_t> &image, const std::string &outputFile)
{
    std::ofstream file(outputFile,std::ios_base::trunc  | std::ios_base::binary);
    if(file.is_open()) {
        std::string line;

        int dx=image.getDx();
        int dy=image.getDy();
        int size=dx*dy;

        file << "P5\n" << dx << " " << dy << "\n" << "255" ;
        file << "\n";

        file.write((char *)image.getData(),size);

        file << "\n";

        file.close();
    }
    else return -1;

    return 0;
}

int writePGMDouble(const Image<double> &image, const std::string &outputFile)
{
    std::ofstream file(outputFile,std::ios_base::trunc  | std::ios_base::binary);
    if(file.is_open()) {
        std::string line;

        int dx=image.getDx();
        int dy=image.getDy();
        int size=dx*dy;

        file << "P5\n" << dx << " " << dy << "\n" << "255" ;
        file << "\n";

        file.write((char *)image.getData(),size);

        file << "\n";

        file.close();
    }
    else return -1;

    return 0;
}

Image<uint8_t> resampleNN(Image<uint8_t> &imageEntre,double r){

    // On dimensionne l'image selon le radio
    int nX = imageEntre.getDx() * r;
    int nY = imageEntre.getDy() * r;

    imageEntre.print();
    // On créer l'image
    Image<uint8_t> imageFinale(nX,nY);

    for(int y = 0; y<nY;y++){
        for(int x = 0;x<nX;x++){
            imageFinale(x,y) = imageEntre(int(x/r),int(x/r));
        }
    }

    imageFinale.print();
    return imageFinale;
}

Image<uint8_t> resampleBilinearInterpolation(Image<uint8_t>& imageEntre, double r){


    // Nouvelle taille pour l'image
    // nX valeur de X
    // nY valeur de Y
    int nX = imageEntre.getDx() * r;
    int nY = imageEntre.getDy() * r;

    // Création de l'image avec la nouvelle taille
    Image<uint8_t> imageRedi(nX,nY);

    // On parcours toute les pixels
    for(int y =0;y<nY;y++){
        for(int x = 0; x< nX;x++){

            // Pixel de départ, sans arrondie. d=double
            double dX = x/r;
            double dY = y/r;
            std::cout << "dX dY : " << dX << " " << dY << "\n";
            // Pixel arrondie avec la fonction floor. e=entier
            int eX = floor(dX);
            int eY = floor(dY);

            std::cout << "eX eY : " << eX << " " << eY << "\n";
            // On récupère les valeurs décimals, r = reste
            double rX = dX-eX;
            double rY = dY-eY;

            std::cout << "rX rY : " << rX << " " << rY << "\n";
            // Position Initiale. On suppose que la distance entre deux points consécutifs est de + 1
            int Qx1y1 = imageEntre(eX,eY);
            int Qx1y2 = imageEntre(eX,eY+1);
            int Qx2y1 = imageEntre(eX+1,eY);
            int Qx2y2 = imageEntre(eX+1,eY+1);

            std::cout << "Qx1y1 Qx1y2 Qx2y1 Qx2y2 : " << Qx1y1 << " " << Qx1y2 << " " << Qx2y1 << " " << Qx2y2 << "\n";


            int R1 = (int)((1 - rX) * (1 - rY) * Qx1y1 + (rX) * (1 - rY) * Qx2y1 + (1 - rX) * (rY) * Qx1y2);
            int R2 =(int)((1 - rX) * (rY) * Qx1y2 + (rX) * (rY) * Qx2y2);

            imageRedi(x,y) = R1+R2;

        }
    }

    return imageRedi;
}

Image<double> convolution(Image<uint8_t>& imageEntre,Image<double> &masque)
{

    int ImaX = imageEntre.getDx();
    int ImaY = imageEntre.getDy();
    // Avoir le centre de notre masque
    int MasqueX = (masque.getDx()/2);
    int MasqueY = (masque.getDy()/2);
    printf("%d\n",ImaX);
    printf("%d\n",ImaY );
    Image<double> imageFinale(ImaX,ImaY);

    // On itère sur tout les pixels de l'image
    // Pour chaque ligne
    // On prend chaque pixels
    for (int x = 0;x<ImaX;x++){
        // Ensuite on change de colonne
        for(int y = 0; y<ImaY;y++){
            // Valeur calculer pour chaque pixel de l'image
            double accumulator = 0;

            // Pour chaque colonne de notre mask
            /*

               -1 0 1
               -1 |0|0|0|
               0  |0|0|0|
               1  |0|0|0|

               Voici comment la boucle du masque fonctionne

*/
            for(int i = -MasqueX;i <= MasqueX; i++){
                // On prend chaque Pixel
                for(int j = -MasqueY;j <= MasqueY; j++){
                    int indeX = x+i;
                    int indeY = y+j;
                    // Si l'index n'est pas compris dans l'image
                    if ( indeX < 0 || indeY < 0 || indeX >= ImaX-1 || indeY >= ImaY-1){
                        // On lui donne la valeur Zero
                        accumulator +=0;
                    }
                    accumulator += masque(i+MasqueX,j+MasqueY)*imageEntre(indeX,indeY);
                }
            }
            imageFinale(x,y) = accumulator;
        }
    }
    return imageFinale;
}


Image<double> gaussienMask(double sigma){

    int N = floor(6*sigma); // Environ 6 sigma

    // Convention si N est Paire. On va chercher la valeurs suivante
    // Modulo pour les doubles
    if((N%2)==0)
        N++;
    Image<double> masqueGaussien(N,N);
    int moitier = N/2;
    double somme = 0.0;

    for (int x = -moitier ; x <= moitier;x++){
        for(int y = -moitier ; y<= moitier;y++){
            // On remets au carre les coordonnées
            // Formule Mathématique pour le masque
            masqueGaussien(x+moitier,y+moitier) =  (exp(-(x*x + y*y)/(2.0*(sigma*sigma)))) / (M_PI*(2.0*(sigma*sigma)));
            somme += masqueGaussien(x+moitier,y+moitier);
        }
    }

    // Ensuite on Renormalisation

    for(int x=0;x<N;x++){
        for(int y=0;y<N;y++){
            masqueGaussien(x,y) /= somme;
        }
    }

    return masqueGaussien;
}

Image<uint8_t> convertionImageCond(Image<double>& imageEntree){

    int imaX = imageEntree.getDx();
    int imaY = imageEntree.getDy();
    Image<uint8_t> imageFinale(imaX, imaY);
    // On parcours notre image
    for(int x = 0; x < imaX; x++) {
      for(int y = 0; y < imaY; y++) {
        // On recupère la valeurs à la position x,y
        double sommes = imageEntree(x,y);
        // Si la Sommes est plus grand on Tronc vers le bas
        if(sommes > 255){
            sommes = 255;
        }
        // Si LS sommes est trop base on Tronc vers le haut
        else if(sommes < 0){
            sommes = 0;
        }
        // On laisse la sommes normal
        imageFinale(x,y) = (uint8_t) sommes;
      }
    }
    return imageFinale;
}

Image<uint8_t> convertionImage(Image<double>& imageEntree){

    int imaX = imageEntree.getDx();
    int imaY = imageEntree.getDy();
    Image<uint8_t> imageSortie(imaX,imaY);
    for (int x = 0 ; x < imaX; x++) {
        for (int y = 0; y < imaY; y++) {
                imageSortie(x,y) = (uint8_t) imageEntree(x,y);
            }
        }

        return imageSortie;
}

Image<uint8_t> sobelOperatorAbsolue(Image<uint8_t>& imageSobel){

    Image<uint8_t> imageSortie(imageSobel.getDx(),imageSobel.getDy());
    for (int x =0;x<imageSobel.getDx();x++){
        for(int y =0;y<imageSobel.getDy();y++){
            // Calcul la valeur absolue
            imageSortie(x,y) = abs(imageSobel(x,y) /4);
        }
    }

    return imageSortie;
}

// Prend en paramètres 2 arguements.
// Deux Images traité avec la matrice sobel et de valeur absolue normé sur 4

Image<uint8_t> sobelOperatorNorme(Image<uint8_t>& imageSobelAbsolue1,Image<uint8_t>& imageSobelAbsolue2){

    Image<uint8_t> imageSortie(imageSobelAbsolue1.getDx(),imageSobelAbsolue1.getDy());
    for (int x =0;x<imageSobelAbsolue1.getDx();x++){
        for(int y =0;y<imageSobelAbsolue1.getDy();y++){
            // sqrt Trouve la racine des valeurs
            imageSortie(x,y) = sqrt((imageSobelAbsolue1(x,y)*imageSobelAbsolue1(x,y))+(imageSobelAbsolue2(x,y)*imageSobelAbsolue2(x,y)));
        }
    }

    return imageSortie;
}
