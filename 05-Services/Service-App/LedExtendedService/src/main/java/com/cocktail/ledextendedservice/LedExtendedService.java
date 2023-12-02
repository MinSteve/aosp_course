package com.cocktail.ledextendedservice;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.drawable.Icon;
import android.content.Intent;
import android.content.Context;
import android.os.IBinder;
import android.util.Log;

public class LedExtendedService extends Service {
    public static final String TAG = LedExtendedService.class.getSimpleName();
    private LedExtendedServiceImpl mService;
    private Bitmap mTestBitmap;

    @Override
    public void onCreate() {
        super.onCreate();
        mService = new LedExtendedServiceImpl(this);
        Log.d(TAG, "LedExtendedService created");
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        startForeground();
        Log.d(TAG, "LedExtendedService start");
        return START_STICKY;
    }

    @Override
    public synchronized IBinder onBind(Intent intent) {
        if (mService == null) {
            mService = new LedExtendedServiceImpl(this);
        }
        Log.d(TAG, "LedExtendedService bind");
        return mService;
    }

    @Override
    public void onDestroy() {
        Log.d(TAG, "LedExtendedService destroyed");
        mService = null;
        super.onDestroy();
    }

    Icon createNotificationIcon() {
        mTestBitmap = Bitmap.createBitmap(50, 50, Bitmap.Config.ARGB_8888);
        final Canvas canvas = new Canvas(mTestBitmap);
        canvas.drawColor(Color.BLUE);
        return Icon.createWithBitmap(mTestBitmap);
    }

    private void startForeground() {
        final NotificationChannel channel = new NotificationChannel("Cocktail/LedExtendedService",
                "LedExtendedService", NotificationManager.IMPORTANCE_NONE);
        channel.setLockscreenVisibility(Notification.VISIBILITY_PRIVATE);

        final NotificationManager notificationManager =
                (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
        notificationManager.createNotificationChannel(channel);

        final Notification.Builder notificationBuilder =
                new Notification.Builder(this, "Cocktail/LedExtendedService");

        final Notification notification = notificationBuilder.setOngoing(true)
                .setContentTitle("App is running")
                .setSmallIcon(createNotificationIcon())
                .setCategory(Notification.CATEGORY_SERVICE)
                .setContentText("Context")
                .build();
        startForeground(1, notification);
        Log.i(TAG, "starting foreground service!!!!");
    }
}