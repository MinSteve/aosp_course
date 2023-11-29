package com.cocktail.ledextendedmanager;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import androidx.annotation.NonNull;

import com.cocktail.ledextendedapi.ILedExtendedCallback;
import com.cocktail.ledextendedapi.ILedExtendedService;

public class LedExtendedManager {
    private static final String TAG = "LedExtendedManager";
    private static final String LED_SETTINGS_PACKAGE = "com.cocktail.audioextendedservice";
    private static final String LED_SETTINGS_CLASS =
            "com.cocktail.ledextendedservice.LedExtendedService";
    private boolean mBound;
    private final Context mContext;

    ILedExtendedService mService;

    private final ServiceConnection mServiceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            Log.i(TAG, "Connected to service");
            mService = ILedExtendedService.Stub.asInterface(service);
            mBound = true;
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            Log.i(TAG, "Disconnected from service");
            mService = null;
            mBound = false;
        }
    };

    public LedExtendedManager(@NonNull Context context) {
        mContext = context;
    }

    public void connectToService() throws RemoteException {
        Intent intent = new Intent();
        intent.setComponent(new ComponentName(LED_SETTINGS_PACKAGE, LED_SETTINGS_CLASS));

        if (!mContext.bindService(intent, mServiceConnection, Context.BIND_AUTO_CREATE)) {
            Log.e(TAG, "Couldn't connectToService");
            throw new RemoteException("Failed to bind to service");
        }
    }

    public void disconnectedToService() throws RemoteException {
        if (mBound) {
            if (mService != null) {
                mContext.unbindService(mServiceConnection);
            }
        }
    }

    public void disconnectFromService() {
        if (mService != null) {
            mContext.unbindService(mServiceConnection);
        }
    }

    public void subscribe(@NonNull ILedExtendedCallback callback) throws RemoteException {
        if (mService == null) {
            throw new RemoteException("Service not connected");
        }
        mService.subscribe(callback);
    }

    public void unsubscribe(@NonNull ILedExtendedCallback callback) throws RemoteException {
        if (mService == null) {
            throw new RemoteException("Service not connected");
        }
        mService.unsubscribe(callback);
    }

    /**
     * Set on/off for the led
     *
     * @param value 1 is ON and 0 is OFF.
     */
    public void setLed(int value) {
        Log.d(TAG, "setLed with " + value);
        try {
            mService.setLed(value);
        } catch (RemoteException e) {
            Log.e(TAG, "Error running setLed", e);
        }
    }

    /**
     * Get current of led status
     *
     * @return Led status. Return -1 is failed.
     */
    public int getLed() {
        Log.d(TAG, "getLed");
        try {
            return mService.getLed();
        } catch (RemoteException e) {
            Log.e(TAG, "Error running getLed", e);
            return -1;
        }
    }
}
