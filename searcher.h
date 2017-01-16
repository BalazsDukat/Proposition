Operand* searcher(Operand* c, string t)
{if(c == NULL) 
	{cout << " reached a NULL on the tree ";
	return NULL;
	}
else 	
	if(t == c -> ret_name())
	{cout << "returning: " << c -> ret_name() << endl;
	return c;
	}
	else
	    {if(t > c -> ret_name())
	    {cout << "found: " << c -> ret_name() << endl;
			c = c -> ret_right();
	    }
	    else
	    {cout << "found: " << c -> ret_name() << endl;
			c = c -> ret_left(); 
	    }
	    return searcher(c,t);
	    }
}
