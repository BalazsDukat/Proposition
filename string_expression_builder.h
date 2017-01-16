#include <sstream>
//#include <stdlib.h>
//#include "tree_builder.h"
//#include "searcher.h"

stringExpression_s* stringExp_builder(istringstream& in, Operand* ROOT)
{stringExpression* l_exp = NULL, *r_exp = NULL;
string temp, Operator;//, right_s;
//int status = 0, right_i = 0;
//LEFT
if(in >> temp)
if(temp == "{")
    {cout << " new stringExpression is being built on the left side " << endl;
    l_exp = stringExp_builder(in, ROOT);
    if(l_exp == NULL) return NULL; //just return NULL and that will be noticed elsewhere.
    else
    if(in >> temp && temp == "}") cout << " stringExpression closed (left) " << endl;
    else
        {cerr << "Expression did not close properly, found: " << temp << " instead of '}'!" << endl;
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
    else
	if(O -> ret_type() == 's')
	{Operand_s* op_s = static_cast<Operand_s* >(O);
	l_exp = new stringWrapper(op_s);
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
if(in >> temp && temp == "&") Operator = temp;
else
{cerr << "WRONG OPERATOR FOR A stringExpression" << temp << endl;
return NULL; //just return NULL and that will be noticed elsewhere.
}
//RIGHT
if(in >> temp)
if(temp == "{")
    {cout << " new stringExpression is being built on the right side " << endl;
    r_exp = stringExp_builder(in, ROOT);
    if(r_exp == NULL) return NULL; //just return NULL and that will be noticed elsewhere.
    else
    if(in >> temp && temp == "}") cout << " stringExpression closed (left) " << endl;
    else
        {cerr << "Expression did not close properly, found: " << temp << " instead of '}'!" << endl;
        //this is really just formality here.
        return NULL; //just return NULL and that will be noticed elsewhere.
        }
    }
else
    {Operand* O = searcher(ROOT,temp);
    if(O == NULL)
    {//create a literal here
    return NULL; //so just return NULL and that will be noticed elsewhere.
    }
    else
	if(O -> ret_type() == 's')
	{Operand_s* op_s = static_cast<Operand_s* >(O);
	r_exp = new stringWrapper(op_s);
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
stringExpression_s* ret_exp = new stringExpression_s(l_exp, Operator, r_exp);
return ret_exp;
}
