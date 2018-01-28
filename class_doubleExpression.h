class doubleExpression : public Expression //ABC
{public:
	virtual double ret_value() = 0;
  char ret_type() {return 'd';}
};
