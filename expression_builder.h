#include <sstream>
#include "side_builder.h" //calls this Exp_builder below. Not to be used separately.

Expression* Exp_builder(istringstream& in, Operand* ROOT)
{Expression* l_exp = NULL, *r_exp = NULL; //generic Expressions
string temp, Operator;
//LEFT
if(in >> temp)
  {cout << "  " << temp << endl;
  if(temp == "(")
  {l_exp = Exp_builder(in, ROOT);//side_builder(in, temp, ROOT);
  if(l_exp == NULL) return NULL; //this is to catch whatever may bubble up from side_builder.
  else if(!(in >> temp && temp == ")"))
    {cerr << "Expression did not close properly, found: " << temp << " instead of ')'!" << endl;
    return NULL; //just return NULL and that will be noticed elsewhere.
    }
  }
  else
  {l_exp = side_builder(temp, ROOT);
  if(l_exp == NULL) return NULL;
  }}
else
  {cerr << "Nothing to read" << endl;
  return NULL; //just return NULL and that will be noticed elsewhere.
  }
//OPERATOR
if(in >> temp) {Operator = temp; cout << "  " << temp << endl;}
else
  {cerr << "NO OPERATOR" << temp << endl;
  return NULL; //just return NULL and that will be noticed elsewhere.
  }
//RIGHT
if(in >> temp)
  {cout << "  " << temp << endl;
  if(temp == "(")
  {r_exp = Exp_builder(in, ROOT);//side_builder(in, temp, ROOT);
  if(r_exp == NULL) return NULL; //this is to catch whatever may bubble up from side_builder.
  else if(!(in >> temp && temp == ")"))
    {cerr << "Expression did not close properly, found: " << temp << " instead of ')'!" << endl;
    return NULL; //just return NULL and that will be noticed elsewhere.
    }
  }
  else
  {r_exp = side_builder(temp, ROOT);
  if(r_exp == NULL) return NULL;
  }}
else
  {cerr << "Nothing to read" << endl;
  return NULL; //just return NULL and that will be noticed elsewhere.
  }
//putting it all together:
Expression* ret_exp = NULL;
if(l_exp -> ret_type() == r_exp -> ret_type())
  {switch(l_exp -> ret_type())
    {case 'i':
        {intExpression* l = static_cast<intExpression* >(l_exp);
        intExpression* r = static_cast<intExpression* >(r_exp);
        if(Operator == "=" || Operator == "<" || Operator == ">" || Operator == "<="  || Operator == ">=")
        ret_exp = new boolExpression_i(l, Operator, r); //THE POROBLEM IS WITH THESE, THESE ALL ARE boolExpressions !!!!!!!!!!!!!!!!!!!
        else ret_exp = new intExpression_i(l, Operator, r);
        //the exact type of the expression should depend on the Operator as that gives a clue about the type of the value that will be returned.
        break;
        }
    case 'd':
        {doubleExpression* l = static_cast<doubleExpression* >(l_exp);
        doubleExpression* r = static_cast<doubleExpression* >(r_exp);
        if(Operator == "=" || Operator == "<" || Operator == ">" || Operator == "<="  || Operator == ">=")
        ret_exp = new boolExpression_d(l, Operator, r);
        else ret_exp = new doubleExpression_d(l, Operator, r);
        break;
        }
    case 's':
        {stringExpression* l = static_cast<stringExpression* >(l_exp);
        stringExpression* r = static_cast<stringExpression* >(r_exp);
        if(Operator == "=")
        ret_exp = new boolExpression_s(l, Operator, r);
        else ret_exp = new stringExpression_s(l, Operator, r);
        break;
        }
    case 'b':
        {boolExpression* l = static_cast<boolExpression* >(l_exp);
        boolExpression* r = static_cast<boolExpression* >(r_exp);
        ret_exp = new boolExpression_b(l, Operator, r); //this doesn't need checking
        break;
        }
    default: cerr << " MISMATCHING OR INVALID SIDES  " << endl;
    }
  }
else cout << "MISMATCHING SIDES IN THE EXPRESSION!" << l_exp -> ret_type() << " and " << r_exp -> ret_type() << endl;
cout << " Type of RETURN EXPRESSION: " << ret_exp -> ret_type() << endl;
return ret_exp;
}
