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

struct ASTNode *getASTNodeAssignment(struct ASTNode *left, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Assignment;
	
	node->assignment_node.left = left;
	node->assignment_node.right = right;

	return node;
}

struct ASTNode *getASTNodeBinaryOp(struct ASTNode *left, struct ASTNode *right, BinaryOpType operator)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = BinaryOp;
	
	node->binarynode.left = left;
	node->binarynode.right = right;
	node->binarynode.op = operator;

	return node;
}

struct ASTNode *getASTNodeCondition(struct ASTNode *left, struct ASTNode *right, CondOpType operator)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = Condition;
	
	node->condition_node.left = left;
	node->condition_node.right = right;
	node->condition_node.op = operator;

	return node;
}

struct ASTNode *getASTNodeDeclaration(DataType operator, struct ASTNode *right)
{
	struct ASTNode *node; 
	node = (struct ASTNode *) malloc(sizeof(struct ASTNode));

	node->nodetype = declaration;
	
	node->declaration_node.right = right;
	node->declaration_node.op = operator;

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
	printf("alok %s\n",node->identifier_node);

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
						// printf("\n");
						break;
		case Assignment:
						// printf("Assignment Operation\n");
						
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
						printf("identifier ");
						printf("%s", root->identifier_node);
						printf("\n");
						break;
		case declaration:
						printf("Declaration\n");
						
						printPostFix(root->declaration_node.right);
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
						printf("\n");
						break;

	}
};