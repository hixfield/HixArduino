#include "HixColor.h"

HixColor::HixColor(uint32_t nColor) : m_nColor(nColor) {
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
