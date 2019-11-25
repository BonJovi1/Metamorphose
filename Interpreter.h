#include <bits/stdc++.h>
using namespace std;

typedef enum returnvaluetype { INT_RET, BOOL_RET, ID_RET }ReturnValueType; 

typedef struct Return_Entity
{
	ReturnValueType return_type;
	union
	{
		int int_value;
		bool bool_value;
		char* id_value;
	};

} what_it_returns;

//To keep track of all functions
typedef struct functions
{
	string name;
	string return_type;
	std::vector<string> argument_names; 
	std::vector<string> argument_types;
	struct ASTNode* block;

} function;

extern what_it_returns interpret(struct ASTNode *root);
extern void print_answer(what_it_returns var); 