/*This is to find out about a string if it can be converted into
a boolean, double, or integer, (or should remain a string), in this order.
Returns a character to indicate the type found.
d for double: has a dot, numbers only otherwise, may have sign
i for integer:  numbers only, may have sign
b for boolean: "true" or "false"
s for string: if won't fit any other category above.
*/

char get_type(string input)
{bool hasDot = false, digitsOnly = false/*, hasSign = false*/;
int inputSize = input.size();
//the first character is checked separately for sign as well
digitsOnly = (isdigit(input[0]) || ((input[0] == '-' || input[0] == '+' || input[0] == '.') && inputSize > 1));
hasDot = (input[0] == '.');
//the 1st character was checked above, so go through the rest of the characters (if any)
for(int i = 1; (i < inputSize && digitsOnly == true); i++)
{digitsOnly = (isdigit(input[i]) || (input[i] == '.' && hasDot == false)/*found a . and it's the 1st one'*/);
if(input[i] == '.') hasDot = true;
}

if(digitsOnly == true)
	if(hasDot == true) return 'd';
	else return 'i';
else
if(inputSize > 1 && (input == "true" || input == "True" || input == "false" || input == "False"))
{cout << "**This is a BOOL** " << input << endl;
  return 'b';
}
//else
//If all else fails:
return 's';
}
