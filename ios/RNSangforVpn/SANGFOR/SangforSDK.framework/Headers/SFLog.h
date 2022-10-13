/*********************************************************************
 * Copyright (C), 2021-2022, Sangfor Technologies Inc.
 * File name: SFLog.h
 * Version: v1.0.0
 * Date: 2022-3-24
 * Description:  SFLog SDK日志相关接口类
********************************************************************/

#import <Foundation/Foundation.h>
#import "SFMobileSecurityTypes.h"

NS_ASSUME_NONNULL_BEGIN

@interface SFLog : NSObject
/**
 * @brief 设置debug日志开关
 */
- (void)setLogLevel:(SFLogLevel)level;

/**
 * @brief 打包日志到本地任务，会删除14天以前的日志
 * @param zipPath 打包后的文件全路径，传入目录名（非.zip结尾），或者指定文件名(dir + xx.zip)，目录不存在会帮着创建，原始文件存在会先删除
 * @discussion
 * 需要传入完整路径
 * 1. 输入：/var/mobile/Containers/Data/Application/1D488E35-1706-4C58-A357-4893E051A9C6/Library/Caches/log
 * 1. 输出：/var/mobile/Containers/Data/Application/1D488E35-1706-4C58-A357-4893E051A9C6/Library/Caches/log/****.zip
 * 2. 输入：/var/mobile/Containers/Data/Application/1D488E35-1706-4C58-A357-4893E051A9C6/Library/Caches/log.zip
 * 2. 输出：/var/mobile/Containers/Data/Application/1D488E35-1706-4C58-A357-4893E051A9C6/Library/Caches/log.zip
 * @return 打包后的路径，返回空表示打包失败
 */
- (NSString *)packLog:(NSString*)zipPath;

/**
 供双域SDK获取SDK日志路径,因为双域SDK我们没有界面，所以可由宿主应用获取并提交日志
 */
- (NSString *)getSDKLogDir;

@end

NS_ASSUME_NONNULL_END
