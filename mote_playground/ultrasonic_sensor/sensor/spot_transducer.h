/*
Escrito por Ricardo Fritsche
*/

#ifndef SPOT_TRANSDUCER_H
#define SPOT_TRANSDUCER_H

#include "ultrasonic.h"

using namespace EPOS;

class Smartpark_Spot_Transducer
{
  static const unsigned int MAX_DEVICES = 4;

  static const unsigned int ERROR = 0;
  static const unsigned int TAKEN = 10;
  static const unsigned int FREE  = 20;

  static const unsigned float TAKEN_VALUE = 15.0; // 15 centimetros

public:
    typedef _UTIL::Observed Observed;
    typedef _UTIL::Observer Observer;

    static const unsigned int UNIT = TSTP::Unit::Length;
    static const unsigned int NUM = TSTP::Unit::I32;
    static const int ERROR = 0;

    static const bool INTERRUPT = false;
    static const bool POLLING = true;

public:
    Smartpark_Spot_Transducer() {}

    static void sense(unsigned int dev, Smart_Data<Smartpark_Spot_Transducer> * data) {
        float s = _ultrasonic[dev]->sense();

        if (s < 1.0) {
          // cout << "Erro ao realizar leitura do sensor (" << s << " cm)" << endl;
          data->_value = ERROR;
        } else if (s < TAKEN_VALUE) {
          // cout << "Vaga OCUPADA :( (" << s << " cm)" << endl;
          data->_value = TAKEN;
        } else {
          // cout << "Vaga LIVRE :) (" << s << " cm)" << endl;
          data->_value = FREE;
        }
    }

    static void actuate(Smart_Data<Smartpark_Spot_Transducer> * data, const Smart_Data<Smartpark_Spot_Transducer>::Value & command) {}

    static void attach(Observer * obs) {}
    static void detach(Observer * obs) {}

private:
    static Ultrasonic * _ultrasonic[MAX_DEVICES];
};

typedef Smart_Data<Smartpark_Spot_Transducer> Smartpark_Spot_Smart_Data;

#endif // SPOT_TRANSDUCER_H