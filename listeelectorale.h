#include <gtk/gtk.h>
typedef struct date_de_naissance{
int jour;
int mois;
int annee;
}date_de_naissance;

typedef struct condidat{
	char nom[100];
	char prenom[100];
	int cin;
	date_de_naissance DN;
	char role[100];
	char orientation[100];
}condidat;
typedef struct
{
	char nom1 [20];
	char prenom1 [20];
	char cin1[30];
	date_de_naissance d;
	char role1[30];
	int id1;
	int vote;
}utilisateur;
typedef struct liste_electorale{
	char nom_le[100];
	int id;
	int c[9];
	int nbVote;
}liste_electorale;

int ajout_liste_electorale(char * filename,liste_electorale e);


int ajouter_un_condidat(char * filename,condidat c);

condidat chercher_un_condidat(char * filename, int cin);
int modifier_condidat(char * filename,int cin,condidat c_modifier);
int supprimer_condidat(char * filename,int cin);
liste_electorale chercher_liste(char * filename,int id);
void trilisteelectorale(char* filename);
int nbVoteParListe(int id);
void afficherListeElectorale(char *filename,GtkWidget *liste);
void afficherCondidat(char *filename,GtkWidget *liste);
