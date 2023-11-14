package com.android.server.led;

import android.hardware.led.ILedService;
import android.os.IBinder;
import android.content.Context;
import android.util.Log;

import com.android.server.led.hal.LedAidl;

public class LedService extends ILedService.Stub {
    static final String TAG = "LedService";

    private final Object ImplLock = new Object();
    private IBinder mBinder;
    private Context mContext;
    private LedAidl mLedAidl;

    public LedService(Context context) {
        super();
        mContext = context;
        Log.i(TAG, "DTA: Start ledService");
    }

    private LedAidl getInstanceLedAidl() {
        if (mLedAidl == null) {
            IBinder binder = LedAidl.getService();
            if (binder != null) {
                Log.i(TAG, "Create new binder to vendor Led AIDL");
                return new LedAidl(binder);
            }
        }
        return mLedAidl;
    }

    public void setLed(int value) {
        synchronized (ImplLock) {
            getInstanceLedAidl().setLed(value);
        }   
    }

    public int getLed() {
        synchronized (ImplLock) {
            return getInstanceLedAidl().getLed();
        }
    }
}