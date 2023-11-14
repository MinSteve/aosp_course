# System Service

## File Structure




## Implement source code


**Define a name of Led Service**

```diff
             //@hide: ATTESTATION_VERIFICATION_SERVICE,
             //@hide: SAFETY_CENTER_SERVICE,
             DISPLAY_HASH_SERVICE,
+            LED_SERVICE,
     })
     @Retention(RetentionPolicy.SOURCE)
     public @interface ServiceName {}
@@ -5067,6 +5068,8 @@ public abstract class Context {
      */
     public static final String SOUND_TRIGGER_SERVICE = "soundtrigger";
 
+    public static final String LED_SERVICE = "led";
+
     /**
      * Use with {@link #getSystemService(String)} to access the
      * {@link com.android.server.soundtrigger_middleware.SoundTriggerMiddlewareService}.
```
*frameworks/base/core/java/android/content/Context.java*
<br/>
<br/>

**Define the Service Interface**

User AIDL to describe public functions exported by the Service:

```aidl
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
```
*frameworks/base/core/java/android/hardware/led/ILedService.aidl*
<br/>
<br/>

**Implement the Service Manager**

User application will call to the functions of the Service Manager, not directly calling to the actual service interface.

*frameworks/base/core/java/android/hardware/led/LedManager.java*
<br/>
<br/>

**Implement the Service**

The Service will implement the actual code for Service Interface functions by extending the <Interface>.Stub class.

*frameworks/base/services/core/java/com/android/server/led/LedService.java*
<br/>
<br/>

**Implement the LED HAL Service**

*frameworks/base/services/core/java/com/android/server/led/hal/LedAidl.java*
<br/>
<br/>

**Add System Service in the System Server**

```diff
 import com.android.server.wm.ActivityTaskManagerService;
 import com.android.server.wm.WindowManagerGlobalLock;
 import com.android.server.wm.WindowManagerService;
+import com.android.server.LedService;
 
 import dalvik.system.VMRuntime;
 
@@ -1419,6 +1420,7 @@ public final class SystemServer implements Dumpable {
         MmsServiceBroker mmsService = null;
         HardwarePropertiesManagerService hardwarePropertiesService = null;
         PacProxyService pacProxyService = null;
+        LedService ledService = null;
 
         boolean disableSystemTextClassifier = SystemProperties.getBoolean(
                 "config.disable_systemtextclassifier", false);
@@ -1466,6 +1468,10 @@ public final class SystemServer implements Dumpable {
                 }
             }, SECONDARY_ZYGOTE_PRELOAD);
 
+            t.traceBegin("StartLedService");
+            ServiceManager.addService("led", new LedService(context));
+            t.traceEnd();
+
             t.traceBegin("StartKeyAttestationApplicationIdProviderService");
             ServiceManager.addService("sec_key_att_app_id_provider",
                     new KeyAttestationApplicationIdProviderService(context));
```
*frameworks/base/services/java/com/android/server/SystemServer.java*
<br/>
<br/>

**Register the Service Manager**

```diff
 import android.telephony.TelephonyFrameworkInitializer;
 import android.telephony.TelephonyRegistryManager;
 import android.transparency.BinaryTransparencyManager;
+import android.hardware.led.LedManager;
 import android.util.ArrayMap;
 import android.util.Log;
 import android.util.Slog;
@@ -1502,6 +1503,14 @@ public final class SystemServiceRegistry {
                     }
                 });
 
+        registerService(Context.LED_SERVICE, LedManager.class,
+                new CachedServiceFetcher<LedManager>() {
+                    @Override
+                    public LedManager createService(ContextImpl ctx) {
+                        return new LedManager(ctx);
+                    }
+                });
+
         registerService(Context.AMBIENT_CONTEXT_SERVICE, AmbientContextManager.class,
                 new CachedServiceFetcher<AmbientContextManager>() {
                     @Override
```
*frameworks/base/core/java/android/app/SystemServiceRegistry.java*
<br/>
<br/>

**Add HAL AIDL Lib for Led Service**

```diff
@@ -167,6 +167,7 @@ java_library_static {
         "android.hardware.power.stats-V1-java",
         "android.hardware.power-V3-java",
         "android.hidl.manager-V1.2-java",
+        "vendor.cocktail.hardware.led-V1-java",
         "capture_state_listener-aidl-java",
         "icu4j_calendar_astronomer",
         "netd-client",
```
*frameworks/base/services/core/Android.bp*
<br/>
<br/>

## Build

1. Build the new source code:

`$ cd frameworks/base/services/core`

`$ mm`

2. If you get notify that need to update API, run command:

`$ cd frameworks/base/services/core`

`$ m api-stubs-docs-non-updatable-update-current-api`

3. After fix, run again step 1 

