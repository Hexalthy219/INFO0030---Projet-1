/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * @author: Russe Cyril s170220
 * @date: 20-02-2020
 * @projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * Déclaration de l'énumération reprenenat les différents type de fichier PNM
 * 
 */
typedef enum Type_PNM_t Type_PNM;

/**
 * Déclaration de la struct Format_Image
 * 
 */
typedef struct Dimension_pixel_t Dimension_pixel;

/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * enregistrement_dimension_image
 * 
 * enregistre dans la variable dimension, les dimensions de l'image contenues dans fichier
 * 
 * @param Dimension_pixel un pointeur sur Dimension_pixel auquel écrire les dimensions
 *                        de l'image PNM
 * @param fichier un pointeur sur FILE permettant d'en lire le contenu
 * 
 * @return:
 *       0 dimensions enregistrées avec succès dans la variable dimension
 *      -1 échec de la lecture des dimensions de l'image
 * 
 */
int enregistrement_dimension_image(Dimension_pixel *dimension, FILE *fichier);

/**
 * verification_type_image
 * 
 * lis le fichier PNM et en detecte le type
 * 
 * @param fichier un pointeur sur un fichier de type FILE
 * 
 * @pre: \
 * @post: \
 * 
 * @return:
 *       PBM
 *       PGM
 *       PPM
 *      -1  Numéro magique malformé / inexistant
 * 
 */
int verification_type_image(Type_PNM *type, FILE*  fichier);

/**
 * verification_extension_fichier
 * 
 * vérifie si l'extension du fichier dans le nom de celui-ci correspond au type de type_image déduit du nombre magique
 * 
 * @param type_image enum contenant le type de l'image de type Type_PNM
 * @param filename une chaine de caractère contenant le nom du fichier
 * 
 * @return  
 *       0 succès de la vérification
 *      -1 échec de la vérification
 * 
 */ 
int verification_extension_fichier(Type_PNM type_image, char *filename);

/**
 * Type_PNM_vers_chaine
 * 
 * revoit une chaine de caractère correspondant aux différents éléments de l'énumération "Type_PNM"
 * 
 * @param type_image une variable de type Type_PNM
 * 
 */
char *Type_PNM_vers_chaine(Type_PNM type_image);

/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succès
 *    -1 Nom du fichier malformé
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char* filename);

#endif // __PNM__

