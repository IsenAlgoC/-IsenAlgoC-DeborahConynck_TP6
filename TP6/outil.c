#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom : Conynck                    Prénom :  Deborah                   */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/


int ajouter_un_contact_dans_rep(Repertoire* rep, Enregistrement enr)
{
#ifdef IMPL_TAB

	//int idx;

	if (rep->nb_elts < MAX_ENREG)
	{
		rep->tab[rep->nb_elts] = enr;
		rep->nb_elts++;
		modif = true;
		return(OK);
	}
	else {
		return(ERROR);
	}

#else 
#ifdef IMPL_LIST
	SingleLinkedElem* ajout = rep->liste->head;
	taille = rep->liste->size;
	for (i = 0; i < taille; i++) {
		if (strcmp(nom, ajout->pers.nom) == 0) {
			trouve = true;
			break;

		}
		ajout = ajout->next;
#endif
#endif

		return(OK);

	} /* fin ajout */
	  /**********************************************************************/
	  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
	  /*   paramètre       et place modif = true                            */
	  /**********************************************************************/
#ifdef IMPL_TAB
	void supprimer_un_contact_dans_rep(Repertoire * rep, int indice) {

		// compléter code ici pour tableau
		if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
		{
			if (indice < rep->nb_elts) {/* et que l'indice pointe a l'interieur */
				for (int i = indice; i < rep->nb_elts; i++) {
					rep->tab[i] = rep->tab[i + 1];
				}
			}

			rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
			modif = true;
		}

		return;
	} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire * rep, SingleLinkedListElem * elem) {

		int ret = DeleteLinkedListElem(rep->liste, elem);
		if (ret == 1) {
			rep->nb_elts--;
			modif = true;
		}

		return (0);
	}
#endif
#endif


	/**********************************************************************/
	/*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
	/* ex Dupont, Jean                 0320304050                         */
	/**********************************************************************/
	void affichage_enreg(Enregistrement enr)
	{
		printf("%s, %s,			     %s\n", enr.nom, enr.prenom, enr.tel);


	} /* fin affichage_enreg */
	  /**********************************************************************/
	  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
	  /* pour les listes                                                    */
	  /* ex | Dupont                |Jean                  |0320304050      */
	  /**********************************************************************/
	void affichage_enreg_frmt(Enregistrement enr)
	{
		// code à compléter ici
		// comme fonction affichage_enreg, mais avec présentation alignées des infos
		printf("|%s,		|%s,		|%s\n", enr.nom, enr.prenom, enr.tel);

	} /* fin affichage_enreg */


	  /**********************************************************************/
	  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
	  /* un autre                                                           */
	  /**********************************************************************/
	bool est_sup(Enregistrement enr1, Enregistrement enr2)
	{
		for (int i = 0; i < MAX_NOM; i++) {
			if (enr1.nom[i] > enr2.nom[i]) {
				return true;
			}
			else {
				return false;
			}
			if (enr1.prenom[i] > enr2.prenom[i]) {
				return true;
			}
			return(false);

		}
	}


	/*********************************************************************/
	/*   Tri Alphabetique du tableau d'enregistrements                   */
	/*********************************************************************/

	void trier(Repertoire * rep)
	{

#ifdef IMPL_TAB

		for (int j = 0; j < rep->nb_elts; j++) {
			for (int i = 0; i < rep->nb_elts; i++) {
				if (est_sup(*((rep->tab) + i), *((rep->tab) + i + 1)) == true) { //est_sup = est supérieure
					Enregistrement tmp; //Variable pour échanger les 2 éléments
					tmp = *((rep->tab) + i);
					*((rep->tab) + i) = *((rep->tab) + i + 1);
					*((rep->tab) + i + 1) = tmp;
				}
			}
		}




#else
#ifdef IMPL_LIST
		// ajouter code ici pour Liste
		// rien à faire !
		// la liste est toujours triée
#endif
#endif


		rep->est_trie = true;

	}
	/* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

	int rechercher_nom(Repertoire * rep, char nom[], int ind)
	{
		int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
		int ind_fin;			/* position (indice) de fin de tableau/liste rep */

		char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
		char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
								/* tableau, afin de les convertir en majuscules et les comparer */
		bool trouve = false;


