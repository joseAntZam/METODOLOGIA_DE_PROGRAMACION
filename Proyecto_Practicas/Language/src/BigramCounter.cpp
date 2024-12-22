#include <BigramCounter.h>
#include <fstream>
using namespace std;

 void BigramCounter::liberarM() {
     for ( int i = 0 ; i< _validCharacters.size() ; i++){
         delete[] _frequency[i];
     }
     delete[] _frequency;

}

    int ** BigramCounter::reservarM(int n) {
        int **v = new int*[n];
        
            for (int i = 0; i < n; i++) {
                        v[i] = new int [n];
            }
        return v;
    }
    
const char* const BigramCounter::DEFAULT_VALID_CHARACTERS="abcdefghijklmnopqrstuvwxyz\xE0\xE1\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xEA\xEB\xEC\xED\xEE\xEF\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF8\xF9\xFA\xFB\xFC\xFD\xFE\xFF";
BigramCounter::BigramCounter(std::string validChars ){
    _validCharacters = validChars;
    _frequency = reservarM(validChars.size());
    for (int i = 0 ; i < validChars.size() ; i++){
        for(int j = 0 ; j < validChars.size() ; j++){
            _frequency[i][j] = 0;
        }
    }
}
BigramCounter::BigramCounter(BigramCounter &orig){
            liberarM();
            this->_frequency = reservarM(orig.getSize());
            this->_validCharacters = orig.getValidCharacters();
            for(int i = 0 ; i<orig.getSize() ; i++){
                for(int j = 0 ; j< orig.getSize() ; j++){
                    this->_frequency[i][j] = orig.getfrequency()[i][j];
                }
            }
}
BigramCounter::~BigramCounter(){
    liberarM();
}



 int BigramCounter::getSize(){
     _validCharacters.size();
 }
 string BigramCounter::getValidCharacters(){
    return _validCharacters;
 }
 int ** BigramCounter::getfrequency(){
     return _frequency;
 }
 
 
 
 int BigramCounter::getNumberActiveBigrams(){
     int contador = 0 ;
     for ( int i = 0 ; i < _validCharacters.size() ; i++){
         for ( int j = 0 ; j < _validCharacters.size() ; j++ ){
             if(_frequency[i][j]){
                 contador++;
             }
         }
     }
     return contador;
 }
 bool BigramCounter::setFrequency(Bigram bigram, int frequency){
     
     int primera = 0;
     int segunda = 0;
     
     bool primeraEncontrada = false;
     bool segundaEncontrada = false;
     
     for( int a = 0 ; a < _validCharacters.size() ; a++){
         if(_validCharacters[a] == bigram.toString()[0]){
             primera = a;
             primeraEncontrada = true;
         }
         else if(_validCharacters[a] == bigram.toString()[1]){
             segunda = a;
             segundaEncontrada = true;
         }
     }
     
     if(primeraEncontrada && segundaEncontrada){
         return false;
     }
          
     else{
         
         _frequency[primera][segunda] = frequency;
         return true;
     }
     
 }
 void BigramCounter::increaseFrequency(Bigram bigram, int frequency){
     int fila = _validCharacters.find(bigram.at(0));
     int columna = _validCharacters.find(bigram.at(1));
     if(fila != string::npos && columna != string::npos){
         if(frequency != 0){
             _frequency[fila][columna] += frequency ;
         }
         else{
             _frequency[fila][columna] += 1 ;
         }
         
     }
 }
  BigramCounter BigramCounter::operator=(BigramCounter orig){
        if(&orig != this){
            liberarM();
            this->_frequency = reservarM(orig.getSize());
            this->_validCharacters = orig.getValidCharacters();
            for(int i = 0 ; i<orig.getSize() ; i++){
                for(int j = 0 ; j< orig.getSize() ; j++){
                    this->_frequency[i][j] = orig.getfrequency()[i][j];
                }
            }
        }
        return *this;
  }
   BigramCounter BigramCounter::operator+=(BigramCounter rhs){
       
       for ( int i = 0 ; i < rhs.getValidCharacters().size() ; i++ ){
           for ( int j = 0 ; j <rhs.getValidCharacters().size() ; j++){
               if(_frequency[i][j] != 0){
               _frequency[i][j] = _frequency[i][j] + rhs.getfrequency()[i][j];
               }
               else{
                   _frequency[i][j]++;
               }
           }
       }
       
       return *this;
       
   }
   void BigramCounter::calculateFrequencies(char* fileName){
       ifstream archivo;
       archivo.open(fileName);
       if(!archivo.is_open()){
            throw out_of_range("Fallo en la apetura");
       }
       else{
           string texto;
           while(archivo >> texto){
               for ( int i = 0 ; i < texto.size()-1; i++){
                   Bigram aux = Bigram(tolower(texto[i]),tolower(texto[i+1]));
                   increaseFrequency(aux);
               }
           }
           
       }
       archivo.close();
   }
   Language BigramCounter::toLanguage(){
       int contador = 0;
       for ( int i = 0 ; i < _validCharacters.size() ; i++ ){
           for ( int j = 0 ; j <_validCharacters.size() ; j++){
               if(_frequency[i][j] != 0){
                   contador++;
               }
           }
       }
       
       Language aux = Language(contador);
       
       int contador2 = 0;
       
         for ( int i = 0 ; i < _validCharacters.size() ; i++ ){
           for ( int j = 0 ; j <_validCharacters.size() ; j++){
               
               if(_frequency[i][j] != 0){
                   Bigram Baux = Bigram(_validCharacters[i],_validCharacters[j]);
                   aux.getVectorBigramFreq()[contador2].setBigram(Baux);
                   aux.getVectorBigramFreq()[contador2].setFrequency(_frequency[i][j]);
                   contador2++;
               }
               
           }
       }
       return aux;
   }
   