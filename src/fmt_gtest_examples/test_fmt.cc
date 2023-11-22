
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>
#include <string>
#include <fmt/color.h>

using namespace fmt::literals;
int main() {
	fmt::print("Hello, world!\n");
	std::vector<int> v = {1, 2, 3};
	fmt::print("{}\n", v);
	// std::string s = fmt::format("{:d}", "I am not a number");
	fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
	    "Hello, {}!\n", "world");
	fmt::print(fg(fmt::color::floral_white) | bg(fmt::color::slate_gray) |
        fmt::emphasis::underline, "Olá, {}!\n", "Mundo");
  	fmt::print(fg(fmt::color::steel_blue) | fmt::emphasis::italic,
        "你好{}！\n", "世界");

	auto out = fmt::memory_buffer();
	fmt::format_to(std::back_inserter(out),
        "For a moment, {} happened.", "nothing");
	auto data = out.data(); // pointer to the formatted data
	auto size = out.size(); // size of the formatted data}
	fmt::print("{1} {0}\n", out.data(), "you");
	fmt::print("Hello, {name}! The answer is {number}. Goodbye, {name}.\n",
		fmt::arg("name", "World"), fmt::arg("number", 42));
	fmt::print("Hello, {name}! The answer is {number}. Goodbye, {name}.\n",
           "name"_a="World", "number"_a=42);
	fmt::print("{}\n", std::numeric_limits<double>::infinity());
}