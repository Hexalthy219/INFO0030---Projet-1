/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: Russe Cyril s170220
 * @date: 20-02-2020
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pnm.h"


/**
 * Définition de l'énumération Type_PNM
 * 
 */
enum Type_PNM_t{PBM, PGM, PPM};

/**
 * Définition de la struct Dimension_pixel
 * 
 */
struct Dimension_pixel_t{
   int nbr_ligne;
   int nbr_colonne;
};

/**
 * Définition du type opaque PNM
 *
 */
struct PNM_t {
   Type_PNM format;
   Dimension_pixel dimension;
   unsigned int valeur_max;
   unsigned int **image;
};


int load_pnm(PNM **image, char* filename) {
   Type_PNM type_image;
   Dimension_pixel dimension;


   if (filename==NULL)
      return -2;
   //if (image==NULL)
     // return -3;

   FILE* fichier = fopen(filename, "r");
   if (fichier==NULL)
      return -2;

   if (verification_type_image(&type_image, fichier)==-1)
      return -3;
   if (verification_extension_fichier(type_image, filename)==-1)
      return -2;

   if(enregistrement_dimension_image(&dimension, fichier)==-1)
      return -3;

   return 0;
}

int enregistrement_dimension_image(Dimension_pixel *dimension, FILE *fichier){
   unsigned int n = 0;
   char contenu_fichier[100];
   int nbr_fscanf = 0; 
   do{
      if (contenu_fichier[0]=='#')
         nbr_fscanf = fscanf(fichier, "%*[^\n]");
      
      nbr_fscanf = fscanf(fichier, "%s[^\n]", contenu_fichier);
      if (contenu_fichier[0]!='#'){
         n++;
         if(n==1){
            dimension->nbr_ligne = atoi(contenu_fichier);
            if (dimension->nbr_ligne == 0)
               return -1;
         }
         else if(n==2){
            dimension->nbr_colonne = atoi(contenu_fichier);
            if (dimension->nbr_colonne == 0)
               return -1;
         }
      }
   }while(nbr_fscanf>0 && n!=2);
   
   return 0;
}

int verification_type_image(Type_PNM *type, FILE*  fichier){

   unsigned int numero_ligne = 0;
   char contenu_fichier[100];
   int nbr_fscanf = 0;

   do{
      if (contenu_fichier[0]=='#')
         nbr_fscanf = fscanf(fichier, "%*[^\n]");
      
      nbr_fscanf = fscanf(fichier, "%s[^\n]", contenu_fichier);
         
      if (contenu_fichier[0]!='#'){
         numero_ligne++;
         if (contenu_fichier[0]!='P')
            return -1;
         if (contenu_fichier[1]=='1'){
            *type =  PBM;
            return 0;
         }
         else if (contenu_fichier[1]=='2'){
            *type = PGM;
            return 0;
         }
         else if (contenu_fichier[1]=='3'){
            *type = PPM;
            return 0;
         }
         else 
            return -1;
      }

   }while(numero_ligne==0 && nbr_fscanf>0);
   return -1;
}

int verification_extension_fichier(Type_PNM type_image, char *filename){
   int taille_nom=0;

   while(filename[taille_nom]!='\0')
      taille_nom++;

   switch (type_image){
      case PBM: 
         if (filename[taille_nom-4]=='.' && filename[taille_nom-3]=='p' && filename[taille_nom-2]=='b' && filename[taille_nom-1]=='m')
            return 0;
         break;
      case PGM:
         if (filename[taille_nom-4]=='.' && filename[taille_nom-3]=='p' && filename[taille_nom-2]=='g' && filename[taille_nom-1]=='m')
            return 0;
         break;
      case PPM:
         if (filename[taille_nom-4]=='.' && filename[taille_nom-3]=='p' && filename[taille_nom-2]=='p' && filename[taille_nom-1]=='m')
            return 0;
         break;
      default: return -1;
   }
   return -1;
}

char *Type_PNM_vers_chaine(Type_PNM image){
   switch (image){
      case PBM:   return "PBM";
      case PGM:   return "PGM";
      case PPM:   return "PPM";
      default:    return "inconnu";
   }
}

int write_pnm(PNM *image, char* filename) {

   /* Insérez le code ici */

   return 0;
}

