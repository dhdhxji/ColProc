#include "colproc/canvas/canvas_strip.h"

#include <cstring>
#include "led_strip.h"
#include "esp_log.h"

const char* TAG = "CanvasString";

CanvasStrip::CanvasStrip(
    size_t w, size_t h, 
    strip_mode_t mode, 
    rmt_channel_t ch,
    gpio_num_t pin
): 
    Canvas(w, h) 
{
    _color_buffer = new uint8_t[_bufferSize()];
    memset(_color_buffer, 0, _bufferSize());
    _mode = mode;

    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(GPIO_NUM_13, ch);
    // set counter clock to 40MHz
    config.clk_div = 2;

    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

    // install ws2812 driver
    led_strip_config_t strip_config = 
        LED_STRIP_DEFAULT_CONFIG(getW()*getH(), (led_strip_dev_t)config.channel);
    _strip = led_strip_new_rmt_ws2812(&strip_config);
    
    if (!_strip) {ESP_LOGE(TAG, "install WS2812 driver failed");}
    ESP_ERROR_CHECK(_strip->clear(_strip, 100));
}

CanvasStrip::~CanvasStrip() {
    delete[] _color_buffer;
}

void CanvasStrip::setPix(size_t x, size_t y, ColRGB col) {
    color_grb_t* pix = _getPixPtr(x, y);
    if(pix != nullptr) {
        *pix = color_grb_t(col);
    }
}

ColRGB CanvasStrip::getPix(size_t x, size_t y) const {
    color_grb_t* pix = _getPixPtr(x, y);
    if(pix != nullptr) {
        return *pix;
    } else {
        return ColRGB(0, 0, 0);
    }
}

void CanvasStrip::display() const {
    ESP_ERROR_CHECK(
        _strip->set_pixels(
            _strip, 
            0,
            getW() * getH(), 
            _color_buffer
        )
    );

    ESP_ERROR_CHECK(_strip->refresh(_strip, 100));
}

CanvasStrip::color_grb_t* CanvasStrip::_getPixPtr(size_t x, size_t y) const {
    // Check bounds
    if(y >= getH() || x >= getW()) {
        return nullptr;
    }

    // According to mode transform coordinates to an index
    size_t index;
    if(_mode == MODE_CONTINUOUS) {
        index = y*getW() + x;
    } else if(_mode == MODE_ZIGZAG) {
        index = y*getW() + ( (y%2 == 0) ? x:(getW()-1-x) );
    } else {
        return nullptr;
    }

    return &((color_grb_t*)_color_buffer)[index];
}

size_t CanvasStrip::_bufferSize() {
    return sizeof(color_grb_t) * getW() * getH();
}