package com.cocktail.ledextendedservice;

import android.content.Context;
import android.os.RemoteCallbackList;
import android.os.RemoteException;
import android.util.Log;

import com.cocktail.ledextendedapi.ILedExtendedService;
import com.cocktail.ledextendedapi.ILedExtendedCallback;

public class LedExtendedServiceImpl extends ILedExtendedService.Stub {
    public static final String TAG = "LedExtendedServiceImpl";
    private int mValue;
    public LedExtendedServiceImpl(Context context) {
        Log.d(TAG, "Construct service Impl");
        mContext = context;
        mLedControlClient = LedControlClient.getLedControlClient();
    }
    private Context mContext;
    private LedControlClient mLedControlClient;
    private final RemoteCallbackList<ILedExtendedCallback> subscribers = new RemoteCallbackList<>();

    @Override
    public void subscribe(ILedExtendedCallback callback) {
        try {
            subscribers.register(callback);
        } catch (Exception e) {
            Log.e(TAG, "Failed to subscribe", e);
        }
    }

    @Override
    public void unsubscribe(ILedExtendedCallback callback) {
        try {
            subscribers.unregister(callback);
        } catch (Exception e) {
            Log.e(TAG, "Failed to unsubscribe", e);
        }
    }

    @Override
    public int
}