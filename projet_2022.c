/*                Système de locations de voiture by Sofiqqne */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définition de la structure Rental avec ses différents paramètres
typedef struct rental{ 
    int jours;
    float km;
    char nom[100];
    char immat[8];
    char plan;
    float prix;
}Rental;

// Définition de la structure Element essentiel à la liste chainée
typedef struct Element Element;
struct Element {
    Rental location;
    Element *suivant;
};

// Définition de la structure Liste 
typedef struct Liste Liste;
struct Liste {
    Element *premier;
};


// Déclaration des différentes fonctions que nous allons utiliser
// Fonction qui crée une liste chaînée
Liste *initialisation(void);

// Fonction qui ajoute la location de l'utilisateur à la liste chaînée
void insertion(Liste *liste, Rental nvLocation);

// Fonction qui demande à l'utilisateur de saisir des informations pour une location
void update_location(Liste *liste);

// Fonction supprime le première élément vide inialisé par la liste chaînée
void suppression_init(Liste *liste);

// Fonction qui supprime toute location choisi au préalable par l'utilisateur 
int delete_location(Liste *liste);

// Fonction qui affiche toute location choisi au préalable par l'utilisateur 
void show_location (Liste *liste);

// Fonction qui affiche toutes les locations enregistrées
void showall_location(Liste *liste);

// Fonction qui calcule le prix d'une location en fonction de la catégorie
float prix(Rental loc);




int main(void){
    printf("---------- Système de gestion de location de voitures ----------\n                 Sofiane Djabali\n\n");
    Liste *liste = initialisation();
    suppression_init(liste);

    // Proposer à l'utilisateur de choisir le nombre maximum de locations possibles
    int max_locations;
    int nb_locations = 0;
    printf("Combien de locations max ? >");
    scanf("%d", &max_locations);


    printf("\n");

    // Démarrage du menu proposant à l'utilisateur de choisir entre 4 catégories différentes
    int choix = 0;
    int exitprogramme = 0;
    while(exitprogramme == 0){ // Tant que la personne ne choisi pas l'option 4 (Quitter), le menu réapparaîtra
        printf("\nIl vous reste %d/%d location(s) disponible(s) !\n", max_locations - nb_locations, max_locations);
        printf(" 1 ---> Créer d'une location\n 2 ---> Supprimer une location\n 3 ---> Voir une location effectuée\n 4 ---> Voir toutes les locations\n 5 ---> Quitter le système\n>");
        scanf("%d",&choix);

        switch (choix)
        {
        case 1 :
            if (nb_locations < max_locations) {
                update_location(liste);
                nb_locations++;
            }
            else {
                printf("\n\nLocations max atteintes !\n");
            }
            break;

        case 2 :
            if (nb_locations > 0) {
                nb_locations-=delete_location(liste);
            }
            else {
                printf("\n\nAucune location à supprimer !\n");
            }
            break;
        
        case 3 :
            if (nb_locations > 0) {
                show_location(liste);
            }
            else {
                printf("\n\nAucune location à visionner !\n");
            }
            
            break;

        case 4 :
            if (nb_locations > 0) {
                showall_location(liste);
            }
            else {
                printf("\n\nAucune location à visionner !\n");
            }
            break;   
        case 5 : 
            exitprogramme = 1;
            break;
        }
    }
}


// Initialisation de la liste chaînée
Liste *initialisation(void) {
    // Allocation de la mémoire dynamique aux structures Liste et Element
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));
    if (liste == NULL || element == NULL){
        exit(EXIT_FAILURE);
    }

    Rental first;
    first.jours = 0;

    element -> location = first;
    element -> suivant = NULL;
    liste -> premier = element ;
    return liste;
}

// Définition de la fonction insertion, qui ajoute les saisis de l'utilisateur à la liste
void insertion(Liste *liste, Rental nvLocation){
    // Création d'un nouvel élement
    Element *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL){
        exit(EXIT_FAILURE);
    }

    nouveau -> location = nvLocation ;

    // Insertion de notre Element au début de la liste 
    nouveau -> suivant = liste -> premier;
    liste -> premier = nouveau ;
}    
 // Définition de la fonction prix destiné au calcul des frais de locations du client en fonction de la catégorie choisit 
