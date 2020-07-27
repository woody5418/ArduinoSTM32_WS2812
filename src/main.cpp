#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <STM32FreeRTOS.h>
#include <ZJConfig.h>

Adafruit_NeoPixel pixels_1(NUMPIXELS_1, WS2812_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_2(NUMPIXELS_2, WS2812_PIN_2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_3(NUMPIXELS_3, WS2812_PIN_3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_4(NUMPIXELS_4, WS2812_PIN_4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels_5(NUMPIXELS_5, WS2812_PIN_5, NEO_GRB + NEO_KHZ800);

TaskHandle_t vTask_pixels_handle;

uint8_t R_CNT = 0;
uint8_t G_CNT = 0;
uint8_t B_CNT = 0;
uint8_t RBG_CNT_FLAG = 0;
static void vTask_pixels(void *pvParameters) {
    pixels_1.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels_2.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels_3.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels_4.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels_5.begin();  // INITIALIZE NeoPixel strip object (REQUIRED)
    while (1) {
        if (RBG_CNT_FLAG == 0) {
            R_CNT += 2;
            G_CNT += 2;
            B_CNT += 2;
            if ((R_CNT >= 0XF0) || (G_CNT >= 0XF0) || (B_CNT >= 0XF0))
                RBG_CNT_FLAG = 1;
        } else {
            R_CNT -= 2;
            G_CNT -= 2;
            B_CNT -= 2;
            if ((R_CNT <= 1) || (G_CNT <= 1) || (B_CNT <= 1)) RBG_CNT_FLAG = 0;
        }
        pixels_1.clear();  // Set all pixel colors to 'off'
        pixels_2.clear();  // Set all pixel colors to 'off'
        pixels_3.clear();  // Set all pixel colors to 'off'
        pixels_4.clear();  // Set all pixel colors to 'off'
        pixels_5.clear();  // Set all pixel colors to 'off'

        for (int i = 0; i < NUMPIXELS_1; i++)
            pixels_1.setPixelColor(i, pixels_1.Color(R_CNT, G_CNT, B_CNT));
        for (int i = 0; i < NUMPIXELS_1; i++)
            pixels_2.setPixelColor(i, pixels_2.Color(R_CNT, G_CNT, B_CNT));
        for (int i = 0; i < NUMPIXELS_1; i++)
            pixels_3.setPixelColor(i, pixels_3.Color(R_CNT, G_CNT, B_CNT));
        for (int i = 0; i < NUMPIXELS_1; i++)
            pixels_4.setPixelColor(i, pixels_4.Color(R_CNT, G_CNT, B_CNT));
        for (int i = 0; i < NUMPIXELS_1; i++)
            pixels_5.setPixelColor(i, pixels_5.Color(R_CNT, G_CNT, B_CNT));
        pixels_1.show();  // Send the updated pixel colors to the hardware.
        pixels_2.show();  // Send the updated pixel colors to the hardware.
        pixels_3.show();  // Send the updated pixel colors to the hardware.
        pixels_4.show();  // Send the updated pixel colors to the hardware.
        pixels_5.show();  // Send the updated pixel colors to the hardware.
        // vTaskDelete(vTask_pixels_handle);
        vTaskDelay(10);
    }
}
void setup() {
    Serial.begin(9600);
    while (!Serial)
        ;
    delay(1000);
    // create print task
    xTaskCreate(vTask_pixels, "vTask_pixels", configMINIMAL_STACK_SIZE + 100,
                NULL, tskIDLE_PRIORITY + 1, &vTask_pixels_handle);
    // start FreeRTOS
    vTaskStartScheduler();
}

//------------------------------------------------------------------------------
void loop() {
    // Not used - idle loop has a very small, configMINIMAL_STACK_SIZE, stack
    // loop must never block
}
