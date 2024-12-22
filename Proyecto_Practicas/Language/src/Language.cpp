
#include "Language.h"
#include <fstream>
#include "stdlib.h"

const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";
const string Language::MAGIC_STRING_B="MP-LANGUAGE-B-1.0";

    
    void Language::liberarM() {

    delete[] _vectorBigramFreq;
    _vectorBigramFreq = nullptr;

}

 BigramFreq * Language::reservarM(int n) {
        BigramFreq *v = nullptr;
        if (n > 0)
            v = new BigramFreq [n];
        return v;
    }


Language::Language(){
    _languageId = "unknown";
   _size = 0;
   //_vectorBigramFreq = reservarM(_size);
}


Language::Language(int numberBigrams){
    _languageId = "unknown"; 
   
    if( numberBigrams<0)
        throw out_of_range("Fuera del rango");
    else{
        _size = numberBigrams;
        _vectorBigramFreq = reservarM(_size);
        for(int i=0; i<_size; i++){
            Bigram vacio = Bigram("__");
            _vectorBigramFreq[i].setBigram(vacio);
            _vectorBigramFreq[i].setFrequency(0);
        }
    }
}
 /**
     * @brief Copy constructor
     * @param orig the Language object used as source for the copy
     */
    Language::Language(const Language& orig){
           // liberarM();
            this->_vectorBigramFreq = reservarM(orig.getSize());
            this->_languageId = orig.getLanguageId();
            this->_size = orig.getSize();
            //this->_vectorBigramFreq = new BigramFreq[orig._size];
            for(int i = 0 ; i<_size ; i++){
                this->_vectorBigramFreq[i] = orig._vectorBigramFreq[i];
            }
    }
    /**
     * @brief Destructor of class Language
     */
    
    Language::~Language(){
       liberarM();
    }
    /**
     * @brief Overloading of the assignment operator for Language class
     * @param orig the Language object used as source for the assignment
     * @return A reference to this object
     */
    Language& Language::operator=(const Language& orig){
        if(&orig != this){
            //delete[] this->_vectorBigramFreq;
            liberarM();
            this->_vectorBigramFreq = reservarM(orig.getSize());
            this->_languageId = orig.getLanguageId();
            this->_size = orig.getSize();
            //this->_vectorBigramFreq = new BigramFreq[orig._size];
            for(int i = 0 ; i<_size ; i++){
                this->_vectorBigramFreq[i] = orig._vectorBigramFreq[i];
            }
        }
        return *this;
    }
    
    


const string &Language::getLanguageId()const{
        return _languageId;
}


void Language::setLanguageId(const string &id){
        _languageId = id;
}


  const BigramFreq &Language::at(int index) const{    
         if(index > _size || index <0) {
           throw std::out_of_range("Fuera del rango");
       }
        else {
           return _vectorBigramFreq[index];
        }
}
   
BigramFreq &Language::at(int index){
       if(index > Language::getSize() || index <0) {
           throw out_of_range("Fuera del rango");
       }
        else {
           return _vectorBigramFreq[index];
        }
}


int Language::getSize()const{
        return _size;
}    


double Language::getDistance(const Language &otherLanguage)const{
    
    
    int suma = 0;
    double distancia;
    double TAMANIO = _size*_size;
    
    if(_size == 0 || otherLanguage.getSize() == 0){
        throw std::out_of_range("invalid_argument");
    }
    
        for ( int i = 0 ; i<_size ; i++){
            
            
            if(otherLanguage.findBigram(_vectorBigramFreq[i].getBigram()) != -1){
               int vabsoluto = abs(findBigram(_vectorBigramFreq[i].getBigram())-otherLanguage.findBigram(_vectorBigramFreq[i].getBigram()));
               suma += vabsoluto;
               
            }
            else if(otherLanguage.findBigram(_vectorBigramFreq[i].getBigram()) == -1){
               int vabsoluto = abs(findBigram(_vectorBigramFreq[i].getBigram())- _size);
               suma += vabsoluto;
            }
            
            
        }

        distancia = suma/(TAMANIO);
        return distancia;
 
}
    
int Language::findBigram(const Bigram& bigram)const{
     int encontrado ;
     bool esta = false;
     
        
        for(int i=0; i < _size; i++){
            
            Bigram aux2 = _vectorBigramFreq[i].getBigram();
            
            if(aux2.toString() == bigram.toString()){
                encontrado = i;
                esta = true;
            }
            
        }
     
     if(esta){
        return encontrado;
     }
     else{
         return -1;
     }
 }



string Language::toString() const {
        string aux = "MP-LANGUAGE-T-1.0";
         aux += "\n"+_languageId+"\n";
         aux += to_string(_size)+"\n";
        
        
        for(int i=0; i< _size;i++){
            aux += _vectorBigramFreq[i].toString() + "\n";
        }
    return aux;
    
}

    
    

