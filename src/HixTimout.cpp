#include "HixTimeout.h"
#include <Arduino.h>


HixTimeout::HixTimeout(unsigned long ulDelayMs, bool bInvalidated) {
  updateTimeoutAndRestart(ulDelayMs);
  m_bInvalidated = bInvalidated;
}

bool HixTimeout::isExpired(bool bRestartIfExpired) {
  //if I am invalidated return expired immediatly
  if (m_bInvalidated) {
    if  (bRestartIfExpired) {
      restart();
    }
    return true;
  }
  //depending on overflow do different calculations
  bool ret = currentDiff() > ((float)m_ulDelayMs);
  //restart if requested
  if (ret && bRestartIfExpired) {
    restart();
  }
  //return our value
  return ret;
}

bool HixTimeout::isRunning(void) {
  return !isExpired(false);
}

void HixTimeout::restart(void) {
  m_bInvalidated = false;
  m_ulStart = millis();
}

void HixTimeout::updateTimeoutAndRestart(unsigned long ulDelayMs) {
  m_ulDelayMs = ulDelayMs;
  restart();
}

void HixTimeout::invalidate() {
  m_bInvalidated = true;
}

bool HixTimeout::isInvalidated() {
  return m_bInvalidated;
}

float HixTimeout::currentDiff(void) {
  float fStart   = m_ulStart;
  float fCurrent = millis();
  float fDiff    = fCurrent - fStart;
  float fMaxUL   = (unsigned long) 0xFFFFFFFF;
  if (fDiff < 0) {
    fDiff += fMaxUL;
  }
  return fDiff;
}

unsigned long HixTimeout::timeLeftMs(void) {
  return m_ulDelayMs - timePastMs();
}

unsigned long HixTimeout::timePastMs(void) {
  return ( isExpired(false) ) ? 0 : currentDiff();
}

unsigned long HixTimeout::timeoutMs(void) {
  return m_ulDelayMs;
}
