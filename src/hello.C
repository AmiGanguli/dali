#include <iostream>

#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/bind.hpp>
#include <boost/ref.hpp>

namespace lex = boost::spirit::lex;

namespace Dali {

enum TokenID
{
	CONSTANT 		= 1,
	VARIABLE_ESCAPED 	= 2,
	VARIABLE_UNESCAPED 	= 3,
	LIST_START 		= 4,
	LIST_END 		= 5,
	WITH_START 		= 6,
	WITH_END 		= 7,
	EACH_START 		= 8,
	EACH_END 		= 9,
	IF_START 		= 10,
	IF_END 			= 11,
	UNLESS_START 		= 12,
	UNLESS_END		= 13
};

template <typename Lexer>
struct count_tokens : lex::lexer<Lexer>
{
	count_tokens()
	{
		this->self.add
			("[^{]+", 				CONSTANT)
			("\\{\\{[^{}#/][^}]*\\}\\}",		VARIABLE_ESCAPED)
			("\\{\\{\\{[^}]*\\}\\}\\}",		VARIABLE_UNESCAPED)
			("\\{\\{#list(\\s+[^}]*)?\\}\\}",	LIST_START)
			("\\{\\{\\/list\\s*\\}\\}",		LIST_END)
			("\\{\\{#with(\\s+[^}]*)?\\}\\}",	WITH_START)
			("\\{\\{\\/with\\s*\\}\\}",		WITH_END)
			("\\{\\{#each(\\s+[^}]*)?\\}\\}",	EACH_START)
			("\\{\\{\\/each\\s*\\}\\}",		EACH_END)
			("\\{\\{#if(\\s+[^}]*)?\\}\\}",		IF_START)
			("\\{\\{\\/if\\s*\\}\\}",		IF_END)
			("\\{\\{#unless(\\s+[^}]*)?\\}\\}",	UNLESS_START)
			("\\{\\{\\/unless\\s*\\}\\}",		UNLESS_END)
			(".",					CONSTANT)
			;
	}
};

struct counter
{
	typedef bool result_type;
	
	template <typename Token>
	bool operator() (Token const& t, std::size_t& c, std::size_t& v, std::size_t& l) const
	{
		std::cout << "token " << t.value() << " " << t.id() << std::endl;
		switch (t.id()) {
		case CONSTANT:
			++c;
			break;
		case VARIABLE_ESCAPED:
		case VARIABLE_UNESCAPED:
			++v;
			break;
		case LIST_END:
		case LIST_START:
			++l;
			break;
		}
		return true;
	}
};


}

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
