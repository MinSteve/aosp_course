package com.cocktail.ledextendedapi;

import com.cocktail.ledextendedapi.ILedExtendedCallback;

interface ILedExtendedService {
    void setLed(int value);
    int getLed();

    /**
     * Register callback.
     *
     * @param callback callback to register.
     */
    void subscribe(in ILedExtendedCallback callback);
    /**
     * Unregister callback.
     *
     * @param callback callback to unregister.
     */
    void unsubscribe(in ILedExtendedCallback callback);
}