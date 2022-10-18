//
//  RNSangforVpn.m
//  RNSangforVpn
//
//  Created by Johnny iDay on 2017/11/30.
//  Copyright © 2017年 Johnny iDay. All rights reserved.
//

#import "RNSangforVpn.h"
#import <SangforSDK/SFUemSDK.h>




@interface RNSangforVpn()
{
//    VPNMode _sdkMode;
    NSURL *_url;
    NSString *_smsCode;
    RCTPromiseResolveBlock _resolve;
    RCTPromiseRejectBlock _reject;
}
@end

@implementation RNSangforVpn

- (dispatch_queue_t)methodQueue
{
    return dispatch_get_main_queue();
}

/*!
认证失败回调

@param error 错误信息
*/
- (void)onAuthFailed:(BaseMessage *)error
{
    _reject([NSString stringWithFormat:@"%ld", error.errCode], error.errStr, error);
}
// - (void)onAuthFailed:(BaseMessage *)msg {
//     NSLog(@"BasicSceneViewController onLoginFailed:%@", msg);
//     [MBProgressHUD hideHUDForView:self.view animated:YES];
//     [AlertUtil showAlert:@"认证失败" message:[NSString stringWithFormat:@"%@,code=%ld",msg.errStr,(long)msg.errCode]];
// }
/*!
 认证过程回调
 nextAuthType为VPNAuthTypeSms、VPNAuthTypeRadius、VPNAuthTypeForceUpdatePwd
 这三个类型的中的一个时，msg才不为空，具体的类参考上面对信息类的定义

 @param nextAuthType 下个认证类型
 @param msg 认证需要的信息类
 */
//- (void)onLoginProcess:(VPNAuthType)nextAuthType message:(BaseMessage *)msg
//{
//    if (nextAuthType != VPNAuthTypeNone) {
//        _resolve(@{@"result": [NSString stringWithFormat:@"%lu", nextAuthType]});
//    }
//}

- (void)onAuthProcess:(SFAuthType)nextAuthType message:(BaseMessage *)msg
{
    if (nextAuthType != SFAuthTypeNone) {
        _resolve(@{@"result": [NSString stringWithFormat:@"%lu", nextAuthType]});
    }
}

/*!
 认证成功回调
 */
- (void)onAuthSuccess
{
    _resolve(@{@"result": @"success"});
}

RCT_EXPORT_MODULE();


RCT_REMAP_METHOD(
   init,
   resolver:(RCTPromiseResolveBlock)resolve
   rejecter:(RCTPromiseRejectBlock)reject)
{
    _resolve = resolve;
    SFSDKMode mode = SFSDKModeSupportVpnSandbox;
    [[SFUemSDK sharedInstance] initSDK:mode
                                 flags:SFSDKFlagsHostApplication
                                 extra:nil];
    _resolve(@{@"success": @"1"});
}

RCT_REMAP_METHOD(login, url:(NSString *)url username:(NSString *)username password:(NSString *)password resolvers:(RCTPromiseResolveBlock)resolves
rejecters:(RCTPromiseRejectBlock)rejects)
{
   _resolve = resolves;
   _reject = rejects;
//    [self.helper startPasswordAuthLogin:_sdkMode vpnAddress:url username:username password:password];
    [[SFUemSDK sharedInstance] startPasswordAuth:url userName:username password:password];

}

RCT_REMAP_METHOD(
 logout,
 resolvers:(RCTPromiseResolveBlock)resolves
 rejecters:(RCTPromiseRejectBlock)rejects)
{
    _resolve = resolves;
    _reject = rejects;
//    [self.helper vpnLogout];
    [[SFUemSDK sharedInstance] registerLogoutDelegate:self];
}

RCT_REMAP_METHOD(SecondLogin,code:(NSString *)code
    resolver:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)reject)
{
    _resolve = resolve;
    _reject = reject;
    //    [self.helper startPasswordAuthLogin:_sdkMode vpnAddress:url username:username password:password];
    [[SFUemSDK sharedInstance] doSecondaryAuth:SFAuthTypeSMS data:@{kAuthKeySMS:code}];

}

RCT_REMAP_METHOD(regetSmsCode,resolversms:(RCTPromiseResolveBlock)resolversms rejectersms:(RCTPromiseRejectBlock)rejectersms)
{
    /**
     * 短信验证码过期后，需要调用重新获取短信验证码
     */
//    [[SFUemSDK sharedInstance].auth regetSmsCode:^(SmsMessage * _Nullable message, NSError * _Nullable error) {
//        if (error) {
//            [self showToast:[NSString stringWithFormat:@"%@",error]];
//        } else {
//            if (message.countDown > 0) {
//                [bAlertView startTimer:countDown];
//            }
//        }
//    }];

}
@end
