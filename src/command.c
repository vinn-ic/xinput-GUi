#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>

#include <gtk/gtk.h>

typedef struct{
    char name[50];
    int id;
    int estado;
}Inputs;


Inputs* ReadXinput(Display *display){
    Inputs *inputs = malloc(20 * sizeof(Inputs));;
    int ndevices;
    XIDeviceInfo *info = XIQueryDevice(display, XIAllDevices, &ndevices);
    
    for(int i=0;i<ndevices;i++){
        strcpy(inputs[i].name, info[i].name);
        inputs[i].id = info[i].deviceid;

        if(info[i].use == XIFloatingSlave){
            inputs[i].estado = 0;
        }else if(info[i].use != XIFloatingSlave){
            inputs[i].estado = 1;
        }
    }
    return inputs;
}

void disableInput(Display *display ,int id){
    XIDetachSlaveInfo change;
    change.type = XIDetachSlave;
    change.deviceid = id;
    
    XIChangeHierarchy(display, (XIAnyHierarchyChangeInfo*)&change, 1);
    XFlush(display);
}

void enableInput(Display *display, int id){
    char commnad[50];
    sprintf(commnad, "xinput disable %d && xinput enable %d", id, id);
    system(commnad);
    g_print("comando executado >> %s", commnad);
}