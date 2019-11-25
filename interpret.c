#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE struct ASTNode *
extern int yylex();
extern int yyparse();
extern FILE *yyin;

int interpret(struct ASTNode *root)
{
	switch (root->nodetype) 
	{
		case BinaryOp:
						switch (root->binarynode.op) 
						{
							case ADD: return(root->binarynode.left + root->binarynode.right);
									  break; 
							case SUB: return(root->binarynode.left - root->binarynode.right);
									  break;
							case MUL: return(root->binarynode.left * root->binarynode.right);
									  break;
							case DIV: return(root->binarynode.left / root->binarynode.right);
									  break;
						}
						// printf("\n");
						break;
		case INT_LITERAL: return root->

	}
};