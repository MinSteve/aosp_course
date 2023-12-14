# Service Application

## Implement source code

**Define the Service Interface**
<br/>
<br/>

**Define the Service Manager**
<br/>
<br/>

**Define the Public API for application**
<br/>
<br/>

**Add SELinux permission**

Copy *led_extended_service* folder to *device/imx8/imx8mm/sepolicy/components*
<br/>
<br/>

**Add Service in the System**
```diff
+
+# LedExtendedService
+PRODUCT_PACKAGES += CocktailLedExtendedService
+
```
*imx8m/evk_8mm/evk_8mm.mk*


## Test

1. Copy LedExtendedApi, LedExtendedManager and LedExtendedService in */vendor/cocktail/components*

2. Build source code to file.jar

3. Copy file.jar to App/libs folder in Android Studio

4. Build App as apk file and

5. Connect device and check `adb device` is available

6. Connect device to Android Studio and test or install apk file by command:
`$adb install -r file.apk`


## Build all source code in AOSP

1. Copy all source code (except led_extended_service folder)

2. Build and run in device