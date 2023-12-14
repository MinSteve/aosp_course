```diff
             <instance>default</instance>
         </interface>
     </hal>
+    <hal format="aidl" option="true">
+        <name>vendor.cocktail.hardware.led</name>
+        <version>1</version>
+        <interface>
+            <name>ILed</name>
+            <instance>default</instance>
+        </interface>
+    </hal>
 </compatibility-matrix>
```
*imx8m/evk_8mm/device_framework_matrix.xml*
<br/>
<br/>

```diff
     c2_component_register_ms \
     c2_component_register_ra
 
+PRODUCT_PACKAGES += \
+    vendor.cocktail.hardware.led \
+    vendor.cocktail.hardware.led-service
+
 ifeq ($(PREBUILT_FSL_IMX_CODEC),true)
 ifneq ($(IMX8_BUILD_32BIT_ROOTFS),true)
 INSTALL_64BIT_LIBRARY := true
```
*imx8m/evk_8mm/evk_8mm.mk*
<br/>
<br/>