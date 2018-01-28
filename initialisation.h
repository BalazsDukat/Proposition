/*Takes a line of data, the root of the binary search tree of nodes and the input column labels.
It goes through all of the input column labels, looks up the node on the search tree with the same name as the label,
and sets the data field of the node to the next bit of data from the line.
This relies on that the order of the column labels is the same as the order of the columns in the data, left to right.*/
#include "get_until.h"

bool initialisation(string line, Operand* ROOT, vector<string> in_col_labels)
{istringstream data(line);
  for(int i = 0; i < in_col_labels.size(); i++)
  {Operand* Op = searcher(ROOT, in_col_labels[i]);
  string temp = get_until(data, ',');
  if(Op != NULL)
  {switch(Op -> ret_type())
  {case 'i':
    {int converted = atoi(temp.c_str());
    Operand_i* Op_i = static_cast<Operand_i* >(Op);
    Op_i -> set_value(converted);
    break;
    }
  case 'd':
    {double converted = atof(temp.c_str());
    Operand_d* Op_d = static_cast<Operand_d* >(Op);
    Op_d -> set_value(converted);
    break;
    }
  case 's':
    {Operand_s* Op_s = static_cast<Operand_s* >(Op);
    Op_s -> set_value(temp);
    break;
    }
  case 'b':
    {Operand_b* Op_b = static_cast<Operand_b* >(Op);
    if(temp == "true" || temp == "True") Op_b -> set_value(true);
    else Op_b -> set_value(false);
    break; //other Operand types can be added here.
    }
  default: //This normally cannot possibly happen.
    {cerr << "### unknown Operand type in initialiasation: " << Op -> ret_type() << endl;
    }
  }
  }
  else cout << "### could not find Operand " << in_col_labels[i] << endl;
  }
return true;
}