void Language::sort(){
    
    
    for(int i = 0 ; i<_size-1 ; i++){
        for ( int j = 0 ; j<_size-i-1 ; j++){
            if(_vectorBigramFreq[j].getFrequency()> _vectorBigramFreq[j+1].getFrequency()){
                BigramFreq cambio = _vectorBigramFreq[j];
                _vectorBigramFreq[j] = _vectorBigramFreq[j+1];
                _vectorBigramFreq[j+1] = cambio;
            }
        }
    }
    
    
    
    BigramFreq aux[_size];
    int contador = 0;
    for ( int i = _size-1 ; i>=0 ; i--){
        aux[contador] = _vectorBigramFreq[i];
        contador++;
    }
    for ( int i = 0 ; i< _size ; i++){
        _vectorBigramFreq[i] = aux[i];
    }
    
    
    
    for (int i = 0 ; i<_size-1 ; i++){
       
        for ( int j = i ; j < _size ; j++){
        
        if(_vectorBigramFreq[i].getFrequency() == _vectorBigramFreq[j].getFrequency()){
            if(_vectorBigramFreq[i].getBigram().toString() > _vectorBigramFreq[j].getBigram().toString() ){
                BigramFreq aux = _vectorBigramFreq[i];
                _vectorBigramFreq[i] = _vectorBigramFreq[j];
                _vectorBigramFreq[j] = aux;
            }
    
            }

        }   
    }
    
    

}




void Language::save(const char fileName[])const{  
    ofstream salida;
    salida.open(fileName);
    
    if(salida){
        
        //metemos frase inicial
            salida << MAGIC_STRING_T << endl;
            //metemos el idioma
            salida << _languageId;
            //metemos cada uno de los bigramas y sus frecuencias
            salida << Language::toString() << endl;
         
       // salida << this;
    } 
    else{
        throw std::out_of_range("Fallo en la apetura");
        }
    
    salida.close();

}

   
void Language::load(const char fileName[]){ 

    
        int Tam;
        string bigramAux;
        int frecuencia;
        string inicial, identificador;
        ifstream entrada;
        entrada.open(fileName);
        
        
        //saca la frase inicial para poder acceder al idioma y el tamaño
        entrada >> inicial;
        //saca el idioma
        entrada >> identificador; 
        //saca el tamaño
        entrada >> Tam; 
            
           
        //Insertamos el tamaño y el idioma
        _languageId = identificador;
        _size = Tam;
        _vectorBigramFreq = reservarM(Tam);
            
        // Sacamos uno a uno cada bigrama y su frecuencia y los vamos almacenando
        for(int i = 0; i < _size; i++){
             entrada >> bigramAux;
             entrada >> frecuencia;
             BigramFreq BigramFreqAux = BigramFreq() ;
             BigramFreqAux.setBigram(bigramAux);
             BigramFreqAux.setFrequency(frecuencia);
             _vectorBigramFreq[i] = BigramFreqAux;
         }
        
            
      
        
        entrada.close();


}
    

void Language::append(BigramFreq & bigramFreq){
    
    int posicion = findBigram(bigramFreq.getBigram());
    
    if(posicion != -1 ){
        int frecuenciaAux = _vectorBigramFreq[posicion].getFrequency() + bigramFreq.getFrequency();
        this->_vectorBigramFreq[posicion].setFrequency(frecuenciaAux);      
    }
    else{
        BigramFreq *v = reservarM(_size+1);
        for (int i = 0 ; i< _size ; i++){
            v[i]= _vectorBigramFreq[i];
        }
        v[_size] = bigramFreq;
        liberarM();
        _size++;
        _vectorBigramFreq = v;
            
    }
}  


 BigramFreq Language::operator[](int index){
     assert(index>=0);
     assert(index<=_size);
     return this->_vectorBigramFreq[index];
 }

 
Language Language::operator+=(Language language){
    
    for ( int i = 0 ; i< language.getSize() ; i++){
        append(language._vectorBigramFreq[i]);
    }
    
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Language &language){
    
    os << "MP-LANGUAGE-T-1.0" << endl;
    os << language.getLanguageId()<<endl;
    os << language.getSize() <<endl;
    for (int i = 0 ; i< language.getSize() ; i++){
            os << language.at(i).toString() << endl; 
    }
    return os;
}


std::istream &operator>>(std::istream &is, Language &language){
   
     string primero;
     string idioma;
     int tamanio;
     
    is>>primero;
    is>>idioma;
    is>>tamanio;
    
    
    language = Language(tamanio);
    language.setLanguageId(idioma);
    //language.
    for ( int i  = 0 ; i< tamanio ; i++){
        BigramFreq aux = BigramFreq();
        is>>aux;
    }
    return is;
}



BigramFreq * Language::getVectorBigramFreq(){
    return _vectorBigramFreq;
}
