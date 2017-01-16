void tree_builder(Operand* c, Operand* Op)
{/*this cannot take NULL, or the Operand pointers would have to be made public.
or possibly this should be a friend of Operand class.*/
if(Op -> ret_name() < c -> ret_name())
    {if(c -> ret_left() == NULL) 
	{c -> set_left(Op);
	cout << " new Operand added to the left of the current one " << endl;
	}
    else tree_builder(c -> ret_left(), Op);
    }
else
if(Op -> ret_name() > c -> ret_name())
    {if(c -> ret_right() == NULL) 
	{c -> set_right(Op);
        cout << " new Operand added to the right of the current one " << endl;
	}
    else tree_builder(c -> ret_right(), Op);
    } //if it is neither smaller, nor greater, it has to be equal
    else cout << " #This is already on the tree: " << Op -> ret_name() << endl;
}
