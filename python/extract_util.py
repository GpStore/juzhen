#! /usr/bin/env python

import os
import re

util_directory = "../src/util/"

output = open("util.i", "w")

ignore_file_list = ["map_reduce.h", "matrix_stl.h", "vector_stl.h", "util.h"]
ignore_func_list = ["Map", "RandVector", "RandMatrix"]

no_complex_file_list = ["vector_map_math.h", "matrix_map_math.h"]
no_complex_func_list = ["Sort", "Max", "Min", "StdDev", "CorrCoeff", "Var", "Cov", "InnerProduct"]

return_double_func_list = ["Norm"]

for i in range(len(ignore_file_list)):
  ignore_file_list[i] = util_directory + ignore_file_list[i]

for i in range(len(no_complex_file_list)):
  no_complex_file_list[i] = util_directory + no_complex_file_list[i]

def my_print(string):
#  print string
  output.write("%s\n" % string)

def change_func_name(funcname):
  ret = ""
  for i in range(len(funcname)):
    if funcname[i] >= 'A' and funcname[i] <= 'Z':
      if ret != "":
        ret = ret + '_'
      ret = ret + funcname[i].lower()
    else:
      ret = ret + funcname[i]
  return ret

def extract_func(filename):
  if filename in ignore_file_list:
    return
  f = open(filename, "r")
  string = f.read()
  f.close()
  my_print('''/**
 * Functions extracted from '%s'.
 */''' % filename)
  string = string.replace("\n", " ")
  string = string.replace("\r", " ")
  funcs = re.findall("template<[ \w,]+>([ \w\&\*<>\(\),]+){", string)
  for func in funcs:
    func = func.replace("DataType", "T")
    func = func.replace(" T ", " double ")
    func = func.replace("<T>", "<double>")
    func = func.replace(" T1 ", " double ")
    func = func.replace("<T1>", "<double>")
    func = func.replace("Matrix<double>", "Matrix")
    func = func.replace("Matrix<CD>", "CMatrix")
    func = func.replace("Matrix<Complex<double> >", "CMatrix")
    func = func.replace("Vector<double>", "Vector")
    func = func.replace("Vector<CD>", "CVector")
    func = func.replace("Vector<Complex<double> >", "CVector")
    for i in range(10):
      func = func.replace("  ", " ")
    func = func.replace("( ", "(")
    func = func.replace(" )", ")")
    func = "  " + func.strip() + ";"
    if (func.find("operator") == -1):
      func_name = re.findall("[ *&](\w+)\(.*\)", func)
      func_name = func_name[0]
      if not func_name in ignore_func_list:
        my_print("%%rename(%s) %s;" % (change_func_name(func_name), func_name))
        my_print(func.strip())
        if not (filename in no_complex_file_list) and not (func_name in no_complex_func_list):
          func = func.replace("Vector", "CVector")
          func = func.replace("CCVector", "CVector")
          func = func.replace("Matrix", "CMatrix")
          func = func.replace("CCMatrix", "CMatrix")
          if not (func_name in return_double_func_list):
            func = func.replace("double", "Complex")
          my_print(func.strip())
	my_print("")
  my_print("")

my_print('''/**
 * This file is automatically generated by a script.
 * DON'T MANUALLY CHANGE IT!
 */

''')

for root, dirs, files in os.walk(util_directory):
  for file in files:
    if file[-2:] == ".h":
      filename = "%s%s" % (root, file)
      extract_func(filename) 

output.close()
