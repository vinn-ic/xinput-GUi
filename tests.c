#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    Display *display;
    int ndevices;
    XIDeviceInfo *info;

    display = XOpenDisplay(NULL);
    if (!display) {
        fprintf(stderr, "Não foi possível abrir o display.\n");
        return 1;
    }

    info = XIQueryDevice(display, XIAllDevices, &ndevices);

    printf("=== Dispositivos de entrada detectados ===\n");
    for (int i = 0; i < ndevices; i++) {
        printf("ID: %d | Nome: %s | Uso: ",
               info[i].deviceid, info[i].name);

        if (info[i].use == XISlaveKeyboard)
            printf("Teclado escravo\n");
        else if (info[i].use == XISlavePointer)
            printf("Mouse/Touchpad escravo\n");
        else if (info[i].use == XIFloatingSlave)
            printf("Desativado (floating slave)\n");
        else if (info[i].use == XIMasterKeyboard)
            printf("Teclado master\n");
        else if (info[i].use == XIMasterPointer)
            printf("Mouse master\n");
        else
            printf("Outro\n");
    }

    // Exemplo: desativar um dispositivo específico (substitua pelo ID desejado)
    int target_id = 12; // coloque o ID que quer desativar
    XIChangeHierarchy(display, (XIAnyHierarchyChange[]){{
        .type = XIDetachSlave,
        .deviceid = target_id
    }}, 1);

    printf("Dispositivo ID %d foi desativado.\n", target_id);

    // Exemplo: reativar (reattach) no master pointer 2
    XIChangeHierarchy(display, (XIAnyHierarchyChange[]){{
        .type = XIAttachSlave,
        .deviceid = target_id,
        .new_master = 2  // geralmente o master pointer é ID 2
    }}, 1);

    printf("Dispositivo ID %d foi reativado.\n", target_id);

    XIFreeDeviceInfo(info);
    XCloseDisplay(display);
    return 0;
}
