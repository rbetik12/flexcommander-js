const flex = require(".")
const readline = require("readline-sync")

if (process.argv.length < 3) {
    console.log("node flexcommander.js [-l -i] <dev path>");
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
    if (flex.FlexOpen(process.argv[3])) {
        console.log("Can't open device! Maybe incorrect path?");
        process.exit(1);
    }
    flex.FlexInitFs();
    while (true) {
        flex.FlexPrintCurrentDir();
        let str = readline.question("");
        let res = flex.FlexProcessInput(str);
        if (res === 2) {
            break;
        }
    }
    flex.FlexClose();
}
else {
    console.log("Unknown option!");
    process.exit(1);
}


