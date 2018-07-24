#define arr_len( x )  ( sizeof( x ) / sizeof( *x ) )

/*
 * showPxl, displays a Pixol to the display with no animation
 * args:
 * - pxl[256][3] - Standard Pixol image
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - color[3] (optional) - Sets all the lit pixels to a specific RGB value
 */
void showPxl(int pxl[256][3], int dlytime, int color[3]={0,0,0}) {
    matrix.fillScreen(0);

    for (int i=0; i<256; i++){
        if (color != {0,0,0}) {
            matrix.setPixelColor(i, pxl[i][color[0]], pxl[i][color[1]], pxl[i][color[2]]);
        }else {
            matrix.setPixelColor(i, pxl[i][0], pxl[i][1], pxl[i][2]);
        }
    }

    matrix.show();
    delay(dlytime);
}

// Notification functions

/*
 * notifyPopupPxl, draws a Pixol that scrolls into view, and back down
 * args:
 * - pxl[256][3] - Standard Pixol image
 * - dlytime - The amount of time (in ms) to keep the image on the display
 */
void notifyPopupPxl(int pxl[256][3], int dlytime) {
    for (int j = 15; j >= 0; j--) {
        matrix.fillScreen(0);
        for (int i = 0; i < 256; i++) {
            matrix.setPixelColor(i + (j * 16),
                pxl[i][0], pxl[i][1], pxl[i][2]);
        }
        matrix.show();
        delay(50);
    }

    delay(dlytime);

    for (int j = 0; j <= 16; j++) {
        matrix.fillScreen(0);
        for (int i = 0; i < 256; i++) {
        matrix.setPixelColor(i + (j * 16),
            pxl[i][0], pxl[i][1], pxl[i][2]);
        }
        matrix.show();
        delay(50);
    }

    delay(100);
}

/*
 * notifyScrollPxl, draws a Pixol that scrolls upward into view, and upwards out; Loop this to scroll X times
 * args:
 * - pxl[256][3] - Standard Pixol image
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - loops (optional) - The total amount of times this should loop through
 */
void notifyScrollPxl(int pxl[256][3], int dlytime, int loops=0) {
    for (int x=0; x<=loops; x++) {
        for (int j = 15; j >= 0; j--) {
            matrix.fillScreen(0);
            for (int i = 0; i < 256; i++) {
                matrix.setPixelColor(i + (j * 16), 
                    pxl[i][0], pxl[i][1], pxl[i][2]);
            }
            matrix.show();
            delay(15);
        }

        delay(dlytime);

        for (int j = 0; j >= -16; j--) {
            matrix.fillScreen(0);
            for (int i = 0; i < 256; i++) {
                matrix.setPixelColor(i + (j * 16),
                    pxl[i][0], pxl[i][1], pxl[i][2]);
            }
            matrix.show();
            delay(15);
        }

        delay(100);
    }
}

// "Animation" or picture transition functions

/* 
 * animatePxl, show a sequence of pixols stored in the same array
 * args:
 * - src[][256][3] - Array containing one or more complete Pixo-Style icons in order to be shown
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - anitime - The amount of time (in ms) between drawing each Pixol during the animation; the lower this number, the faster the animation
 */
void animatePxl(int src[][256][3], int dlytime, int anitime) {
    for (int i=0; i < arr_len(src); i++) {
        for (int i=0; i<256; i++){
            matrix.setPixelColor(i, src[i][0], src[i][1], src[i][2]);
        }
        matrix.show();
        delay(anitime);
    }

    delay(dlytime);
}

/*
 * blinkPxl, flash a Pixol on screen repeatedly
 * args:
 * - pxl[256][3] - Standard Pixol image, displayed all at once
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - loops (optional) - The total amount of times this should blink
 * - color[3] (optional) - Sets all the lit pixels to a specific RGB value
 */
void blinkPxl(int pxl[256][3], int dlytime, int loops=0, int color={0,0,0}) {
    for (int i=0; i<=loops; i++) {
        showPxl(pxl, dlytime, color);
        matrix.fillScreen(0);
        delay(dlytime);
        showPxl(pxl, dlytime, color);
    }
}

/*
 * scanChangePxl, Change from one Pixol to another with a scanline appearence
 * args:
 * - src[256][3] - Standard Pixo-Style icon that we change from, displayed all at once
 * - dst[256][3] - Standard Pixo-Style icon that we change to, displayed one pixel at a time
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - anitime - The amount of time (in ms) between drawing each pixel during the transition; the lower this number, the faster the transition
 */
void scanChangePxl(int src[256][3], int dst[256][3], int dlytime, int anitime) {
    for (int i=0; i<256; i++){
        matrix.setPixelColor(i, src[i][0], src[i][1], src[i][2]);
    }
    matrix.show();

    delay(dlytime);

    for (int i=0; i<256; i++){
        matrix.setPixelColor(i, dst[i][0], dst[i][1], dst[i][2]);
        matrix.show();
        delay(anitime);
    }

    delay(dlytime);
}

/*
 * randChangePxl, Change from one Pixol to another with a random pixel selection
 * args:
 * - src[256][3] - Standard Pixo-Style icon that we change from, displayed all at once
 * - dst[256][3] - Standard Pixo-Style icon that we change to, displayed one pixel at a time
 * - dlytime - The amount of time (in ms) to keep the image on the display
 * - anitime - The amount of time (in ms) between drawing each pixel during the transition; the lower this number, the faster the transition
 */
void randChangePxl(int src[256][3], int dst[256][3], int dlytime, int anitime) {
    int changed[256];
    for (int i=0; i<256; i++){
        matrix.setPixelColor(i, src[i][0], src[i][1], src[i][2]);
    }
    matrix.show();

    delay(dlytime);

    for (int i=0; i<256; i++){
        int selected = random(0, 256);
        // If the selected pixel was inside changed array, select a new one...
        // Add selected to changed array
        matrix.setPixelColor(selected, dst[selected][0], dst[selected][1], dst[selected][2]);
        matrix.show();
        delay(anitime);
    }

    delay(dlytime);
}
