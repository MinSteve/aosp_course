package com.example.myaidl;

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
import android.widget.Toast;

public class MainActivity extends AppCompatActivity  implements View.OnClickListener{
    private static final String TAG ="MainActivity";
    IMyAidlInterface iADILService;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        View button1 = findViewById(R.id.button_1);
        button1.setOnClickListener(this);
    }

    @Override
    protected void onStart() {
        super.onStart();
        Intent intent = new Intent("IMyAidlInterface");
        intent.setPackage("com.example.myaidl");

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
            iADILService = IMyAidlInterface.Stub.asInterface(iBinder);
            Log.d(TAG, "Service Connected!!");
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            iADILService = null;
            Log.d(TAG, "Service Disconnected!!");
        }
    };

    @Override
    public void onClick(View view) {
        switch (view.getId()) {
            // TODO your logic to evaluate the indivual button
            case R.id.button_1:
                if (iADILService != null) {
                    try {
                        int color = iADILService.getColor();
                        view.setBackgroundColor(color);
                    } catch (RemoteException e) {
                        e.printStackTrace();
                    }
                }
                break;
        }
    }
}