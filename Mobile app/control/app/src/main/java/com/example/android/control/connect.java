package com.example.android.control;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.Toolbar;

import java.util.ArrayList;
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
        btpaired = (Button) findViewById(R.id.button);
        deviceList = (ListView) findViewById(R.id.listView);
        mybt = BluetoothAdapter.getDefaultAdapter();
        if (mybt == null) {
            Toast.makeText(getApplicationContext(), "Bluetooth devices not available", Toast.LENGTH_LONG).show();
            finish();
        } else if (!mybt.isEnabled()) {
            Intent turnbton = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(turnbton, 1);
        }
        btpaired.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                paireddeviceslist();
            }
        });
    };

    private void paireddeviceslist() {
        paireddevices = mybt.getBondedDevices();
        ArrayList list = new ArrayList();
        if (paireddevices.size() > 0) {
            for (BluetoothDevice bt : paireddevices) {
                list.add(bt.getName() + "\n" + bt.getAddress());
            }
        } else {
            Toast.makeText(getApplicationContext(), "No Paired Bluetooth Devices Found.", Toast.LENGTH_LONG).show();
        }
        final ArrayAdapter adapter = new ArrayAdapter(this, android.R.layout.simple_list_item_1, list);
        deviceList.setAdapter(adapter);
        deviceList.setOnItemClickListener(mylistclick);
    }

    private AdapterView.OnItemClickListener mylistclick = new AdapterView.OnItemClickListener() {
        @Override
        public void onItemClick(AdapterView<?> av, View v, int pos, long id) {
            String info = ((TextView) v).getText().toString();
            String address = info.substring(info.length() - 17);


            Intent i = new Intent(connect.this, MainActivity.class);
            i.putExtra(EXTRAADD, address);
            startActivity(i);


        }
    };








}
