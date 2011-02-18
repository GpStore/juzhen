/*
+---------------------------------------------------------------------------+
|  Matrix Library for C++ (mlcpp)                                           |
+---------------------------------------------------------------------------+
|                                                                           |
|  Copyright 2011 Hui Chen                                                  |
|                                                                           |
|  Licensed under the Apache License, Version 2.0 (the "License");          |
|  you may not use this file except in compliance with the License.         |
|  You may obtain a copy of the License at                                  |
|                                                                           |
|      http://www.apache.org/licenses/LICENSE-2.0                           |
|                                                                           |
|  Unless required by applicable law or agreed to in writing, software      |
|  distributed under the License is distributed on an "AS IS" BASIS,        |
|  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. |
|  See the License for the specific language governing permissions and      |
|  limitations under the License.                                           |
|                                                                           |
+---------------------------------------------------------------------------+
*/

#ifndef MLCPP_BENCH_BENCH_H_
#define MLCPP_BENCH_BENCH_H_

#include <sys/time.h>
#include <string.h>

#include <fstream>
#include <sstream>
#include <iostream>

#ifdef MLCPP
#include <mlcpp.h>
#else
#include <Eigen/Dense>
#endif

#define MAXN 100
#define MINN 2 
#define STEPN 1
#define NB 10

static int counter=0;

#define PREFIX "small_"

#ifdef MLCPP 
#define FNAME "mlcpp_"
#else
#define FNAME "eigen_"
#endif

#define BEGIN_BENCH(s) \
{\
{\
std::stringstream out;\
out << PREFIX << counter;\
filename =out.str()+ ".plt";\
myfile.open(filename.c_str());\
myfile << "set term png \nset out \"" + out.str()+".png\"\nset title \"" + s + "\"\nset xlabel \"N\" \nset ylabel \"Seconds\" \nplot 'mlcpp_"+out.str() + ".txt' using 1:2 title 'mlcpp' w l, 'eigen_"+out.str() + ".txt' using 1:2 title 'eigen' w l ";\
myfile.close();\
}\
{\
std::stringstream out;\
out << PREFIX << counter++;\
filename =FNAME+out.str()+ ".txt";\
}\
myfile.open(filename.c_str());\
std::cout << "==============================" << std::endl;\
for (size_t ni=MINN; ni<=MAXN; ni+=STEPN) {\
H1.resize(ni,ni);\
H2.resize(ni,ni);\
H3.resize(ni,ni);\
H4.resize(ni,ni);\
gettimeofday(&t1, NULL);\
std::cout << s << '\t'; \
for(size_t i=0; i<NB; i++) {

#define END_BENCH \
}\
gettimeofday(&t2, NULL); \
std::cout <<  (t2.tv_sec-t1.tv_sec) + (t2.tv_usec-t1.tv_usec)/1000000. << " s" << std::endl; \
myfile << ni <<'\t' << (t2.tv_sec-t1.tv_sec) + (t2.tv_usec-t1.tv_usec)/1000000. << std::endl;\
}\
myfile.close();\
}

#ifdef MLCPP
#define DEFV(vi) \
zmatrix H##vi (MAXN, MAXN); \
for (size_t i=0; i<MAXN; i++) \
for (size_t j=0; j<MAXN; j++) \
H##vi(i,j) = 1;
#else
#define DEFV(vi) \
MatrixXcd H##vi (MAXN, MAXN); \
for (size_t i=0; i<MAXN; i++) \
for (size_t j=0; j<MAXN; j++) \
H##vi(i,j) = 1;
#endif


#ifdef MLCPP
using namespace mlcpp;
#else
using namespace Eigen;
#endif


#endif
