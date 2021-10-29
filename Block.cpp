#include "Block.h"

Block::Block(){
    value = 0;
    r = 0;
    g = 0;
    b = 0;
}

Block::Block(int number){
    value = number;
    AssignColor();
}

void Block::AssignColor(){
    if (value <= 0){
        //white
        r = 250;
        g = 250;
        b = 250;
    }
    if (value <= 2 && value > 0){
        //ecru
        r = 220;
        g = 211;
        b = 182;
    }
    if (value <= 4 && value > 2){
        //dark ecru
        r = 194;
        g = 178;
        b = 128;
    }
    if (value <= 8 && value > 4){
        //light orange
        r = 254;
        g = 216;
        b = 177;
    }
    if (value <= 16 && value > 8){
        //dark orange
        r = 255;
        g = 140;
        b = 0;
    }
    if (value <= 32 && value > 16){
        //red 
        r = 255;
        g = 114;
        b = 111;
    }
    if (value <= 64 && value > 32){
        //darker red
        r = 255;
        g = 42;
        b = 38;
    }
    if (value <= 128 && value > 64){
        //very light yellow
        r = 255;
        g = 255;
        b = 224;
    }
    if (value <= 256 && value > 128){
        //light yellow
        r = 255;
        g = 255;
        b = 102;
    }
    if (value <= 512 && value > 256){
        //yellow
        r = 255;
        g = 255;
        b = 0;
    }
    if (value <= 1024 && value > 512){
        //dark yellow
        r = 204;
        g = 204;
        b = 0;
    }
    if (value > 1024){
        //even darker yellow
        r = 153;
        g = 153;
        b = 0;
    }
}

int Block::GetR(){
    return r;
}

int Block::GetG(){
    return g;
}

int Block::GetB(){
    return b;
}

int Block::GetValue(){
    return value;
}
