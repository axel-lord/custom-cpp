#pragma once

#include <iostream>
#include <ostream>
#include <utility>
#include <concepts>

namespace util
{

template<typename T>
concept printable = requires (T t)
{
	std::declval<std::ostream>() << t;
};

auto print(std::ostream& stream, printable auto const& value)
{
	stream << value;
	stream << '\n';
}

auto print(printable auto const& value)
{
	print(std::cout, value);
}

auto print(std::ostream& stream, printable auto const& value, printable auto const&... values)
{
	stream << value;
	((stream << ", " << values), ...);
	stream << '\n';
}

auto print(printable auto const& value, printable auto const&... values)
{
	print(std::cout, value, values...);
}

}
