#include <gtk/gtk.h>
#include <stdio.h>

#include "command.h"

#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>

// ver a mecanica para mudar a cor do botão indivudual mente, sepah vai ter que tirar do for  

static void butonClick(GtkWidget *button, gpointer data) {
    GtkStyleContext *ClassB = gtk_widget_get_style_context(button);
    Display *display = XOpenDisplay(NULL);

    if(gtk_style_context_has_class(ClassB, "red")){
        //ativar
        gtk_style_context_remove_class(ClassB, "red");
        gtk_style_context_add_class(ClassB, "green");
        const gchar *text = gtk_button_get_label(GTK_BUTTON(button));
        int numID = atoi(text);
        enableInput(display, numID);
    }else if(gtk_style_context_has_class(ClassB, "green")){
        //desativar
        gtk_style_context_remove_class(ClassB, "green");
        gtk_style_context_add_class(ClassB, "red");
        const gchar *text = gtk_button_get_label(GTK_BUTTON(button));
        int numID = atoi(text);
        disableInput(display, numID);
    }
}

static void creatChoice(Inputs *inputs ,GtkWidget *boxButton, GtkWidget *boxLabel, int ndevices){

    for(int i=0;i<ndevices;i++){
        char labelName[200];
        char buttonName[200];
        sprintf(buttonName, "%d", inputs[i].id);
        sprintf(labelName, "%s", inputs[i].name);

        GtkCssProvider *provider = gtk_css_provider_new();
        gtk_css_provider_load_from_data(provider,
        "button.green {"
            "background: green;"
            "color: white;"
            "font-size: 16px;"
            "border-radius: 8px;"
        "}"
        "button.red {"
            "background: red;"
            "color: white;"
            "font-size: 16px;"
            "border-radius: 8px;"
        "}"
        , -1, NULL);

        //GtkStyleContext *context = gtk_widget_get_style_context(boxButton);
        GdkScreen *screen = gdk_screen_get_default();
        gtk_style_context_add_provider_for_screen(
            screen,
            GTK_STYLE_PROVIDER(provider),
            GTK_STYLE_PROVIDER_PRIORITY_USER
        );
   


        GtkWidget *label = gtk_label_new(labelName);
        gtk_box_pack_start(GTK_BOX(boxLabel), label, TRUE,TRUE, 5);

        GtkWidget *button = gtk_button_new_with_label(buttonName);
        gtk_box_pack_start(GTK_BOX(boxButton), button,TRUE,TRUE,5);

        GtkStyleContext *ctx = gtk_widget_get_style_context(button);
        if(inputs[i].estado == 0){
            gtk_style_context_add_class(ctx, "red");
        }else if(inputs[i].estado == 1){
            gtk_style_context_add_class(ctx, "green");
        }
        g_signal_connect(button, "clicked", G_CALLBACK(butonClick), NULL);
    
    }
}



int main(int argc, char *argv[]) {
    Display *display = XOpenDisplay(NULL);

    int ndevices;
    XIDeviceInfo *info = XIQueryDevice(display, XIAllDevices, &ndevices);
    free(info);
    Inputs *inputs = ReadXinput(display);


    gtk_init(&argc, &argv);

    GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(win), "xinput GUI");
    gtk_window_set_default_size(GTK_WINDOW(win), 600,600);
    g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *boxMain = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(win), boxMain);

    GtkWidget *boxButton = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_end(GTK_BOX(boxMain),boxButton,TRUE, TRUE, 10);

    


    GtkWidget *boxLabel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 25);
    gtk_box_pack_start(GTK_BOX(boxMain), boxLabel, TRUE, TRUE, 10);





    //g_signal_connect(button, "clicked", G_CALLBACK(butonClick), NULL);
    creatChoice(inputs ,boxButton, boxLabel, ndevices);


    gtk_widget_show_all(win);
    gtk_main();

    free(inputs);
    return 0;
}


/*
gcc ^
  -IC:/msys64/mingw64/bin/../include/gtk-3.0 ^
  -IC:/msys64/mingw64/bin/../include/pango-1.0 ^
  -IC:/msys64/mingw64/bin/../include ^
  -IC:/msys64/mingw64/bin/../include/harfbuzz ^
  -IC:/msys64/mingw64/bin/../include/cairo ^
  -IC:/msys64/mingw64/bin/../include/freetype2 ^
  -IC:/msys64/mingw64/bin/../include/pixman-1 ^
  -IC:/msys64/mingw64/bin/../include/gdk-pixbuf-2.0 ^
  -IC:/msys64/mingw64/bin/../include/libpng16 ^
  -IC:/msys64/mingw64/bin/../include/webp ^
  -DLIBDEFLATE_DLL ^
  -IC:/msys64/mingw64/bin/../include/atk-1.0 ^
  -IC:/msys64/mingw64/bin/../include/fribidi ^
  -IC:/msys64/mingw64/bin/../include/glib-2.0 ^
  -IC:/msys64/mingw64/bin/../lib/glib-2.0/include ^
  main.c command.c -o main.exe ^
  -LC:/msys64/mingw64/bin/../lib ^
  -lgtk-3 -lgdk-3 -lz -lgdi32 -limm32 -lshell32 -lole32 -luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lhid -lwinspool -lcomctl32 -lcomdlg32 ^
  -lpangocairo-1.0 -lpangowin32-1.0 -lpango-1.0 -lcairo-gobject -lcairo -lharfbuzz -lgdk_pixbuf-2.0 -latk-1.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lintl

*/