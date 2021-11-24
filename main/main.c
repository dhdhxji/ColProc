/* RMT example -- RGB LED Strip

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt.h"
#include "led_strip.h"
#include "colproc/defs.h"

static const char *TAG = "example";

#define RMT_TX_CHANNEL RMT_CHANNEL_0

#define EXAMPLE_CHASE_SPEED_MS (10)


void app_main(void)
{

    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(13, RMT_TX_CHANNEL);
    // set counter clock to 40MHz
    config.clk_div = 2;

    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

    // install ws2812 driver
    led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(5, (led_strip_dev_t)config.channel);
    led_strip_t *strip = led_strip_new_rmt_ws2812(&strip_config);
    if (!strip) {ESP_LOGE(TAG, "install WS2812 driver failed");}
    ESP_ERROR_CHECK(strip->clear(strip, 100));
    

    color_t colors[] = {
        {
            .r = 50,
            .g = 0,
            .b = 0
        },
        {
            .r = 0,
            .g = 50, 
            .b = 0
        },
        {
            .r = 0,
            .g = 0,
            .b = 0
        },
        {
            .r = 25,
            .g = 25,
            .b = 0
        },
        {
            .r = 25,
            .g = 0,
            .b = 25
        }
    };

    ESP_ERROR_CHECK(strip->set_pixels(
        strip, 
        0, 
        sizeof(colors)/sizeof(colors[0]), 
        (const uint8_t*)colors)
    );

    ESP_ERROR_CHECK(strip->refresh(strip, 100));
}
