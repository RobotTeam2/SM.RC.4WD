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
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Display;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.webkit.JavascriptInterface;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class Main2Activity extends AppCompatActivity {
    private static final String  TAB_JS ="js";

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
    private static final String  TAB_BLE ="ble";

    Context mCtxt;
    private BluetoothGatt mGatt = null;
    BluetoothGattCharacteristic mCharacteristic = null;

    WebView mWebView = null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        mWebView = (WebView) findViewById(R.id.webView);
        WebSettings webSettings = mWebView.getSettings();
        webSettings.setJavaScriptEnabled(true);
        webSettings.setSupportZoom(true);
        webSettings.setBuiltInZoomControls(false);
        webSettings.setLoadWithOverviewMode(true);
        webSettings.setUseWideViewPort(true);



        mWebView.addJavascriptInterface(new JavaScriptBlE(), "BLE");

        mWebView.setWebViewClient(new WebViewClient());
        mWebView.loadUrl("file:///android_asset/html/index.html");


        mBleMgr = (BluetoothManager) this.getSystemService(Context.BLUETOOTH_SERVICE);
        mBleAdapter = mBleMgr.getAdapter();
        mBleScan = mBleAdapter.getBluetoothLeScanner();
        ArrayList<BluetoothDevice> deviceList = new ArrayList<>();
        mCtxt = this;
        scan(true);


    }

    public class JavaScriptBlE {
        @JavascriptInterface
        public void run(String messege) {
            Log.d(TAB_JS,messege);
            if(mGatt != null && mCharacteristic != null) {
                byte[] bytes = messege.getBytes(StandardCharsets.UTF_8);
                mCharacteristic.setValue(bytes);
                mGatt.writeCharacteristic(mCharacteristic);
            } else {
                Log.e(TAB_BLE,"Please wait for Connect to RC Car!");
            }
        }
    }

    private ScanCallback initCallbacks() {

        return new ScanCallback() {
            @Override
            public void onScanResult(int callbackType, ScanResult result) {
                super.onScanResult(callbackType, result);
                Log.d(TAB_BLE,"result=<" + result + ">");
                if (result != null && result.getDevice() != null) {
                    BluetoothDevice device = result.getDevice();
                    Log.d(TAB_BLE,"device.getName()=<" + device.getName() + ">");
                    if(mName.equals(device.getName())) {
                        Log.d(TAB_BLE,"match: device.getAddress()=<" + device.getAddress() + ">");
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
            Log.d(TAB_BLE,"status=<" + status + ">" + "newState=<" + newState +">");

            // 接続成功し、サービス取得
            if (newState == BluetoothProfile.STATE_CONNECTED) {
                mGatt = gatt;
                Log.d(TAB_BLE,"gatt=<" + gatt + ">");
                discoverService();
            }

        }

        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            super.onServicesDiscovered(gatt, status);
            BluetoothGattService service = gatt.getService(UUID.fromString(mUUID));
            Log.d(TAB_BLE,"service=<" + service + ">");
            mCharacteristic = service.getCharacteristic(UUID.fromString(mUUID));
            Log.d(TAB_BLE,"mCharacteristic=<" + mCharacteristic + ">");
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
