class boolExpression : public Expression //ABC
{public:
	virtual bool ret_value() = 0;
        char ret_type() {return 'b';}
};
