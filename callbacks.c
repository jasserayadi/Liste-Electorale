#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include "listeelectorale.h"
#include "callbacks.h"
#include "interface.h"
#include "support.h"


void
on_treeviewlisteelectorale_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	
}


void
on_treeviewcandidat_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
	GtkTreeIter iter;
	gint id;
	GtkTreeModel *model =gtk_tree_view_get_model(treeview);
	if(gtk_tree_model_get_iter(model,&iter,path)){
		gtk_tree_model_get(GTK_LIST_STORE(model),&iter,2,&id,-1);
		supprimer_condidat("condidat.txt",id);
		afficherCondidat("condidat.txt",treeview);
	}
}


void
on_buttonrecherchecandidat_clicked     (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *entrycin,*treeview,*interface;
	entrycin=lookup_widget(object,"entrycinarechercher");
	interface=lookup_widget(object,"CHERCHER_UN_CONDIDAT");
	treeview=lookup_widget(interface,"treeviewcandidat");
	int cin=atoi(gtk_entry_get_text(GTK_ENTRY(entrycin)));
	condidat c;
	c=chercher_un_condidat("condidat.txt",cin);
	if(c.cin!=-1){
		ajouter_un_condidat("recherchecondidat.txt",c);
		afficherCondidat("recherchecondidat.txt",treeview);
		remove("recherchecondidat.txt");
	}
	else{
		afficherCondidat("condidat.txt",treeview);
	}
}


void
on_buttonrechercherlisteelectorale_clicked
                                        (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *entryid,*treeview,*interface;
	entryid=lookup_widget(object,"entryidlistearechercher");
	interface=lookup_widget(object,"LISTE_ELECTORALE");
	treeview=lookup_widget(interface,"treeviewlisteelectorale");
	int id=atoi(gtk_entry_get_text(GTK_ENTRY(entryid)));
	liste_electorale e;
	e=chercher_liste("listeelecorale.txt",id);
	if(e.id!=-1){
		ajout_liste_electorale("rechercheliste.txt",e);
		afficherListeElectorale("rechercheliste.txt",treeview);
		remove("rechercheliste.txt");
	}
	else{
		afficherListeElectorale("listeelecorale.txt",treeview);
	}
}
int go=0;

void
on_radiobuttonajoutercondidat_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
		go=0;
}


void
on_radiobuttonmodifiercondidat_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
		go=1;
}


void
on_radiobuttonsuuprimercondidat_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
		go=2;
}
void
on_radiobuttongotoajouterliste_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton)))
		go=3;
}

void
on_buttongoto_clicked                  (GtkWidget       *object,
                                        gpointer         user_data)
{
	printf("\n*********\n%d",go);
	GtkWidget *interfaceafficher,*interfaceajouter,*interfacemodifier,*interfacesupprimer,*treeview,*interfaceajouterliste;
	interfaceafficher=lookup_widget(object,"LISTE_ELECTORALE");
	gtk_widget_destroy(interfaceafficher);
	if(go==0){
		interfaceajouter=create_formulaire_d_un_condidat();
		gtk_widget_show(interfaceajouter);
	}
	else if(go==1){
		interfacemodifier=create_modifier_un_condidat();
		gtk_widget_show(interfacemodifier);
	}
	else if(go==2){
		interfacesupprimer=create_CHERCHER_UN_CONDIDAT();
		gtk_widget_show(interfacesupprimer);
		treeview=lookup_widget(interfacesupprimer,"treeviewcandidat");
  		afficherCondidat("condidat.txt",treeview);
	}
	else{
		interfaceajouterliste=create_ajouter_une_liste_electorale();
		gtk_widget_show(interfaceajouterliste);
	}
}


void
on_buttonretourcandidat_clicked        (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *interfacelogin,*interfacelisteelectorale,*treeview1;
	interfacelisteelectorale=lookup_widget(object,"LISTE_ELECTORALE");
	gtk_widget_destroy(interfacelisteelectorale);
	interfacelogin=create_connexion();
	gtk_widget_show(interfacelogin);
}


