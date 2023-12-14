/*
 * Copyright (C) 2023 Dung Tran Anh
 */

package vendor.cocktail.hardware.led;

/**
 * Extended interface for Assisted GNSS support.
 */
@VintfStability
interface ILed {
    /**
     * Set status of the led
     *
     * @param status Value will be set for the led.
     */
    void setLed(in int status);

    /**
     * Get status of the led
     */
    int getLed();
}