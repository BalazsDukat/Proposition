#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <conio.h> //not for linux
/*
#include <mysql_connection.h>
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
#include <resultset_metadata.h>
*/
using namespace std;

#include "class_Operand.h"
#include "class_Expression.h"
#include "class_boolExpression.h"
#include "class_intExpression.h"
#include "class_stringExpression.h"
#include "class_doubleExpression.h"
#include "class_Operand_b.h"
#include "class_Operand_i.h"
#include "class_Operand_d.h"
#include "class_Operand_s.h"
#include "class_boolExpression_b.h"
#include "class_boolExpression_i.h"
#include "class_boolExpression_d.h"
#include "class_boolExpression_s.h"
#include "class_intExpression_i.h"
#include "class_doubleExpression_d.h"
#include "class_stringExpression_s.h"
#include "class_Wrappers.h"
#include "class_Assigners.h"
#include "class_Rule.h"
#include "searcher.h"
#include "tree_builder.h"
#include "expression_builder.h"
#include "assigner_builder.h"
#include "Operands_from_file.h"
#include "rule_builder.h"
#include "initialisation.h"
#include "write_out.h"

int main()
{// 1) ////////////////// READ FROM DESCRIPTOR AND BUILD OPERANDS AND SEARCH TREE
/*Root of the binary search tree of Operands and handle for creating new Operands.*/
  Operand* ROOT = NULL;
/*Two vectors that will serve as lists of Operand names. They are column labels in tables.*/
  vector<string> in_col_labels, out_col_labels;
/*a string for storing the current line.*/
  string line;
/*Get the two set of Operands. They are on different lists but go into the same data structure.
They have different origins and supposed to serve different purposes. Only the ones in the
output descriptor will be written into the new table.*/
  Operands_from_file("input_descriptor", ROOT, in_col_labels);
  Operands_from_file("output_descriptor", ROOT, out_col_labels);

// 2) /////////////////////////// BUILDING RULES
/*This happens only once but better to keep it separate.*/
vector<Rule> RB = rule_builder("rules.txt", ROOT); //this will store the rules in memory

// 3) INITIALISING OPERANDS, RUNNING RULES ON THEM, WRITING OUTPUT, until all rows have been processed
  ifstream data_file("data.csv");
  ofstream output_file("OutPut.csv");
  /*for each data line/object:
  1 initialise. from file or from db
  when initialising from file: take line, then process it based on the inputfile descriptor
  2 run the rules
  3 write the output. into file or db
  then start again from 1 while there's input.
  */
  while(getline(data_file,line)) //for each row. setting Operand values and then firing rules.
  {if(initialisation(line, ROOT, in_col_labels)) //initialise
	 {for(int i = 0; i < RB.size(); i++)
      {RB[i].fire(); //fire all rules
      cout << " Rule number: " << i << endl;
      }
  // 4) OUTPUT //the results should be written out here.
	 write_out(line, ROOT, out_col_labels, output_file); //write out the results
	 }
	 else cerr << "There was a problem with the initialisation of Operands for this line: "
	 << line << endl;//and then get next line and continue.
//for DB version:
  //prepared statment here, that writes out results into a database table or csv file.
  //a separate outputwriter function here goes through the result-table columnames
  //which could be given in a file. searcher can find each and output their values into the output file.
  }
output_file.close();
cout << "Finished successfully! Press any key to exit." << endl;
char c = getch();  //not for linux
}
