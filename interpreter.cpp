#include <bits/stdc++.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>

#include "ast.h"
#include "Interpreter.h"

using namespace std;

// Initializing symbol tables
map<string, what_it_returns> symbol_table;

what_it_returns interpret(struct ASTNode *root)
{
	switch (root->nodetype) 
	{
		// case expression:
		// 	interpret(root->expression_node.left);
		// 	interpret(root->expression_node.right);

		case declaration:
			what_it_returns temp;
			temp.return_type = INT_RET;
			temp.int_value = 0;

			symbol_table[root->declaration_node.right->identifier_node] = temp;
			
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

		// case Condition:
		// 	switch (root->condition_node.op) 
		// 	{
		// 		case EQ: 
		// 			if(interpret(root->condition_node.left) == interpret(root->condition_node.right) ) 
		// 				return 1;
		// 			else
		// 				return 0;
		// 	}
		// 	break;
		
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
				temp = interpret(root->forstatement_node.right);
				symbol_table[loop_variable].int_value = symbol_table[loop_variable].int_value + increment; 
			}

			return temp;
			break;
			
			// root->forstatement_node.center


		case INTLITERAL:
			what_it_returns obj;
			obj.return_type = INT_RET;
			obj.int_value = root->litval;
			return obj;
			break;

		case identifier:
			// cout<<"AGAIN"<<root->identifier_node;
			if(symbol_table.find(root->identifier_node) == symbol_table.end())
			{
				cout<<"Variable not declared :";
				break;
			}
			obj.return_type = ID_RET;
			obj.int_value = symbol_table[root->identifier_node].int_value ;
			return obj;
			break;

	}
};


/* Printing the symbol table out
for(auto k:symbol_table)              
{
	cout<<k.first<< " ";
	cout<<k.second.int_value<<endl;
}
-------------------------------*/