float prix(Rental loc){
    float semaine = 0;
    float tranche_km  = 0;
    float km_average;
    float resultat = 0;

// Plan a
    if(loc.plan == 'a'){
        resultat = loc.jours * 25.0 + loc.km * 0.15;   
    }
// Plan b
    if(loc.plan == 'b'){
        km_average = loc.km / loc.jours;
        resultat = loc.jours * 35.0 ;
        if(km_average > 100){
            int x = loc.km - 100;
            while(x >= 100){
                x = x - 100;
                tranche_km += 1;
            }
            resultat += ((loc.km - 100) * 0.15);
            resultat +=  x * 0.10 ; 
        }
    }
// Plan c
    if(loc.plan == 'c'){
        while(loc.jours > semaine){
            resultat += 120;
            semaine += 7;
        }
        km_average = loc.km / (semaine / 7);
        if(km_average > 900){
            resultat += 60 * (semaine / 7);
        }

        if(km_average > 1500){
            resultat += 130 * (semaine / 7);
            resultat += ((loc.km - 1500) * 0.15);
        }
    }

    return resultat;
}

// Définition de la fonction update_location, qui demande à l'utilisateur de saisir les informations tel que les kilomètres parcourus, le nom du client etc... pour compléter une location
void update_location(Liste *liste){
    int i;
    Rental location;

    printf("Merci de saisir les différentes informations nécessaires :\n");
    // Kilomètres
    do{
        printf("Kilomètres parcourus : ");
        scanf("%f", &location.km);
    }while(location.km <= 0);
    
    // Nom du client
    rename :

    printf("Nom : ");
    scanf("%s", location.nom);

    int a = strlen(location.nom);
    for(i = 0; i < a ; i++){ 
        // Vérifie si pour chaque caractère dans le tableau si il est une lettre (en vérifiant si il est présent dans le code ascii)
        if((location.nom[i] < 65 || location.nom[i] > 90) && (location.nom[i] < 97 || location.nom[i] > 122)){
            printf("Erreur, il ne s'agit pas d'un nom\n");
            goto rename;
        }
    }


    // Nombres de jours de location
    do{
        printf("Durée de la location (en jours) : ");
        scanf("%d", &location.jours);
    }while(location.jours <= 0);

    // Numéro immatriculation
    re_immat :

    printf("Numéro d'immatriculation : ");
    scanf("%s", location.immat);

    for(i = 0; i < 3; i++){
        // Vérifie pour chaque caractère jusqu'à la 3ème cellule si c'est une lettre
        if((location.immat[i] < 65 || location.immat[i] > 90) && (location.immat[i] < 97 || location.immat[i] > 122)){
            printf("Erreur, veuillez rentrer un numéro d'immatriculation valide (ex : ABC1234)\n");
        goto re_immat;
        }
    }

    for(i = 3; i < 7; i++){
        // Vérifie pour chaque caractère à partir de la 4ème cellule du tableau si c'est un chiffre
        if(location.immat[i] < 48 || location.immat[i] > 57){
            printf("Erreur, veuillez rentrer un numéro d'immatriculation valide (ex : ABC1234)\n");
        goto re_immat;
        }

    }

    // Catégories
    re_plan :

    printf("Catégorie de facturation : ");
    scanf("%1s", &location.plan);

    // Vérifie si la lettre rentré correspond à un plan existant
    if(location.plan != 'a' && location.plan != 'b' && location.plan != 'c'){
        printf("Erreur, veuillez rentrer une catégorie de facturation existante (ex : a, b ou c)\n");
        goto re_plan;
    }

    location.prix = prix(location);    
    insertion(liste, location);
}

// Définition de la fonction suppression_init, qui supprime le première élément que la liste inilialise automatiquement
void suppression_init(Liste *liste) {
    if (liste == NULL) {
        exit( EXIT_FAILURE );
    }
    if (liste -> premier != NULL) {
        Element * aSupprimer = liste -> premier ;
        liste -> premier = liste ->premier -> suivant ;
        free( aSupprimer );
    }
}

