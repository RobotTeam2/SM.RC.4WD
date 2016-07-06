How to Build.


1. git clone https://github.com/maeikei/SM.RC.4WD  
2. cd SM.RC.4WD/3dcam  
3. ./build.sh
  Please modify following portion, once you face a fatal error:

  #include "utils.h"
  to
  #include "../utils.h"

  in libuvc/include/libuvc/libuvc_internal.h 
4. ./camera.sh
