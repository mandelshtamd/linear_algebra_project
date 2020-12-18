#ifndef LINEAR_ALGEBRA_PROJECT_ARITHMETIC_RESTRICTION_HPP
#define LINEAR_ALGEBRA_PROJECT_ARITHMETIC_RESTRICTION_HPP

#include <type_traits>

namespace LinearAlgebra {

    template<typename T,
            std::enable_if_t<std::is_arithmetic<T>::value, bool> = true>
    class ArithmeticRestriction {
    };

}

#endif //LINEAR_ALGEBRA_PROJECT_ARITHMETIC_RESTRICTION_HPP
