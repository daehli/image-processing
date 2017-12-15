# TP3 : Filtres linéaires & Convoltion

 Réaliser par:

**Daehli Nadeau-Otis**

# Introduction

Dans ce TP, nous allons appliquer différents filtres sur des images en niveau de gris. Les filtres abordés seront le filtre de lissage, filtre de réhaussement des contours et le filtre détecteur d'arêtes (Sobel).

## Organisation du Repo

Chacun des filtres sera transformé en exécutable. Les instructions de compilation et d'exécution se trouvent au début du fichier.  

* [mainConvolution.cpp](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/mainConvolution.cpp#L2-5)
* [mainSobel.cpp](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/mainSobel.cpp#L4-7)

J'ai aussi réalisé un petit script qui permet de convertir toutes les images PGM en PNG. Ensuite, le script supprime toutes les images avec l'extension `.pgm` Le script ce trouve dans le dossier `/images` et ce nomme [`convert.sh`](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/images/convert.sh#L2-7).


## Convolution

La fonction de convolution transforme une image initiale avec un masque en une nouvelle image. Le principe de la convolution est d’itérer à travers toutes les [rangées et colonne de l'image initiale (pixel).](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/bas_niveau.hpp#L212-217) Ensuite, on applique un [filtre sur tout les pixels](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/bas_niveau.hpp#L221-234) de l'image à transformer.

## Filtres de lissage

Le filtre de lissage permet de réduire les détails d'une image. Comme son nom l'indique, elle lisse l'image. Premièrement nous allons tester, notre fonction sur un filtre [`M1`](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/mainConvolution.cpp#L32-36). Ce filtre devrait lisser l'image uniformément.

Identité | M1 | M2 |
---  | ---  | ---  |
![alt text][boatMatrice] |  ![alt text][boatM1]|  ![alt text][boatM2] |

L'image identité est une convolution avec une matrice identité. Il n'a donc aucun changement avec l'image initiale. Si nous comparons les images `M1` et `M2`, nous pouvons voir que l'image devient de plus en plus floue. Les intensités de gris sont réduites.

## Masque gaussien

Le masque gaussien permet de créer un filtre. Il est paramétré par l’argument `sigma`. Plus le paramètre est élevé (maximum 7), plus l'image devient floue.

`sigma` 0.5 | `sigma` 1 | `sigma`2 |
---  | ---  | ---  |
![alt text][boatGaussSigmaDemi] |  ![alt text][boatGaussSigma1]|  ![alt text][boatGaussSigma2] |


`sigma` 3 | `sigma` 4 | `sigma`7 |
---  | ---  | ---  |
![alt text][boatGaussSigma3] |  ![alt text][boatGaussSigma4]|  ![alt text][boatGaussSigma7] |

Plus `sigma` est élevé, plus les valeurs de la matrice à ces extrémités seront grand par rapport à sa valeur centrale. De ce fait, l'image devient plus floue à mesure que le `sigma` augmente.


## Filtres de réhaussement des contours

Ce filtre permet de mettre les contours en évidence. Les endroits qui sont [supérieur à 255](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/bas_niveau.hpp#L294-303) seront tronqués à 255. Les endroits [inférieurs à 0](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/bas_niveau.hpp#L294-303) seront tronqués vers le haut à 0.

`M3` | `M4`
---  | ---  
![alt text][boatM3] |  ![alt text][boatM4]

Le filtre `M4` met les contours trop en évidence, nous avons l'impression que l'image contient des artéfacts. Pour permettre le plein potentiel au filtre M4, nous pourrions l'utiliser avec un filtre gaussien. Regardons les résultats avec un filtre gaussien sur `M3` et `M4`.

`M3` | `Sigma 2` | `Sigma 3` | `Sigma 7`
---  | ---  |  --- | --- |
Résultat: | ![alt text][boatGaussSigma2M3] |  ![alt text][boatGaussSigma3M3] | ![alt text][boatGaussSigma7M3]

`M4` | `Sigma 2` | `Sigma 3` | `Sigma 7`
---  | ---  |  --- | --- |
Résultat: | ![alt text][boatGaussSigma2M4] |  ![alt text][boatGaussSigma3M4] | ![alt text][boatGaussSigma7M4]


Les images restent très floues, sauf que les contours sont plus apparents et mieux définis. Dû au filtre de `sigma`, le bruit présent sur le filtre `M4` a pratiquement disparu.

## Filtres détecteurs d'arêtes

Les filtres détecteurs d'arêtes sont convoqués avec 2 matrices. Une matrice [horizontal](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/mainSobel.cpp#L32-37) et une autre matrice [vertical](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/mainSobel.cpp#L38-43). Par la suite, on doit récupérer la valeur absolue de chaque pixel sur l'image convoluée. Ensuite, on [normalise](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/bas_niveau.hpp#L335-350) les matrices et on fait convolué les matrices sortantes entre elles pour obtenir une superposition des images.


`Sobel` X | `Sobel` Y | `Sobel` Comp
---  | ---  |  --- |
![alt text][boatSobelX] | ![alt text][boatSobelY] |  ![alt text][boatSobelXY]

Mon algorithme a une erreur puisque mon `sobel`  de X et Y sont les mêmes. Mon `sobel` de Y aurait dû détecté les lignes verticales au lieu des lignes horizontales. J'ai décidé de superposer mes deux images pour voir le résultat. J'étais seulement curieux.  

## Conclusion

Les trois types de filtres nous ont permis de manipuler des images et d'obtenir des résultats différents à chaque fois.

##### Filtre de lissage
Ces filtres permettent de flouer une image. Elle lisse les détails et uniformise les couleurs de l'image initiale.

##### Masque gaussien
Ce filtre permet aussi de flouer des images, sauf que celui-ci est paramétré par un argument `sigma`. Plus `sigma` est élevé ,plus l'image est flouée et plus `sigma` est petit, moins l'image sera flouée.

##### Filtres de réhaussement des contours

Ce filtre altère les niveaux de gris lorsque l'image change d'intensité de gris. Elle permet de mettre en évidence les contours d'une image.

##### Filtres détecteurs d'arêtes
Ce filtre ressemble au filtre de réhaussement des contours, mais au lieu de détecter l'intensité des niveaux de gris, il est l'interpolation de 2 filtres qui détecte des lignes horizontale et verticale dans une image.


## Perspective

Il aurait été intéressant de connaitre pourquoi il se forme un encadré noir autour d'une photo, lorsque `sigma` augmente. Il aurait été aussi intéressant de vérifier mon algorithme de filtres détecteurs d'arêtes puisque celui-ci me retour le même filtre sur 2 masques différents.



[boatM1]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatM1.png
[boatM2]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatM2.png
[boatM2]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatM2.png
[boatM3]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatM3.png
[boatM4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatM4.png
[boatMatrice]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatMatrice.png
[boatGaussSigma1]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma1.png
[boatGaussSigma2]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma2.png
[boatGaussSigma3]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma3.png
[boatGaussSigma4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma4.png
[boatGaussSigma7]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma7.png
[boatGaussSigmaDemi]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigmaDemi.png
[boatGaussSigma2M3]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma2M3.png
[boatGaussSigma3M3]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma3M3.png
[boatGaussSigma7M3]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma7M3.png
[boatGaussSigma2M4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma2M3.png
[boatGaussSigma3M4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma3M3.png
[boatGaussSigma7M4]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatGaussSigma7M3.png
[boatSobelX]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatSobelX.png
[boatSobelY]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatSobelY.png
[boatSobelXY]: https://git.unistra.fr/nadeauotis/P4y/raw/master/TP3/images/boatSobelYX.png
