/*Takes a line of data, the root of the binary search tree of nodes and the input column labels.
It goes through all of the input column labels, looks up the node on the search tree with the same name as the label,
and sets the data field of the node to the next bit of data from the line.
This relies on that the order of the column labels is the same as the order of the columns in the data, left to right.*/
#include "get_until.h"

bool initialisation(string line, Operand* ROOT, vector<string> in_col_labels)
{istringstream data(line);
  for(int i = 0; i < in_col_labels.size() - 1; i++) //initialisation
  {Operand* Op = searcher(ROOT, in_col_labels[i]);
  string temp = get_until(data, ',');
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
  else cout << "### could not find Operand " << in_col_labels[i] << endl;
  }
return true;
}