// Définition de la fonction delete_location, qui supprime les locations souhaitées par l'utilisateur
int delete_location(Liste *liste){
    // Déclaration des différentes variables essentielles 
    char nom_cherche[100];
    char immat_cherche[100];
    char nomx[100];
    char immatx[100];
    int i,j;
    int star_nom, star_immat;
    int loc_suppr = 0;

    // Proposition de saisie
    printf("Veuillez entrer le nom du client : ");
    scanf("%s", nom_cherche);
    printf("Veuillez entrer l'immatriculation : ");
    scanf("%s", immat_cherche);

    j = 0;
    star_nom = 0;
    // Boucle qui lorsqu'elle détecte la présention du caratère '*' dans la saise du nom, le supprimera de la saisie afin de pouvoir parcourir la liste et chercher ce qui est demandée
    for (i = 0; i < 100; i++){
        if (nom_cherche[i] != '*'){
            nomx[j] = nom_cherche[i];
            j++;
        }
        else{
            star_nom = 1;
        }
    }
    // Boucle qui lorsqu'elle détecte la présention du caratère '*' dans la saise du numéro d'immatriculation, le supprimera de la saisie afin de pouvoir parcourir la liste et chercher ce qui est demandée
    j = 0;
    star_immat = 0;
    for (i = 0; i < 100; i++){
        if (immat_cherche[i] != '*'){
            immatx[j] = immat_cherche[i];
            j++;
        }
        else{
            star_immat = 1;
        }
    }



    Element * actuel = liste -> premier ;
    Element * precedent = NULL;

    //Tant qu'il y a quelque chose dans Actuel, on compare la saisie de l'utilisateur à ce qui est déjà présent dans les locations
    while (actuel != NULL){
        // Nom demandé == nom de location && immat demandé == immat de location
        if(strcmp(actuel -> location.nom, nomx) == 0 && strcmp(actuel -> location.immat, immatx) == 0){
            if(precedent == NULL) { // Si la saisie de l'utilisateur et ce qui est déja présent est la même, on supprime la location en question
                liste -> premier = actuel -> suivant;
                free(actuel);
                actuel = liste -> premier;
                loc_suppr++;
            }
            else {
                precedent -> suivant = actuel -> suivant;
                free(actuel);
                actuel = precedent -> suivant;
            }
        }
        // On compare toujours la saisie de l'utilisateur à ce qui est déjà présent dans les locations en prenant en compte que si '*' est ajouté à la saisie, on supprime toutes les locations contenant ce nom
        // Nom demandé == nom de location && une étoile accompagne le nom
        else if(strcmp(actuel -> location.nom, nomx) == 0 && star_nom == 1){
            if(precedent == NULL) {
                liste -> premier = actuel -> suivant;
                free(actuel);
                actuel = liste -> premier;
                loc_suppr++;
            }
            else {
                precedent -> suivant = actuel -> suivant;
                free(actuel);
                actuel = precedent -> suivant;
            }
        }
        // On compare toujours la saisie de l'utilisateur à ce qui est déjà présent dans les locations en prenant en compte que si '*' est ajouté à la saisie, on supprime toutes les locations contenant ce numéro d'immatriculation
        //immat demandé == immat de location && une étoile accompagne l'immat
        else if(strcmp(actuel -> location.immat, immatx) == 0 && star_immat == 1){
            if(precedent == NULL) {
                liste -> premier = actuel -> suivant;
                free(actuel);
                actuel = liste -> premier;
                loc_suppr++;
            }
            else {
                precedent -> suivant = actuel -> suivant;
                free(actuel);
                actuel = precedent -> suivant;
            }
        }

        else{
            precedent = actuel;
            actuel = actuel -> suivant;
        }
    }
    return loc_suppr;   
}


