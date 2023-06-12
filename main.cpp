#define TAGLOG_HEADER_ONLY
#include <taglog/taglog.hpp>

#include <numbers>

int main()
{
    taglog::init();

#ifdef _DEBUG
    taglog::begin_tag("debug_build");
#else
    taglog::begin_tag("release_build");
#endif

    taglog::define_tag("trace", taglog::Color::eBrightBlack, taglog::Color::eNone);
    taglog::define_tag("debug", taglog::Color::eWhite, taglog::Color::eNone);
    taglog::define_tag("info", taglog::Color::eNone, taglog::Color::eNone);
    taglog::define_tag("warning", taglog::Color::eBrightYellow, taglog::Color::eNone);
    taglog::define_tag("error", taglog::Color::eBrightRed, taglog::Color::eNone);
    taglog::define_tag("system", taglog::Color::eGreen, taglog::Color::eNone);

    {
        taglog::ScopedTag scopeTag1("scope_1");
        taglog::log("{} {}!", "Hello", "World");
        taglog::log("Hello, my name is {}. I am {} years old!", "Stuart", 25);
        taglog::log("{:.3f}, {:x}, {:b}", std::numbers::pi, 12345, 12345);
        {
            taglog::ScopedTag scopeTag2("scope_2");
            taglog::tagged_log("info,system,rendering", "Some object has be created. id={}", 123453454);
        }
    }

#ifdef _DEBUG
    taglog::end_tag("debug_build");
#else
    taglog::end_tag("release_build");
#endif

    taglog::terminate();

    return 0;
}
