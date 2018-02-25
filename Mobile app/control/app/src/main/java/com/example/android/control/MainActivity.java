package com.example.android.control;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.nfc.Tag;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

//a thread is a single program making multiple tasks at the same time like google chrome when we open multiple tabs
// each tab is a thread
public class MainActivity extends AppCompatActivity {

    //creating a bluetooth adapter object
    BluetoothAdapter mBluetoothAdapter;


    // Create a BroadcastReceiver for ACTION_FOUND
    private final BroadcastReceiver mBroadcastReceiver1 = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            // When discovery finds a device
            if (action.equals(mBluetoothAdapter.ACTION_STATE_CHANGED)) {
                final int state = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE, mBluetoothAdapter.ERROR);

                switch(state){
                    case BluetoothAdapter.STATE_OFF:
                        msg("state off");
                        break;
                    case BluetoothAdapter.STATE_TURNING_OFF:
                        msg("state turning off");
                        break;
                    case BluetoothAdapter.STATE_ON:
                        msg("state on");
                        break;
                    case BluetoothAdapter.STATE_TURNING_ON:
                        msg("state turning on");
                        break;
                }
            }
        }
    };

    @Override
    protected void onDestroy() {
        msg("destroying the broadcast receiver");
        super.onDestroy();
        unregisterReceiver(mBroadcastReceiver1);
    }

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //btn for off and on
        Button btnONOFF = (Button) findViewById(R.id.btnONOFF);

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();


        btnONOFF.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                msg("enabling/disabling bluetooth");
                enableDisableBT();
            }
        });

    }
    // fast way to call Toast
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(), s, Toast.LENGTH_LONG).show();
    }


    public void enableDisableBT(){
        if(mBluetoothAdapter == null){
            msg("does not have bluetooth in mobile");
        }
        if(!mBluetoothAdapter.isEnabled()){
            msg("enabling bluetooth");
            Intent enableBTIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivity(enableBTIntent);

            IntentFilter BTIntent = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
            registerReceiver(mBroadcastReceiver1, BTIntent);
        }
        if(mBluetoothAdapter.isEnabled()){
            msg("disabling bluetooth");
            mBluetoothAdapter.disable();

            IntentFilter BTIntent = new IntentFilter(BluetoothAdapter.ACTION_STATE_CHANGED);
            registerReceiver(mBroadcastReceiver1, BTIntent);
        }

    }

}
