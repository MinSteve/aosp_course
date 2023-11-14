package android.hardware.led;

import android.annotation.IntDef;
import android.annotation.NonNull;
import android.annotation.Nullable;
import android.annotation.SystemApi;
import android.annotation.SystemService;
import android.os.ServiceManager.ServiceNotFoundException;
import android.content.Context;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

import android.os.RemoteException;

@SystemService(Context.LED_SERVICE)
public class LedManager {
    private static final String TAG = "LedManager";
    
    @NonNull private final Context mContext;
    private static ILedService mLedService;

    public static final int LED_OFF = 0;
    public static final int LED_ON = 1;
    
    /**
     * Creates an LedManager
     * 
     *  @hide
     */
    public LedManager(@NonNull Context context) throws ServiceNotFoundException {
        this(context, ILedService.Stub.asInterface(
            ServiceManager.getServiceOrThrow(Context.LED_SERVICE)));
    }

    /**
     * Creates a LedManager with a provided service implementation.
     *
     * @hide
     */
    public LedManager(@NonNull Context context, @NonNull ILedService service) {
        mContext = context;
        mLedService = service;
        Log.d(TAG, "InvcaseManager: mContext= " + mContext + " mService= " + mLedService);
    }

    public void setLed(int value) {
        try {
            mLedService.setLed(value);
        } catch (RemoteException e) {
            throw e.rethrowFromSystemServer();
        }
    }

    @Nullable
    public int getLed() {
        try {
            return mLedService.getLed();
        } catch (RemoteException e) {
            throw e.rethrowFromSystemServer();
        }
    }
}