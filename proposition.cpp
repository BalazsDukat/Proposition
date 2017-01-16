#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <conio.h>

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

int main()
{// 1) ////////////////// READ FROM DESCRIPTOR AND BUILD OPERANDS AND SEARCH TREE
  int in_col_count = 0, out_col_count = 0;
  vector<string> in_col_labels, out_col_labels;
  string line, temp, name, type;
  ifstream input_descriptor_file("input_descriptor.csv"); //user editable
  Operand* ROOT = NULL, *newOperand;
  while(getline(input_descriptor_file,line))
  {istringstream input_descriptor(line);
  newOperand = NULL;
  if(input_descriptor >> name && input_descriptor >> type) //just the 1st 2 words one each
  {if(type == "int") newOperand = new Operand_i(name);
  else if(type == "string") newOperand = new Operand_s(name);
  else cerr << "### Invalid column type: " << type << endl;
  cout << name << " " << type << endl;
  } else cerr << "COULDN'T READ tha name and type pair from input-descriptor!!" << endl;
  if(newOperand != NULL) 
	  if(tree_builder(ROOT,newOperand)) 
	  {in_col_count++; cout << in_col_count;
	  in_col_labels.push_back(name);
	  }
	  else cout << "### Nothing to be placed onto the search tree." << endl;
  else cerr << "### Incomplete input_descriptor.csv, got a line but not a string from it.";
  }
	input_descriptor_file.close();
	//now for the output
  ifstream output_descriptor_file("output_descriptor.csv"); //user editable
	while(getline(output_descriptor_file,line))
  {istringstream output_descriptor(line);
  newOperand = NULL;
  if(output_descriptor >> name && output_descriptor >> type) //just the 1st 2 words one each
  {if(type == "int") newOperand = new Operand_i(name);
  else if(type == "string") newOperand = new Operand_s(name);
  else cerr << "### Invalid column type: " << type << endl;
  cout << name << " " << type << endl;
  }
	else cerr << "COULDN'T READ tha name and type pair from output-descriptor!!"
	<< endl;
  if(newOperand != NULL)
	  if(tree_builder(ROOT,newOperand))
	  {out_col_count++;
	  out_col_labels.push_back(name);
	  }
	  else cout << "### Nothing to be placed onto the search tree." << endl;
  else cerr << "### Incomplete descriptor.csv, got a line but not a string from it.";
  }
  output_descriptor_file.close();
// ASSIGNERS SHOULD ONLY ASSIGN VALUES TO RESULT OPERANDS!
// 2) /////////////////////////// BUILDING RULES
//the building of rulebase from file happens only once, so it is just part of main now.
vector<Rule> RB; //this will store the rules in memory
ifstream rules_file("rules.txt"); //user editable
int counter = 0;
while(getline(rules_file,line))
{istringstream rule(line);
cout << counter; counter++;
if((rule >> temp) && (temp == "IF"))
	{Rule* Rp = NULL;
	if(Rp = new Rule(boolExp_builder(rule, ROOT)))//if this goes well, we continue. Might need to be changed.
		{cout << endl << "% we probably have an IF-side here ^_^ %" << endl;
		if((rule >> temp) && (temp == "THEN") && (Rp != NULL))
		{Rp -> add_THEN(Assigner_builder(rule, ROOT));//multiple THENs? while not ELSE go on... , as separator
		cout << endl << "% we probably have a THEN-part here ^_^ %" << endl;
		}
		else cout << "### badly formed Rule, has no THEN part!" << endl
     << "#### or the rule doesn't even exist." << endl
		 << " or could not read from file." << endl;
		if((rule >> temp) && (temp == "ELSE") && (Rp != NULL))
    {Rp -> add_ELSE(Assigner_builder(rule, ROOT));//multiple ELSEs? as with THENs.
    cout << endl << "% we probably have an ELSE-part here ^_^ %" << endl;
    }
		else cout << " no ELSE part, but that's OK" << endl;
		RB.push_back(*Rp);
		}
	else cout << "### INVALID EXPRESSION, NO RULE MADE! " << endl;
	}
else cout << "### DOESN'T START WITH IF, this is not a rule!" << endl
<< " or could not read from file." << endl;
}
rules_file.close();
// 3) INITIALISING OPERANDS, RUNNING RULES ON THEM, WRITING OUTPUT, until all rows have been processed
  ifstream data_file("data.csv"); //user editable
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
char c = getch();
}
