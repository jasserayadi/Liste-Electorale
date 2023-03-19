#include <gtk/gtk.h>


void
on_treeviewlisteelectorale_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_treeviewcandidat_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);

void
on_buttonrecherchecandidat_clicked     (GtkWidget       *object,
                                        gpointer         user_data);

void
on_buttonrechercherlisteelectorale_clicked
                                        (GtkWidget       *object,
                                        gpointer         user_data);

void
on_radiobuttonajoutercondidat_toggled  (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonmodifiercondidat_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonsuuprimercondidat_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttongoto_clicked                  (GtkWidget       *object,
                                        gpointer         user_data);

void
on_buttonretourcandidat_clicked        (GtkWidget       *object,
                                        gpointer         user_data);

void
on_buttonajoutercandidat_clicked       (GtkWidget       *object,
                                        gpointer         user_data);

void
on_buttonretourajouter_clicked         (GtkWidget       *object,
                                        gpointer         user_data);

void
on_buttonmodifiercandidat_clicked      (GtkWidget       *object,
                                        gpointer         user_data);

void
on_buttonretourmodifier_clicked        (GtkWidget       *object,
                                        gpointer         user_data);

void
on_buttonretourlisteelectorale_clicked (GtkWidget       *object,
                                        gpointer         user_data);

void
on_checkbuttonvalider_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonajouterlisteelectorale_clicked
                                        (GtkWidget       *object,
                                        gpointer         user_data);

void
on_buttonretourajouterlisteelectorale_clicked
                                        (GtkWidget       *object,
                                        gpointer         user_data);

void
on_radiobuttongotoajouterliste_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttontrilisteelectorale_clicked    (GtkWidget       *object,
                                        gpointer         user_data);
