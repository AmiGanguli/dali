#include <iostream>
#include <list>
#include <string>

namespace Dali {

class Block {
};

class List : public Block {
};

class With : public Block {
};

class Each : public Block {
};

class If : public Block {
};

class Unless : public Block {
};

// The hand-crafted parser is used here for size.  Our requirements are
// quite basic and, for example, the Boost::Spirit lexer alone as almost
// 3MB.  While we're not generally memory constrained, it seemed wrong
// to use that much when the hand-crafted parser is actually pretty simple.
//
	
enum State
{
	START	 		= 0,
	BRACE_ONE	 	= 1,
	BRACE_TWO	 	= 2,
	BRACE_THREE	 	= 3,
	CLOSE_ONE	 	= 4,
	CLOSE_TWO	 	= 5,
	CLOSE_THREE	 	= 6,
	HASH		 	= 7,
	HASH_KEYWORD	 	= 8,
	HASH_KEYWORD_SPACE 	= 9,
	SLASH		 	= 10,
	SLASH_KEYWORD	 	= 11,
	SLASH_KEYWORD_SPACE 	= 12,
	VARIABLE		= 13,
	VARIABLE_DOT		= 14,
	VARIABLE_SPACE		= 15,
	COMMENT			= 16,
	ERR			= 17
};

enum CharClasses
{
	CHAR_OTHER		= 0,
	CHAR_OPEN		= 1,
	CHAR_CLOSE		= 2,
	CHAR_HASH		= 3,
	CHAR_SLASH		= 4,
	CHAR_SPACE		= 5,
	CHAR_DOT		= 6,
	CHAR_BANG		= 7
}

const static transition_table[ERR][CHAR_SPACE] = {
/*					CHAR_OTHER	CHAR_OPEN	CHAR_CLOSE	CHAR_HASH	CHAR_SLASH	CHAR_SPACE 		CHAR_DOT 	CHAR_BANG */
/* START 		*/	{ 	START,		BRACE_ONE,	START,		START,		START,		START,			START,		START		},
/* BRACE_ONE		*/	{	START,		BRACE_TWO,	START,		START,		START,		START,			START,		START		},
/* BRACE_TWO		*/	{	VARIABLE,	BRACE_THREE,	ERR,		HASH,		SLASH,		BRACE_TWO,		ERR,		COMMENT		},
/* BRACE_THREE	 	*/	{	VARIABLE,	ERR,		ERR,		ERR,		ERR,		BRACE_THREE,		ERR,		ERR		},
/* CLOSE_ONE		*/	{	ERR,		ERR,		CLOSE_TWO,	ERR,		ERR,		ERR,			ERR,		ERR		},
/* CLOSE_TWO		*/	{	START,		BRACE_ONE,	CLOSE_THREE,	START,		START,		START,			START,		START		},
/* CLOSE_THREE	 	*/	{	START,		BRACE_ONE,	START,		START,		START,		START,			START,		START		},
/* HASH		 	*/	{	HASH_KEYWORD,	ERR,		ERR,		ERR,		ERR,		HASH,			ERR,		ERR		},
/* HASH_KEYWORD	 	*/	{	HASH_KEYWORD,	ERR,		CLOSE_ONE,	ERR,		ERR,		HASH_KEYWORD_SPACE,	ERR,		ERR		},
/* HASH_KEYWORD_SPACE 	*/	{	VARIABLE,	ERR,		CLOSE_ONE,	ERR,		ERR,		HASH_KEYWORD_SPACE,	ERR,		ERR		},
/* SLASH		*/	{	SLASH_KEYWORD,	ERR,		ERR,		ERR,		ERR,		ERR,			ERR, 		ERR		},
/* SLASH_KEYWORD	*/	{	SLASH_KEYWORD,	ERR,		CLOSE_ONE,	ERR,		ERR,		SLASH_KEYWORD_SPACE,	ERR, 		ERR		},
/* SLASH_KEYWORD_SPACE	*/	{	ERR,		ERR,		CLOSE_ONE,	ERR,		ERR,		SLASH_KEYWORD_SPACE,	ERR, 		ERR		},
/* VARIABLE		*/	{	VARIABLE,	ERR,		CLOSE_ONE,	ERR,		ERR,		SLASH_KEYWORD_SPACE,	VARIABLE_DOT, 	ERR		},
/* VARIABLE_DOT		*/	{	VARIABLE,	ERR,		ERR,		ERR,		ERR,		VARIABLE_SPACE,		ERR, 		ERR		},
/* VARIABLE_SPACE	*/	{	ERR,		ERR,		CLOSE_ONE,	ERR,		ERR,		VARIABLE_SPACE,		ERR, 		ERR		},
/* COMMENT		*/	{	COMMENT,	COMMENT,	CLOSE_ONE,	COMMENT,	COMMENT,	COMMENT,		COMMENT,	COMMENT		},
/* ERR			*/	{	ERR,		ERR,		ERR,		ERR,		ERR,		ERR,			ERR, 		ERR		}
};

void
noop()
{
}

const static transition_actions[ERR][ERR] = {
/*					START		BRACE_ONE	BRACE_TWO	BRACE_THREE	CLOSE_ONE	CLOSE_TWO	CLOSE_THREE	HASH	HASH_KEYWORD	HASH_KEYWORD_SPACE */
/* START 		*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* BRACE_ONE		*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* BRACE_TWO		*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* BRACE_THREE	 	*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* CLOSE_ONE		*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* CLOSE_TWO		*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* CLOSE_THREE	 	*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* HASH		 	*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* HASH_KEYWORD	 	*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* HASH_KEYWORD_SPACE 	*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* SLASH		*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* SLASH_KEYWORD	*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* SLASH_KEYWORD_SPACE	*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* VARIABLE		*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* VARIABLE_DOT		*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* VARIABLE_SPACE	*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		},
/* ERR			*/	{	noop,		noop,		noop,		noop,		noop,		noop,		noop,		noop,	noop,		noop		}
};

class Template
{
protected:
	State state;
	std::list<Template*> children;
	char *text;

	
	
public:
	Template(std::string text_)
		: state(START)
	{
		int len = text_.length();
		const char *start = text_.c_str();
		const char *end = start + len;
		
		text = new char[len + 1];
		parse(start, end, text);
	}

	~Template()
	{
		delete [] text;
	}

	const char *
	parse(const char* start, const char* end, char *text)
	{
		
		while (start < end) {
		}
	}
};

class Constant : Template
{
};

class Simple : public Template
{
private:
	std::list<Frame> children;
public:
	
};

class Parser
{

};

} // Dali

int
main(int argc, char* argv[])
{
	std::size_t c = 0, v = 0, l = 0;

	std::string str ("Hello world {{this is a var}} {{{unesc}}} {{#list}}  {regular text} {{/list}}");

	Dali::count_tokens<lex::lexertl::lexer<> > count_functor;

	char const* first = str.c_str();
	char const* last = &first[str.size()];
	bool r = lex::tokenize(
		first,
		last,
		count_functor,
		boost::bind(
			Dali::counter(),
			_1,
			boost::ref(c),
			boost::ref(v),
			boost::ref(l)
		)
	);

	// print results
	if (r) {
		std::cout
			<< "const: " << c << ", vars: " << v
			<< ", list: " << l << "\n";
	} else {
		std::string rest(first, last);
		std::cout
			<< "Lexical analysis failed\n" << "stopped at: \""
			<< rest << "\"\n";
	}
	return 0;
}
