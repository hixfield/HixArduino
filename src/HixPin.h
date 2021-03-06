#ifndef HixPin_h
#define HixPin_h

class HixPin {
   protected:
    const int m_nPinNumber;

   public:
    int getPinNumber();
    HixPin(int nPinNumber);
    virtual bool begin() = 0;
};

#endif
