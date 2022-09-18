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

import com.sangfor.sdk.base.SFAuthResultListener;
import com.sangfor.sdk.base.SFAuthType;
import com.sangfor.sdk.base.SFBaseMessage;


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
public class AtrustVpnModule extends ReactContextBaseJavaModule implements LifecycleEventListener , SFAuthResultListener  {

    private static Promise PROMISE;
    private String TAG = "LoginAtrust";

    public AtrustVpnModule(ReactApplicationContext reactContext) {
        super(reactContext);
        reactContext.addLifecycleEventListener(this);
    }

    @ReactMethod
    public void init(final Promise promise) {
        PROMISE = promise;
        AsyncTask task = new AsyncTask<Object, Object, Boolean>() {
          @Override
      		protected Boolean doInBackground(Object... params) {
      			return true;
      		}
          @Override
      		protected void onPostExecute(Boolean result) {
            //SangforAuthManager sfAuth = SangforAuthManager.getInstance();
            SFSDKMode sdkMode = SFSDKMode.MODE_VPN;
            try {
                int sdkFlags =  SFSDKFlags.FLAGS_HOST_APPLICATION;      //表明是单应用或者是主应用
                sdkFlags |= SFSDKFlags.FLAGS_VPN_MODE_TCP;              //表明使用VPN功能中的TCP模式
                SFMobileSecuritySDK.getInstance().initSDK(getReactApplicationContext(), sdkMode, sdkFlags, null);//初始化SDK
                WritableMap map = Arguments.createMap();
                map.putString("success", "1");
                promise.resolve(map);
            } catch (Exception e) {
                promise.reject(e.getMessage(), e);
            }
          }
        };
        task.execute();
    }

    @ReactMethod
    public void login(final String url , final String username, final String password,
                    final Promise promise) {
        PROMISE = promise;
        SFMobileSecuritySDK.getInstance().setAuthResultListener(this);
        AsyncTask task = new AsyncTask<Object, Object, Boolean>() {

            @Override
        		protected Boolean doInBackground(Object... params) {
        			   return true;
        		}

            @Override
        		protected void onPostExecute(Boolean result) {

              try{
                SFMobileSecuritySDK.getInstance().startPasswordAuth(url, username, password);
                // WritableMap map = Arguments.createMap();
                // map.putString("success", "111");
                // promise.resolve(map);
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
        //SFMobileSecuritySDK.getInstance().registerLogoutListener(this);
        AsyncTask task = new AsyncTask<Object, Object, Boolean>() {

            @Override
            protected Boolean doInBackground(Object... params) {
                 return true;
            }

            @Override
            protected void onPostExecute(Boolean result) {
                //SangforAuthManager.getInstance().vpnLogout();
                SFMobileSecuritySDK.getInstance().logout();
            }
        };
        task.execute();
    }

    @Override
    public String getName() {
        return "RNSangforAtrustVpn";
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
    public void onAuthProgress(SFAuthType nextAuthType, SFBaseMessage message) {
        SFLogN.info(TAG, "need next auth, authType: " + nextAuthType.name());
        //dismissWaitingDialog();
        //显示下一步认证UI界面
        //showAuthDialog(nextAuthType, message);
    }

    @Override
    public void onAuthSuccess(final SFBaseMessage message) {
        //SFLogN.info(TAG, "auth success");
        this.resolve("1");
    }

    @Override
    public void onAuthFailed(final SFAuthType authType, final SFBaseMessage message) {
        //SFLogN.error2(TAG, "auth failed", "errMsg: " + message.mErrStr + ",authType: " + authType.name());
        this.resolve("errMsg: " + message.mErrStr);
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
