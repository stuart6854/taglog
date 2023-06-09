#define TAGLOG_HEADER_ONLY
#include <taglog/taglog.hpp>

#include <numbers>

int main()
{
    taglog::init();

    taglog::define_tag("trace", taglog::Color::eBrightBlack, taglog::Color::eNone);
    taglog::define_tag("debug", taglog::Color::eWhite, taglog::Color::eNone);
    taglog::define_tag("info", taglog::Color::eNone, taglog::Color::eNone);
    taglog::define_tag("warning", taglog::Color::eBrightYellow, taglog::Color::eNone);
    taglog::define_tag("error", taglog::Color::eBrightRed, taglog::Color::eNone);
    taglog::define_tag("system", taglog::Color::eGreen, taglog::Color::eNone);

    taglog::log("{} {}!", "Hello", "World");
    taglog::log("Hello, my name is {}. I am {} years old!", "Stuart", 25);
    taglog::log("{:.3f}, {:x}, {:b}", std::numbers::pi, 12345, 12345);

    taglog::tagged_log("info,system,rendering", "Some object has be created. id={}", 123453454);

    taglog::terminate();

    return 0;
}
