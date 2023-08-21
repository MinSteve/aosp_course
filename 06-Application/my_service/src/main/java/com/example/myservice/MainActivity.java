package com.example.myservice;

import androidx.appcompat.app.AppCompatActivity;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private static final String TAG = "MainActivity";
    LocalService mLocalService;
    Messenger  mMessengerService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        View button1 = findViewById(R.id.button_1);
        View button2 = findViewById(R.id.button_2);

        button1.setOnClickListener(this);
        button2.setOnClickListener(this);
    }

    @Override
    protected void onStart() {
        super.onStart();
        // Bind to LocalService
        Intent intent1 = new Intent(this, LocalService.class);
        bindService(intent1, localConnection, Context.BIND_AUTO_CREATE);

        // Bind to MessengerService
        Intent intent2 = new Intent(this, MessengerService.class);
        bindService(intent2, messengerConnection, Context.BIND_AUTO_CREATE);

    }

    @Override
    protected void onStop() {
        super.onStop();
        unbindService(localConnection);
        unbindService(messengerConnection);
    }

    // implement ServiceConnection for LocalBinder
    private ServiceConnection localConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName className,
                                       IBinder service) {
            // We've bound to LocalService, cast the IBinder and get LocalService instance.
            LocalService.LocalBinder binder = (LocalService.LocalBinder) service;
            mLocalService = binder.getService();
        }

        @Override
        public void onServiceDisconnected(ComponentName arg0) {
            mLocalService = null;
        }
    };

    // implement ServiceConnection for Messenger
    private ServiceConnection messengerConnection = new ServiceConnection() {

        @Override
        public void onServiceConnected(ComponentName className,
                                       IBinder service) {
            mMessengerService = new Messenger(service);
        }

        @Override
        public void onServiceDisconnected(ComponentName arg0) {
            mMessengerService = null;
        }
    };

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            // TODO your logic to evaluate the indivual button
            case R.id.button_1:
                Log.d(TAG, "onClick: button_1");
                if (mLocalService != null) {
                    int num = mLocalService.getRandomNumber();
                    Toast.makeText(this, "number: " + num, Toast.LENGTH_SHORT).show();
                }
                break;

            case R.id.button_2:

                if (mMessengerService != null) {
                    Message msg = Message.obtain(null, MessengerService.MSG_SAY_HELLO, 0, 0);
                    try {
                        mMessengerService.send(msg);
                    } catch (RemoteException e) {
                        e.printStackTrace();
                    }
                }
                break;
            default:
                Log.d(TAG, "onClick: Undefine behaviour");
        }
    }
}