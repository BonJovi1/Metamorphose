#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

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

void printPostFix(struct ASTNode *root)
{
	switch (root->nodetype) 
	{
		case BinaryOp:
						printf("Binary Operator\n");
						
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
						printf("\n");
						break;
		// case TernaryOp: printPostFix(root->ternarynode.first);
		// 				printPostFix(root->ternarynode.second);
		// 				printPostFix(root->ternarynode.third);
		// 				printf("? ");
		// 				break;
		case INTLITERAL:
						printf("%d ", root->litval);
						break;
	}
};