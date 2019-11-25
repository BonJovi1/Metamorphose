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
			// temp = interpret(root->declaration_node.right);
			// string var = root->declaration_node.right->identifier_node;
			symbol_table[root->declaration_node.right->identifier_node] = temp;
			// .insert(make_pair(var, temp));
			return temp;
			// 
			// return temp;
			break;

		case Assignment:

			temp = interpret(root->assignment_node.right);
			
			if(symbol_table.find(root->assignment_node.left->identifier_node) == symbol_table.end())
			{
				cout<<"Variable not declared :";
				break;
			}
			symbol_table[root->assignment_node.left->identifier_node] = temp;
			// for(auto k:symbol_table)
			// {
			// 	cout<<k.first<< " ";
			// 	cout<<k.second.int_value<<endl;
			// }
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