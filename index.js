const flexNative = require('bindings')('flexcommander-native');
exports.Init = flexNative.FlexInit;
exports.ProbeDevices = flexNative.FlexProbeDevices;
exports.IterateDevices = flexNative.FlexIterateDevices;
exports.FlexOpen = flexNative.FlexOpen;