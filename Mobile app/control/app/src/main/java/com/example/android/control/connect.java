package com.example.android.control;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toolbar;

import java.util.Set;

/**
 * Created by omar 2 on 2/25/2018.
 */

public class connect extends AppCompatActivity {
    Button btpaired;
    ListView deviceList;
    private BluetoothAdapter mybt=null;
    private Set<BluetoothDevice> paireddevices;
    public static String EXTRAADD="device address";
    String ab=null;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.connect);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

    }




}
