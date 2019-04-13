//
// Created by jonb on 3/24/19.
//

#pragma once

#include <cstddef>
#include <memory.h>
#include <string>
#include <algorithm>

// Compiler defines
#if defined(__clang__)
#define HSM_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define HSM_COMPILER_GCC
#elif defined(_MSC_VER)
#define HSM_COMPILER_MSC
#endif

using namespace std;

// Copied from https://blog.molecular-matters.com/2015/12/11/getting-the-type-of-a-template-argument-as-string-without-rtti/
// and https://github.com/amaiorano/hsm/commit/f5c3b9a5c23fd07a2092336b1bc6d6f82526a022#diff-02ce6e99bf2b3da47e4d0d45b5436caaR170
namespace internal
{



    static const unsigned int FRONT_SIZE = sizeof("internal::GetTypeNameHelper<") - 1u;
    static const unsigned int BACK_SIZE = sizeof(">::GetTypeName") - 1u;

    template <typename T>
    struct GetTypeNameHelper
    {


        static const char* GetTypeName(void)
        {
            #if defined(HSM_COMPILER_MSC)
                // e.g.: hsm::internal::GetTypeNameHelper<struct HeroStates::Alive>::Apply
                #define FUNCTION_MACRO __FUNCTION__
                #define PREFIX "hsm::internal::GetTypeNameHelper<"
                #define SUFFIX_1 ">::Apply"
                #define SUFFIX_2 ""
                #define NUM_TYPE_REPEATS 1
            #elif defined(HSM_COMPILER_CLANG)
                // e.g.: static const char *hsm::internal::GetTypeNameHelper<HeroStates::Alive>::Apply() [T = HeroStates::Alive]
                #define FUNCTION_MACRO __PRETTY_FUNCTION__
                #define PREFIX "static const char *hsm::internal::GetTypeNameHelper<"
                #define SUFFIX_1 ">::Apply() [T = "
                #define SUFFIX_2 "]"
                #define NUM_TYPE_REPEATS 2
            #elif defined(HSM_COMPILER_GCC)
                // e.g.: static const char* hsm::internal::GetTypeNameHelper<T>::Apply() [with T = HeroStates::Alive]
                #define FUNCTION_MACRO __PRETTY_FUNCTION__
                #define PREFIX "static const char* hsm::internal::GetTypeNameHelper<T>::Apply() [with T = "
                #define SUFFIX_1 "]"
                #define SUFFIX_2 ""
                #define NUM_TYPE_REPEATS 1
            #else
                #error "Implement for current compiler"
            #endif

            const size_t funcNameLength = sizeof(FUNCTION_MACRO) - 1u;
            const size_t prefixLength = sizeof(PREFIX) - 1u;
            const size_t suffixLength = sizeof(SUFFIX_1) - 1u + sizeof(SUFFIX_2) - 1u;
            //static_assert((funcNameLength - (prefixLength + suffixLength)) % NUM_TYPE_REPEATS == 0, "NUM_TYPE_REPEATS is probably incorrect");
            const size_t typeLength = (funcNameLength - (prefixLength + suffixLength)) / NUM_TYPE_REPEATS;

            static char typeName[typeLength + 1u];
            memcpy(&typeName[0], FUNCTION_MACRO + prefixLength, typeLength);
            return typeName;

            #undef FUNCTION_MACRO
            #undef PREFIX
            #undef SUFFIX_1
            #undef SUFFIX_2
            #undef NUM_TYPE_REPEATS
        }
    };
}
template <typename T>
string GetTypeName(void)
{
    string result = internal::GetTypeNameHelper<T>::GetTypeName();
    result.erase(std::find(result.begin(), result.end(), ' '));
    return result;
}
