package com.android.server.led.hal;

import vendor.cocktail.hardware.led.ILed;
import android.os.IBinder;
import android.util.Log;
import android.os.RemoteException;
import android.annotation.Nullable;
import android.annotation.NonNull;
import android.util.Log;
import android.os.ServiceManager;

import java.util.Objects;

public final class LedAidl {
    static final String TAG = "LedAidl";
    private static final String LED_VENDOR_INTERFACE =
            "vendor.cocktail.hardware.led.ILed/default";
    
    private ILed mLed;

    public static @Nullable IBinder getService() {
        return ServiceManager.getService(LED_VENDOR_INTERFACE);
    }

    public LedAidl(@NonNull IBinder binder) {
        mLed = ILed.Stub.asInterface(binder);
    }

    public void setLed(int value) {
        try {
            mLed.setLed(value);
        } catch (RemoteException e) {
            Log.e(TAG, "setLed with " + value + "failed", e);
        }
    }

    public int getLed() {
        try {
            return mLed.getLed();
        } catch (RemoteException e) {
            Log.e(TAG, "getLed failed");
            
        }
        throw new IllegalArgumentException("get failed");
    }
}