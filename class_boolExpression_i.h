class boolExpression_i : public boolExpression
{public:
        boolExpression_i(intExpression*, string, intExpression*);
        bool ret_value();
private:	
	intExpression* left;
	intExpression* right;
};

boolExpression_i::boolExpression_i(intExpression* l, string o, intExpression* r)
{Operator = o;
left = l;
right = r;
}

bool boolExpression_i::ret_value()
{if(Operator == "=")
	{if(left -> ret_value() == right -> ret_value()) return true;
	else return false;	
	}		
if(Operator == "<=") 
	{if(left -> ret_value() <= right -> ret_value()) return true;
	else return false;	
	}
if(Operator == ">=") 
	{if(left -> ret_value() >= right -> ret_value()) return true;
	else return false;	
	}
if(Operator == "<") 
	{if(left -> ret_value() < right -> ret_value()) return true;
	else return false;	
	}
if(Operator == ">") 
	{if(left -> ret_value() > right -> ret_value()) return true;
	else return false;	
	}
bad_Operator();
return false; //just in case
}
