package android.hardware.led;

/**
 * API to led service.
 *
 * {@hide}
 */
interface ILedService {
    void setLed(int value);
    int getLed();
}