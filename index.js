const flexNative = require('bindings')('flexcommander-native');
exports.Hello = flexNative._Hello;
exports.FlexInit = flexNative.FlexInit;
exports.FlexProbeDevices = flexNative.FlexProbeDevices;
exports.FlexIterateDevices = flexNative.FlexIterateDevices;
