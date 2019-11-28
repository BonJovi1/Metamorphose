#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

struct ASTNode *getASTNodeForLoop(struct ASTNode *start, struct ASTNode *end, struct ASTNode *increment)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = ForLoop;

	node->forloop_node.start = start;
	node->forloop_node.end = end;
	node->forloop_node.increment = increment;

	return node;
}

struct ASTNode *getASTNodeForStatement(struct ASTNode *left, struct ASTNode *center, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = ForStatement;

	node->forstatement_node.left = left;
	node->forstatement_node.center = center;
	node->forstatement_node.right = right;

	return node;
}

struct ASTNode *getASTNodeIfStatement(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = IfStatement;

	node->ifstatement_node.left = left;
	node->ifstatement_node.right = right;

	return node;
}


struct ASTNode *getASTNodeIfElseStatement(struct ASTNode *left, struct ASTNode *center, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = IfElseStatement;;

	node->ifelse_node.left = left;
	node->ifelse_node.center = center;
	node->ifelse_node.right = right;

	return node;
}

struct ASTNode *getASTNodeAssignment(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Assignment;

	node->assignment_node.left = left;
	node->assignment_node.right = right;

	return node;
}

struct ASTNode *getASTNodeArrayAssignment(struct ASTNode *left, struct ASTNode *center, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = ArrayAssignment;

	node->arrayassignment_node.left = left;
	node->arrayassignment_node.center = center;
	node->arrayassignment_node.right = right;

	return node;
}

struct ASTNode *getASTNodeExpression(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = expression;

	node->expression_node.left = left;
	node->expression_node.right = right;
	return node;
}

struct ASTNode *getASTNodePrintPossibilities(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = PrintPossibilities;

	node->expression_node.left = left;
	node->expression_node.right = right;
	return node;
}

struct ASTNode *getASTNodeBinaryOp(struct ASTNode *left, struct ASTNode *right, BinaryOpType opera)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = BinaryOp;

	node->binarynode.left = left;
	node->binarynode.right = right;
	node->binarynode.op = opera;

	return node;
}

struct ASTNode *getASTNodeCondition(struct ASTNode *left, struct ASTNode *right, CondOpType opera)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Condition;

	node->condition_node.left = left;
	node->condition_node.right = right;
	node->condition_node.op = opera;

	return node;
}

struct ASTNode *getASTNodeDeclaration(DataType opera, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = declaration;

	node->declaration_node.op = opera;
	node->declaration_node.right = right;

	return node;
}

struct ASTNode *getASTNodeArrayDeclaration(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = arraydeclaration;

	node->arraydeclaration_node.left = left;
	node->arraydeclaration_node.right = right;

	return node;
}

struct ASTNode *getASTNodeArrayVariable(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = arrayvariable;

	node->arrayvariable_node.left = left;
	node->arrayvariable_node.right = right;

	return node;
}


// struct ASTNode *getASTNodeTernaryOp(struct ASTNode *first, 
// 									struct ASTNode *second,
// 									struct ASTNode *third)
// {
// 	struct ASTNode *node; 

// 	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

// 	node->nodetype = TernaryOp;
// 	node->ternarynode.first = first;
// 	node->ternarynode.second = second;
// 	node->ternarynode.third = third;

// 	return node;
// }

struct ASTNode *getASTNodeIntLiteral(int litval)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = INTLITERAL;
	node->litval = litval;

	return node;
}

struct ASTNode *getASTNodeID(char* str)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = identifier;
	node->identifier_node = str;

	return node;
}

struct ASTNode *getASTNodeBreak(char* str)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Break;
	node->break_node = str;

	return node;
}

struct ASTNode *getASTNodePrint(struct ASTNode *root)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Print;
	node->print_node.left = root;

	return node;
}

struct ASTNode *getASTNodeScan(struct ASTNode *root)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Scan;
	node->scan_node.left = root;

	return node;
}

struct ASTNode *getASTNodeMultipleID(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = MultipleID;

	node->multipleid_node.left = left;
	node->multipleid_node.right = right;

	return node;
}

void printPostFix(struct ASTNode *root)
{
	switch (root->nodetype) 	
	{
		case BinaryOp:
			// printf("Binary Operator ");
		
			printPostFix(root->binarynode.left);
			printPostFix(root->binarynode.right);
			switch (root->binarynode.op) 
			{
				case ADD: printf("+ ");
						  break; 
				case SUB: printf("- ");
						  break;
				case MUL: printf("* ");
						  break;
				case DIV: printf("/ ");
						  break;
			}
			// printf("\n");
			break;
			// case TernaryOp: printPostFix(root->ternarynode.first);
			// 				printPostFix(root->ternarynode.second);
			// 				printPostFix(root->ternarynode.third);
			// 				printf("? ");
			// 				break;
		case INTLITERAL:
			printf("%d ", root->litval);
			break;
		case Assignment:
			printPostFix(root->assignment_node.left);
			printPostFix(root->assignment_node.right);
			printf("\n");
			break;
		case ForLoop:
			// printf("For Loop\n");	
			printPostFix(root->forloop_node.start);
			printPostFix(root->forloop_node.end);
			printPostFix(root->forloop_node.increment);
			printf("\n");
			break;
		case Condition:
			// printf("Condition Operation\n");
			
			printPostFix(root->condition_node.left);
			printPostFix(root->condition_node.right);
			switch (root->condition_node.op) 
			{
				case EQ: printf("== ");
						break; 
				case LE: printf("<= ");
						break;
				case GE: printf(">= ");
						break;
				case LT: printf("< ");
						break;
				case GT: printf("> ");
						break;
			}
			printf("\n");
					break;
		case identifier:
			printf("%s ", root->identifier_node);
			printf("\n");
			break;
		
		case expression:
			// printf("For Loop\n");	
			printPostFix(root->expression_node.left);
			printPostFix(root->expression_node.right);
			printf("\n");
			break;
		
		case declaration:
			// printf("Declaration\n");
			switch (root->declaration_node.op) 
			{
				case INTS: printf("int ");
						break; 
				case CHARS: printf("char ");
						break;
				case UINTS: printf("uint ");
						break;
				case BOOLS: printf("bool ");
						break;
				case STRINGS: printf("string ");
						break;
				case ARRAYS: printf("array ");
						break;
			}
			printPostFix(root->declaration_node.right);
			printf("\n");
			break;
}
};