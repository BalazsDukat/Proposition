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
    //if it happens here, that is a problem! This should be something actually present on the searchtree, we want to assign a new value to it.
    return NULL; //so just return NULL and that will be noticed elsewhere.
    }//else all is well, carry on
//OPERATOR frankly, this can be anything now.
if(in >> temp) Operator = temp;
else
{cerr << "NO OPERATOR" << temp << endl;
return NULL; //just return NULL and that will be noticed elsewhere.
} cout << "Operator: " << temp << endl;
//RIGHT
if(in >> temp) //Assigner builde (this) has to handle this in the same way as Exp_builder does, has to be prepared to return just a wrapper on th right side
{if(temp == "(")
{r_exp = Exp_builder(in, ROOT); //build an Expression; its return value will be assigned to the Operand on the left.
  if(r_exp == NULL)
  {cerr << "Failed to build right-side Expression in the assigner.\n";
  return NULL; //just return NULL and that will be noticed elsewhere.
  }
  else
  if(in >> temp && temp == ")") cout << " Expression closed (assigner right) " << endl;
  else
      {cerr << "Expression in Assigner did not close properly, found: " << temp << " instead of ')'!" << endl;
      //this is really just formality here.
      return NULL; //just return NULL and that will be noticed elsewhere.
      }
}
else
  {r_exp = side_builder(temp, ROOT);
  if(r_exp == NULL) return NULL;
  }
}
else
  {cerr << "Nothing to read" << endl;
  return NULL; //just return NULL and that will be noticed elsewhere.
  }
//putting it all together:
Assigner* a = NULL;
if(l_op -> ret_type() == r_exp -> ret_type())
//the 2 ret_type()-s are not related and their outputs are the same only because of convention, not inheritance!
{switch(l_op -> ret_type())
	{case 'd':
		{Operand_d* l = static_cast<Operand_d* >(l_op);
		doubleExpression* r = static_cast<doubleExpression* >(r_exp);
		a = new Assigner_d(l, /*Operator,*/ r);
		break;
		}
	case 'i':
		{Operand_i* l = static_cast<Operand_i* >(l_op);
		intExpression* r = static_cast<intExpression* >(r_exp);
		a = new Assigner_i(l, /*Operator,*/ r);
		break;
		}
	case 's':
		{Operand_s* l = static_cast<Operand_s* >(l_op);
		stringExpression* r = static_cast<stringExpression* >(r_exp);
		a = new Assigner_s(l, /*Operator,*/ r);
		break;
		}
	case 'b':
		{Operand_b* l = static_cast<Operand_b* >(l_op);
		boolExpression* r = static_cast<boolExpression* >(r_exp);
		a = new Assigner_b(l, /*Operator,*/ r);
		break;
		}
	default: cerr << "Unkown Operand type in assigner_builder.\n";
	}
} else cout << "MISMATCHING SIDES IN THE EXPRESSION (in an Assigner)!" << l_op -> ret_name() << l_op -> ret_type() << r_exp -> ret_type() << endl;
return a;
}
