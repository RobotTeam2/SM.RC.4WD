var RC4WD = RC4WD || {};
RC4WD.ws = RC4WD.ws || new WebSocket('ws://'+location.host+'/ws','4wd-protocol');
RC4WD.top = function () {
    console.log('top');
    if(typeof BLE != 'undefined') {
        BLE.run('top');
    }
    console.log(RC4WD.ws);
    if(RC4WD.ws.readyState) {
        console.log('top');
        RC4WD.ws.send('top')
    }
}
RC4WD.buttom = function () {
    console.log('buttom');
    if(typeof BLE != 'undefined') {
        BLE.run('buttom');
    }
    console.log(RC4WD.ws);
}
RC4WD.left = function () {
    console.log('left');
    if(typeof BLE != 'undefined') {
        BLE.run('left');
    }
    console.log(RC4WD.ws);
}
RC4WD.right = function () {
    console.log('right');
    if(typeof BLE != 'undefined') {
        BLE.run('right');
    }
    console.log(RC4WD.ws);
}
RC4WD.stop = function () {
    console.log('stop');
    if(typeof BLE != 'undefined') {
        BLE.run('stop');
    }
    console.log(RC4WD.ws);
}
