/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Bigram.cpp
 * Author: jose
 * 
 * Created on 30 de marzo de 2023, 23:09
 */

#include "Bigram.h"
#include <exception>


Bigram::Bigram(const string& text) {
    if(text.length() == 2){
        _text[0] = text[0];
        _text[1] = text[1];
       _text[2] = '\0';
    }else{
        _text[0] = '_';
        _text[1] = '_';
       _text[2] = '\0';
    }
    
}

Bigram::Bigram(char first, char second) {
    _text[0] = first;
    _text[1]= second;
    _text[2]= '\0';
    
}

Bigram::Bigram(const char text[]){
    
      
        _text[0] = text[0];
        _text[1] = text[1];
       _text[2] = '\0';
       
  
}

string Bigram::getText() const{
    string text_aux = "";
    for(int i = 0 ; i< 2 ; i++){
    text_aux += _text[i];
    }
    return text_aux;
}

string Bigram::toString() const{
     string text_aux = "";
    for(int i = 0 ; i< 2 ; i++){
    text_aux += _text[i];
    }
    return text_aux;
}

const char& Bigram::at(int index) const{
    if( index < 0 || index > 1){
        throw out_of_range("El indice "+to_string(index) +"está fuera del rango");
    }
    return _text[index];
}

char& Bigram::at(int index){
      if( index < 0 || index > 1){
        throw out_of_range("El indice "+to_string(index) +"está fuera del rango");
    }
    return _text[index];
}

void Bigram::toUpper(){
    char letter1 , letter2;
    letter1 = toupper(_text[0]);
    letter2 = toupper(_text[1]);
    _text[0]= letter1;
    _text[1]= letter2;
}

bool isValidCharacter(char character, const std::string& validCharacters){
    bool esta = false;
    for(int i = 0 ; i<validCharacters.length() ; i++){
        if(validCharacters[i] == character){
            esta = true;
        }
    }
    return esta;

}

std::ostream &operator<<(std::ostream &os, Bigram &bigram){
    os<<bigram.toString();
    return os;
}

std::istream &operator>>(std::istream &is, Bigram &bigram){
    string texto;
    is>>texto;
    bigram = Bigram(texto);
    return is;
    
    
}
