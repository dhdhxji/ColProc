#ifndef TEXT_H
#define TEXT_H

#include "colproc/gen/generator.h"
#include "colproc/variable/variable.h"
#include "mcufont.h"
#include <string>
#include <stdexcept>


class GeneratorText: public Generator
{
public:
    GeneratorText(Variable<std::string>* text, Variable<std::string>* font) {
        _text = text;
        _font = font;
    }

    struct render_ctx_t
    {
        GeneratorText* gen;
        Canvas* canv;
    };
    

    virtual void generate(uint32_t time, Canvas* canvas) override {
        render_ctx_t ctx = {
            .gen = this,
            .canv = canvas
        };
        
        const mf_font_s* font = mf_find_font(_font->getValue().c_str());
        if(font == nullptr) {
            throw std::runtime_error(
                std::string("Font \"") +
                _font->getValue() + 
                "\" not found" 
            );
        }
        
        mf_render_aligned(
            font, 
            0,
            0, 
            MF_ALIGN_LEFT,
            _text->getValue().c_str(),
            _text->getValue().length(),
            char_callback,
            &ctx
        );
    }

protected:
    static void pixel_callback(
        int16_t x, 
        int16_t y, 
        uint8_t count, 
        uint8_t alpha, 
        void *state) 
    {
        while (count--) {
            Canvas* c = reinterpret_cast<render_ctx_t*>(state)->canv;
            if(x < 0 || x >= c->getW() || 
               y < 0 || y >= c->getH()) 
            {
                continue;
            }

            c->setPix(x, y, ColRGB(255, 255, 255));

            x++;
        }
    }

    static uint8_t char_callback(
        int16_t x0, 
        int16_t y0, 
        mf_char character, 
        void *state) 
    {
        return mf_render_character(
            mf_find_font(
                reinterpret_cast<render_ctx_t*>(state)->gen->_font->getValue().c_str()
            ), 
            x0, 
            y0, 
            character, 
            &pixel_callback, 
            state
        );
    }

protected:
    Variable<std::string>* _text;
    Variable<std::string>* _font;
};

#endif // TEXT_H
