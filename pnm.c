/**
 * pnm.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de manipulation d'images PNM.
 * 
 * @author: Russe Cyril s170220
 * @date: 27-02-2020
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
//enum Type_PNM_t{PBM, PGM, PPM};

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
   unsigned int ***valeurs_pixel;
};


int load_pnm(PNM **image, char* filename) {
   Type_PNM type_image;
   Dimension_pixel dimension;
   unsigned int valeur_max;


   if (filename==NULL)
      return -2;

   FILE* fichier = fopen(filename, "r");
   if (fichier==NULL)
      return -2;

   //Vérifications format
   if (verification_type_image(&type_image, fichier)==-1)
      return -3;
   if (verification_extension_fichier(type_image, filename)==-1)
      return -2;

   //enregistrement dimensions
   if(enregistrement_dimension_image(&dimension, fichier)==-1)
      return -3;

   //enregistrement valeur max
   if(type_image==PGM || type_image==PPM){
      if(enregistrement_valeur_max(&valeur_max, fichier)==-1)
         return -3;
   }


   *image = constructeur_PNM(dimension, type_image, valeur_max, fichier);
   if (*image==NULL)
      return -1;

   return 0;
}

PNM *constructeur_PNM(Dimension_pixel dimensions, Type_PNM format, unsigned int valeur_max, FILE *fichier){
   int i, j, nbr_valeur_ppm=0;
   char stockage_valeur_fichier[100];

   //malloc la matrice et chaque élément de celle-ci
   PNM *image = malloc(sizeof(PNM));
   if (image==NULL)
      return NULL;

   image->valeurs_pixel = malloc(dimensions.nbr_ligne * sizeof(unsigned int**));
   if(image->valeurs_pixel==NULL){
      free(image);
      return NULL;
   }

   for(i=0; i<dimensions.nbr_ligne; i++){
      image->valeurs_pixel[i] = malloc(dimensions.nbr_colonne * sizeof(unsigned int*));
      if (image->valeurs_pixel[i]==NULL){
         for(i--; i>=0; i--){//free reste du tableau avant la ligne n'ayant pu être malloc
            for(j=0; j<dimensions.nbr_colonne; j++)
               free(image->valeurs_pixel[i][j]);
            free(image->valeurs_pixel[i]);
         }
         free(image->valeurs_pixel);
         free(image);
         return NULL;
      }
      else{
         for(j=0; j<dimensions.nbr_colonne; j++){
            if(image->format==PPM)
               image->valeurs_pixel[i][j] = malloc(3 * sizeof(unsigned int));
            else
               image->valeurs_pixel[i][j] = malloc(sizeof(unsigned int));

            if(image->valeurs_pixel[i][j]==NULL){
               for(j--; j>=0; j--)//free éléments de la colonne avant l'élément n'ayant pu être malloc
                  free(image->valeurs_pixel[i][j]);
               free(image->valeurs_pixel[i]);

               for(i--;i>=0; i--){//free reste du tableau avant la colonne dans laquelle un élément n'a pu être malloc
                  for(j=0; j<dimensions.nbr_colonne; j++)
                     free(image->valeurs_pixel[i][j]);
                  free(image->valeurs_pixel[i]);
               }
            free(image->valeurs_pixel);
            free(image);
            return NULL;
            }
         }
      }

   }

   //initialisation des valeurs de l'image

   image->dimension.nbr_ligne = dimensions.nbr_ligne;
   image->dimension.nbr_colonne = dimensions.nbr_colonne;
   image->format = format;
   if(image->format == PBM)
      image->valeur_max = 1;
   else
      image->valeur_max = valeur_max;

   if(image->format==PBM || image->format==PGM){
      for(i=0; i<dimensions.nbr_ligne; i++){
         for (j=0; j<dimensions.nbr_colonne;){
            fscanf(fichier, "%s", stockage_valeur_fichier);
            if(stockage_valeur_fichier[0]!='#'){
               image->valeurs_pixel[i][j][0] = atoi(stockage_valeur_fichier);
               if(atoi(stockage_valeur_fichier) > (int)image->valeur_max){
                  libere_PNM(image);
                  return NULL;
               }
               j++;
            }
            else
               fscanf(fichier, "%*[^\n]");
         }
      }
   }
   else{
      for(i=0; i<dimensions.nbr_ligne; i++){
         for (j=0; j<dimensions.nbr_colonne;){
            fscanf(fichier, "%s", stockage_valeur_fichier);
            if(stockage_valeur_fichier[0]!='#'){
               image->valeurs_pixel[i][j][nbr_valeur_ppm] = atoi(stockage_valeur_fichier);
               if(atoi(stockage_valeur_fichier) > (int)image->valeur_max){
                  libere_PNM(image);
                  return NULL;
               }
               if(nbr_valeur_ppm==2)
                  j++;
               nbr_valeur_ppm++;
               nbr_valeur_ppm%=3;
            }
            else
               fscanf(fichier, "%*[^\n]");
         }
      }
   }
   fclose(fichier);

   return image;
}

void libere_PNM(PNM *image){
   if(image==NULL)
      return;
   for(int i=0; i<image->dimension.nbr_ligne; i++){
      for(int j=0; j<image->dimension.nbr_colonne; j++)
         free(image->valeurs_pixel[i][j]);
      free(image->valeurs_pixel[i]);
   }
   free(image->valeurs_pixel);
   free(image);
}

int enregistrement_valeur_max(unsigned int *valeur_max, FILE  *fichier){
   char contenu_fichier[100];
   int nbr_fscanf = 0;
   do{
      if(contenu_fichier[0]!='#'){
         nbr_fscanf = fscanf(fichier, "%s[^\n]", contenu_fichier);
         if (atoi(contenu_fichier)<=255 && atoi(contenu_fichier)>=0){
            *valeur_max = atoi(contenu_fichier);
            return 0;
         }
         else
            return -1;
      }
      else
         fscanf(fichier, "%*[^\n]");
      
   }while(nbr_fscanf>0);

   return -1;
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
            return 0;
         }
      }
   }while(nbr_fscanf>0);
   
   return -1;
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
   FILE *fichier;

   if(image==NULL)
      return -2;

   if(verification_extension_fichier(image->format, filename)==-1)
      return -1;
   
   if(verification_char_interdit_filename(filename)==-1)
      return -1;

   fichier = fopen(filename, "w");
   if (fichier==NULL)
      return -2;
   
   if(ecriture_en_tete_PNM(image, fichier)==-1){
      fclose(fichier);
      return -2;
   }

   if(ecriture_image(image, fichier)==-1){
      fclose(fichier);
      return -2;
   }
   
   
   fclose(fichier);
   
   return 0;
}

int ecriture_image(PNM *image, FILE *fichier){
    for(int i=0; i<image->dimension.nbr_ligne; i++){
      for(int j=0; j<image->dimension.nbr_colonne; j++){
         if(image->format==PPM){
            for(int x=0; x<3; x++)
               fprintf(fichier, "%u ", image->valeurs_pixel[i][j][x]);
         }
         else
            fprintf(fichier, "%u ", image->valeurs_pixel[i][j][0]);
      }
      fprintf(fichier, "\n");
   }
   return 0;
}

int verification_char_interdit_filename(char *filename){
   char caractere=1;
   int i=0;
   while(caractere!='\0'){
      caractere=filename[i];
      if(caractere=='/' || caractere==92 || caractere==':' || caractere=='*' || caractere=='?' || caractere=='"' || caractere=='<' || caractere=='>' || caractere=='|')
         return -1;
      i++;
   }
   return 0;
}

int ecriture_en_tete_PNM(PNM *image, FILE *fichier){
   switch (image->format)
   {
   case PBM:
      fprintf(fichier, "P1\n");
      break;
   case PGM:
      fprintf(fichier, "P2\n");
      break;
   case PPM:
      fprintf(fichier, "P3\n");
      break;
   default:
      return -1;
   }

   fprintf(fichier, "%d %d\n", image->dimension.nbr_ligne, image->dimension.nbr_colonne);

   if(image->format!=PBM)
      fprintf(fichier, "%d\n", image->valeur_max);

   return 0;

}



