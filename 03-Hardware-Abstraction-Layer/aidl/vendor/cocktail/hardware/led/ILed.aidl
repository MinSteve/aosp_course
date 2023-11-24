package vendor.cocktail.hardware.led;

@VintfStability
interface ILed {
    void setLed(in int status);
    int getLed();
}