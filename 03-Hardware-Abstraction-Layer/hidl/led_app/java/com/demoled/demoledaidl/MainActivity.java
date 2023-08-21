package com.demoled.demoledaidl;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity  implements View.OnClickListener{
    private static final String TAG ="MainActivity";
    IDemoLedAidlInterface iADILService;
    private TextView text_view;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "MainActivity: onCreate function is called");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        View button_on = findViewById(R.id.button_on);
        button_on.setOnClickListener(this);

	View button_off = findViewById(R.id.button_off);
	button_off.setOnClickListener(this);

	View buttion_get_val = findViewById(R.id.button_getval);
	buttion_get_val.setOnClickListener(this);

	text_view = findViewById(R.id.Led_status);
    }

    @Override
    protected void onStart() {
        super.onStart();
	Log.i(TAG, "MainActivity: onStart() function is called");
        Intent intent = new Intent("com.demoled.demoledaidl.AIDLService");
        intent.setPackage("com.demoled.demoledaidl");

        bindService(intent, mConnection, BIND_AUTO_CREATE);
    }

    @Override
    protected void onStop() {
        super.onStop();
        unbindService(mConnection);
    }

    private ServiceConnection mConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
            Log.i(TAG, "onServiceConnected() function is called");
            iADILService = IDemoLedAidlInterface.Stub.asInterface(iBinder);
            Log.i(TAG, "Service Connected!!");
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            iADILService = null;
            Log.i(TAG, "Service Disconnected!!");
        }
    };

    @Override
    public void onClick(View view) {
        Log.i(TAG, "onClick() function is called");
        switch (view.getId()) {
            // TODO your logic to evaluate the indivual button
            case R.id.button_on:
                Log.i(TAG, "case R.id.button_on is called");
                if (iADILService != null) {
                    try {
			Log.i(TAG, "click button on");
                        iADILService.TurnLedOn();
                    } catch (RemoteException e) {
                        e.printStackTrace();
                    }
                }
                break;
            case R.id.button_off:
                Log.i(TAG, "case R.id.button_off is called");
		if (iADILService != null) {
			try {
				iADILService.TurnLedOff();
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
		break;
	    case R.id.button_getval:
		int val;
		Log.i(TAG, "case R.id.button_getval is called");
		if (iADILService != null) {
			try {
				val = iADILService.GetLedStatus();
				text_view.setText("Led status:" + val);
			} catch (RemoteException e) {
				e.printStackTrace();
			}
		}
        }
    }
}
