// ILedExentedCallback.aidl
package com.cocktail.ledextendedapi;

/**
 * Binder interface to callback the settings key events.
 *
 * @hide
 */
interface ILedExtendedCallback {
    /**
     * Demonstrates some basic types that you can use as parameters
     * and return values in AIDL.
     */
    void onGetLed();
}