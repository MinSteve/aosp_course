package com.example.myservice;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

import java.util.Random;

public class LocalService extends Service {
    private static final String TAG = "LocalService";

    private final IBinder binder = new LocalBinder();
    private final Random mGenerator = new Random();

    public class LocalBinder extends Binder {
        LocalService getService() {
            // Return this instance of LocalService so clients can call public methods.
            return LocalService.this;
        }
    }

    public LocalService() {
    }

    @Override
    public void onCreate() {
        Log.d(TAG, "LocalService onCreate");
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.d(TAG, "LocalService binding");
        return binder;
    }

    public int getRandomNumber() {
        return mGenerator.nextInt(100);
    }

    @Override
    public void onDestroy() {
        Log.d(TAG, "LocalService destroy");
    }
}