#ifdef IMPL_TAB
		ind_fin = rep->nb_elts - 1;
		strcpy_s(tmp_nom, _countof(tmp_nom), nom);    //on copie le nom dans tmp_nom, et on le passe en majuscule avec strupr
		while (trouve == false) {  //on va comparer tmp_nom a chaque élément du répertoire 
			strcpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom);   //on copie dans tmp_nom2 le nom du répertoire et on le passe en majuscule pour comparer dans le même format
			for (int i = 0; i < 80; i++) {
				if (_strcmpi(tmp_nom, tmp_nom2) == 0) {				 //on compare/ question sur le _
					trouve = true;								//si ce sont les mêmes trouve devient true 
				}
				else if (i == ind_fin) {
					return -1;
				}

			}
			return i - 1; //retourne l'indice du nom trouvé

#else
#ifdef IMPL_LIST
		SingleLinkedListElem* tmp = rep->liste->head;     // positionne le pointeur sur la tête de la liste chaînée
		for (i = 0; i < rep->liste->size; i++) {
			if (_stricmp(nom, tmp->pers.nom) == 0) {    // compare si le nom taper correspond au nom de la personne du maillon sélectionné
				trouve = true;
				break;           // sort de la boucle si le nom à été trouvé
			}
			tmp = tmp->next;     //positionne le pointeur sur le maillon suivant
		}


#endif
#endif




		return((trouve) ? i : -1);
		}
	}
/* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char* s)
{

	int longueur = strlen(s);
	for (int i = 0; i < longueur; i++) {
		if (isalpha(s[i])) {
			s[i] = s[i + 1];
		}
	}


	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire * rep, char nom_fichier[])
{
	FILE* fic_rep;
	errno_t err;/* le fichier */
#ifdef IMPL_TAB
	//Enregistrement enr;
	err = fopen_s(&fic_rep, nom_fichier, "w");
	if (fic_rep == NULL) return -1;
	for (int i = 0; i < rep->nb_elts; i++) {

		int nbDeCar = 4 + strlen(rep->tab[i].nom) + strlen(rep->tab[i].prenom) + strlen(rep->tab[i].tel);  // 4 pour 2*";" et "\n" et "\0"
		char* buffer = (char*)malloc(nbDeCar * sizeof(char));
		if (buffer == NULL) {
			printf("Memoire insuffisante.");
			return -1;
		}
		strcpy_s(buffer, nbDeCar, rep->tab[i].nom);
		printf("%c", SEPARATEUR);
		strcat_s(buffer, nbDeCar, rep->tab[i].prenom);
		printf("%c", SEPARATEUR);
		strcat_s(buffer, nbDeCar, rep->tab[i].tel);
		printf("%c", SEPARATEUR);
		fputs(buffer, fic_rep);
		free(buffer);
	}
	fclose(fic_rep);

#else
#ifdef IMPL_LIST
	if ((err = fopen_s(&fic_rep, nom_fichier, "w")) != 0) {
		return(err);
	}
	else {
		LinkedList* liste = rep->liste;
		for (size_t i = 0; i < liste->size; i++) {
			printf(fic_rep, "%s%c%s%c%s\n", GetElementAt(liste, i)->pers.nom, SEPARATEUR, GetElementAt(liste, i)->pers.prenom, SEPARATEUR, GetElementAt(liste, i)->pers.tel);
		}
		fclose(fic_rep);
	}
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire * rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char* char_nw_line;

	_set_errno(0);
	if (((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL))
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
				Enregistrement pers;
				if (lire_champ_suivant(buffer, &idx, pers.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, pers.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, pers.tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
				ajouter_un_contact_dans_rep(rep, pers);
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */