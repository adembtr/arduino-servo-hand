#include  <Servo.h>

#define forIntI for(int i = 0;  i <4 ; i++)
#define forIntJ for(int j = 0;  j <100 ; j++)

Servo Fingers[4];
int pins[4] = {10,9,6,5};
int dir[4]; // yön bilgisi
double range[4][2] = {{0,170}, {0,170}, {0,170},{0,170}};
double steps[4]; // adım büyüklüğü
double Cmd[4] = {0,0,0,1} ;// anlık konumlar 0=tam kapalı 1= tma açık, 0.5=orta

void setup(){
  forIntI{
    Fingers[i].attach(pins[i]);
    steps[i] = (range[i][1] - range[i][0]) / 100;
    dir[i]= 1;
  }
  Serial.setTimeout(1);
  Serial.begin(9600);
}

void CmdSet(double a, double b, double c, double d) {
  Cmd[0] = a; Cmd[1] = b; Cmd[2] = c; Cmd[3] = d;
}


void loop(){
  CmdSet(0,0,0,0);
  dynamicPos(Cmd );
  CmdSet(1,1,1,1);
  dynamicPos(Cmd );
  CmdSet(1,1,0,0);
  dynamicPos(Cmd );
  CmdSet(0,0,1,1);
  dynamicPos(Cmd );

}

void dynamicPos(double dizi[]){
  //hedef açı hesapla
  forIntI{
    dizi[i] = 1 - dizi[i];  // tersle
    dizi[i] = (range[i][1] - range[i][0]) * dizi[i] + range[i][0]; // açı hesapla
  }

  //yumuşak animasyon
  forIntJ{
    forIntI{
      double nPos = Fingers[i].read(); // servo nun şu anki açısı
      if(nPos > dizi[i]) Fingers[i].write(nPos - steps[i]); // şu an eğer hedefin üstünde isem geri git
      else if(nPos < dizi[i]) Fingers[i].write(nPos + steps[i]); // hedefin altında isem iler git
      else Fingers[i].write(nPos); // bir şey yapma eşit ise hareket etme
    } 
    delay(20);
  }
}




