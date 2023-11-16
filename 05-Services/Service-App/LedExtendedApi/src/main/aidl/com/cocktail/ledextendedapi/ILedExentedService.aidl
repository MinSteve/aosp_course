// ILedExentedService.aidl
package com.cocktail.ledextendedapi;

import com.cocktail.ledextendedapi.ILedExtendedCallback;

interface ILedExentedService {
    void setLed(int value);
    int getLed();
}