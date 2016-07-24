package watorvapor.com.ble_rc_4wd;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Context;
import android.os.Handler;
import android.os.ParcelUuid;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import android.support.v4.view.ViewPager;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;

import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {

    /**
     * The {@link android.support.v4.view.PagerAdapter} that will provide
     * fragments for each of the sections. We use a
     * {@link FragmentPagerAdapter} derivative, which will keep every
     * loaded fragment in memory. If this becomes too memory intensive, it
     * may be best to switch to a
     * {@link android.support.v4.app.FragmentStatePagerAdapter}.
     */
    private SectionsPagerAdapter mSectionsPagerAdapter;
    BluetoothManager mBleMgr;
    BluetoothAdapter mBleAdapter;
    BluetoothLeScanner mBleScan;
    private static final long SCAN_PERIOD = 10000;
    private ScanCallback mScanCallback;
    private Handler mHandler = new Handler();
    private boolean mScanning = false;
    private static final String mUUID = "ac5636ee-3d36-4afe-9662-ec47fbfe1dd0";
    private static final String mName = "sm.rc.4wd";
    private boolean mConnected = false;
    private static final String  TAB ="ble";

    Context mCtxt;
    private BluetoothGatt mGatt;
    BluetoothGattCharacteristic mCharacteristic;

    /**
     * The {@link ViewPager} that will host the section contents.
     */
    private ViewPager mViewPager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        // Create the adapter that will return a fragment for each of the three
        // primary sections of the activity.
        mSectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager());

        // Set up the ViewPager with the sections adapter.
        mViewPager = (ViewPager) findViewById(R.id.container);
        mViewPager.setAdapter(mSectionsPagerAdapter);


        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
            }
        });

        mBleMgr = (BluetoothManager) this.getSystemService(Context.BLUETOOTH_SERVICE);
        mBleAdapter = mBleMgr.getAdapter();
        mBleScan = mBleAdapter.getBluetoothLeScanner();
        ArrayList<BluetoothDevice> deviceList = new ArrayList<>();
        mCtxt = this;
        scan(true);

    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    /**
     * A placeholder fragment containing a simple view.
     */
    public static class PlaceholderFragment extends Fragment {
        /**
         * The fragment argument representing the section number for this
         * fragment.
         */
        private static final String ARG_SECTION_NUMBER = "section_number";

        public PlaceholderFragment() {
        }

        /**
         * Returns a new instance of this fragment for the given section
         * number.
         */
        public static PlaceholderFragment newInstance(int sectionNumber) {
            PlaceholderFragment fragment = new PlaceholderFragment();
            Bundle args = new Bundle();
            args.putInt(ARG_SECTION_NUMBER, sectionNumber);
            fragment.setArguments(args);
            return fragment;
        }

        @Override
        public View onCreateView(LayoutInflater inflater, ViewGroup container,
                                 Bundle savedInstanceState) {
            View rootView = inflater.inflate(R.layout.fragment_main, container, false);
            TextView textView = (TextView) rootView.findViewById(R.id.section_label);
            textView.setText(getString(R.string.section_format, getArguments().getInt(ARG_SECTION_NUMBER)));
            return rootView;
        }
    }

    /**
     * A {@link FragmentPagerAdapter} that returns a fragment corresponding to
     * one of the sections/tabs/pages.
     */
    public class SectionsPagerAdapter extends FragmentPagerAdapter {

        public SectionsPagerAdapter(FragmentManager fm) {
            super(fm);
        }

        @Override
        public Fragment getItem(int position) {
            // getItem is called to instantiate the fragment for the given page.
            // Return a PlaceholderFragment (defined as a static inner class below).
            return PlaceholderFragment.newInstance(position + 1);
        }

        @Override
        public int getCount() {
            // Show 3 total pages.
            return 3;
        }

        @Override
        public CharSequence getPageTitle(int position) {
            switch (position) {
                case 0:
                    return "SECTION 1";
                case 1:
                    return "SECTION 2";
                case 2:
                    return "SECTION 3";
            }
            return null;
        }
    }
    private ScanCallback initCallbacks() {

        return new ScanCallback() {
            @Override
            public void onScanResult(int callbackType, ScanResult result) {
                super.onScanResult(callbackType, result);
                Log.d(TAB,"result=<" + result + ">");
                if (result != null && result.getDevice() != null) {
                    BluetoothDevice device = result.getDevice();
                    Log.d(TAB,"device.getName()=<" + device.getName() + ">");
                    if(mName.equals(device.getName())) {
                        Log.d(TAB,"match: device.getAddress()=<" + device.getAddress() + ">");
                        if(false==mConnected) {
                            mConnected =true;
                            connect(mCtxt,device);
                        }
                    }
                }
            }

            @Override
            public void onBatchScanResults(List<ScanResult> results) {
                super.onBatchScanResults(results);
            }

            @Override
            public void onScanFailed(int errorCode) {
                super.onScanFailed(errorCode);
            }

        };

    }
    private void scan(final boolean enable) {
        mScanCallback = initCallbacks();
        if (enable) {
            mHandler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    mScanning = false;
                    mBleScan.stopScan(mScanCallback);
                }
            }, SCAN_PERIOD);

            mScanning = true;
            mBleScan.startScan(mScanCallback);
            // スキャンフィルタを設定するならこちら
            mBleScan.startScan(mScanCallback);
        } else {
            mScanning = false;
            mBleScan.stopScan(mScanCallback);
        }
    }

    private BluetoothGattCallback mGattCallback = new BluetoothGattCallback() {
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status,
                                            int newState) {
            super.onConnectionStateChange(gatt, status, newState);
            Log.d(TAB,"status=<" + status + ">" + "newState=<" + newState +">");

            // 接続成功し、サービス取得
            if (newState == BluetoothProfile.STATE_CONNECTED) {
                mGatt = gatt;
                Log.d(TAB,"gatt=<" + gatt + ">");
                discoverService();
            }

        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            super.onServicesDiscovered(gatt, status);
            BluetoothGattService service = gatt.getService(UUID.fromString(mUUID));
            Log.d(TAB,"service=<" + service + ">");
            mCharacteristic = service.getCharacteristic(UUID.fromString(mUUID));
            Log.d(TAB,"mCharacteristic=<" + mCharacteristic + ">");
            byte[] bytes = {0x10,0x20,0x0,0x35};
            mCharacteristic.setValue(bytes);
            mGatt.writeCharacteristic(mCharacteristic);
/*
            serviceList = gatt.getServices();

            for (BluetoothGattService s : serviceList) {
                // サービス一覧を取得したり探したりする処理
                // あとキャラクタリスティクスを取得したり探したりしてもよい
            }
*/
        }
    };

    // Gattへの接続要求
    public void connect(Context context, BluetoothDevice device) {

        mGatt = device.connectGatt(context, false, mGattCallback);
        mGatt.connect();

    }

    // サービス取得要求
    public void discoverService() {

        if (mGatt != null) {
            mGatt.discoverServices();
        }

    }
}
