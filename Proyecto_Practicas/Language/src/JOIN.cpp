
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
    outputStream << "JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>] " << endl;
    outputStream << "       join the Language files <file1.bgr> <file2.bgr> ... into <outputFile.bgr>" << endl;
    outputStream << endl;
    outputStream << "Parameters:" << endl;
    outputStream << "-t|-b: text mode or binary mode for the output file (-t by default)" << endl;
    outputStream << "-o <outputFile.bgr>: name of the output file (output.bgr by default)" << endl;
    outputStream << "<file*.bgr>: each one of the files to be joined" << endl;
}
 
/**
 * This program reads an undefined number of Language objects from the files
 * passed as parameters to main(). It obtains as result the union of all the 
 * input Language objects. The result is then sorted by decreasing order of 
 * frequency and alphabetical order of bigrams when there is any tie in 
 * frequencies. Finally, the resulting Language is saved in an output file. The 
 * program must have at least an output file. 
 * Running example:
 * >  JOIN [-t|-b] [-o <outputFile.bgr>] <file1.bgr> [<file2.bgr> ... <filen.bgr>]
 * @param argc The number of command line parameters
 * @param argv The vector of command line parameters (cstrings)
 * @return 0 If there is no error; a value > 0 if error
**/
int main(int argc, char* argv[]) {
 
    if (argc == 1) {
        showEnglishHelp(cerr);
        return 1;
    }
    
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
                         if ((argv[i][1]== 'o')) {
                            argumentobgr = i+1;  //3
                            contador = 2;
                        }
                         
                        if((argv[i][1]== 'T') || (argv[i][1]== 'B') ||  (argv[i][1]== 'O')){
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
    
    Language aux = Language();
    aux.load(argv[textos[0]]);
    
    for(int i = 1 ; i<textos.size(); i++){
        Language aux2 = Language();
        aux2.load(argv[textos[i]]);
        aux += aux2;
    }
    
    aux.sort();
    
    archivo<<aux;
    
    archivo.close();
    
    return 0;
    
}

 
