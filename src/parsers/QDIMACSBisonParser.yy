%require "3.0" /* require bison 3.0 or above */

/* select the skeleton file to be used as a parser template */
%skeleton "lalr1.cc"

/* enable tracking of parser locations */
%locations 

/* the constructor of the generated parser class takes these arguments
 * and stores them in equivalently named private member fields */
%parse-param {QDIMACSLexer &lexer} {IQbfInstanceBuilder &builder}

/* define some parser name settings */
%define parser_class_name {QDIMACSBisonParser}
%define api.namespace {logic}
%define api.prefix {logic}
%file-prefix "QDIMACSBison"

/* turn on error reporting (we need to define the 'error' function) */
%define parse.error verbose

/* include this code near the top of the generated header file, where
 * we need to include the relevant hand-written header files */
%code top
{
	#include "../preamble.h"
	#include "QDIMACSBisonParser.hpp"
	#include "QDIMACSLexer.hpp"
}

/* include this code in the generated header file, before the union of
 * types is defined; we need to define all the types used in the union here */
%code requires
{
	#include <string>
	#include <vector>
	#include <cstdint>

	namespace logic
	{
		typedef std::int32_t num_t;
		typedef std::vector<std::int32_t> num_vector;
	}
}

/* define the union of types that can be used for tokens in the grammer
 * (that is, for terminal and non-terminal symbols) */
%union
{
	std::string *string;
	logic::num_t number;
	logic::num_vector *numberlist;
	IQbfClause *clause;
}

/* include this code in the generated header file after the above union;
 * specifically, include here what is needed for the implementation */
%code requires
{
	#include <unordered_set>
	#include <algorithm>
}

/* include this code in the generated source code file; it is placed
 * before the generated parser source code */
%code
{
	// define that the our lexer function (called 'logiclex' by bison,
	// as per our api.prefix) is provided by the 'lex' function of the lexer
	#define logiclex lexer.lex

	// define auxilliary global variables in an anonymous namespace
	namespace logic
	{
		namespace
		{ 
			num_t clauseCount_ = 0;
			num_t quantifierNesting_ = -1;
			num_t variableCount_ = 0;
			std::unordered_set<num_t> unseenVariables_(0);
		}
	}
}

/* declarations of terminal symbols (tokens), and their types */
%token PROBLEM EXISTS FORALL NEG CNF DNF ZERO EOL
%token<string> COMMENT
%token<number> NUMBER

/* specify the types of non-terminal symbols, where needed */
%type<string> comment
%type<number> variable literal varcount clausecnt
%type<numberlist> qvars literals
%type<clause> clause

/* set the destructor code for certain types and/or symbols */
%destructor { delete $$; } <string>

/* set the starting symbol for the grammer */
%start qdimacs

%% /* GRAMMAR */

qdimacs	 :	comments cnf quantse clauses
		 	{
				if(clauseCount_ < 0)
				{
					error(yyla.location, "too many clauses");
					YYERROR;
				}
				if(clauseCount_ > 0)
				{
					error(yyla.location, "not enough clauses");
					YYERROR;
				}
				if(!unseenVariables_.empty())
				{
					std::string message("unused variables: ");
					for(num_t variable : unseenVariables_)
						message += "'" + std::to_string(variable) + "' ";
					error(yyla.location, message);
					YYERROR;
				}
			}
		 |  comments dnf quantsf clauses
		 	{
				if(clauseCount_ < 0)
				{
					error(yyla.location, "too many clauses");
					YYERROR;
				}
				if(clauseCount_ > 0)
				{
					error(yyla.location, "not enough clauses");
					YYERROR;
				}
				if(!unseenVariables_.empty())
				{
					std::string message("unused variables: ");
					for(num_t variable : unseenVariables_)
						message += "'" + std::to_string(variable) + "' ";
					error(yyla.location, message);
					YYERROR;
				}
			}
		 ;

comments :  comment comments
		 |
		 ;

comment  :  COMMENT EOL
		 ;

cnf      :	PROBLEM CNF varcount clausecnt EOL
		    {
				builder.setCnf();
				builder.setVariableCount($3);

				variableCount_ = $3;
				clauseCount_ = $4;
				unseenVariables_.reserve(variableCount_);

				for(num_t var = 1; var <= variableCount_; ++var)
					unseenVariables_.insert(var);
			}
		 ;

dnf		 :	PROBLEM DNF varcount clausecnt EOL
		    {
				builder.setDnf();
				builder.setVariableCount($3);

				variableCount_ = $3;
				clauseCount_ = $4;
				unseenVariables_.reserve(variableCount_);

				for(num_t var = 1; var <= variableCount_; ++var)
					unseenVariables_.insert(var);
			}
	     ;

varcount :  NUMBER
		 	{
				if($1 <= 0)
				{
					error(yyla.location, "variable count too small");
					YYERROR;
				}
				$$ = $1;
			}
		 ;

clausecnt:  NUMBER
		 	{
				if($1 <= 0)
				{
					error(yyla.location, "clause count too small");
					YYERROR;
				}
				$$ = $1;
			}
		 ;

quantsf  :	quantse forall
		 |
		 ;

quantse  :	quantsf exists
		 |
		 ;

exists   :  EXISTS qvars ZERO EOL
		 	{
				++quantifierNesting_;
			
				for(auto variable : *$2)
					builder.setQuantifierLevel(variable, quantifierNesting_);
				delete $2;
			}
		 ;

forall   :  FORALL qvars ZERO EOL
		 	{
				++quantifierNesting_;
			
				for(auto variable : *$2)
					builder.setQuantifierLevel(variable, quantifierNesting_);
				delete $2;
			}
		 ;

qvars    :  qvars variable
		    {
				$$ = $1;
				$$->push_back($2);
			}
		 |  variable
		 	{
				$$ = new num_vector({ $1 });
			}
		 ;

variable :  NUMBER
		 	{
				if($1 > variableCount_)
				{
					error(yyla.location, "variable out of bounds");
					YYERROR;
				}
				$$ = $1;
			}
		 ;

clauses  :  clause clauses	{ --clauseCount_; }
		 |  clause 			{ --clauseCount_; }
		 ;

clause   :  literals ZERO EOL
		 	{
				$$ = &builder.addClause();

				for(auto literal : *$1)
					if(literal < 0)
						$$->addVariable(-literal, true);
					else
						$$->addVariable(literal);

				delete $1;
			}
		 ;

literals :  literal literals
		 	{
				$$ = $2;
				$$->push_back($1);
			}
		 |  literal
		    {
				$$ = new num_vector({ $1 });
			}
		 ;

literal  :  variable
		 	{
				unseenVariables_.erase($1);
				$$ = $1;
			}
		 |  NEG variable
		 	{
				unseenVariables_.erase($2);
				$$ = -$2;
			}
		 ;

%% /* CODE TO PLACE AT THE END OF THE GENERATED SOURCE CODE FILE */

namespace logic
{
	void QDIMACSBisonParser::error(
		const QDIMACSBisonParser::location_type &l,
		const std::string &m)
	{
		std::cerr << l << ": " << m << "; last parsed token: '"
			<< lexer.YYText() << "'" << std::endl;
	}
}
