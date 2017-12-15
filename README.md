# Rapport Daehli 

Pour lire mon rapport veuillez cliquer sur le lien suivant 

[Rapport de Daehli Nadeau-Otis](https://git.unistra.fr/nadeauotis/P4y/blob/master/TP3/src/rapportDaehli.md)

# Séance 3

Thèmes abordés :  filtres linéaires, convolution

## Convolution


La convolution discrète d'une image $`I`$ à deux dimensions par un masque ou noyau de convolution $`M`$ de taille $`N_x\times N_y`$ est définie en un point par :


```math
(I\ast M)(i,j)=\sum_{k=0}^{N_x-1} \sum_{l=0}^{N_y-1} M(k,l) I(i+k-c_x,j+l-c_y),
```

où $`(c_x,c_y)=(\lfloor{\frac{N_x}{2}\rfloor},\lfloor{\frac{N_y}{2}\rfloor})`$ sont les coordonnées du centre du masque. Le masque peut être vu comme une image dont les coordonnées $`(0,0)`$ représentent le coin supérieur gauche et $`(N_x-1,N_y-1)`$ le coin inférieur droit.

Généralement le masque est carré de taille impaire mais ce n'est pas une obligation.

Les coefficients du masque sont à valeurs réelles ; le résultat (l'image convoluée) est donc également à valeurs réelles.

### Travail à réaliser

Écrire une fonction `convolve` qui calcule la convolution d'une image à partir d'un masque passé en paramètres et qui retourne l'image convoluée. Le type du résultat sera une image de type `double`.
Les coefficients du masque pourront être stockés dans une image de type `double`.
La valeur des points situés en dehors du support de l'image sera fixée arbitrairement à 0.

## Filtres de lissage

Les filtres de lissage utilisent des masques dont les valeurs sont toutes positives.
Voici des exemples de masques de lissage :

$`
M_1=
\frac{1}{9}
\begin{bmatrix}
1 & 1 & 1\\
1 & 1 & 1\\
1 & 1 & 1
\end{bmatrix}
`$,
$`\;
M_2=
\frac{1}{16}
\begin{bmatrix}
1 & 2 & 1\\
2 & 4 & 2\\
1 & 2 & 1
\end{bmatrix}
`$



### Masque gaussien

Un masque gaussien est obtenu en discrétisant la fonction gaussienne définie en 2D par :
```math
G_\sigma(x,y)= \frac{1}{2\pi\sigma^2}  e^{{\textstyle -\frac{x^2+y^2}{2\sigma^2}}}
```

Le support (ensemble des points où la fonction est non nulle) de cette fonction est non borné, mais ses valeurs décroissent rapidement à mesure qu'on s'éloigne de l'origine (comme l'inverse de l'exponentielle du carré de la distance à l'origine !). On adopte donc la convention (standard) de l'approcher par un masque de taille $`N\times N`$ avec $`N\approx 6\sigma`$, impair. 

Dans un second temps, il est nécessaire de re-normaliser les coefficients de manière à ce que la somme des poids du masque soit égale à 1.
<!---
#### Exemple : 
- Pour $`\sigma=1`$, la taille du masque sera de $`N\times N=7\times 7`$.
- Les coefficients du masque seront calculés à partir de $`G_\sigma`$ de la manière suivante :
$`
\begin{bmatrix}
\ldots & \ldots & \ldots & \ldots & \ldots\\
\ldots & G_\sigma(-1,-1) & G_\sigma(0,-1)& G_\sigma(1,-1)& \ldots\\
\ldots &G_\sigma(-1,0) & G_\sigma(0,0) & G_\sigma(1,0)& \ldots \\
\ldots & G_\sigma(-1,1) & G_\sigma(0,1) & G_\sigma(1,1)& \ldots \\
\ldots & \ldots & \ldots & \ldots & \ldots
\end{bmatrix}
`$
- Les coefficients sont ensuite normalisés de manière à ce que leur somme soit égale à 1.--->

### Travail à réaliser

- Tester votre fonction de convolution avec les masques précalculés $`M_1`$ et $`M_2`$. 
- Écrire une fonction `gaussianMask` qui renvoie un masque gaussien pour une valeur de $`\sigma`$ passée en paramètre.   
- Expérimenter des convolutions avec des masques gaussiens pour  $`\sigma=1`$, $`\sigma=2`$, $`\sigma=1/2`$.
- Les images résultant des convolutions seront converties en images 8 bits par arrondi des valeurs. 

## Filtres de réhaussement des contours

Les filtres réhausseurs de contours utilisent des masques à coefficients positifs et négatifs dont la somme des poids vaut 1. Ainsi dans les zones homogènes de l'image les niveaux de gris ne sont pas altérés, et dans les zones de transition les contours sont renforcés. Voici des exemples de tels filtres :

$`M_3=
\begin{bmatrix}
0&-1&0\\
-1&5&-1\\
0&-1&0
\end{bmatrix}`$,
$`\;M_4=
\begin{bmatrix}
-1&-1&-1\\
-1&9&-1\\
-1&-1&-1
\end{bmatrix}`$

Les valeurs de l'image résultante peuvent sortir de l'intervalle des valeurs de l'image initiale.
Habituellement on effectue une troncature du résultat en calculant pour chaque valeur v :

$`
v=\left\{
\begin{array}{cl}
0, &  \text{si } v\leq 0  \\
v, &   \text{si }v \in [0\ldots 255]  \\
255, &  \text{si }v\geq 255 
\end{array}\right.`$

### Travail à réaliser

- Expérimenter les filtres de réhaussement des contours définis par les masques $`M_3`$ et $`M_4`$.
- Expérimenter des réhaussements de contours sur des images lissées par des filtres gaussiens pour plusieurs valeurs de $`\sigma`$.

## Filtres détecteurs d'arêtes

Les masques de Sobel horizontaux et verticaux définissent des filtres détecteurs d'arête  :

$`S_x= 
\begin{bmatrix}
-1&0&1\\
-2&0&2\\
-1&0&1
\end{bmatrix},\;`$
et 
$`S_y=\begin{bmatrix}
-1&-2&-1\\
0&0&0\\
1&2&1
\end{bmatrix}`$

Il est à noter que les valeurs de l'image résultante peuvent sortir de l'intervalle des valeurs de l'image initiale, et qu'on s'intéresse ici davantage à la *valeur absolue* de la réponse du filtre en chaque point, qu'à l'image elle même. 

Cependant si l'on souhaite visualiser le résultat dans une image 8 bits, il est nécessaire, d'une part, de calculer la valeur absolue de la réponse, d'autre part, de normaliser les valeurs par la somme des poids "positifs" (ici P=4).
Enfin, toujours à des fins de visualisation, il peut être intéressant d'étirer le contraste de l'image afin que la valeur maximale soit égale à 255.

### Travail à réaliser

- À partir de ces noyaux, écrire un programme  permettant de calculer et de stocker dans une image `uint8_t` une carte des contours par approximation de la norme (ou magnitude) du gradient.

- On souhaite maintenant calculer une "pyramide" de carte de contours. Calculer une carte de contours par la méthode précédente sur plusieurs versions lissées d'une image par un filtre gaussien avec des écarts-types $`\sigma`$ croissants.
-  Extraire les contours les plus significatifs à chaque niveau de la pyramide à l'aide d'un seuillage.
-  Dans le rapport, représenter l'image des contours extraits pour chaque valeur retenue de $`\sigma`$.

## Bonus

L'opérateur de convolution en deux dimensions peut vite devenir coûteux en temps de calcul pour des tailles élevées du masque.
Un moyen de réduire fortement les temps de calcul est d'utiliser la propriété d'associativité de la convolution.
Un masque $`M`$ est dit séparable s'il peut être décomposé en deux masques $`M_1`$ et $`M_2`$ tels que : $`M=M_1\ast M_2`$.
Comme la convolution est associative, on peut alors écrire :
```math
I\ast M=I\ast (M_1\ast M_2)=(I\ast M_1)\ast M_2
```

Par exemple un filtre moyenneur (ce qui signifie : dont tous les coefficients sont égaux et de somme 1) est séparable puisqu'on peut écrire :
```math
\frac{1}{9}
\begin{bmatrix}
1 & 1 & 1\\
1 & 1 & 1\\
1 & 1 & 1
\end{bmatrix}
=
\left(
\frac{1}{3}\begin{bmatrix}
1 \\ 
1 \\ 
1
\end{bmatrix}
\ast \frac{1}{3}
\begin{bmatrix}
1 & 1 & 1
\end{bmatrix}
\right)
```

Un filtre moyenneur par un masque 2D peut donc se décomposer en deux filtres moyenneurs par des masques 1D (plus rapides à calculer).

### Travail à réaliser

- Le masque gaussien est séparable. Écrire une fonction qui calcule un filtre gaussien pour un écart-type donné en utilisant le principe de décomposition ci-dessus. Comparer avec les résultats obtenus avec un masque 2D.
- Comparer le nombre de multiplications à effectuer :
	- pour calculer la convolution d'une image de $`N`$ pixels par un masque 2D de taille $`M\times M`$
	- pour calculer deux convolutions d'une image de $`N`$ pixels par deux masques 1D de taille $`M`$




