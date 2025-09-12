#ifndef COMMAND_H
#define COMMAND_H

#include <X11/Xlib.h>  // para o tipo Display

typedef struct {
    char name[50];
    int id;
    int estado;
} Inputs;

Inputs* ReadXinput(Display *display);

void disableInput(Display *display, int id);
void enableInput(Display *display, int id);

#endif