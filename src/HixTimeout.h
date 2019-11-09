#ifndef HixTimeout_h
#define HixTimeout_h

class HixTimeout {

  private:

    unsigned long m_ulDelayMs;
    unsigned long m_ulStart;
    bool          m_bInvalidated;

    float currentDiff(void);

  public:

    HixTimeout(unsigned long ulDelayMs, bool bInvalidated = false);
    void restart(void);
    void invalidate(void);
    bool isExpired(bool bRestartIfExpired = false);
    bool isRunning(void);
    bool isInvalidated(void);
    void updateTimeoutAndRestart(unsigned long ulDelayMslyMs);
    unsigned long timeLeftMs(void);
    unsigned long timePastMs(void);
    unsigned long timeoutMs(void);

};

#endif