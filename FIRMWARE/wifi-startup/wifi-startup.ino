#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_DotStarMatrix.h>
#include <Adafruit_DotStar.h>
#include <ArduinoJson.h>
#include "pixols.h"
#include "pixo-displaylib.h"

#define DATAPIN    19
#define CLOCKPIN   18
#define SHIFTDELAY 30
#define BRIGHTNESS 15
#define MAX_FPS    45 

Adafruit_DotStarMatrix matrix = Adafruit_DotStarMatrix(
    16, 16, DATAPIN, CLOCKPIN,
    DS_MATRIX_TOP  + DS_MATRIX_LEFT +
    DS_MATRIX_ROWS + DS_MATRIX_PROGRESSIVE,
    DOTSTAR_BGR);

void setup(void) {
    matrix.begin();
    matrix.setBrightness(BRIGHTNESS);

    scanChangePxl(darkness, sh, 1000, 10);
}

void loop() {
    uint32_t t;
    while (((t = micros()) - prevTime) < (1000000L / MAX_FPS)); // FPS Limit?
    prevTime = t;
}