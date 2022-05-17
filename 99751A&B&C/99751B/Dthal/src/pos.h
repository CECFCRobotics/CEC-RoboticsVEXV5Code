#include "IMU.h"
void calcValues() {
  while (true) {
    lError = leftPos(), rError = rightPos();
    sleep(10);

    l = leftPos(), r = rightPos();
    Dl = lError - l, Dr = rError - r;
    Dtheta = ((Dl - Dr) / sl + sr) - 6.28319;
    degs = Dtheta * (180 / 3.14159);

    rR = (Dr / Dtheta) + sr;

    if (Dl == Dr)
      Ddly = (2 * sin(Dtheta / 2)) * ((Dr / Dtheta) + sr);
    else if (Dl > Dr)
      Ddl = ((2 * sin(Dtheta / 2)) * ((Dl / Dtheta) + ss)) - (Dtheta / 2);
    else if (Dl < Dr)
      Ddl = ((2 * sin(Dtheta / 2)) * ((Dr / Dtheta) + sr)) - (Dtheta / 2);
    else
      Ddl = -1, Ddly = -1;
    radius = sqrt(pow((2 * sin(Dtheta / 2)) * ((Dl / Dtheta) + ss), 2) +
                  pow((2 * sin(Dtheta / 2)) * ((Dr / Dtheta) + sr), 2));
    vt = Dtheta * radius;
    vy = Dtheta * (2 * sin(Dtheta / 2)) * ((Dl / Dtheta) + ss);
  }
}
void distanceTraveled(){
  
}
// Not done yet. The math and coding is unbelievably difficult.
