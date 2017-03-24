#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
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
#include "class_Operand_b.h"
#include "class_Operand_i.h"
#include "class_Operand_s.h"
#include "class_boolExpression_b.h"
#include "class_boolExpression_i.h"
#include "class_boolExpression_s.h"
#include "class_intExpression_i.h"
#include "class_stringExpression_s.h"
#include "class_Wrappers.h"
#include "class_Assigners.h"
#include "class_Rule.h"
#include "searcher.h"
#include "tree_builder.h"
#include "int_expression_builder.h"
#include "string_expression_builder.h"
#include "bool_expression_builder.h"
#include "assigner_builder.h"
#include "Operands_from_file.h"
#include "rule_builder.h"

int main()
{// 1) ////////////////// READ FROM DESCRIPTOR AND BUILD OPERANDS AND SEARCH TREE
/*Root of the binary search tree of Operands and handle for creating new Operands.*/
  Operand* ROOT = NULL, *newOperand;
/*Two vectors that will serve as lists of Operand names. They are column labels in tables.*/
  vector<string> in_col_labels, out_col_labels;
/*Generally useful variables, a string for each line and a general variable.*/
  string line, temp;
/*Get the two set of Operands. They are on different lists but go into the same data structure.*/
  Operands_from_file("input_descriptor", ROOT, in_col_labels);
	Operands_from_file("output_descriptor", ROOT, out_col_labels);
	
// 2) /////////////////////////// BUILDING RULES
/*This happens only once but better to keep it separate.*/
vector<Rule> RB = rule_builder("rules.txt", ROOT); //this will store the rules in memory

// 3) INITIALISING OPERANDS, RUNNING RULES ON THEM, WRITING OUTPUT, until all rows have been processed
  ifstream data_file("data.csv");
  ofstream output_file("OutPut.csv");
  
  while(getline(data_file,line)) //for each row. setting Operand values and then firing rules.
  {istringstream data(line);
  for(int i = 0; i < in_col_labels.size()-1; i++) //initialisation
  {Operand* Op = NULL;
	if(data >> temp) Op = searcher(ROOT, in_col_labels[i]);
  if(Op != NULL)
  {switch(Op -> ret_type())
	{case 'i':
		{Operand_i* Op_i = static_cast<Operand_i* >(Op);
		istringstream string_to_int(temp);
    int i;
    if(string_to_int >> i) Op_i -> set_value(i);
    else cerr << "### Conversion from string to int failed." << endl;
    break;
  	}
	case 's':
		{Operand_s* Op_s = static_cast<Operand_s* >(Op);
    Op_s -> set_value(temp);
    break; //other Operand types can be added here.
  	}
	default: //This normally cannot possibly happen.
		cout << "### unknown Operand type: " << Op -> ret_type() << endl;
	}
  }
  else cout << "### could not find Operand ";
  cout << in_col_labels[i] << endl; //just to show what's happening.
  }
  for(int i = 0; i < RB.size(); i++) RB[i].fire(); //firing all rules
// 4) OUTPUT //the results should be written out here.
  //prepared statment here, that writes out results into a database table or csv file.
  //for now the same data.csv will be used for output, adding columns to it.
  //a separate outputwriter function here should go through the result-table columnames
  //which could be given in a file. searcher can find each and output their values into the output file.
  for(int i = 0; i < out_col_labels.size(); i++)
	{temp = out_col_labels[i];
	newOperand = searcher(ROOT,temp);
      if(newOperand == NULL)
        {cerr << "Operand " << temp << " cannot be found!" << endl;
				//if it happens here, that is a problem!
				output_file << temp << "*missing*";
        }
      else if(newOperand -> ret_type() == 'i')
        {Operand_i* op_i = static_cast<Operand_i* >(newOperand);
				output_file << op_i -> ret_value();
        }
      else if(newOperand -> ret_type() == 's')
        {Operand_s* op_s = static_cast<Operand_s* >(newOperand);
				output_file << op_s -> ret_value();
        }
      else if(newOperand -> ret_type() == 'b')
        {Operand_b* op_b = static_cast<Operand_b* >(newOperand);
				output_file << op_b -> ret_value();
        }
      else
        {cerr<< " WRONG TYPE RETURNED: " << newOperand -> ret_type() << endl;
        output_file << "wrong_type:" << newOperand -> ret_type() << "*for:" << temp;
        }
	output_file << " ";
  }
	output_file << endl;
  }
output_file.close();
cout << "Finished successfully! Press any key to exit." << endl;
//char c = getch();
}
