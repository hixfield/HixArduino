#include "HixColor.h"

HixColor::HixColor(uint32_t nColor) : m_nColor(nColor) {
}

HixColor::HixColor(const char* szRGBString) {
    //must always have 6 characters
    if (strlen(szRGBString) < 6) {
        m_nColor = 0;
        return;
    }
    //storin components
    const uint32_t hexBase = 16;
    uint32_t nR = hexCharToInt(szRGBString[5]) * hexBase + hexCharToInt(szRGBString[4]);
    uint32_t nG = hexCharToInt(szRGBString[3]) * hexBase + hexCharToInt(szRGBString[2]);
    uint32_t nB = hexCharToInt(szRGBString[1]) * hexBase + hexCharToInt(szRGBString[0]);
    //reassemble
    m_nColor= (nR << 16) | (nG << 8) | nB;
}

uint32_t HixColor::getRGB(void) {
    return m_nColor;
}

void HixColor::setRGB(uint32_t nColor) {
    m_nColor = nColor;
}

uint32_t HixColor::getDimmedWithPercent(uint8 nDimPercent) {
    //full power does not need calculations
    if (nDimPercent >= 100) return m_nColor;
    //make base colors
    uint32_t nR = m_nColor >> 16;
    uint32_t nG = (m_nColor & 0x00FF00) >> 8;
    uint32_t nB = m_nColor & 0x0000FF;
    //dim individual components
    nR = ((nR * (uint32_t)nDimPercent) / (uint32_t)100) & 0x0000FF;
    nG = ((nG * (uint32_t)nDimPercent) / (uint32_t)100) & 0x0000FF;
    nB = ((nB * (uint32_t)nDimPercent) / (uint32_t)100) & 0x0000FF;
    //reassemble
    return (nR << 16) | (nG << 8) | nB;
}