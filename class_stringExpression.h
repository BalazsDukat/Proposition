class stringExpression : public Expression //ABC
{public:
	virtual string ret_value() = 0;
        char ret_type() {return 's';}
};
