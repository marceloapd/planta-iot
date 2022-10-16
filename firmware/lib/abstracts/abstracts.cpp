#include <Arduino.h>

int seg(int seg){
    return seg*1000;
}

int min(int min){
    return min*60000;
}

int hour(int hour){
    return min(hour)*60;
}