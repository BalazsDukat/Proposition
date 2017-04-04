bool write_out(string line, Operand* ROOT, vector<string> out_col_labels, ofstream& output_file)
{string temp;
Operand* newOperand = NULL;
for(int i = 0; i < out_col_labels.size(); i++)
	{temp = out_col_labels[i];
	newOperand = searcher(ROOT,temp);
      if(newOperand == NULL)
        {cerr << "Operand " << temp << " cannot be found!" << endl;
				//if it happens here, that is a problem!
				output_file << temp << "*missing*";
        }
      else if(newOperand -> ret_type() == 'i')
        {Operand_i* op_i = static_cast<Operand_i* >(newOperand);
				output_file << op_i -> ret_value();
        }
      else if(newOperand -> ret_type() == 's')
        {Operand_s* op_s = static_cast<Operand_s* >(newOperand);
				output_file << op_s -> ret_value();
        }
      else if(newOperand -> ret_type() == 'b')
        {Operand_b* op_b = static_cast<Operand_b* >(newOperand);
				output_file << op_b -> ret_value();
        }
      else
        {cerr<< " WRONG TYPE RETURNED: " << newOperand -> ret_type() << "*for:" << temp << endl;
        output_file << "wrong_type:" << newOperand -> ret_type() << "*for:" << temp;
        }
	if(i < out_col_labels.size() - 1) output_file << ",";
	else output_file << endl;
  }
return true;
}
