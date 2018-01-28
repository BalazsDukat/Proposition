Operand* searcher(Operand* c, string t) //c = ROOT at start
{if(c == NULL) return NULL;
else
	if(t == c -> ret_name()) return c;
	else
	    {if(t > c -> ret_name()) c = c -> ret_right();
	    else c = c -> ret_left();
	    }
return searcher(c,t);
}
