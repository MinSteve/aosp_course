```diff
 # memtrack
 /(vendor|system/vendor)/bin/hw/android\.hardware\.memtrack-service\.imx       u:object_r:hal_memtrack_default_exec:s0
 
+# led demo
+/(vendor|system/vendor)/bin/hw/vendor\.cocktail\.hardware\.led-service  u:object_r:hal_led_default_exec:s0
+
 # hantro v4l2 daemon
 /vendor/bin/vsidaemon                         u:object_r:vsidaemon_exec:s0
 /dev/vsi_daemon_ctrl                          u:object_r:vsi_daemon_ctrl_device:s0
```
*imx8m/sepolicy/file_contexts*
<br/>
<br/>


```diff
 android.hardware.drm.IDrmFactory/widevine u:object_r:hal_drm_service:s0
+vendor.cocktail.hardware.led.ILed/default u:object_r:hal_led_service:s0
\ No newline at end of file
```
*imx8m/sepolicy/service_contexts*
<br/>
<br/>