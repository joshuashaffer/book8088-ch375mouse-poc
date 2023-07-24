#include <conio.h>
#include <i86.h>
#include <stdint.h>

#ifndef NDEBUG
#include <string.h>
#include <stdio.h>
#else
#define printf(...)
#define fprintf(...)
#define fopen(...) NULL
#define fclose(...) 0
#define fflush(...) 0
#define strcmp(...) 0
typedef int* FILE;
#define NULL 0
#define stdout NULL

// Ignore warning 628
#pragma warning(disable: 628)
#endif

#include "usb_host.hpp"

const int16_t max_x = 80;
const int16_t max_y = 25;

/**
 * Set the character at the given position to the given character.
 * @param c Character to set.
 * @param x X position.
 * @param y Y position.
 * @param style Style to set.
 * @return  The old character at the given position.
 */
inline uint8_t set_char(char c, int x, int y, uint8_t style = 0x00) {
    __segment screen = 0xB800;
    char __based(void) *base = 0;
    uint8_t old = *(screen :> base + (y * max_x + x) * 2);
    *(screen :> base + (y * max_x + x) * 2) = c;
    *(screen :> base + (y * max_x + x) * 2 + 1) = style;
    return old;
}

int main(int argc, char *argv[]) {
    MeUSBHost usb_host;

    printf("CH375 HID Mouse Driver.\n$");

    if (argc > 1) {
        if (strcmp(argv[1], "-") == 0) {
            usb_host.debug_fp = stdout;
        } else {
            usb_host.debug_fp = fopen(argv[1], "w");
        }
    }

    int16_t t = usb_host.probeDevice();
    printf("Device ready: %x\n$", t);

    // Center of the screen
    int x = max_x >> 1;
    int y = max_y >> 1;

    uint8_t old = set_char('X', x, y, 0xFF);


    while (usb_host.device_ready) {
        uint16_t bytes_read = usb_host.host_recv();
        if (bytes_read == 0) {
            continue;
        }
        mouse_report_t *mouse_report = usb_host.p_mouse_report();

        set_char(old, x, y);
        x += mouse_report->dx >> 2;
        y += mouse_report->dy >> 2;

        if (x < 0) {
            x = 0;
        } else if (x >= max_x) {
            x = max_x - 1;
        }
        if (y < 0) {
            y = 0;
        } else if (y >= max_y) {
            y = max_y - 1;
        }

        old = set_char('X', x, y, 0xFF);
    }
    return 0;
}
