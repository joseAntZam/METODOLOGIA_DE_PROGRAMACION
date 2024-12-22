/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this /*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */


/* 
 * File:   BigramFreq.cpp
 * Author: jose
 * 
 * Created on 30 de marzo de 2023, 23:10
 */

#include "BigramFreq.h"
#include <exception>

  BigramFreq::BigramFreq(){
      _bigram = Bigram();
      _frequency = 0;
  }
    
   const Bigram& BigramFreq::getBigram()const{
        return _bigram;
    }

    
    int BigramFreq::getFrequency() const{
        return _frequency;
    }

    
    void BigramFreq::setBigram(const Bigram& bigram){
        _bigram = bigram;
    }
 
    void BigramFreq::setFrequency(int frequency){
        
        if( frequency < 0){
         throw std::out_of_range("La frecuencia "+std::to_string(frequency) +"está fuera del rango");
        }
        _frequency = frequency;
    }
    
    
    string BigramFreq::toString()const{
        string aux;
        aux = _bigram.toString();
        aux += " ";
        aux += to_string(_frequency);
       
        return aux;
    }

    
std::ostream &operator<<(std::ostream &os, BigramFreq &bigramFreq){
    
    os<<bigramFreq.getBigram().toString();
    os<<" ";
    os<<bigramFreq.getFrequency();
    return os;
}


std::istream &operator>>(std::istream &is, BigramFreq &bigramFreq){
    Bigram aux = Bigram("__");
    int frecuencia;
    is>>aux;
    is>>frecuencia;
    
    bigramFreq.setBigram(aux);
    bigramFreq.setFrequency(frecuencia);
    
    return is;
    
}


bool operator>(BigramFreq &bigramFreq1, BigramFreq &bigramFreq2){
    return (bigramFreq1.getFrequency() > bigramFreq2.getFrequency());
}


bool operator<(BigramFreq &bigramFreq1, BigramFreq &bigramFreq2){
    return (bigramFreq1.getFrequency() < bigramFreq2.getFrequency());
}


bool operator==(BigramFreq &bigramFreq1, BigramFreq &bigramFreq2){
    return ((bigramFreq1.getBigram().toString() == bigramFreq2.getBigram().toString()) && (bigramFreq1.getFrequency() == bigramFreq2.getFrequency()));
}


bool operator!=(BigramFreq &bigramFreq1, BigramFreq &bigramFreq2){
    return ((bigramFreq1.getBigram().toString() != bigramFreq2.getBigram().toString()) || (bigramFreq1.getFrequency() != bigramFreq2.getFrequency()));
}

bool operator<=(BigramFreq &bigramFreq1, BigramFreq &bigramFreq2){
    return (bigramFreq1.getFrequency() <= bigramFreq2.getFrequency());
}


bool operator>=(BigramFreq &bigramFreq1, BigramFreq &bigramFreq2){
    return (bigramFreq1.getFrequency() >= bigramFreq2.getFrequency());
}
