#include <sstream>
//#include "searcher.h"
Assigner* Assigner_builder(istringstream& in, Operand* ROOT)
{cout << " *ASSIGNER BUILDER STARTS" << endl;
Operand* l_op = NULL;
Expression* r_exp = NULL;
string temp, Operator;
//LEFT
if(in >> temp) l_op = searcher(ROOT,temp);
else
{cerr << "Nothing to read!" << endl;
return NULL; //just return NULL and that will be noticed elsewhere.
}
if(l_op == NULL)
    {cerr << "Operand " << temp << " cannot be found!" << endl;
    //if it happens here, that is a problem! This should be something actually present on the searchtree.
    return NULL; //so just return NULL and that will be noticed elsewhere.
    }//else nothing, carry on
//OPERATOR frankly, this can be anything now.
if(in >> temp) Operator = temp;
else
{cerr << "NO OPERATOR" << temp << endl;
return NULL; //just return NULL and that will be noticed elsewhere.
}
//RIGHT
if(in >> temp)
if(temp == "(")
    {cout << " new boolExpression is being built on the left side " << endl;
    r_exp = boolExp_builder(in, ROOT);
    if(r_exp == NULL) return NULL; //just return NULL and that will be noticed elsewhere.
    else
    if(in >> temp && temp == ")") cout << " boolExpression closed (assigner right) " << endl;
    else
        {cerr << "Expression did not close properly, found: " << temp << " instead of ')'!" << endl;
        //this is really just formality here.
        return NULL; //just return NULL and that will be noticed elsewhere.
        }
    }
else
if(temp == "[")
    {cout << " new intExpression is being built on the left side " << endl;
    r_exp = intExp_builder(in, ROOT);
    if(r_exp == NULL) return NULL; //just return NULL and that will be noticed elsewhere.
    else
    if(in >> temp && temp == "]") cout << " intExpression closed (assigner right) " << endl;
    else
        {cerr << "Expression did not close properly, found: " << temp << " instead of ']'!" << endl;
        //this is really just formality here.
        return NULL; //just return NULL and that will be noticed elsewhere.
        }
    }
else
if(temp == "{")
    {cout << " new stringExpression is being built on the left side " << endl;
    r_exp = stringExp_builder(in, ROOT);
    if(r_exp == NULL) return NULL; //just return NULL and that will be noticed elsewhere.
    else
    if(in >> temp && temp == "}") cout << " stringExpression closed (assigner right) " << endl;
    else
        {cerr << "Expression did not close properly, found: " << temp << " instead of '}'!" << endl;
        //this is really just formality here.
        return NULL; //just return NULL and that will be noticed elsewhere.
        }
    }
else
    {Operand* O = searcher(ROOT,temp);
    if(O == NULL)
		{int converted;
        if(converted = atoi(temp.c_str()))
          {Operand_i* op_i = new Operand_i(temp);
          op_i -> set_value(converted);
          r_exp = new intWrapper(op_i);
          tree_builder(ROOT,op_i);
          }
	      else
				if(temp == "true")
				  {Operand_b* op_b = new Operand_b(temp);
				  op_b -> set_value(true);
				  r_exp = new boolWrapper(op_b);
				  tree_builder(ROOT, op_b);
				  }
				else
				if(temp == "false")
					{Operand_b* op_b = new Operand_b(temp);
					op_b -> set_value(false);
					r_exp = new boolWrapper(op_b);
					tree_builder(ROOT, op_b);
					}
  			else
	        {Operand_s* op_s = new Operand_s(temp);
	        op_s -> set_value(temp);
	        r_exp = new stringWrapper(op_s);
				 	tree_builder(ROOT, op_s);
	        }
		}
    else
		if(O -> ret_type() == 'i')
		{Operand_i* op_i = static_cast<Operand_i* >(O);
		r_exp = new intWrapper(op_i);
		}
    else
    if(O -> ret_type() == 's')
		{Operand_s* op_s = static_cast<Operand_s* >(O);
		r_exp = new stringWrapper(op_s);
    }
    else
    if(O -> ret_type() == 'b')
		{Operand_b* op_b = static_cast<Operand_b* >(O);
		r_exp = new boolWrapper(op_b);
    }
		else
		{cerr<< " WRONG TYPE RETURNED: " << O -> ret_type() << endl;
    return NULL; //so just return NULL and that will be noticed elsewhere.
    }
	}
else
{cerr << "Nothing to read!" << endl;
return NULL; //just return NULL and that will be noticed elsewhere.
}
//putting it all together:
Assigner* a = NULL;
if(l_op -> ret_type() == r_exp -> ret_type()) 
//the 2 ret_type()-s are not related and their outputs are the same only because of convention, not inheritance!
{switch(l_op -> ret_type())
	{case 'i': 
		{Operand_i* l = static_cast<Operand_i* >(l_op);
		intExpression* r = static_cast<intExpression* >(r_exp);
		a = new Assigner_i(l, /*Operator,*/ r); break;
		}
	case 's': 
		{Operand_s* l = static_cast<Operand_s* >(l_op);
		stringExpression* r = static_cast<stringExpression* >(r_exp);
		a = new Assigner_s(l, /*Operator,*/ r); break;
		}
	case 'b': 
		{Operand_b* l = static_cast<Operand_b* >(l_op);
		boolExpression* r = static_cast<boolExpression* >(r_exp);
		a = new Assigner_b(l, /*Operator,*/ r); break;
		}
	default: cerr << " MISMATCHING OR INVALID SIDES  " << endl;
	}
} else cout << "MISMATCHING SIDES IN THE EXPRESSION!" << l_op -> ret_type() << r_exp -> ret_type() << endl;
return a;
}
