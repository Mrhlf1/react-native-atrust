/******************************************************
 * Copyright (C), 2021-2022, Sangfor Technologies Inc.
 * File name: SFSecurityProtocol.h
 * Author:  sangfor
 * Version: v1.0.0
 * Date: 2022-2-25
 * Description: SDK定义的协议
*******************************************************/

#import <Foundation/Foundation.h>
#import "SFSecurityTypes.h"
#import "SFSecurityObject.h"

NS_ASSUME_NONNULL_BEGIN

@protocol SFAuthResultDelegate<NSObject>

@required

/**
 * 认证成功回调
 * @param message 认证成功服务端返回的信息
 */
- (void)onAuthSuccess:(SFBaseMessage *)message;

/**
 * 认证过程回调，组合认证时回调下一次认证相关信息
 * nextAuthType为AuthTypeSMS、AuthTypeRadius、AuthTypeRenewPassword
 * 这三个类型的中的一个时，msg才不为空，具体的类参考上面对信息类的定义
 * @param nextAuthType 下个认证类型
 * @param message 认证需要的信息类
 */
- (void)onAuthProcess:(SFAuthType)nextAuthType message:(SFBaseMessage *)message;

/**
 * 认证失败回调
 * @param message 错误信息
 */
- (void)onAuthFailed:(SFBaseMessage *)message;

@end

@protocol SFLogoutDelegate <NSObject>

@required

/**
 * 注销回调
 * @param type 注销类型
 * @param message 错误信息
 */
- (void)onLogout:(SFLogoutType)type message:(SFBaseMessage *)msg;

@end

@protocol SFTunnelDelegate <NSObject>

@required
/**
 * 隧道启动成功回调
 * @param message 错误信息
 */
- (void)onTunnelStartSuccess;

/**
 * 隧道启动失败回调
 * @param message 错误信息
 */
- (void)onTunnelStartFailed:(SFBaseMessage *)msg;

@end

@protocol SFAppLaunchDelegate<NSObject>

@required

/**
 * 应用被拉起回调
 * @param launchInfo 拉起信息
 */
- (void)onAppLaunched:(const SFLaunchInfo *)launchInfo;

@end

NS_ASSUME_NONNULL_END
