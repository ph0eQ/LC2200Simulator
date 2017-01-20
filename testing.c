#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "micro_table.h"


typedef struct {
	GtkWidget *window1;
	GtkWidget *entry1;
	GtkWidget *entry2;
	GtkWidget *label1;
} AppWidgets;
typedef struct reg_fields{
    GtkEntry *zero;
    GtkEntry *at;
    GtkEntry *v0;
    GtkEntry *a0;
    GtkEntry *a1;
    GtkEntry *a2;
    GtkEntry *t0;
    GtkEntry *t1;
    GtkEntry *t2;
    GtkEntry *s0;
    GtkEntry *s1;
    GtkEntry *s2;
    GtkEntry *k0;
    GtkEntry *sp;
    GtkEntry *fp;
    GtkEntry *ra;
    GtkEntry *PC;
    GtkEntry *IR;
} reg_fields;

    
int main( int    argc,
      char **argv )
{
    GtkBuilder *builder;
    GtkWidget  *window;
    GError     *error = NULL;
    reg_fields regs = {0};
    /* Init GTK+ */
    gtk_init( &argc, &argv );

    /* Create new GtkBuilder object */
    builder = gtk_builder_new();
    /* Load UI from file. If error occurs, report it and quit application.
     * Replace "tut.glade" with your saved project. */
    if( ! gtk_builder_add_from_file( builder, "testing.glade", &error ) )
    {
        g_warning( "%s", error->message );
        g_free( error );
        return( 1 );
    }

    /* Get main window pointer from UI */
    window = GTK_WIDGET( gtk_builder_get_object( builder, "LC2200" ) );

    /* Connect signals */
    gtk_builder_connect_signals( builder, NULL );
    //GtkEntry *zero = GTK_ENTRY(gtk_builder_get_object(builder, "entry1"));
    regs.zero = GTK_ENTRY(gtk_builder_get_object(builder, "entry1"));
        gtk_entry_set_text(regs.zero, "ZERO 1");
    regs.at = GTK_ENTRY(gtk_builder_get_object(builder, "entry10"));
            gtk_entry_set_text(regs.at, "AT 2");
    regs.v0 = GTK_ENTRY(gtk_builder_get_object(builder, "entry2"));
            gtk_entry_set_text(regs.v0, "V0 3");
    regs.a0 = GTK_ENTRY(gtk_builder_get_object(builder, "entry11"));
            gtk_entry_set_text(regs.a0, "A0 4");
    regs.a1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry3"));
                gtk_entry_set_text(regs.a1, "A1 5");
    regs.a2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry12"));
                gtk_entry_set_text(regs.a2, "A2 6");
    regs.t0 = GTK_ENTRY(gtk_builder_get_object(builder, "entry4"));
                gtk_entry_set_text(regs.t0, "t0 7");
    regs.t1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry13"));
                gtk_entry_set_text(regs.t1, "t1 8");
    regs.t2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry5"));
                    gtk_entry_set_text(regs.t2, "t2 9");
    regs.s0 = GTK_ENTRY(gtk_builder_get_object(builder, "entry14"));
                        gtk_entry_set_text(regs.s0, "s0 10");
    regs.s1 = GTK_ENTRY(gtk_builder_get_object(builder, "entry6"));
                            gtk_entry_set_text(regs.s1, "s1 11");
    regs.s2 = GTK_ENTRY(gtk_builder_get_object(builder, "entry15"));
                            gtk_entry_set_text(regs.s2, "s2 12");
    regs.k0 = GTK_ENTRY(gtk_builder_get_object(builder, "entry7"));
                            gtk_entry_set_text(regs.k0, "k0 13");
    regs.sp = GTK_ENTRY(gtk_builder_get_object(builder, "entry16"));
                            gtk_entry_set_text(regs.sp, "sp 14");
    regs.fp = GTK_ENTRY(gtk_builder_get_object(builder, "entry8"));
                            gtk_entry_set_text(regs.fp, "fp 15");
    regs.ra = GTK_ENTRY(gtk_builder_get_object(builder, "entry17"));
                             gtk_entry_set_text(regs.ra, "ra 16");
          regs.PC = GTK_ENTRY(gtk_builder_get_object(builder, "entry9"));
                            gtk_entry_set_text(regs.PC, "PC 17");
    regs.IR = GTK_ENTRY(gtk_builder_get_object(builder, "entry18"));
                             gtk_entry_set_text(regs.IR, "IR 18");
    /* Destroy builder, since we don't need it anymore */
    g_object_unref( G_OBJECT( builder ) );

    /* Show window. All other widgets are automatically shown by GtkBuilder */
    gtk_widget_show( window );

    /* Start main loop */
    gtk_main();

    return( 0 );
}

/* Show the About box */
void help_about(GtkWidget *widget){
	gtk_dialog_run(GTK_DIALOG(widget));
	gtk_widget_hide(widget);
}