// Définition de la fonction delete_location, qui supprimera les locations souhaitées par l'utilisateur
void show_location (Liste *liste){
    // Déclaration des différentes variables essentielles 
    float sommetotale = 0;
    char nom_cherche[100];
    char immat_cherche[100];
    char nomx[100];
    char immatx[100];
    int i,j;
    int star_nom, star_immat;

    printf("Veuillez entrer le nom du client : ");
    scanf("%s", nom_cherche);
    printf("Veuillez entrer l'immatriculation : ");
    scanf("%s", immat_cherche);

    j = 0;
    star_nom = 0;
    // Boucle qui lorsqu'elle détecte la présention du caratère '*' dans la saise du nom, le supprimera du la saisie afin de pouvoir parcourir la liste et chercher ce qui est demandée
    for (i = 0; i < 100; i++){
        if (nom_cherche[i] != '*'){
            nomx[j] = nom_cherche[i];
            j++;
        }
        else{
            star_nom = 1;
        }
    }

    j = 0;
    star_immat = 0;
    // Boucle qui lorsqu'elle détecte la présention du caratère '*' dans la saise du numéro d'immatriculation, le supprimera de la saisie afin de pouvoir parcourir la liste et chercher ce qui est demandée
    for (i = 0; i < 100; i++){
        if (immat_cherche[i] != '*'){
            immatx[j] = immat_cherche[i];
            j++;
        }
        else{
            star_immat = 1;
        }
    }



    Element * actuel = liste -> premier ;
     //Tant qu'il y a quelque chose dans Actuel, on compare la saisie de l'utilisateur à ce qui est déjà présent dans les locations
     while (actuel != NULL){
        if(strcmp(actuel -> location.nom, nomx) == 0 && strcmp(actuel -> location.immat, immatx) == 0){
            printf("-------------------------------\n");
            printf("           %s\n", actuel -> location.nom);
            printf("Véhicule immatriculé : %s\n", actuel -> location.immat);
            printf("Catégorie %c\n", actuel -> location.plan);
            printf("Durée de la location : %d\n", actuel -> location.jours);
            printf("Kilomètres : %.2f\n", actuel -> location.km);
            printf("Prix TTC : %.2f €\n", actuel -> location.prix);
            printf("-------------------------------\n");
            printf("\n");
            sommetotale += actuel -> location.prix;
        }
        // On compare tojours la saisie de l'utilisateur à ce qui est déjà présent dans les locations en prenant en compte que si '*' est ajouté à la saisie, on affiche toutes les locations contenant ce nom
        else if(strcmp(actuel -> location.nom, nomx) == 0 && star_nom == 1){
            printf("-------------------------------\n");
            printf("           %s\n", actuel -> location.nom);
            printf("Véhicule immatriculé : %s\n", actuel -> location.immat);
            printf("Catégorie %c\n", actuel -> location.plan);
            printf("Durée de la location : %d\n", actuel -> location.jours);
            printf("Kilomètres : %.2f\n", actuel -> location.km);
            printf("Prix TTC : %.2f €\n", actuel -> location.prix);
            printf("-------------------------------\n");
            printf("\n");
            sommetotale += actuel -> location.prix;
        }

        // On compare tojours la saisie de l'utilisateur à ce qui est déjà présent dans les locations en prenant en compte que si '*' est ajouté à la saisie, on affiche toutes les locations contenant ce numéro d'immatriculation
        else if(strcmp(actuel -> location.immat, immatx) == 0 && star_immat == 1){
            printf("-------------------------------\n");
            printf("           %s\n", actuel -> location.nom);
            printf("Véhicule immatriculé : %s\n", actuel -> location.immat);
            printf("Catégorie %c\n", actuel -> location.plan);
            printf("Durée de la location : %d\n", actuel -> location.jours);
            printf("Kilomètres : %.2f\n", actuel -> location.km);
            printf("Prix TTC : %.2f €\n", actuel -> location.prix);
            printf("-------------------------------\n");
            printf("\n");
            sommetotale += actuel -> location.prix;
        }
        actuel = actuel -> suivant;
     }
     printf("Somme totale dû : %.2f €\n", sommetotale);   
}

void showall_location(Liste *liste){
    float sommetotale = 0;
    if (liste == NULL) {
        exit(EXIT_FAILURE);
    }

    Element * actuel = liste -> premier ;

    while (actuel != NULL) {
        printf("-------------------------------\n");
        printf("           %s\n", actuel -> location.nom);
        printf("Véhicule immatriculé : %s\n", actuel -> location.immat);
        printf("Catégorie %c\n", actuel -> location.plan);
        printf("Durée de la location : %d\n", actuel -> location.jours);
        printf("Kilomètres : %.2f\n", actuel -> location.km);
        printf("Prix TTC : %.2f €\n", actuel -> location.prix);
        printf("-------------------------------\n");
        printf("\n");
        sommetotale += actuel -> location.prix;
        actuel = actuel -> suivant;
    }
    
    printf("Somme totale dû : %.2f €\n", sommetotale);
}
