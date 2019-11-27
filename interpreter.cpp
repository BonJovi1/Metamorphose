#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>

#include "ast.h"
#include "Interpreter.h"

using namespace std;

map<string, what_it_returns> symbol_table;

what_it_returns interpret(struct ASTNode *root)
{
	switch (root->nodetype) 
	{
		case expression:
			what_it_returns lol1, lol2;
			lol1 = interpret(root->expression_node.left); 
			lol2 = interpret(root->expression_node.right); 
			return lol2;

		case declaration:
			what_it_returns temp;
			temp.return_type = INT_RET;
			temp.int_value = 0;

			symbol_table[root->declaration_node.right->identifier_node] = temp;
			
			return temp;
			break;

		case arraydeclaration:
			
			temp.return_type = ARRAY_RET;
			temp.array_value.no_of_elements = root->arraydeclaration_node.right->litval;

			symbol_table[root->arraydeclaration_node.left->identifier_node] = temp;
			
			return temp;
			break;

		case Assignment:

			temp = interpret(root->assignment_node.right);
			
			//checking if variable is there in the symbol table
			if(symbol_table.find(root->assignment_node.left->identifier_node) == symbol_table.end())
			{
				cout<<"Variable not declared :";
				break;
			}
			symbol_table[root->assignment_node.left->identifier_node] = temp;
			return temp;
			break;

		case ArrayAssignment:

			temp = interpret(root->arrayassignment_node.right);
			//checking if array variable is there in the symbol table
			if(symbol_table.find(root->arrayassignment_node.left->identifier_node) == symbol_table.end())
			{
				cout<<"Variable not declared :";
				break;
			}

			char* arrayname;
			int newvalue;
			arrayname = root->arrayassignment_node.left->identifier_node;
			newvalue = temp.int_value;
			
			struct ASTNode *location;
			location = root->arrayassignment_node.center;
			temp = interpret(location);
			
			int locvalue;
			if(location->nodetype == INTLITERAL)
				locvalue = location->litval;
			else if(location->nodetype == identifier)
				locvalue = symbol_table[location->identifier_node].int_value; 
			else
				locvalue = temp.int_value;
			
			symbol_table[arrayname].array_value.arr[locvalue] = newvalue;
			return symbol_table[arrayname];
			break;

		case BinaryOp:
			what_it_returns a,b,final;
			a = interpret(root->binarynode.left);
			b = interpret(root->binarynode.right);
			switch (root->binarynode.op) 
			{
				case ADD: 	
					final.return_type = INT_RET;
					final.int_value = (a.int_value + b.int_value);
					return(final);
					break;

				case AND: 	
					final.return_type = INT_RET;
					final.int_value = (a.int_value & b.int_value);
					return(final);
					break;

			}
			break;

		case Condition:
			a = interpret(root->condition_node.left);
			b = interpret(root->condition_node.right);
			// cout<<"left value = "<< a.int_value;
			// cout<<endl;
			// cout<<"right value = "<< b.int_value;
			// cout<<endl;
			final.return_type = BOOL_RET;
			switch (root->condition_node.op) 
			{
				case EQ: 	
					final.return_type = BOOL_RET;
					if(a.int_value == b.int_value)
						final.bool_value = 1;
					else
						final.bool_value = 0;
					return(final);
					break;

				case LT: 	
					final.return_type = BOOL_RET;
					if(a.int_value < b.int_value)
						final.bool_value = 1;
					else
						final.bool_value = 0;
					return(final);
					break;

				case GT: 	
					final.return_type = BOOL_RET;
					if(a.int_value > b.int_value)
						final.bool_value = 1;
					else
						final.bool_value = 0;
					return(final);
					break;
			}
			break;
		
		case ForStatement:

			// checking if loop_variable is declared 
			temp = interpret(root->forstatement_node.left);

			char* loop_variable; 
			loop_variable = root->forstatement_node.left->identifier_node; // the loop variable 
			
			/* ------------------------------------------------------------------------------
			Interpreting the for loop boundary conditions
			Ideally, should've written another recursive function for this, but no time xD 
			---------------------------------------------------------------------------------*/
			int start, end, increment;

			start = root->forstatement_node.center->forloop_node.start->litval;
			end = root->forstatement_node.center->forloop_node.end->litval;
			increment = root->forstatement_node.center->forloop_node.increment->litval;

			temp.return_type = INT_RET;
			temp.int_value = start;
			symbol_table[loop_variable] = temp;

			while(symbol_table[loop_variable].int_value < end)
			{
				// cout<<"Iteration"<<endl;
				a = interpret(root->forstatement_node.right);
				symbol_table[loop_variable].int_value = symbol_table[loop_variable].int_value + increment; 
			}

			// cout<<"ANSWER: "<<a.int_value;
			return a;
			break;
			
		case IfStatement:
			what_it_returns temp_condition, temp_exprs;
			temp_condition = interpret(root->ifstatement_node.left);
			// cout<< " Condition Result "<< temp_condition.bool_value << endl;
			if(temp_condition.bool_value == (1==1))
			{
				// cout<<"BON JOVI"<<endl;
				temp_exprs = interpret(root->ifstatement_node.right);
				return temp_exprs;
			}
			else
			{
				// cout<<"ALOK"<<endl;
				what_it_returns tempnew;
				tempnew.return_type = MESSAGE_RET;
				tempnew.message = "if statement condition not satisfied";
				return tempnew;
			}


		case INTLITERAL:
			what_it_returns obj;
			obj.return_type = INT_RET;
			obj.int_value = root->litval;
			return obj;
			break;

		case identifier:
			if(symbol_table.find(root->identifier_node) == symbol_table.end())
			{
				cout<<"Variable not declared :";
				break;
			}
			obj.return_type = ID_RET;
			obj.int_value = symbol_table[root->identifier_node].int_value ;
			return obj;
			break;

		case arrayvariable:
			
			arrayname = root->arrayvariable_node.left->identifier_node;
			location = root->arrayvariable_node.right;
			obj = interpret(location);
			if(symbol_table.find(arrayname) == symbol_table.end())
			{
				cout<<"Variable not declared :";
				break;
			}

			if(location->nodetype == INTLITERAL)
				locvalue = location->litval;
			else if(location->nodetype == identifier)
				locvalue = symbol_table[location->identifier_node].int_value; 
			else
				locvalue = obj.int_value; 

			obj.return_type = ARRAY_RET;
			obj.int_value = symbol_table[arrayname].array_value.arr[locvalue];
			return obj;
			break;

		case Print:
			location = root->print_node.left;
			
			// if(location->nodetype == INTLITERAL)
			// 	locvalue = location->litval;
			 
			what_it_returns lol3;
			lol3 = symbol_table[location->identifier_node];
			if(lol3.return_type == ARRAY_RET)
			{
				for(int i=0; i<lol3.array_value.no_of_elements; i++ )
					cout<<lol3.array_value.arr[i]<<" ";
				cout<<endl;
			}
			else
				cout<<lol3.int_value;

			return lol3;
			break;


	}
};
// case INT_RET: 
//     cout<<obj.int_value<<endl;
// 	break;
// case BOOL_RET: 
// 	cout<<obj.bool_value<<endl;
// 	break;
// case ARRAY_RET:
// 	for(int i=0; i<5; i++ )
// 		cout<<obj.array_value.arr[i]<<" ";
// 	cout<<endl;
// 	break;
// case MESSAGE_RET:
// 	cout<<obj.message;


/* Printing the symbol table out
for(auto k:symbol_table)              
{
	cout<<k.first<< " ";
	cout<<k.second.int_value<<endl;
}
-------------------------------*/