const flex = require(".")

if (process.argv.length < 3) {
    console.log("node flexcommnader.js [-l -i] <dev path>");
    console.log("-l list all the available devices");
    console.log("-i interactive mode");
    process.exit(1);
}

if (process.argv[2] == '-l') {
    flex.Init();
    flex.ProbeDevices();
    flex.IterateDevices();
}
else if (process.argv[2] == "-i" && process.argv.length >= 4) {
    console.log(flex.FlexOpen(process.argv[3]));
}
else {
    console.log("Unknown option!");
    process.exit(1);
}


