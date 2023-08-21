// IDemoLedAidlInterface.aidl
package com.demoled.demoledaidl;

// Declare any non-default types here with import statements

interface IDemoLedAidlInterface {
    /**
     * Demonstrates some basic types that you can use as parameters
     * and return values in AIDL.
     */
    int GetLedStatus();
    void TurnLedOn();
    void TurnLedOff();
}
