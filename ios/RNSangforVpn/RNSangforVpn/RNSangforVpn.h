//
//  RNSangforVpn.h
//  RNSangforVpn
//
//  Created by Johnny iDay on 2017/11/30.
//  Copyright © 2017年 Johnny iDay. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <React/RCTBridgeModule.h>
//#import <React/RCTLog.h>
#import <SangforSDK/SFSecurityProtocol.h>
#import <SangforSDK/SFUemSDK.h>


@interface RNSangforVpn : NSObject<RCTBridgeModule,SFAuthResultDelegate>

@end
