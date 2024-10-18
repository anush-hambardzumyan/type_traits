#include <iostream>
#include <type_traits>  // for standard type comparisons
#include <cstdint>      // for fixed-width integer types
#include "TypeTraits.tpp" // include the header where your type traits are defined

int main() {
    // Test integral_constant and bool_constant
    TypeTraits::integral_constant<int, 42> intConstant;
    std::cout << "integral_constant<int, 42>::value = " << intConstant() << "\n";

    TypeTraits::true_type trueType;
    TypeTraits::false_type falseType;
    std::cout << "true_type value = " << trueType() << "\n";
    std::cout << "false_type value = " << falseType() << "\n";

    // Test is_same
    std::cout << "is_same<int, int> = " << TypeTraits::is_same_v<int, int> << "\n";
    std::cout << "is_same<int, float> = " << TypeTraits::is_same_v<int, float> << "\n";

    // Test remove_cv
    std::cout << "remove_cv<const int>::type is int = " << TypeTraits::is_same_v<TypeTraits::remove_cv_t<const int>, int> << "\n";

    // Test remove_extent
    std::cout << "remove_extent<int[5]>::type is int = " << TypeTraits::is_same_v<TypeTraits::remove_extent_t<int[5]>, int> << "\n";

    // Test is_integral
    std::cout << "is_integral<int> = " << TypeTraits::is_integral_v<int> << "\n";
    std::cout << "is_integral<float> = " << TypeTraits::is_integral_v<float> << "\n";

    // Test is_floating_point
    std::cout << "is_floating_point<double> = " << TypeTraits::is_floating_point_v<double> << "\n";
    std::cout << "is_floating_point<int> = " << TypeTraits::is_floating_point_v<int> << "\n";

    // Test is_pointer
    std::cout << "is_pointer<int*> = " << TypeTraits::is_pointer_v<int*> << "\n";
    std::cout << "is_pointer<int> = " << TypeTraits::is_pointer_v<int> << "\n";

    // Test remove_pointer
    std::cout << "remove_pointer<int*>::type is int = " << TypeTraits::is_same_v<TypeTraits::remove_pointer_t<int*>, int> << "\n";

    // Test enable_if
    TypeTraits::enable_if_t<TypeTraits::is_integral_v<int>, int> integralVariable = 10;
    std::cout << "integralVariable = " << integralVariable << "\n";

    // Test conditional
    using ConditionalType = TypeTraits::conditional_t<true, int, double>;
    std::cout << "conditional<true, int, double> is int = " << TypeTraits::is_same_v<ConditionalType, int> << "\n";

    // Test underlying_type for an enum
    enum class Color : std::uint8_t { Red, Green, Blue };
    std::cout << "underlying_type<Color>::type is uint8_t = " 
              << TypeTraits::is_same_v<TypeTraits::underlying_type_t<Color>, std::uint8_t> << "\n";

    return 0;
}
