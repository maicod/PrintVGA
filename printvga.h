/*
  printvga library by maicod June 2021

  printvga library is a wrapper-library for Bitluni's ESP32LIB
  (https://github.com/bitluni/ESP32Lib) so that needs to be installed too. It
  only works on an ESP32 based board.

  The printvga library is Licensed with a MIT License, Copyright (c) 2021 maicod

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef PRINTVGA_H
#define PRINTVGA_H

#include <Arduino.h>

#include <ESP32Lib.h>
#include <Ressources/CodePage437_8x8.h>

const int redPin = 14;
const int greenPin = 19;
const int bluePin = 27;
const int hsyncPin = 32;
const int vsyncPin = 33;

VGA3Bit vga;

unsigned int firstaccess;

unsigned int oldchr;


void printvgabegin() {

  vga.init(vga.MODE640x400, redPin, greenPin, bluePin, hsyncPin, vsyncPin);

  vga.setFont(CodePage437_8x8);

  vga.setTextColor(vga.RGB(255, 255, 255));

}


void printvga (int intgr) {

  String intstr = String(intgr);

  char intchar[(intstr.length() + 1)];

  intstr.toCharArray(intchar, (intstr.length() + 1));

  if (firstaccess == 0) {
    vga.setCursor(0, 392);
    firstaccess = 1;
  }

  vga.print(intchar);

}


void printvga (float floatval, int dcmls) {

  String floatstr = String(floatval, dcmls);

  char floatchar[(floatstr.length() + 1)];

  floatstr.toCharArray(floatchar, (floatstr.length() + 1));

  if (firstaccess == 0) {
    vga.setCursor(0, 392);
    firstaccess = 1;
  }

  vga.print(floatchar);

}


void printvga (char* txtchar) {

  int charlength = strlen(txtchar);

  if (firstaccess == 0) {
    vga.setCursor(0, 392);
    firstaccess = 1;
  }

  for (int chr = 0; chr < charlength; chr++) {

    if (txtchar[chr] == 10) {
      vga.scroll(8, vga.RGB(0));
      vga.println();
      oldchr = chr + 1;
    }

    if (txtchar[chr] == 9) {

      float tab = (chr - oldchr) / 4.00;

      int rounded = tab;

      tab = tab - rounded;

      if (int(tab) == tab) {
        tab = 0;
      }

      if (charlength == 1) {
        tab = 0;
      }

      if (chr - oldchr == 0) {
        tab = 0;
      }

      for (int space = 0; space < (4 - (tab * 4)); space++) {
        vga.print(" ");
      }

      oldchr = chr + 1;

    }

    if  ((txtchar[chr] != 9) && (txtchar[chr] != 10)) {
      vga.print(txtchar[chr]);
    }

  }

  oldchr = 0;

}


void printvga (String txtstr) {

  char txtchar[(txtstr.length() + 1)];

  txtstr.toCharArray(txtchar, (txtstr.length() + 1));

  int charlength = strlen(txtchar);

  if (firstaccess == 0) {
    vga.setCursor(0, 392);
    firstaccess = 1;
  }

  for (int chr = 0; chr < charlength; chr++) {

    if (txtchar[chr] == 10) {
      vga.scroll(8, vga.RGB(0));
      vga.println();
      oldchr = chr + 1;
    }

    if (txtchar[chr] == 9) {
      float tab = (chr - oldchr) / 4.00;
      int rounded = tab;
      tab = tab - rounded;

      if (int(tab) == tab) {
        tab = 0;
      }

      if (charlength == 1) {
        tab = 0;
      }

      if (chr - oldchr == 0) {
        tab = 0;
      }

      for (int space = 0; space < (4 - (tab * 4)); space++) {
        vga.print(" ");
      }

      oldchr = chr + 1;

    }

    if  ((txtchar[chr] != 9) && (txtchar[chr] != 10)) {
      vga.print(txtchar[chr]);
    }

  }

  oldchr = 0;

}

#endif

