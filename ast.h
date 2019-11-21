typedef enum  astnodetype {BinaryOp, INTLITERAL} ASTNodeType;
typedef enum  binaryoptype {ADD, SUB, MUL, DIV} BinaryOpType; 

extern struct ASTNode *getASTNodeBinaryOp(struct ASTNode *left, struct ASTNode *right, BinaryOpType operator);
//extern struct ASTNode *getASTNodeTernaryOp(struct ASTNode *first, struct ASTNode *second, struct ASTNode *third);
extern struct ASTNode *getASTNodeIntLiteral(int litval);

extern void printPostFix(struct ASTNode *root);

struct ASTNode {
	ASTNodeType nodetype;

	union {
	
		struct 
		{
			BinaryOpType op; 
			struct ASTNode *left;
			struct ASTNode *right; 
		} binarynode;	

		int litval;
	};

};

