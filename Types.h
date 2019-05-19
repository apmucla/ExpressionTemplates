#ifndef TYPES_HAS_BEEN_INCLUDED
#define TYPES_HAS_BEEN_INCLUDED

//------------------------------------------------------------------------------

/// @brief Provides an alias for the resulting type when adding an instance of
/// type T1 to an instance of type T2.
template <typename T1, typename T2>
struct PromoteSum { using type = decltype(T1{} + T2{}); };

/// @brief Provides an alias for the resulting type when subtracting an instance
/// of type T2 from an instance of type T1.
template <typename T1, typename T2>
struct PromoteDiff { using type = decltype(T1{} - T2{}); };

//------------------------------------------------------------------------------

/// C++14-inspired alias for PromoteSum::type, simplying client syntax.
template <typename T1, typename T2>
using PromoteSum_t = typename PromoteSum<T1, T2>::type;

/// C++14-inspired alias for PromoteDiff::type, simplying client syntax.
template <typename T1, typename T2>
using PromoteDiff_t = typename PromoteDiff<T1, T2>::type;

//------------------------------------------------------------------------------

#endif // TYPES_HAS_BEEN_INCLUDED
