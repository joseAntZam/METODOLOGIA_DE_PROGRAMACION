
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
    outputStream << "LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> .... ]" << endl;
    outputStream << "           learn the model for the language languageId from the text files <text1.txt> <text2.txt> <text3.txt> ..." << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-l languageId: language identifier (unknown by default)" << endl;
    outputStream << "-o outputFilename: name of the output file (output.bgr by default)" << endl;
    outputStream << "<text1.txt> <text2.txt> <text3.txt> ....: names of the input files (at least one is mandatory)" << endl;
}
 
/**
 * This program learns a Language model from a set of input tex files (tex1.txt,
 * tex2.txt, ...
 * Running example:
 * > LEARN [-t|-b] [-l languageId] [-o outputFilename] <text1.txt> [<text2.txt> <text3.txt> ....]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error

 */
int main(int argc, char *argv[]) {   
    
    
    if (argc == 1) {
        showEnglishHelp(cerr);
        return 1;
    }
    
    
    int argumentoIdioma = -1;
    int argumentobgr = -1;
  
    int contador= 0;
    vector<int> textos;
    
    for ( int i = 1 ; i < argc ; i=i+contador){
        
            if (argv[i][0] == '-') {
                        if ((argv[i][1]== 't') ) {

                            contador = 1;
                        } 
                         if ((argv[i][1]== 'b') ) {

                            contador = 1;
                        } 
                         if ((argv[i][1]== 'l') ){
                            argumentoIdioma = i+1;   //1
                           // cout<<argumentoIdioma<<endl<<endl<<endl;
                            contador = 2;
                        } 
                         if ((argv[i][1]== 'o')) {
                            argumentobgr = i+1;  //3
                            contador = 2;
                        }
                         
                        if((argv[i][1]== 'T') || (argv[i][1]== 'B') || (argv[i][1]== 'L') || (argv[i][1]== 'O')){
                            showEnglishHelp(cerr);
                            return 1;
                        }
                }
            
            else{     
                        textos.push_back(i) ;
                        contador = 1;
                }
       
       }
    
    
    
    string nombre;
    if(argumentobgr == -1){
         nombre="output.bgr";
    }
    else{
        nombre = argv[argumentobgr];
    }
    
        ofstream archivo(nombre);
    
        
        BigramCounter aux{};
        for(int i=0 ; i< textos.size() ; i++){
            aux.calculateFrequencies(argv[textos[i]]);
            //cout<<argv[textos[i]]<<endl;
        }

        Language laux= aux.toLanguage();
        
        if(argumentoIdioma != -1){
            laux.setLanguageId(argv[argumentoIdioma]);
        }
        
        laux.sort();
        
        //cout<<laux.toString()<<endl;
        //cout<<laux.getSize()<<endl;
        archivo<<laux;
        archivo.close();
       
        return 0;
       
        
}
