#include <sstream>
//#include <stdlib.h>
//#include "tree_builder.h"
//#include "searcher.h"

intExpression_i* intExp_builder(istringstream& in, Operand* ROOT)
  {
  intExpression* l_exp = NULL, *r_exp = NULL;
  string temp, Operator;//, right_s;
//int status = 0, right_i = 0;
//LEFT
  if(in >> temp)
    if(temp == "[")
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
    else
      {Operand* O = searcher(ROOT,temp);
      if(O == NULL)
        {int converted;
        if(converted = atoi(temp.c_str()))
          {Operand_i* op_i = new Operand_i(temp);
          op_i -> set_value(converted);
          l_exp = new intWrapper(op_i);
          tree_builder(ROOT,op_i);
          }
        else
          {cerr << "### " << temp <<
					" should be a name of an intOperand or a number" << endl;
          return NULL; //so just return NULL and that will be noticed elsewhere.
          }
        }
      else if(O -> ret_type() == 'i')
        {Operand_i* op_i = static_cast<Operand_i* >(O);
        l_exp = new intWrapper(op_i);
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
  if(in >> temp && (temp == "+" || temp == "-" || temp == "*" || temp == "/"
  || temp == "^")) Operator = temp;
  else
    {cerr << "WRONG OPERATOR FOR AN intExpression" << temp << endl;
    return NULL; //just return NULL and that will be noticed elsewhere.
    }
//RIGHT
  if(in >> temp)
    if(temp == "[")
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
          {cerr << "### " << temp <<
					" should be a name of an intOperand or a number" << endl;
          return NULL; //so just return NULL and that will be noticed elsewhere.
          }
        }
      else if(O -> ret_type() == 'i')
        {Operand_i* op_i = static_cast<Operand_i* >(O);
        r_exp = new intWrapper(op_i);
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
  intExpression_i* ret_exp = new intExpression_i(l_exp, Operator, r_exp);
  return ret_exp;
  }
