bool Operands_from_file(string filename, Operand*& ROOT, vector<string>& col_labels)
{// 1) ////////////////// READ FROM DESCRIPTOR AND BUILD OPERANDS AND SEARCH TREE
/*Take the filename, create th Operands, put them into the binary search tree, and also give back a list of them.*/
  string line, temp, name, type;

  ifstream descriptor_file(filename.c_str()); //user editable
  Operand* newOperand = NULL;
  while(getline(descriptor_file,line))
  {istringstream descriptor(line);
	newOperand = NULL;
  if(descriptor >> name && descriptor >> type) //just the 1st 2 words one each
  {if(type == "int") newOperand = new Operand_i(name);
  else if(type == "string") newOperand = new Operand_s(name);
  else cerr << "### Invalid column type: " << type << endl;
  cout << name << " " << type << endl; //diagnostic message
  } else cerr << "COULDN'T READ the name and type pair from input-descriptor!!" << endl;
  if(newOperand != NULL)
	  if(tree_builder(ROOT,newOperand))
	  {col_labels.push_back(name);
	  }
	  else cout << "### Nothing to be placed onto the search tree." << endl;
  else
	{ cerr << "### Incomplete input_descriptor, got a line but not a string from it.";
		descriptor_file.close();
		return false;
	}
  }
  descriptor_file.close();
	return true;
} //after this we still need to get the information source as well, which will be an input filestream. This was just the descriptor.
/*After this comes the building of Rules and tying them into the Operands. Reading from the input datafile follows from this.*/
