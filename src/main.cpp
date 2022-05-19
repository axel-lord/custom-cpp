#include <span>

#include <util/print.hpp>

int main(int argc, char ** argv)
{
	for(auto&& arg : std::span(argv, argc))
		util::print(arg);

	util::print("a", 2, 4, "hello", 'c', 3.6);
}
