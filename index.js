import React, {Component} from 'react';
import PropTypes from 'prop-types';

import {
    NativeModules,
    Platform
} from 'react-native';

// const vpn = NativeModules.RNSangforVpn;
let vpn;
if(Platform.OS === 'ios'){
  vpn = NativeModules.RNSangforVpn;
}else if (Platform.OS === 'android') {
  vpn = NativeModules.RNSangforAtrustVpn
}
export default vpn;
// export const Mode = {
//   EasyApp: 0,
//   L3VPN: 1,
// }