void
on_buttonajoutercandidat_clicked       (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *nom,*prenom,*jour,*mois,*annee,*cin,*role,*orientation,*dialog;
	nom=lookup_widget(object,"entrynomcandidat");
	prenom=lookup_widget(object,"entryprenomcandidat");
	jour=lookup_widget(object,"spinbuttonjourcandidat");
	mois=lookup_widget(object,"spinbuttonmoiscandidat");
	annee=lookup_widget(object,"spinbuttonanneecandidat");
	cin=lookup_widget(object,"entrycincandidat");
	role=lookup_widget(object,"entryrolecandidat");
	orientation=lookup_widget(object,"comboboxorientationcandidat");
	
	condidat c,cchercher;
	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
	strcpy(c.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)));
	c.DN.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
	c.DN.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
	c.DN.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
	c.cin=atoi(gtk_entry_get_text(GTK_ENTRY(cin)));
	strcpy(c.role,gtk_entry_get_text(GTK_ENTRY(role)));
	strcpy(c.orientation,gtk_combo_box_get_active_text(GTK_COMBO_BOX(orientation)));
	cchercher=chercher_un_condidat("condidat.txt",c.cin);
	if(strcmp(c.nom,"")==0|| strcmp(c.prenom,"")==0|| c.cin==0||strcmp(c.role,"")==0||strcmp(c.orientation,"")==0){
		dialog=gtk_message_dialog_new(GTK_WINDOW(dialog),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_WARNING,
			GTK_BUTTONS_OK,
			"Remplire tous les champs");
		gtk_window_set_title(GTK_WINDOW(dialog),"Altert");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
	else{
		if(cchercher.cin!=-1){
			dialog=gtk_message_dialog_new(GTK_WINDOW(dialog),
				GTK_DIALOG_DESTROY_WITH_PARENT,
				GTK_MESSAGE_WARNING,
				GTK_BUTTONS_OK,
				"CIN existe deja");
			gtk_window_set_title(GTK_WINDOW(dialog),"Altert");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
		}
		else{
			ajouter_un_condidat("condidat.txt",c);
		}
	}
	
	

}


void
on_buttonretourajouter_clicked         (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *interfaceajouter,*interfacelisteelectorale,*treeview1;
	interfaceajouter=lookup_widget(object,"formulaire_d_un_condidat");
	gtk_widget_destroy(interfaceajouter);
	interfacelisteelectorale=create_LISTE_ELECTORALE();
	gtk_widget_show(interfacelisteelectorale);
	treeview1=lookup_widget(interfacelisteelectorale,"treeviewlisteelectorale");
  	afficherListeElectorale("listeelecorale.txt",treeview1);
	go=0;
}


void
on_buttonmodifiercandidat_clicked      (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *nom,*prenom,*jour,*mois,*annee,*cin,*role,*orientation,*dialog;
	nom=lookup_widget(object,"entrynomcandidatm");
	prenom=lookup_widget(object,"entryprenomcandidatm");
	jour=lookup_widget(object,"spinbuttonjourcandidatm");
	mois=lookup_widget(object,"spinbuttonmoiscandidatm");
	annee=lookup_widget(object,"spinbuttonanneecandidatm");
	cin=lookup_widget(object,"entrycincandidatm");
	role=lookup_widget(object,"entryrolecandidatm");
	orientation=lookup_widget(object,"comboboxorientationcandidatm");
	
	condidat c,cchercher;
	strcpy(c.nom,gtk_entry_get_text(GTK_ENTRY(nom)));
	strcpy(c.prenom,gtk_entry_get_text(GTK_ENTRY(prenom)));
	c.DN.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(jour));
	c.DN.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois));
	c.DN.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee));
	c.cin=atoi(gtk_entry_get_text(GTK_ENTRY(cin)));
	strcpy(c.role,gtk_entry_get_text(GTK_ENTRY(role)));
	strcpy(c.orientation,gtk_combo_box_get_active_text(GTK_COMBO_BOX(orientation)));
	cchercher=chercher_un_condidat("condidat.txt",c.cin);
	if(strcmp(c.nom,"")==0|| strcmp(c.prenom,"")==0|| c.cin==0||strcmp(c.role,"")==0||strcmp(c.orientation,"")==0){
		dialog=gtk_message_dialog_new(GTK_WINDOW(dialog),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_WARNING,
			GTK_BUTTONS_OK,
			"Remplire tous les champs");
		gtk_window_set_title(GTK_WINDOW(dialog),"Altert");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
	else{
		if(cchercher.cin==-1){
			dialog=gtk_message_dialog_new(GTK_WINDOW(dialog),
				GTK_DIALOG_DESTROY_WITH_PARENT,
				GTK_MESSAGE_WARNING,
				GTK_BUTTONS_OK,
				"CIN n'existe pas");
			gtk_window_set_title(GTK_WINDOW(dialog),"Altert");
			gtk_dialog_run(GTK_DIALOG(dialog));
			gtk_widget_destroy(dialog);
		}
		else{
			modifier_condidat("condidat.txt",c.cin,c);
		}
	}
	
}


void
on_buttonretourmodifier_clicked        (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *interfacemodifier,*interfacelisteelectorale,*treeview1;
	interfacemodifier=lookup_widget(object,"modifier_un_condidat");
	gtk_widget_destroy(interfacemodifier);
	interfacelisteelectorale=create_LISTE_ELECTORALE();
	gtk_widget_show(interfacelisteelectorale);
	treeview1=lookup_widget(interfacelisteelectorale,"treeviewlisteelectorale");
  	afficherListeElectorale("listeelecorale.txt",treeview1);
	go=0;
}


void
on_buttonretourlisteelectorale_clicked (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *interfacecondidat,*interfacelisteelectorale,*treeview1;
	interfacecondidat=lookup_widget(object,"CHERCHER_UN_CONDIDAT");
	gtk_widget_destroy(interfacecondidat);
	interfacelisteelectorale=create_LISTE_ELECTORALE();
	gtk_widget_show(interfacelisteelectorale);
	treeview1=lookup_widget(interfacelisteelectorale,"treeviewlisteelectorale");
  	afficherListeElectorale("listeelecorale.txt",treeview1);
	go=0;
}

