package com.demoled.demoledaidl;

import android.app.Service;
import android.content.Intent;
import android.graphics.Color;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import java.util.Random;
import arpi.hardware.demoled.V1_0.IDemoled;

public class AIDLService extends Service {
    private static final String TAG ="Demoled:";
    private IDemoled Demoled;

    public AIDLService() {
	    try {
		    Log.i(TAG, "AIDLService is called");
		    Demoled = IDemoled.getService(true);
	    } catch(Exception ec) {
		    Log.d(TAG, "Cannot get IDemoled service");
	    }
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        return binder;
    }

    private final IDemoLedAidlInterface.Stub binder = new IDemoLedAidlInterface.Stub() {
	public int GetLedStatus()
	{
		int val;
		try {
			Log.d(TAG, "Jumpt to GetLedStatus function");
			val = Demoled.read_led_status();
			return val;
		} catch (RemoteException e) {
			e.printStackTrace();
			return -1;
		}
        }

	public void TurnLedOn()
	{
		try {
			Log.d(TAG, "Jumpt to TurnLedOn function");
			Demoled.turn_led_on();
		} catch (RemoteException e) {
			e.printStackTrace();
		}
	}

	public void TurnLedOff()
	{
		try {
			Log.d(TAG, "Jumpt to TurnLedOff function");
			Demoled.turn_led_off();
		} catch (RemoteException e) {
			e.printStackTrace();
		}
	}
    };
}
