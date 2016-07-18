$( document ).ready(function() {
  console.log( "ready!" );
  $('#dir-top').click(function(){
    console.log( "dir-top" );
    RC4WD.top();
  });
  $('#dir-buttom').click(function(){
    console.log( "dir-buttom" );
    RC4WD.buttom();
  });
  $('#dir-left').click(function(){
    console.log( "dir-left" );
    RC4WD.left();
  });
  $('#dir-right').click(function(){
    console.log( "dir-right" );
    RC4WD.right();
  });
  $('#dir-center').click(function(){
    console.log( "dir-center" );
    RC4WD.stop();
  });
});

