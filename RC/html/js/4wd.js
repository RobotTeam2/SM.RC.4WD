var RC4WD = RC4WD || {};
RC4WD.ws = RC4WD.ws || new WebSocket(location.host+'/ws');
RC4WD.top = function () {
    console.log('top');
    if(BLE) {
        BLE.run('top');
    }
    console.log(RC4WD.ws);
}
RC4WD.buttom = function () {
    console.log('buttom');
    if(BLE) {
        BLE.run('buttom');
    }
    console.log(RC4WD.ws);
}
RC4WD.left = function () {
    console.log('left');
    if(BLE) {
        BLE.run('left');
    }
    console.log(RC4WD.ws);
}
RC4WD.right = function () {
    console.log('right');
    if(BLE) {
        BLE.run('right');
    }
    console.log(RC4WD.ws);
}
RC4WD.stop = function () {
    console.log('stop');
    if(BLE) {
        BLE.run('stop');
    }
    console.log(RC4WD.ws);
}
