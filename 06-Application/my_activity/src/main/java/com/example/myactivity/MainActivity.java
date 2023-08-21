package com.example.myactivity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Toast;
import android.util.Log;
import android.os.ServiceManager;
import android.os.IBinder;
import arpi.hardware.helloaidl.IHello;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toast.makeText(this, "onCreate() - first method to be called!", Toast.LENGTH_SHORT).show();
    }

    public void onStart() {
        super.onStart();
        Toast.makeText(this, "onStart() - activity just started!", Toast.LENGTH_SHORT).show();
    }

    public void onResume() {
        super.onResume();
        Toast.makeText(this, "onResume() - activity in foreground and running!", Toast.LENGTH_SHORT).show();
    }

    public void onPause() {
        super.onPause();
        Toast.makeText(this, "onPause() - activity want to background!", Toast.LENGTH_SHORT).show();
    }

    public void onStop() {
        super.onStop();
        Toast.makeText(this, "onStop() - activity in background!", Toast.LENGTH_SHORT).show();
    }

    public void onRestart() {
        super.onRestart();
        Toast.makeText(this, "onRestart() - activity is restarting!", Toast.LENGTH_SHORT).show();
    }

    public void onDestroy() {
        super.onDestroy();
        Toast.makeText(this, "onDestroy() - releasing all resources!", Toast.LENGTH_SHORT).show();
    }
}
