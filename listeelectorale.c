#include "listeelectorale.h"
#include<stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
enum{
	NOM,
	PRENOM,
	CIN,
	DATEN,
	ROLE,
	ORIENTATION,
	COLUMNS2
};
enum{
	ID,
	NOMLE,
	CANDIDAT1,
	CANDIDAT2,
	CANDIDAT3,
	CANDIDAT4,
	CANDIDAT5,
	CANDIDAT6,
	CANDIDAT7,
	CANDIDAT8,
	CANDIDAT9,
	COLUMNS
};

int ajout_liste_electorale(char * filename,liste_electorale e)
{
	FILE* f=fopen(filename,"a");
	if(f!=NULL){
	
		fprintf(f,"%d %s %d %d %d %d %d %d %d %d %d\n",e.id,e.nom_le,e.c[0],e.c[1],e.c[2],e.c[3],e.c[4],e.c[5],e.c[6],e.c[7],e.c[8]);

		fclose(f);
		return 1;
	}
	else {
		return 0;
	}
}

liste_electorale chercher_liste(char * filename,int id){
	liste_electorale e;
	FILE* f=fopen(filename,"r");
	if(f!=NULL){
		while(fscanf(f,"%d %s %d %d %d %d %d %d %d %d %d\n",&e.id,e.nom_le,&e.c[0],&e.c[1],&e.c[2],&e.c[3],&e.c[4],&e.c[5],&e.c[6],&e.c[7],&e.c[8])!=EOF)
		{
			if(e.id==id)
			{
				fclose(f);
				return e;
			}
		}
		fclose(f);
		e.id=-1;
		return e;
		
	}
}
int ajouter_un_condidat(char * filename,condidat c){
	FILE* f=fopen(filename,"a");
	if(f!=NULL){
	
		fprintf(f,"%s %s %d %d %d %d %s %s\n",c.nom,c.prenom,c.cin,c.DN.jour,c.DN.mois,c.DN.annee,c.role,c.orientation);

		fclose(f);
		return 1;
	}
	else {
		return 0;
	}
}
condidat chercher_un_condidat(char * filename, int cin){
	condidat c;
	FILE* f=fopen(filename,"r");
	if(f!=NULL){
		while(fscanf(f,"%s %s %d %d %d %d %s %s\n",c.nom,c.prenom,&c.cin,&c.DN.jour,&c.DN.mois,&c.DN.annee,c.role,c.orientation)!=EOF)
		{
			if(c.cin==cin)
			{
				fclose(f);
				return c;
			}
		}
		fclose(f);
		c.cin=-1;
		return c;
		
	}
		

}
int supprimer_condidat(char * filename,int cin){
	condidat c;
	FILE* f=fopen(filename,"r");
	FILE *f1=fopen("tmp.txt","a");
	if(f!=NULL && f1!=NULL){
		while(fscanf(f,"%s %s %d %d %d %d %s %s\n",c.nom,c.prenom,&c.cin,&c.DN.jour,&c.DN.mois,&c.DN.annee,c.role,c.orientation)!=EOF)
		{
			if(c.cin!=cin)
			{
				fprintf(f1,"%s %s %d %d %d %d %s %s\n",c.nom,c.prenom,c.cin,c.DN.jour,c.DN.mois,c.DN.annee,c.role,c.orientation);
			}
		}
		fclose(f);
		fclose(f1);
		remove(filename);
		rename("tmp.txt",filename);
		return 1;
		
		
	}
	return 0;
}
int modifier_condidat(char * filename,int cin,condidat c_modifier){
	condidat c;
	FILE* f=fopen(filename,"r");
	FILE *f1=fopen("tmp.txt","a");
	if(f!=NULL && f1!=NULL){
		while(fscanf(f,"%s %s %d %d %d %d %s %s\n",c.nom,c.prenom,&c.cin,&c.DN.jour,&c.DN.mois,&c.DN.annee,c.role,c.orientation)!=EOF)
		{
			if(c.cin!=cin)
			{
				fprintf(f1,"%s %s %d %d %d %d %s %s\n",c.nom,c.prenom,c.cin,c.DN.jour,c.DN.mois,c.DN.annee,c.role,c.orientation);
			}
			else{
				fprintf(f1,"%s %s %d %d %d %d %s %s\n",c_modifier.nom,c_modifier.prenom,c_modifier.cin,c_modifier.DN.jour,c_modifier.DN.mois,c_modifier.DN.annee,c_modifier.role,c_modifier.orientation);
			}
		}
		fclose(f);
		fclose(f1);
		remove(filename);
		rename("tmp.txt",filename);
		return 1;
		
		
	}
	return 0;
}
void trilisteelectorale(char* filename){
	liste_electorale e,aide,tableau[999];
	FILE* f=fopen(filename,"r");
	int n=0,i,j,max,nbVote[999],aide2;
	//fichier => tableau
	if(f!=NULL){
		while(fscanf(f,"%d %s %d %d %d %d %d %d %d %d %d\n",&e.id,e.nom_le,&e.c[0],&e.c[1],&e.c[2],&e.c[3],&e.c[4],&e.c[5],&e.c[6],&e.c[7],&e.c[8])!=EOF)
		{
			tableau[n]=e;
			nbVote[n]=nbVoteParListe(e.id);
			n++;
			
		}
		fclose(f);
		
		
	}
	//tri tableau
	for(i=0;i<n-1;i++){
		max=i;
		for(j=i+1;j<n;j++){
			if(nbVote[j]>nbVote[max])
				max=j;
		}
		if(max!=i){
			aide=tableau[i];
			tableau[i]=tableau[max];
			tableau[max]=aide;
			aide2=nbVote[i];
			nbVote[i]=nbVote[max];
			nbVote[max]=aide2;
		}
	}
	//tablea triee=> fichier
	FILE* f1=fopen("listeelectoraletriee.txt","w");
	if(f1!=NULL){
		for(i=0;i<n;i++){
			fprintf(f1,"%d %s %d %d %d %d %d %d %d %d %d\n",tableau[i].id,tableau[i].nom_le,tableau[i].c[0],tableau[i].c[1],tableau[i].c[2],tableau[i].c[3],tableau[i].c[4],tableau[i].c[5],tableau[i].c[6],tableau[i].c[7],tableau[i].c[8]);
		}
		fclose(f1);
	}
}

