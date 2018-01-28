class boolExpression_s : public boolExpression
{public:
        boolExpression_s(stringExpression*, string, stringExpression*);
        bool ret_value();
private:
	stringExpression* left;
	stringExpression* right;
};

boolExpression_s::boolExpression_s(stringExpression* l, string o, stringExpression* r)
{Operator = o;
left = l;
right = r;
}

bool boolExpression_s::ret_value()
{if(Operator == "=") // this is to be extended with a few more
	{if(left -> ret_value() == right -> ret_value()) return true;
	else return false;
	}
bad_Operator();
return false; //just in case
}
