/*********************************************************************
 * Copyright (C), 2021-2022, Sangfor Technologies Inc.
 * File name: SFLaunch.h
 * Version: v1.0.0
 * Date: 2022-3-24
 * Description:  SFLaunch SDK主从相关接口类
********************************************************************/

#import <Foundation/Foundation.h>
#import "SFMobileSecurityTypes.h"
#import "SFSecurityProtocol.h"

NS_ASSUME_NONNULL_BEGIN

@interface SFLaunch : NSObject

/// 启动应用
/// @param bundleId 应用的bundleid
/// @param reason 启动应用原因
/// @param extraData 扩展数据，用于自定义传输数据
- (BOOL)launchApp:(NSString *)bundleId reason:(SFLaunchReason)reason extraData:(nullable NSString *)extraData;

/// 设置App拉起代理对象
/// @param delegate 代理对象
- (void)setAppLaunchDelegate:(nullable id<SFAppLaunchDelegate>)delegate;

/// 根据APP的BundleId判断应用是否授权
/// @param bundleId bundleId
- (BOOL)checkAppAuthorized:(NSString *)bundleId;

@end

NS_ASSUME_NONNULL_END
