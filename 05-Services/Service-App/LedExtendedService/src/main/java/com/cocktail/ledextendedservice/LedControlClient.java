package com.cocktail.ledextendedservice;

import vendor.cocktail.hardware.led.ILed;
import android.os.IBinder;
import android.os.Binder;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.util.Log;
import android.util.Slog;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.util.List;
import java.util.Objects;

import androidx.annotation.Nullable;


public class LedControlClient {
    public static final String TAG = "LedControlClient";
    private static final String LED_CONTROL_SERVICE =
            "vendor.cocktail.hardware.led.ILed/default";
    private static LedControlClient mLedControlClient;
    private Ibinder mBinder;
    private ILed mLed;
    private boolean mListenerRegistered = false;
    static @Nullable IBinder getService() {
        return Binder.allowBlocking(ServiceManager.waitForDeclaredService(
                LED_CONTROL_SERVICE));
    }

    public LedControlClient() {
        init();
    }

    public static LedControlClient getLedControlClient() {
        if (mLedControlClient == null) {
            mLedControlClient = new LedControlClient();
        }
        return mLedControlClient;
    }

    public void init() {
        mBinder = Object.requireNonNull(getService());
        mLed = ILed.Stub.asInterface(mBinder);
    }

    public void setLed(int value) {
        try {
            mLed.setLed(value);
        } catch (RemoteException e) {
            Log.e(TAG, "setLed with " + value + " failed");
        }
    }

    public int getLed() {
        try {
            return mLed.getLed();
        } catch (RemoteException e) {
            Log.e(TAG, "getLed failed " + e);
        }
    }
}