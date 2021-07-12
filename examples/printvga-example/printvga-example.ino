/*
   Example Sketch for the printvga library which is a wrapper-library
   for Bitluni's ESP32LIB (https://github.com/bitluni/ESP32Lib) so that needs to be installed too.
   It only works on an ESP32 based board.

   The printvga library is Licensed with a MIT License, Copyright (c) 2021 maicod
*/

#include <printvga.h>

void setup()
{

  printvgabegin();

  Serial.begin(115200);

}


void loop() {

  //////////////////////////////////////////printing text////////////////////////////////////////////


  // Char string

  char* mytext = "the quick brown fox jumps over the lazy dog";

  printvga (mytext);

  printvga ("\n\n"); //using \n makes next text start at a new line, add a backslash with \\

  // String

  String mystring = "the now not so lazy dog catches the not quick enough fox in flight\n\n";

  printvga (mystring);

  // Direct printing

  printvga ("this text is printed directly\n\n");

  //Tabs

  printvga ("the colons should align\t :\n"); //every \t is a 4 character wide spacing

  printvga ("hopefully it worked \t :\n");

  printvga ("this works \t\t\t\t : too\n\n");

  // Halfway line breaks

  printvga ("this line breaks\nhalfway\n\n");

  //////////////////////////////////////////printing values////////////////////////////////////////////


  //printing an integer

  int intval = 356;

  printvga("integer from variable\t : ");

  printvga(intval);

  printvga("\n");

  printvga("integer direct\t\t\t : ");

  printvga(478);

  printvga("\n\n");

  //printing a floating point value

  float floatval = 3.56712;

  printvga("floating point value\n");

  printvga("with 4 decimals\t\t\t : ");

  printvga(floatval, 4); //second parameter is the nr of decimals

  printvga("\n\n");

  printvga("------------------------------------------------------------------------------\n\n");

  //FIFO scrolling example

  printvga("FIFO scrolling coming up in 20 seconds :\n\n");

  for (int ctdown = 20; ctdown > 0; ctdown--) {
    printvga(ctdown);
    printvga(" ");
    delay(1000);
  }

  printvga("\n\n");

  for (int ct = 10000; ct < 10100; ct++) {
    printvga(ct);
    printvga("\n");
    delay(50);
  }

  printvga("\nThis demo will restart in 10 seconds :\n\n");

  for (int ctdown = 10; ctdown > 0; ctdown--) {
    printvga(ctdown);
    printvga(" ");
    delay(1000);
  }

  printvga("\n");

  vga.clear(0);

}
