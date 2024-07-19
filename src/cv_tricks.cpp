#pragma once

#include <iostream>
#include <vector>
#include <string>

#define CV_TRICKS_EXPORT

void cv_tricks()
{
#ifdef NDEBUG
    std::cout << "cv-tricks/0.1: Hello World Release!\n";
#else
    std::cout << "cv-tricks/0.1: Hello World Debug!\n";
#endif

    // ARCHITECTURES
#ifdef _M_X64
    std::cout << "  cv-tricks/0.1: _M_X64 defined\n";
#endif

#ifdef _M_IX86
    std::cout << "  cv-tricks/0.1: _M_IX86 defined\n";
#endif

#ifdef _M_ARM64
    std::cout << "  cv-tricks/0.1: _M_ARM64 defined\n";
#endif

#if __i386__
    std::cout << "  cv-tricks/0.1: __i386__ defined\n";
#endif

#if __x86_64__
    std::cout << "  cv-tricks/0.1: __x86_64__ defined\n";
#endif

#if __aarch64__
    std::cout << "  cv-tricks/0.1: __aarch64__ defined\n";
#endif

    // Libstdc++
#if defined _GLIBCXX_USE_CXX11_ABI
    std::cout << "  cv-tricks/0.1: _GLIBCXX_USE_CXX11_ABI " << _GLIBCXX_USE_CXX11_ABI << "\n";
#endif

    // MSVC runtime
#if defined(_DEBUG)
#if defined(_MT) && defined(_DLL)
        std::cout << "  cv-tricks/0.1: MSVC runtime: MultiThreadedDebugDLL\n";
#elif defined(_MT)
        std::cout << "  cv-tricks/0.1: MSVC runtime: MultiThreadedDebug\n";
#endif
#else
#if defined(_MT) && defined(_DLL)
        std::cout << "  cv-tricks/0.1: MSVC runtime: MultiThreadedDLL\n";
#elif defined(_MT)
        std::cout << "  cv-tricks/0.1: MSVC runtime: MultiThreaded\n";
#endif
#endif

    // COMPILER VERSIONS
#if _MSC_VER
    std::cout << "  cv-tricks/0.1: _MSC_VER" << _MSC_VER<< "\n";
#endif

#if _MSVC_LANG
    std::cout << "  cv-tricks/0.1: _MSVC_LANG" << _MSVC_LANG<< "\n";
#endif

#if __cplusplus
    std::cout << "  cv-tricks/0.1: __cplusplus" << __cplusplus << "\n";
#endif

#if __INTEL_COMPILER
    std::cout << "  cv-tricks/0.1: __INTEL_COMPILER" << __INTEL_COMPILER<< "\n";
#endif

#if __GNUC__
    std::cout << "  cv-tricks/0.1: __GNUC__" << __GNUC__ << "\n";
#endif

#if __GNUC_MINOR__
    std::cout << "  cv-tricks/0.1: __GNUC_MINOR__" << __GNUC_MINOR__ << "\n";
#endif

#if __clang_major__
    std::cout << "  cv-tricks/0.1: __clang_major__" << __clang_major__<< "\n";
#endif

#if __clang_minor__
    std::cout << "  cv-tricks/0.1: __clang_minor__" << __clang_minor__<< "\n";
#endif

#if __apple_build_version__
    std::cout << "  cv-tricks/0.1: __apple_build_version__" << __apple_build_version__<< "\n";
#endif

    // SUBSYSTEMS

#if __MSYS__
    std::cout << "  cv-tricks/0.1: __MSYS__" << __MSYS__<< "\n";
#endif

#if __MINGW32__
    std::cout << "  cv-tricks/0.1: __MINGW32__" << __MINGW32__<< "\n";
#endif

#if __MINGW64__
    std::cout << "  cv-tricks/0.1: __MINGW64__" << __MINGW64__<< "\n";
#endif

#if __CYGWIN__
    std::cout << "  cv-tricks/0.1: __CYGWIN__" << __CYGWIN__<< "\n";
#endif
}

void cv_tricks_print_vector(const std::vector<std::string>& strings)
{
    for (std::vector<std::string>::const_iterator it = strings.begin(); it != strings.end(); ++it)
    {
        std::cout << "cv_tricks/0.1 " << *it << std::endl;
    }
}

int main(int argc, char* argv[]){
    cv_tricks_print_vector({"val1", "val2"});
}
