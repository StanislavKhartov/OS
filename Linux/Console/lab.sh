g++ -c NumLib/library.cpp -o NumLib/cmake-build-debug/NumLib.o
ar r NumLib/cmake-build-debug/libNumLib.a NumLib/cmake-build-debug/NumLib.o

g++ -c Dll/library.cpp -o Dll/cmake-build-debug/libDll.o -LNumLib/cmake-build-debug -lNumLib
g++ -shared -fPIC -o Dll/cmake-build-debug/libDll.so Dll/library.cpp


g++ -c Test/main.cpp -o Test/cmake-build-debug/Test -LNumLib/cmake-build-debug -LDll/cmake-build-debug -lNumLib -lDll


