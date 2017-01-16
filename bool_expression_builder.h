#include <sstream>
//#include <stdlib.h>
//#include "tree_builder.h"
//#include "searcher.h"

boolExpression* boolExp_builder(istringstream& in, Operand* ROOT)
  {
  Expression* l_exp = NULL, *r_exp = NULL;
  string temp, Operator;
//LEFT
  if(in >> temp)
    if(temp == "(")
      {cout << " new boolExpression is being built on the left side " << endl;
      l_exp = boolExp_builder(in, ROOT);
      if(l_exp == NULL) return
          NULL; //just return NULL and that will be noticed elsewhere.
      else if(in >> temp && temp == ")")
			cout << " boolExpression closed (left) " << endl;
      else
        {cerr << "Expression did not close properly, found: " << temp <<
             " instead of ')'!" << endl;
        //this is really just formality here.
        return NULL; //just return NULL and that will be noticed elsewhere.
        }
      }
    else if(temp == "[")
      {cout << " new intExpression is being built on the left side " << endl;
      l_exp = intExp_builder(in, ROOT);
      if(l_exp == NULL) return NULL; //just return NULL and that will be noticed elsewhere.
      else if(in >> temp && temp == "]")
			cout << " intExpression closed (left) " << endl;
      else
        {cerr << "Expression did not close properly, found: " << temp <<
             " instead of ']'!" << endl;
        //this is really just formality here.
        return NULL; //just return NULL and that will be noticed elsewhere.
        }
      }
    else if(temp == "{")
      {cout << " new stringExpression is being built on the left side " << endl;
      l_exp = stringExp_builder(in, ROOT);
      if(l_exp == NULL) return NULL; //just return NULL and that will be noticed elsewhere.
      else if(in >> temp && temp == "}")
			cout << " stringExpression closed (left) " << endl;
      else
        {cerr << "Expression did not close properly, found: " << temp <<
             " instead of '}'!" << endl;
        //this is really just formality here.
        return NULL; //just return NULL and that will be noticed elsewhere.
        }
      }
    else
      {Operand* O = searcher(ROOT,temp);
      if(O == NULL)
        {cerr << "Operand " << temp << " cannot be found!" << endl;
        //if it happens here, that is a problem!
        return NULL; //so just return NULL and that will be noticed elsewhere.
        }
      else if(O -> ret_type() == 'i')
        {Operand_i* op_i = static_cast<Operand_i* >(O);
        l_exp = new intWrapper(op_i);
        }
      else if(O -> ret_type() == 's')
        {Operand_s* op_s = static_cast<Operand_s* >(O);
        l_exp = new stringWrapper(op_s);
        }
      else if(O -> ret_type() == 'b')
        {Operand_b* op_b = static_cast<Operand_b* >(O);
        l_exp = new boolWrapper(op_b);
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
//OPERATOR
  if(in >> temp) Operator = temp;
  else
    {cerr << "NO OPERATOR" << temp << endl;
    return NULL; //just return NULL and that will be noticed elsewhere.
    }
//RIGHT
  if(in >> temp)
    if(temp == "(")
      {cout << " new boolExpression is being built on the right side " << endl;
      r_exp = boolExp_builder(in, ROOT);
      if(r_exp == NULL) return NULL; //just return NULL and that will be noticed elsewhere.
      else if(in >> temp && temp == ")")
			cout << " boolExpression closed (right) " << endl;
      else
        {cerr << "Expression did not close properly, found: " << temp <<
             " instead of ')'!" << endl;
        //this is really just formality here.
        return NULL; //just return NULL and that will be noticed elsewhere.
        }
      }
    else if(temp == "[")
      {cout << " new intExpression is being built on the right side " << endl;
      r_exp = intExp_builder(in, ROOT);
      if(r_exp == NULL) return NULL; //just return NULL and that will be noticed elsewhere.
      else if(in >> temp && temp == "]")
			cout << " intExpression closed (right) " << endl;
      else
        {cerr << "Expression did not close properly, found: " << temp <<
             " instead of ']'!" << endl;
        //this is really just formality here.
        return NULL; //just return NULL and that will be noticed elsewhere.
        }
      }
    else if(temp == "{")
      {cout << " new stringExpression is being built on the right side " << endl;
      r_exp = stringExp_builder(in, ROOT);
      if(r_exp == NULL) return NULL; //just return NULL and that will be noticed elsewhere.
      else if(in >> temp && temp == "}")
			cout << " stringExpression closed (right) " << endl;
      else
        {cerr << "Expression did not close properly, found: " << temp
				<< " instead of '}'!" << endl;
        //this is really just formality here.
        return NULL; //just return NULL and that will be noticed elsewhere.
        }
      }
    else
      {Operand* O = searcher(ROOT,temp);
      if(O == NULL) //It could be a simple separate literal builder here.
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
      else if(O -> ret_type() == 'i')
        {Operand_i* op_i = static_cast<Operand_i* >(O);
        r_exp = new intWrapper(op_i);
        }
      else if(O -> ret_type() == 's')
        {Operand_s* op_s = static_cast<Operand_s* >(O);
        r_exp = new stringWrapper(op_s);
        }
      else if(O -> ret_type() == 'b')
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
  boolExpression* ret_exp = NULL;
  if(l_exp -> ret_type() == r_exp -> ret_type())
    {switch(l_exp -> ret_type())
      {case 'i':
          {intExpression* l = static_cast<intExpression* >(l_exp);
          intExpression* r = static_cast<intExpression* >(r_exp);
          ret_exp = new boolExpression_i(l, Operator, r);
          break;
          }
      case 's':
          {stringExpression* l = static_cast<stringExpression* >(l_exp);
          stringExpression* r = static_cast<stringExpression* >(r_exp);
          ret_exp = new boolExpression_s(l, Operator, r);
          break;
          }
      case 'b':
          {boolExpression* l = static_cast<boolExpression* >(l_exp);
          boolExpression* r = static_cast<boolExpression* >(r_exp);
          ret_exp = new boolExpression_b(l, Operator, r);
          break;
          }
      default: cerr << " MISMATCHING OR INVALID SIDES  " << endl;
      }
    }
  else cout << "MISMATCHING SIDES IN THE EXPRESSION!" << l_exp -> ret_type()
	<< r_exp -> ret_type() << endl;
  return ret_exp;
  }
