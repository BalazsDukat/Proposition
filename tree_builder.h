bool build(Operand* current, Operand* Op)
{if(Op -> ret_name() < current -> ret_name())
    {if(current -> ret_left() == NULL)
      {current -> set_left(Op);
      return true;
      }
    else return build(current -> ret_left(), Op);
    }
else
if(Op -> ret_name() > current -> ret_name())
    {if(current -> ret_right() == NULL)
      {current -> set_right(Op);
      return true;
      }
    else return build(current -> ret_right(), Op);
    } //if it is neither smaller, nor greater, it has to be equal
else cout << " #This is already on the tree: " << Op -> ret_name() << endl;
return false;
}

bool tree_builder(Operand*& ROOT, Operand* Op)
{if(ROOT != NULL) return build(ROOT, Op);
else ROOT = Op;
return true;
}
