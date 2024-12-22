touch tests//.timeout
CMD="valgrind --leak-check=full /home/jose/SubirGIT/MP/Proyecto_Practicas/Language/./dist/LEARN/GNU-Linux/LEARN  -l spanish -o tests/output/test_ES.bgr ../Books/test_ES.txt 1> tests//.out25 2>&1"
eval $CMD
rm tests//.timeout
