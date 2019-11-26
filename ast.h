typedef enum  astnodetype { BinaryOp, 
							INTLITERAL, 
							Assignment, 
							ForLoop, 
							ForStatement,
							Condition, 
							identifier,
							declaration,
							expression} 
							ASTNodeType;

typedef enum  binaryoptype {ADD, SUB, MUL, DIV, AND, OR} BinaryOpType; 
typedef enum  condoptype {EQ, LE, GE, LT, GT} CondOpType; 
typedef enum  datatype {INTS, CHARS, UINTS, BOOLS, STRINGS, ARRAYS } DataType; 

extern struct ASTNode *getASTNodeBinaryOp(struct ASTNode *left, 
										  struct ASTNode *right, 
										  BinaryOpType opera);

extern struct ASTNode *getASTNodeAssignment(struct ASTNode *left, 
											struct ASTNode *right);

extern struct ASTNode *getASTNodeForLoop(struct ASTNode *start, 
										 struct ASTNode *end, 
										 struct ASTNode *increment);

extern struct ASTNode *getASTNodeForStatement(struct ASTNode *left, 
										 struct ASTNode *right, 
										 struct ASTNode *center);

extern struct ASTNode *getASTNodeCondition(struct ASTNode *left, 				
										   struct ASTNode *right, 
										   CondOpType opera);

extern struct ASTNode *getASTNodeDeclaration(DataType opera, 
											 struct ASTNode *right);

extern struct ASTNode *getASTNodeExpression(struct ASTNode *left, 
											struct ASTNode *right);

extern struct ASTNode *getASTNodeIntLiteral(int litval);
extern struct ASTNode *getASTNodeID(char* str);
//extern struct ASTNode *getASTNodeTernaryOp(struct ASTNode *first, struct ASTNode *second, struct ASTNode *third);

extern void printPostFix(struct ASTNode *root);

struct ASTNode {
	ASTNodeType nodetype;

	union {
		
		//binary operation
		struct 
		{
			BinaryOpType op; 
			struct ASTNode *left;
			struct ASTNode *right; 
		} binarynode;

		//condition operation
		struct 
		{
			CondOpType op; 
			struct ASTNode *left;
			struct ASTNode *right; 
		} condition_node;

		//declaration
		struct 
		{
			DataType op; 
			struct ASTNode *right; 
		} declaration_node;

		//assignment operation
		struct
		{
			struct ASTNode *left;
			struct ASTNode *right;
		} assignment_node;

		//for loop parameters
		struct
		{
			struct ASTNode *start;
			struct ASTNode *end;
			struct ASTNode *increment;
		} forloop_node;

		//for loop statement
		struct
		{
			struct ASTNode *left;
			struct ASTNode *center;
			struct ASTNode *right;
		} forstatement_node;

		//expression
		struct 
		{
			struct ASTNode *left;
			struct ASTNode *right; 
		} expression_node;

		//numbers
		int litval;
		char* identifier_node;
	};

};

