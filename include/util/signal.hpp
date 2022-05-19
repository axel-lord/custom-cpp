#pragma once

#include <iterator>
#include <utility>
#include <vector>
#include <functional>

namespace util {

namespace concepts
{
template<typename T, typename... Args>
concept signal = requires (T t)
{
	t.emit(std::declval<Args>()...);
};

template<typename T, typename... Args>
concept property = requires (T t)
{
	signal<decltype(t.changed), Args...>;
	t.set(std::declval<Args>()...);
};

template<typename T, typename... Args>
concept callable = requires (T t)
{
	t(std::declval<Args>()...);
};

template<typename T, typename... Args>
concept signal_receptor = signal<T, Args...> || property<T, Args...> || callable<T, Args...>;

}

template<typename... Args>
class Signal
{
private:
	std::vector<std::function<void(Args...)>> connected;
public:
	void emit(Args... args) const
	{
		for (auto&& f : connected)
			f(args...);
	}

	void connect(concepts::callable<Args...> auto const& callable)
	{
		connected.push_back(std::ref(callable));
	}

	void connect(concepts::signal<Args...> auto const& other)
	{
		auto activateSignal = [sig=std::ref(other)] (Args... args)
		{
			sig.get().emit(args...);
		};
		connect(activateSignal);
	}

	void connect(concepts::property<Args...> auto const& property)
	{
		auto setProperty = [prop=std::ref(property)] (Args... args)
		{
			prop.set(args...);
		};
		connect(setProperty);
	}

	void connect(void (*function)(Args...))
	{
		connected.push_back(function);
	}
};

template<typename... Args>
void connect(Signal<Args...>& from, concepts::signal_receptor<Args...> auto const& to)
{
	from.connect(to);
}

template<typename... Args>
void connect(Signal<Args...>& from, void (*to)(Args...))
{
	from.connect(to);
}

}

