/******************************************************
 * Copyright (C), 2021-2022, Sangfor Technologies Inc.
 * File name: SFSecurityObject.h
 * Author:  hj
 * Version: v1.0.0
 * Date: 2022-2-25
 * Description: SDK定义的对象
*******************************************************/

#import <Foundation/Foundation.h>
#import "SFSecurityTypes.h"

NS_ASSUME_NONNULL_BEGIN

/*! @brief 错误信息的基础类
 *
 */
@interface SFBaseMessage : NSObject
/*! 错误码 */
@property (nonatomic, assign) NSInteger errCode;
/*! 错误提示字符串 */
@property (nonatomic, copy) NSString *errStr;
/*! 服务端透传字符串 */
@property (nonatomic, copy) NSString *serverInfo;
@end

/*! @brief 下一次认证类型为VPNAuthTypeSms时，返回的信息
 *
 *  短信认证需要的结构体
 */
@interface SFSmsMessage : SFBaseMessage
/*! 短信认证的手机号码 */
@property (nonatomic, copy) NSString *phoneNum;
/*! 重新发送短信倒计时时间 */
@property (nonatomic, assign) int countDown;
/*! 上次发送的短信验证码是否在有效期 */
@property (nonatomic, assign) BOOL stillValid;
/*! 网关类型,用于判断短信验证码是否发往moa */
@property (nonatomic, copy) NSString *smsApps;
@end

/*! @brief 下一次认证类型为SFAuthTypeRand时，返回的信息
 *
 *  图形验证码要的结构体
 */
@interface SFRandCodeMessage : SFBaseMessage
@property (nonatomic, strong) NSData * randcode;
@end

/*! @brief 下一次认证类型为AuthTypeRadius时，返回的信息
 *
 *  挑战认证(Radius认证)需要的结构体
 */
@interface SFRadiusMessage : SFBaseMessage
/*! 挑战认证的提示信息 */
@property (nonatomic, copy) NSString *radiusMsg;
@end

/*! @brief 下一次认证类型为AuthTypeToken时，返回的信息
 *
 *  挑战认证(Token认证)需要的结构体
 */
@interface SFTokenMessage : SFBaseMessage
/*! Token认证的类型，普通token还是totp token */
@property (nonatomic, assign) BOOL totpType;
/*! Totp Token认证是否需要绑定 */
@property (nonatomic, assign) BOOL needBind;
/*! Totp Token认证是否可以重绑 */
@property (nonatomic, assign) BOOL isAllowRebind;
/*! Totp Token认证的绑定信息的user */
@property (nonatomic, copy) NSString *user;
/*! Totp Token认证的绑定信息的period */
@property (nonatomic, copy) NSString *period;
/*! Totp Token认证的绑定信息的digits */
@property (nonatomic, copy) NSString *digits;
/*! Totp Token认证的绑定信息的algorithm */
@property (nonatomic, copy) NSString *algorithm;
/*! Totp Token认证的绑定信息的secret */
@property (nonatomic, copy) NSString *secret;
/*! Totp Token认证的绑定信息的issuer */
@property (nonatomic, copy) NSString *issuer;
@end

/*! @brief 下一次认证类型为VPNAuthTypeForceUpdatePwd时，返回的信息
 *
 *  强制修改密码认证需要的结构体
 */
@interface SFResetPswMessage : SFBaseMessage
/*! 请求修改密码认证的密码规则信息 */
@property (nonatomic, copy) NSString *resetPswMsg;

@end

/*! @brief 主从接口回调信息
 *
 *  被拉起应用需要的信息
 */
@interface SFLaunchInfo : NSObject
@property (nonatomic, assign) SFLaunchReason launchReason;
@property (nonatomic, copy) NSString *srcAppName;
@property (nonatomic, copy) NSString *srcAppBundleId;
@property (nonatomic, copy) NSString *srcAppURLScheme;
@property (nonatomic, copy) NSString *extraData;

@end


NS_ASSUME_NONNULL_END
