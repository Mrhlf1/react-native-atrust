require 'json'

package = JSON.parse(File.read(File.join(__dir__, 'package.json')))

Pod::Spec.new do |s|
  s.name                = package['name']
  s.version             = "1.0"
  s.summary             = "atrust"
  s.description         = <<-DESC
                            Atrust Manager for React Native
                         DESC
  s.homepage            = "https://github.com/Mrhlf1/react-native-atrust.git"
  s.license             = package['license']
  s.author              = "hlf"
  s.source              = { :git => "https://github.com/Mrhlf1/react-native-atrust.git", :tag => "v#{s.version}" }
  s.requires_arc        = true
  s.platform            = :ios, "7.0"
  s.preserve_paths      = "*.framework"
  s.vendored_frameworks = 'ios/RNSangforVpn/SANGFOR/SangforSDK.framework'
  s.source_files        = 'ios/RNSangforVpn/RNSangforVpn/*.{h,m}'
  s.dependency 'React'
end
