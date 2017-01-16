class boolExpression_b : public boolExpression
{public:
        boolExpression_b(boolExpression*, string, boolExpression*);
        bool ret_value();
private:
	boolExpression* left;
	boolExpression* right;
};

boolExpression_b::boolExpression_b(boolExpression* l, string o, boolExpression* r)
{Operator = o;
left = l;
right = r;
}

bool boolExpression_b::ret_value()
{if(Operator == "AND")
	{if((left -> ret_value() == true) && (right -> ret_value() == true))
		return true;
		else return false;
	}
else
if(Operator == "OR")
	{if((left -> ret_value() == true) || (right -> ret_value() == true))
		return true;
		else return false;
	}
else
if(Operator == "XOR")
	{if((left -> ret_value() == true) ^ (right -> ret_value() == true))
		return true;
		else return false;
	}
bad_Operator();
return false; //just in case
}
