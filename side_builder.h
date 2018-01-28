#include "get_type.h"
//Expression* Exp_builder(istringstream& , Operand* );//no need

//SIDE BUILDER
Expression* side_builder(string temp, Operand* ROOT)
{Expression* ret_exp;
Operand* Op = searcher(ROOT, temp);
if(Op == NULL) //Operand not found. literal builder here.
{char stringType = get_type(temp); cout << "** stringType : " << stringType << " " << temp << endl;
switch(stringType)
  {case 'i':
    {int converted = atoi(temp.c_str());
    Operand_i* Op_i = new Operand_i(temp);
    Op_i -> set_value(converted);
    ret_exp = new intWrapper(Op_i);
    tree_builder(ROOT, Op_i);
    break;
    }
  case 'd':
    {double converted = atof(temp.c_str());
    Operand_d* Op_d = new Operand_d(temp);
    Op_d -> set_value(converted);
    ret_exp = new doubleWrapper(Op_d);
    tree_builder(ROOT, Op_d);
    break;
    }
  case 's':
    {Operand_s* Op_s = new Operand_s(temp); //no conversion necessary, as it's a string
    Op_s -> set_value(temp);
    ret_exp = new stringWrapper(Op_s);
    tree_builder(ROOT, Op_s);
    break;
    }
  case 'b':
    {Operand_b* Op_b = new Operand_b(temp);
    if(temp == "true" || temp == "True") Op_b -> set_value(true);
    else Op_b -> set_value(false);
    ret_exp = new boolWrapper(Op_b);
    tree_builder(ROOT, Op_b);
    break;
    }
  default: //This normally cannot possibly happen.
    {cerr << "### unknown string type: " << stringType << endl;
    ret_exp = NULL;
    }
  }
}
else //if Op != NULL, the assumption is that it is valid, returned be searcher. Error handling to be added here.
{switch(Op -> ret_type())
  {case 'i':
    {int converted = atoi(temp.c_str());
    Operand_i* Op_i = static_cast<Operand_i* >(Op);
    Op_i -> set_value(converted);
    ret_exp = new intWrapper(Op_i);
    break;
    }
  case 'd':
    {double converted = atof(temp.c_str());
    Operand_d* Op_d = static_cast<Operand_d* >(Op);
    Op_d -> set_value(converted);
    ret_exp = new doubleWrapper(Op_d);
    break;
    }
  case 's':
    {Operand_s* Op_s = static_cast<Operand_s* >(Op);
    Op_s -> set_value(temp);
    ret_exp = new stringWrapper(Op_s);
    break;
    }
  case 'b':
    {Operand_b* Op_b = static_cast<Operand_b* >(Op);
    if(temp == "true" || temp == "True") Op_b -> set_value(true);
    else Op_b -> set_value(false);
    ret_exp = new boolWrapper(Op_b);
    break; //other Operand types can be added here.
    }
  default: //This normally cannot possibly happen.
    {cerr << "### unknown Operand type in side builder: " << Op -> ret_type() << endl;
    ret_exp = NULL;
    }
  }cout << Op -> ret_type() << Op -> ret_name();
}
return ret_exp;
}
