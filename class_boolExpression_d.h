class boolExpression_d : public boolExpression
{public:
        boolExpression_d(doubleExpression*, string, doubleExpression*);
        bool ret_value();
private:	
	doubleExpression* left;
	doubleExpression* right;
};

boolExpression_d::boolExpression_d(doubleExpression* l, string o, doubleExpression* r)
{Operator = o;
left = l;
right = r;
}

bool boolExpression_d::ret_value()
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
