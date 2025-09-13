#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>

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
    XIDetachSlaveInfo detach;
    detach.type = XIDetachSlave;
    detach.deviceid = id;
    XIChangeHierarchy(display, (XIAnyHierarchyChangeInfo*)&detach, 1);
    XFlush(display);
    
    
    XIAttachSlaveInfo change;
    int ndevices;
    int masterID = -1;
    int isKeyboard = -1;

    XIDeviceInfo *master = XIQueryDevice(display, XIAllDevices, &ndevices);
    XIDeviceInfo *dev = NULL;

    for(int i=0;i<ndevices;i++){
        if(master[i].deviceid == id){
            dev = &master[i];
            break;
        }
    }
    
    if(dev->use == XISlaveKeyboard || dev->use == XIMasterKeyboard) isKeyboard = 1;
    if(dev->use == XISlavePointer || dev->use == XIMasterPointer) isKeyboard = 0;

    XIFreeDeviceInfo(master);

    XIDeviceInfo *info = XIQueryDevice(display, XIAllDevices,  &ndevices);
    for(int i=0;i<ndevices;i++){
        if(isKeyboard && info[i].use == XIMasterKeyboard){
            masterID = info[i].deviceid;
            break;
        }if(isKeyboard == 0 && info[i].use == XIMasterPointer){
            masterID = info[i].deviceid;
            break;
        }
    }
    
    change.type = XIAttachSlave;
    change.deviceid = id;
    change.new_master = masterID;

    XIChangeHierarchy(display, (XIAnyHierarchyChangeInfo*)&change, 1);
    XFlush(display);

    XIFreeDeviceInfo(info);
    usleep(100000);
}