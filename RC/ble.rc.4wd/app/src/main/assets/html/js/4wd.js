var RC4WD = RC4WD || {};

RC4WD.top = function () {
    console.log('top');
    if(BLE) {
        BLE.run('top');
    }
}
RC4WD.buttom = function () {
    console.log('buttom');
    if(BLE) {
        BLE.run('buttom');
    }
}
RC4WD.left = function () {
    console.log('left');
    if(BLE) {
        BLE.run('left');
    }
}
RC4WD.right = function () {
    console.log('right');
    if(BLE) {
        BLE.run('right');
    }
}
RC4WD.stop = function () {
    console.log('stop');
    if(BLE) {
        BLE.run('stop');
    }
}