int nbVoteParListe(int id){
	utilisateur u;
	int nb=0;
	FILE *f=fopen("utilisateur.txt","r");
	if(f==NULL){
		return 0;
	}
	else{
		while(fscanf(f,"%s %s %s %d %d %d %s %d %d\n",u.nom1,u.prenom1,u.cin1,&u.d.jour,&u.d.mois,&u.d.annee,u.role1,&u.id1,&u.vote)!=EOF)
		{
			if(u.vote==id)
				nb++;
		}
		fclose(f);
		return nb;
	}
}
void afficherListeElectorale(char *filename,GtkWidget *liste){
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	liste_electorale e;
	store=gtk_tree_view_get_model(liste);
	if(store==NULL){
		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Id",renderer,"text",ID,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Nom liste electorale",renderer,"text",NOMLE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Candidat 1",renderer,"text",CANDIDAT1,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Candidat 2",renderer,"text",CANDIDAT2,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Candidat 3",renderer,"text",CANDIDAT3,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Candidat 4",renderer,"text",CANDIDAT4,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Candidat 5",renderer,"text",CANDIDAT5,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Candidat 6",renderer,"text",CANDIDAT6,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Candidat 7",renderer,"text",CANDIDAT7,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Candidat 8",renderer,"text",CANDIDAT8,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Candidat 9",renderer,"text",CANDIDAT9,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	}
	store=gtk_list_store_new(COLUMNS,G_TYPE_INT,G_TYPE_STRING,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT);
	FILE *f=fopen(filename,"r");
	if(f==NULL)
		return;
	else{
		while(fscanf(f,"%d %s %d %d %d %d %d %d %d %d %d\n",&e.id,e.nom_le,&e.c[0],&e.c[1],&e.c[2],&e.c[3],&e.c[4],&e.c[5],&e.c[6],&e.c[7],&e.c[8])!=EOF)
		{
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,ID,e.id,NOMLE,e.nom_le,CANDIDAT1,e.c[0],
					CANDIDAT2,e.c[1],CANDIDAT3,e.c[2],CANDIDAT4,e.c[3],CANDIDAT5,e.c[4],
					CANDIDAT6,e.c[5],CANDIDAT7,e.c[6],CANDIDAT8,e.c[7],CANDIDAT9,e.c[8],-1);
			
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
	}
}

void afficherCondidat(char *filename,GtkWidget *liste){
	char date[15],jour[4],mois[4],annee[8];
	condidat c;
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter;
	GtkListStore *store;
	store=gtk_tree_view_get_model(liste);
	if(store==NULL){
		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Nom",renderer,"text",NOM,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Prenom",renderer,"text",PRENOM,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("CIN",renderer,"text",CIN,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Date de la naissance",renderer,"text",DATEN,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Role",renderer,"text",ROLE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer=gtk_cell_renderer_text_new();
		column=gtk_tree_view_column_new_with_attributes("Orientation",renderer,"text",ORIENTATION,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);


	}
	store=gtk_list_store_new(COLUMNS2,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	FILE *f=fopen(filename,"r");
	if(f==NULL)
		return;
	else{
		while(fscanf(f,"%s %s %d %d %d %d %s %s\n",c.nom,c.prenom,&c.cin,&c.DN.jour,&c.DN.mois,&c.DN.annee,c.role,c.orientation)!=EOF)
		{
			sprintf(jour,"%d",c.DN.jour);
			sprintf(mois,"%d",c.DN.mois);
			sprintf(annee,"%d",c.DN.annee);
			strcpy(date,"");
			strcat(date,jour);
			strcat(date,"/");
			strcat(date,mois);
			strcat(date,"/");
			strcat(date,annee);
			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store,&iter,NOM,c.nom,PRENOM,c.prenom,CIN,c.cin,
					DATEN,date,ROLE,c.role,ORIENTATION,c.orientation,-1);
			
		}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);
	}
}

