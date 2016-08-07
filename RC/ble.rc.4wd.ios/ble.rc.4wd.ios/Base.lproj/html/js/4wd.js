var RC4WD = RC4WD || {};

RC4WD.top = function () {
    console.log('top');
    open("ble.rc.4wd://top”);
}
RC4WD.buttom = function () {
    console.log('buttom');
    open("ble.rc.4wd://buttom”);
}
RC4WD.left = function () {
    console.log('left');
    open("ble.rc.4wd://left”);
}
RC4WD.right = function () {
    console.log('right');
    open("ble.rc.4wd://right”);
}
RC4WD.stop = function () {
    console.log('stop');
    open("ble.rc.4wd://stop”);
}
