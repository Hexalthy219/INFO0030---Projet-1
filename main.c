/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Russe Cyril s170220
 * @date: 27-02-2020
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "pnm.h"


int main(int argc, char *argv[]) {

   /* options :
   *  -h -> help
   *  -f 
   */
   char *optstring = "hf:";
   int val;
   PNM *image;
   char *filename, *format;

   while((val=getopt(argc, argv, optstring))!=EOF){
      switch(val){
         case'h':
            printf("help\n");break;
         case 'f':
            filename = optarg;break;
      }
   }

   printf("%s\n",filename);

   int retour_chargement = load_pnm(&image, filename);//exemples_images/arcenciel.ppm
   printf("retour chargement : %d\n", retour_chargement);

   retour_chargement = write_pnm(image, "test.pbm");
   printf("retour chargement : %d\n", retour_chargement);

   libere_PNM(image);
   return 0;
}

