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
else {
    console.log("Unknown option!");
    process.exit(1);
}


