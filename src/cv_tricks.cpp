#include <spdlog/spdlog.h>

#include <vector>
#include <string>


void cv_tricks_print_vector(const std::vector<std::string>& strings)
{
    for (const auto & string : strings)
    {
        spdlog::info("cv_tricks/0.1 {}", string);
    }
}

int main(int argc, char* argv[])
{
    cv_tricks_print_vector({"val1", "val2"});
}
