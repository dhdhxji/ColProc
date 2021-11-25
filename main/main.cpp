/* RMT example -- RGB LED Strip

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "driver/rmt.h"
#include "led_strip.h"

#include "colproc/defs.h"
#include "colproc/colproc.h"
#include "colproc/gen/random.h"

static const char *TAG = "example";

#define RMT_TX_CHANNEL RMT_CHANNEL_0
#define EXAMPLE_CHASE_SPEED_MS (10)


#define LED_COUNT 5
static color_t color_buf[LED_COUNT];

static ColProc* build_processor() {
    return new ColRpocGenRandom(2000);
}

extern "C" {
    void app_main(void);
}

void app_main(void)
{

    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(GPIO_NUM_13, RMT_TX_CHANNEL);
    // set counter clock to 40MHz
    config.clk_div = 2;

    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

    // install ws2812 driver
    led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(LED_COUNT, (led_strip_dev_t)config.channel);
    led_strip_t *strip = led_strip_new_rmt_ws2812(&strip_config);
    if (!strip) {ESP_LOGE(TAG, "install WS2812 driver failed");}
    ESP_ERROR_CHECK(strip->clear(strip, 100));

    ColProc* processor = build_processor();

    for(;;) {
        uint32_t time = esp_timer_get_time() / 1000;

        processor->get_colors(time, color_buf, LED_COUNT);
        ESP_ERROR_CHECK(
            strip->set_pixels(strip, 0,LED_COUNT, 
            (const uint8_t*)(color_buf))
        );

        ESP_ERROR_CHECK(strip->refresh(strip, 100));
    }

}
