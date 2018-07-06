package com.example.android.control2;


import android.Manifest;
import android.annotation.SuppressLint;
import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences;
import android.media.MediaPlayer;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.Toast;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.ArrayList;
import java.util.UUID;


public class MainActivity extends AppCompatActivity implements AdapterView.OnItemClickListener{
    private static final String TAG = "MainActivity";

    BluetoothAdapter mBluetoothAdapter;
    Button btnEnableDisable_Discoverable;

    BluetoothConnectionService mBluetoothConnection;
    Button btnStartConnection;
    BluetoothSocket btSocket = null;
    private static final UUID MY_UUID_INSECURE =
            UUID.fromString("8ce255c0-200a-11e0-ac64-0800200c9a66");

    public ArrayList<BluetoothDevice> mBTDevices = new ArrayList<>();

    public DeviceListAdapter mDeviceListAdapter;

    ListView lvNewDevices;
    BluetoothDevice mBTDevice;






    private BroadcastReceiver mBroadcastReceiver3 = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            msg("onReceive: ACTION FOUND.");

            if (action.equals(BluetoothDevice.ACTION_FOUND)){
                BluetoothDevice device = intent.getParcelableExtra (BluetoothDevice.EXTRA_DEVICE);
                mBTDevices.add(device);
                msg("onReceive: " + device.getName() + ": " + device.getAddress());
                mDeviceListAdapter = new DeviceListAdapter(context, R.layout.device_adapter_view, mBTDevices);
                lvNewDevices.setAdapter(mDeviceListAdapter);
            }
        }
    };
    /**
     * Broadcast Receiver that detects bond state changes (Pairing status changes)
     */
    private final BroadcastReceiver mBroadcastReceiver4 = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();

            if(action.equals(BluetoothDevice.ACTION_BOND_STATE_CHANGED)){
                BluetoothDevice mDevice = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                //3 cases:
                //case1: bonded already
                if (mDevice.getBondState() == BluetoothDevice.BOND_BONDED){
                    msg("BroadcastReceiver: BOND_BONDED.");
                }
                //case2: creating a bone
                if (mDevice.getBondState() == BluetoothDevice.BOND_BONDING) {
                    msg("BroadcastReceiver: BOND_BONDING.");
                }
                //case3: breaking a bond
                if (mDevice.getBondState() == BluetoothDevice.BOND_NONE) {
                    msg("BroadcastReceiver: BOND_NONE.");
                }
            }
        }
    };


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnEnableDisable_Discoverable = (Button) findViewById(R.id.btnDiscoverable_on_off);
        lvNewDevices = (ListView) findViewById(R.id.lvNewDevices);
        mBTDevices = new ArrayList<>();

        //Broadcasts when bond state changes (ie:pairing)
        IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_BOND_STATE_CHANGED);
        registerReceiver(mBroadcastReceiver4, filter);

        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        lvNewDevices.setOnItemClickListener(MainActivity.this);



    }




    public void enableDisableBT(){
        if(mBluetoothAdapter == null){
            msg("enableDisableBT: Does not have BT capabilities.");
        }
        if(!mBluetoothAdapter.isEnabled()){
            msg("enableDisableBT: enabling BT.");
            Intent enableBTIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivity(enableBTIntent);


        }
        if(mBluetoothAdapter.isEnabled()){
            msg("enableDisableBT: disabling BT.");
            mBluetoothAdapter.disable();


        }

    }
    public void startConnection(){
        startBTConnection(mBTDevice,MY_UUID_INSECURE);
    }

    //starting bluetooth connection


    public void startBTConnection(BluetoothDevice device, UUID uuid){
        msg("startBTConnection: Initializing RFCOM Bluetooth Connection.");


        try
        {
            if (btSocket == null )
            {
                mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();//get the mobile bluetooth device
                BluetoothDevice dispositivo = mBluetoothAdapter.getRemoteDevice(mBTDevice.getAddress());//connects to the device's address and checks if it's available
                btSocket = dispositivo.createInsecureRfcommSocketToServiceRecord(MY_UUID_INSECURE);//create a RFCOMM (SPP) connection
                BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                if(BluetoothDevice.DEVICE_TYPE_CLASSIC == device.getType()) {
                    btSocket =(BluetoothSocket) mBTDevice.getClass().getMethod("createRfcommSocket", new Class[] {int.class}).invoke(mBTDevice,1);//start connection
                    btSocket.connect();
                }
            }
        }
        catch (IOException e)
        {
            msg("Error in connection");
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
        }
    }




    public void btnEnableDisable_Discoverable(View view) {
        msg("btnEnableDisable_Discoverable: Making device discoverable for 300 seconds.");

        Intent discoverableIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
        discoverableIntent.putExtra(BluetoothAdapter.EXTRA_DISCOVERABLE_DURATION, 300);
        startActivity(discoverableIntent);





    }

    public void btnDiscover(View view) {
        msg("btnDiscover: Looking for unpaired devices.");

        if(mBluetoothAdapter.isDiscovering()){
            mBluetoothAdapter.cancelDiscovery();
            msg("btnDiscover: Canceling discovery.");

            //check BT permissions in manifest

            mBluetoothAdapter.startDiscovery();
            IntentFilter discoverDevicesIntent = new IntentFilter(BluetoothDevice.ACTION_FOUND);
            registerReceiver(mBroadcastReceiver3, discoverDevicesIntent);
        }
        if(!mBluetoothAdapter.isDiscovering()){

            //check BT permissions in manifest

            mBluetoothAdapter.startDiscovery();
            IntentFilter discoverDevicesIntent = new IntentFilter(BluetoothDevice.ACTION_FOUND);
            registerReceiver(mBroadcastReceiver3, discoverDevicesIntent);

        }
    }

    /**
     * This method is required for all devices running API23+
     * Android must programmatically check the permissions for bluetooth. Putting the proper permissions
     * in the manifest is not enough.
     *
     * NOTE: This will only execute on versions > LOLLIPOP because it is not needed otherwise.
     */

    @Override
    public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
        //first cancel discovery because its very memory intensive.
        mBluetoothAdapter.cancelDiscovery();


        mBTDevice = mBTDevices.get(i);
        mBluetoothConnection = new BluetoothConnectionService(MainActivity.this);
    }
    private void msg(String s)
    {
        Toast.makeText(getApplicationContext(), s, Toast.LENGTH_SHORT).show();
    }
    private void left1()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("L".toString().getBytes());
                msg("sending L");
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void forward1()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("F".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void right1()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("R".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void backward1()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("B".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void stop1()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("S".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void low1()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("2".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void medium1()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("3".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void high1()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("4".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void no1()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("1".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void line_trackk()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("A".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void circlee()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("C".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void rectanglee()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("R".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void infinityy()
    {
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write("I".toString().getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void distance()
    {

        EditText distance = (EditText)findViewById(R.id.dist);
        Editable dis = distance.getText();
        String dis1 = dis.toString();
        if(dis1.length()==1)
            dis1 = "00"+ dis1;
        else if(dis1.length()==2)
            dis1 = '0'+dis1;
        else if(dis1.length()>3){
            msg("distance must be 3 characters");
            return;
        }
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write(('#' + dis1).getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }
    private void angle()
    {
        EditText angle = (EditText)findViewById(R.id.ang);
        Editable ang = angle.getText();
        String ang1 = ang.toString();
        if(ang1.length()==1){
            ang1 = "00"+ang1;
        }
        else if(ang1.length()==2){
            ang1 = '0' + ang1;
        }
        else if(ang1.length()>3){
            msg("angle must be 3 characters");
            return;
        }
        if (btSocket!=null)
        {
            try
            {
                btSocket.getOutputStream().write(('@' + ang1).getBytes());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
        else{
            msg("connect first");
            setContentView(R.layout.activity_main);
        }
    }



    public void left(View view) {
        left1();
    }

    public void backward(View view) {
        backward1();
    }

    public void forward(View view) {
        forward1();
    }

    public void right(View view) {
        right1();
    }

    public void stop(View view) {
        stop1();
    }

    public void rock_nd_roll(View view) {

        setContentView(R.layout.rock_and_roll);

    }

    public void on_off(View view) {
        msg("onClick: enabling/disabling bluetooth.");
        enableDisableBT();
    }

    public void start(View view) {
        startConnection();
    }

    public void low(View view) {low1();}

    public void medium(View view) {medium1();}

    public void high(View view) {high1();}

    public void no(View view) {no1();}

    public void line_track(View view) {line_trackk();}


    public void easy(View view) {
        setContentView(R.layout.easy_driving);
    }
    public void connect_page(View view) {
        setContentView(R.layout.activity_main);
    }


    public void distanccee(View view) {
        distance();
    }

    public void anglee(View view) {
        angle();
    }

    public void rectangle(View view) {
        rectanglee();
    }

    public void circle(View view) {
        circlee();
    }

    public void infinity(View view) {
        infinityy();
    }
}