
#include <iostream>
#include<cstring>
#include <fstream>
#include <vector>
#include "BigramCounter.h"
#include "Language.h"
using namespace std;
/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
    outputStream << "Error, run with the following parameters:" << endl;
    outputStream << "CLASSIFY <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ....]" << endl;
    outputStream << "          Obtains the identifier of the closest language to the input text file" << endl;
    outputStream << endl;
}

/**
 * This program print the language identifier of the closest language 
 * for an input text file (<text.txt>) among the set of provided models:
 * <lang1.bgr>, <lang2.bgr>, ...
 * 
 * Running example:
 * > CLASSIFY  <text.txt> <lang1.bgr> [<lang2.bgr> <lang3.bgr> ...]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
 */
int main(int argc, char *argv[]) {
    
    if (argc <3 ) {
        showEnglishHelp(cerr);
        return 1;
    }
    
    //texto convertido a language
     BigramCounter aux{};
        
     aux.calculateFrequencies(argv[1]);
     
     Language laux= aux.toLanguage();
     laux.sort();
     
     //primer bgr convertido a language
     
     Language laux2 = Language();
     laux2.load(argv[2]);
     laux2.sort();
    
     double distancia = laux.getDistance(laux2);
     string idioma = laux2.getLanguageId();
     
    
     
     for(int i = 3 ; i< argc ; i++ ){
         Language laux3 = Language();
         laux3.load(argv[i]);
         laux3.sort();
         
         double distanciAux = laux.getDistance(laux3);
         
         
         if(distanciAux < distancia){
             distancia = distanciAux;
             idioma = laux3.getLanguageId();
         }
     }
     
     
     cout<<"Final decision: language "<<idioma<<" with a distance of "<<distancia<<endl;
     return 0;
}
