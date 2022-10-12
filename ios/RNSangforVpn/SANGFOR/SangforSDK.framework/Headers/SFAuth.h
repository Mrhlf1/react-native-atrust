/*********************************************************************
 * Copyright (C), 2021-2022, Sangfor Technologies Inc.
 * File name: SFAuth.h
 * Version: v1.0.0
 * Date: 2022-3-24
 * Description:  SFAuth SDK高级认证相关接口类
********************************************************************/

#import <Foundation/Foundation.h>
#import "SFMobileSecurityTypes.h"

NS_ASSUME_NONNULL_BEGIN

@interface SFAuth : NSObject

/**
 * @brief 短信主认证接口
 * @discussion
 * 此接口调用之前必须已经调用过setAuthResultDelegate并设置了非空的认证回调
 * 主应用调用，子应用调用会导致断言
 * @param url 认证的url信息
 * @param phoneNumber 手机号
 */
- (void)startPrimarySmsAuth:(NSURL * __nonnull)url phoneNumber:(NSString * __nonnull)phoneNumber;

/**
 * @brief  通用定制认证方式,异步接口
 * @discussion
 * 此接口调用之前必须已经调用过setAuthResultDelegate并设置了非空的认证回调
 * 主应用调用，子应用调用会导致断言
 * @param url 认证的url信息
 * @param path 认证路径
 * @param data 透传数据,JSON格式
 * @return YES:调用认证方法成功
 */
- (void)startPrimaryAuth:(NSURL * __nonnull)url path:(NSString * __nonnull)path data:(NSString * __nullable)data;

/**
 * @brief 异步请求，重新获取短信验证码
 */
- (void)regetSmsCode:(SFRegetSmsCodeBlock)comp;

/**
 * @brief 同步请求，重新获取图形校验码
 * @discussion
 * 阻塞请求，返回图片信息，用于更新图形校验码
 */
- (void)regetRandCode:(SFRegetRandCodeBlock)comp;

/**
 * @brief 同步接口，获取认证状态信息
 * 具体值含义参考SFAuthStatus枚举
 */
- (SFAuthStatus)getAuthStatus;

@end

NS_ASSUME_NONNULL_END
