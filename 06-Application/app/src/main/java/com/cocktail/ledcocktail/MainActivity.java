package com.cocktail.ledcocktail;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.RemoteException;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.util.Log;

import com.cocktail.ledextendedmanager.*;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "LedCocktailApp";
    private LedExtendedManager mLedManager;
    private Button setOn, setOff;
    private TextView ledStatus;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
    }

    private void init() {
        mLedManager = new LedExtendedManager(this);
        try {
            mLedManager.connectToService();
        } catch (RemoteException e) {
            Log.e(TAG, "Couldn't connectToServive");
        }

        setOn = (Button) findViewById(R.id.OnBtn);
        setOff = (Button) findViewById(R.id.OffBtn);
        ledStatus = (TextView) findViewById(R.id.textView2);
        setOn.setOnClickListener(new View.OnClickListener() {
            int retVal;

            @Override
            public void onClick(View v) {
                mLedManager.setLed(1);

                try {
                    retVal = mLedManager.getLed();
                } catch (NumberFormatException e) {
                    Log.e(TAG, "getLed failed in setOn");
                    retVal = -1;
                }

                ledStatus.setText(retVal);
            }
        });

        setOff.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int retVal;

                mLedManager.setLed(0);

                try {
                    retVal = mLedManager.getLed();
                } catch (NumberFormatException e) {
                    Log.e(TAG, "getLed failed in setOff");
                    retVal = -1;
                }

                ledStatus.setText(retVal);
            }
        });

    }
}