package com.trkj.atrust.vpn;

import java.net.URL;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.widget.Toast;
import android.os.AsyncTask;

import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.LifecycleEventListener;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.Arguments;

import com.sangfor.ssl.IVpnDelegate;
import com.sangfor.ssl.SFException;
import com.sangfor.ssl.SangforAuthManager;
import com.sangfor.ssl.common.ErrorCode;
import com.sangfor.ssl.BaseMessage;
import com.sangfor.ssl.IConstants.VPNMode;
import com.sangfor.ssl.LoginResultListener;

import com.sangfor.atrust.JNIBridge.JniTool;
import com.sangfor.sdk.Internal.LoadLibraryHelper;
import com.sangfor.sdk.SFMobileSecuritySDK;
import com.sangfor.sdk.base.SFConstants;
import com.sangfor.sdk.base.SFSDKFlags;
import com.sangfor.sdk.base.SFSDKMode;
import com.sangfor.sdk.base.SFSDKOptions;
import com.sangfor.sdk.utils.IGeneral;
import com.sangfor.sdk.utils.SFLogN;

/**
 * Created by m2mbob on 16/5/6.
 */
public class VpnModule extends ReactContextBaseJavaModule implements LifecycleEventListener, LoginResultListener {

    private static Promise PROMISE;
    private boolean inited;
    private String mode;
    private String host;
    private int port;

    public VpnModule(ReactApplicationContext reactContext) {
        super(reactContext);
        reactContext.addLifecycleEventListener(this);
    }

    @ReactMethod
    public void init(final String mode, final Promise promise) {
        PROMISE = promise;
        AsyncTask task = new AsyncTask<Object, Object, Boolean>() {

          @Override
      		protected Boolean doInBackground(Object... params) {
      			return true;
      		}

          @Override
      		protected void onPostExecute(Boolean result) {
            //SangforAuthManager sfAuth = SangforAuthManager.getInstance();
            SFSDKMode sdkMode = SFSDKMode.MODE_VPN_SANDBOX;
            try {
                if (!inited) {
                    sdkMode.setLoginResultListener(VpnModule.this);
                    inited = true;
                }
                // String ip = host.replaceAll("(?i)https://", "").replaceAll("(?i)http://", "");
                // VpnModule.this.host = host;
                // VpnModule.this.mode = mode;
                // VpnModule.this.port = port;
                // WritableMap map = Arguments.createMap();
                // map.putString("success", "1");
                // promise.resolve(map);

                int sdkFlags =  SFSDKFlags.FLAGS_HOST_APPLICATION;      //表明是单应用或者是主应用
                sdkFlags |= SFSDKFlags.FLAGS_VPN_MODE_TCP;              //表明使用VPN功能中的TCP模式
                SFMobileSecuritySDK.getInstance().initSDK(getReactApplicationContext(), sdkMode, sdkFlags, null);//初始化SDK

            } catch (Exception e) {
                promise.reject(e.getMessage(), e);
            }
          }
        };
        task.execute();
    }

    @ReactMethod
    public void init(final Promise promise) {
        this.init("MODE_VPN", promise);
    }

    @ReactMethod
    public void login(final String url , final String username, final String password,
                    final Promise promise) {
        PROMISE = promise;
        AsyncTask task = new AsyncTask<Object, Object, Boolean>() {

            @Override
        		protected Boolean doInBackground(Object... params) {
        			   return true;
        		}

            @Override
        		protected void onPostExecute(Boolean result) {
              try{
                // SangforAuthManager sfAuth = SangforAuthManager.getInstance();
                // sfAuth.startPasswordAuthLogin(getCurrentActivity().
                //   getApplication(), getCurrentActivity(), VPNMode.L3VPN,
                //   new URL(VpnModule.this.host + ":" + VpnModule.this.port), username, password);
                SFMobileSecuritySDK.getInstance().startPasswordAuth(url, username, password);
                } catch(Exception e) {
                  PROMISE.reject("failed", e.getMessage());
                }
            }
        };
        task.execute();
    }

    @ReactMethod
    public void logout(final Promise promise) {
        if (promise != null) {
            PROMISE = promise;
        }
        AsyncTask task = new AsyncTask<Object, Object, Boolean>() {

            @Override
            protected Boolean doInBackground(Object... params) {
                 return true;
            }

            @Override
            protected void onPostExecute(Boolean result) {
                SangforAuthManager.getInstance().vpnLogout();
            }
        };
        task.execute();
    }

    @Override
    public String getName() {
        return "RNSangforVpn";
    }

    @Override
  	public void onLoginProcess(int nextAuthType,  BaseMessage message) {
      if (message != null && message.getErrorStr() != null && message.getErrorStr().length() > 0) {
        this.onLoginFailed(message.getErrorCode(), message.getErrorStr());
      } else {
        this.resolve(nextAuthType + "");
      }
    }

    @Override
  	public void onLoginSuccess() {
      this.resolve("1");
    }

    private void resolve(String message) {
      WritableMap map = Arguments.createMap();
      map.putString("success", message);
      if (PROMISE != null) {
        PROMISE.resolve(map);
        PROMISE = null;
      }
    }

    @Override
  	public void onLoginFailed(ErrorCode errorCode, String errorStr) {
      if (PROMISE != null) {
        PROMISE.reject("failed", errorStr);
        PROMISE = null;
      }
    }

    @Override
    public void onHostResume() {
    }

    @Override
    public void onHostPause() {
    }

    @Override
    public void onHostDestroy() {
      this.logout(null);
    }

}
