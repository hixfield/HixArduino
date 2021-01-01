#ifndef HixColor_h
#define HixColor_h

#include <Arduino.h>

//different colors
class HixColor {
   private:
    uint32_t m_nColor;
    uint32_t hexCharToInt(char c);

   public:
    //default colors
    static const uint32_t black = 0x000000;
    static const uint32_t white = 0xFFFFFF;
    static const uint32_t red = 0xFF0000;
    static const uint32_t green = 0x00FF00;
    static const uint32_t blue = 0x0000FF;
    static const uint32_t orange = 0xFF8C00;
    static const uint32_t magenta = 0xFF00FF;
    //constructor
    HixColor(uint32_t nColor = HixColor::black);
    HixColor(const char* szRGBString);
    //getters/setters
    uint32_t getRGB(void);
    void setRGB(uint32_t nColor);
    //utility functions
    uint32 getDimmedWithPercent(uint8_t nDimPercent);
};

#endif