int valide=0;
void
on_checkbuttonvalider_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
	if(gtk_toggle_button_get_active(togglebutton))
		valide=1;
}


void
on_buttonajouterlisteelectorale_clicked
                                        (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *nomliste,*idliste,*id1,*id2,*id3,*id4,*id5,*id6,*id7,*id8,*id9,*dialog;
	nomliste=lookup_widget(object,"entrynomlisteelectorale");
	idliste=lookup_widget(object,"entryidlisteelectorale");
	id1=lookup_widget(object,"entryid0listeelectorale");
	id2=lookup_widget(object,"entryid1listeelectorale");
	id3=lookup_widget(object,"entryid2listeelectorale");
	id4=lookup_widget(object,"entryid3listeelectorale");
	id5=lookup_widget(object,"entryid4listeelectorale");
	id6=lookup_widget(object,"entryid5listeelectorale");
	id7=lookup_widget(object,"entryid6listeelectorale");
	id8=lookup_widget(object,"entryid7listeelectorale");
	id9=lookup_widget(object,"entryid8listeelectorale");

	liste_electorale l,lrechercher;
	strcpy(l.nom_le,gtk_entry_get_text(GTK_ENTRY(nomliste)));
	l.id=atoi(gtk_entry_get_text(GTK_ENTRY(idliste)));
	l.c[0]=atoi(gtk_entry_get_text(GTK_ENTRY(id1)));
	l.c[1]=atoi(gtk_entry_get_text(GTK_ENTRY(id2)));
	l.c[2]=atoi(gtk_entry_get_text(GTK_ENTRY(id3)));
	l.c[3]=atoi(gtk_entry_get_text(GTK_ENTRY(id4)));
	l.c[4]=atoi(gtk_entry_get_text(GTK_ENTRY(id5)));
	l.c[5]=atoi(gtk_entry_get_text(GTK_ENTRY(id6)));
	l.c[6]=atoi(gtk_entry_get_text(GTK_ENTRY(id7)));
	l.c[7]=atoi(gtk_entry_get_text(GTK_ENTRY(id8)));
	l.c[8]=atoi(gtk_entry_get_text(GTK_ENTRY(id9)));
	l.nbVote=0;
	if(strcmp(l.nom_le,"")==0|| l.id==0||l.c[0]==0||l.c[1]==0||l.c[2]==0||l.c[3]==0||l.c[4]==0||l.c[5]==0||l.c[6]==0||l.c[7]==0||l.c[8]==0){
dialog=gtk_message_dialog_new(GTK_WINDOW(dialog),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_WARNING,
			GTK_BUTTONS_OK,
			"Remplire tous les champs");
		gtk_window_set_title(GTK_WINDOW(dialog),"Altert");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
	}
	else{
		lrechercher=chercher_liste("listeelecorale.txt",l.id);
		if(lrechercher.id!=-1){
dialog=gtk_message_dialog_new(GTK_WINDOW(dialog),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_WARNING,
			GTK_BUTTONS_OK,
			"Id existe deja");
		gtk_window_set_title(GTK_WINDOW(dialog),"Altert");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
		}
		else{
			if(valide==0){
dialog=gtk_message_dialog_new(GTK_WINDOW(dialog),
			GTK_DIALOG_DESTROY_WITH_PARENT,
			GTK_MESSAGE_WARNING,
			GTK_BUTTONS_OK,
			"Veuillez valider avant d'ajouter la liste");
		gtk_window_set_title(GTK_WINDOW(dialog),"Altert");
		gtk_dialog_run(GTK_DIALOG(dialog));
		gtk_widget_destroy(dialog);
			}
			else{
				ajout_liste_electorale("listeelecorale.txt",l);
				valide=0;
			}
		}
	}
	
	
}


void
on_buttonretourajouterlisteelectorale_clicked
                                        (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *interfaceajouterliste,*interfacelisteelectorale,*treeview1;
	interfaceajouterliste=lookup_widget(object,"ajouter_une_liste_electorale");
	gtk_widget_destroy(interfaceajouterliste);
	interfacelisteelectorale=create_LISTE_ELECTORALE();
	gtk_widget_show(interfacelisteelectorale);
	treeview1=lookup_widget(interfacelisteelectorale,"treeviewlisteelectorale");
  	afficherListeElectorale("listeelecorale.txt",treeview1);
	go=0;
}





void
on_buttontrilisteelectorale_clicked    (GtkWidget       *object,
                                        gpointer         user_data)
{
	GtkWidget *interfacelisteelectorale,*treeview1;
	interfacelisteelectorale=lookup_widget(object,"LISTE_ELECTORALE");
	trilisteelectorale("listeelecorale.txt");
	treeview1=lookup_widget(interfacelisteelectorale,"treeviewlisteelectorale");
  	afficherListeElectorale("listeelectoraletriee.txt",treeview1);

}

