## compile java to dex format
javac TestJava.java
d8 TestJava.class --output TestJava.jar
adb push TestJava.jar /data/local/tmp/

## run by app_process
adb shell CLASSPATH=/data/local/tmp/TestJava.jar app_process ./ com.example.TestJava

## run by android runtime
adb push out/target/product/rpi4/system/bin/native_start_java /data/local/tmp
adb shell CLASSPATH=/data/local/tmp/TestJava.jar /data/local/tmp/native_start_java
adb logcat | grep TestJava
