/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Russe Cyril s170220
 * @date: 20-02-2020
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
   *  
   */
   char *optstring = "h";
   PNM *image;


   int retour_chargement = load_pnm(image, "exemples_images/washington.pbm");
   printf("retour chargement : %d\n", retour_chargement);
   

   return 0;
}

