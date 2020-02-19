/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: Russe Cyril s170220
 * @date: 19-02-2020
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pnm.h"


/**
 * Définition du type opaque PNM
 *
 */
struct PNM_t {
   char *nombre_magique;
   unsigned int valeur_max;
   unsigned int **image;
};


int load_pnm(/*PNM **image,*/ char* filename) {
   int type_image;


   if (filename==NULL)
      return -2;
   //if (image==NULL)
   //   return -3;



   FILE* fichier = fopen(filename, "r");
   if (fichier==NULL)
      return -3;
   type_image = verification_type_image(fichier);

   printf("type fichier : %d\n", type_image);

   return 0;
}


int verification_type_image(FILE*  fichier){

   unsigned int numero_ligne = 0;
   char type_image[100];
   int nbr_fscanf = 0;

   do{
      if (type_image[0]=='#')
         nbr_fscanf = fscanf(fichier, "%*[^\n]");
      
      nbr_fscanf= fscanf(fichier, "%s[^\n]", type_image);
         
      if (type_image[0]!='#'){
         numero_ligne++;
         if (type_image[0]!='P')
            return -1;
         if (type_image[1]=='1')
            return 1;
         else if (type_image[1]=='2')
            return 2;
         else if (type_image[1]=='3')
            return 3;
         else 
            return -1;
      }

   }while(numero_ligne==0 && nbr_fscanf>0);
   return -1;
}

int write_pnm(PNM *image, char* filename) {

   /* Insérez le code ici */

   return 0;
}

