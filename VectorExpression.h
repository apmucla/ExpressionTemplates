#ifndef VECTOR_EXPRESSION_HAS_BEEN_INCLUDED
#define VECTOR_EXPRESSION_HAS_BEEN_INCLUDED

#include "Types.h"

#include <iostream>
#ifdef MY_DEBUG
#include <cassert>
#endif

//------------------------------------------------------------------------------

template <typename D, typename T>
class VectorExpression
{
public:
    T operator[](size_t i) const
    {
        return static_cast<const D&>(*this)[i];
    }

    size_t size() const
    {
        return static_cast<const D&>(*this).size();
    }

private:
    VectorExpression() = default;

    friend D;
};

template <typename D, typename T>
std::ostream& operator<<(std::ostream& os, const VectorExpression<D, T>& exp)
{
    os << "{";
    for (size_t i = 0, iMax = exp.size() - 1; i < iMax; ++i) {
        os << exp[i] << ", ";
    }
    os << exp[exp.size() - 1] << "}";
    return os;
}

//------------------------------------------------------------------------------

template <typename V1, typename V2>
class VectorSum : public VectorExpression<VectorSum<V1, V2>,
                                          PromoteSum_t<typename V1::value_type,
                                                       typename V2::value_type>>
{
public:
    // Tricky! This alias must be provided in the case where, e.g. VectorSum
    // is templated on VectorSum.
    using value_type = PromoteSum_t<typename V1::value_type,
                                    typename V2::value_type>;

    VectorSum(const V1& v1, const V2& v2) : mV1(v1), mV2(v2)
    {
#ifdef MY_DEBUG
        assert(mV1.size() == mV2.size());
#endif
    }

    value_type operator[](size_t i) const { return mV1[i] + mV2[i]; }
    size_t size() const { return mV1.size(); }

private:
    const V1& mV1;
    const V2& mV2;
};

template <typename V1, typename V2>
class VectorDiff : public VectorExpression<VectorDiff<V1, V2>,
                                           PromoteDiff_t<typename V1::value_type,
                                                         typename V2::value_type>>
{
public:
    // Tricky! This must be aliased as value_type, and must be included for
    // cases where a VectorDiff is templated on a VectorDiff.
    using value_type = PromoteDiff_t<typename V1::value_type,
                                     typename V2::value_type>;

    VectorDiff(const V1& v1, const V2& v2) : mV1(v1), mV2(v2)
    {
#ifdef MY_DEBUG
        assert(mV1.size() == mV2.size());
#endif
    }

    value_type operator[](size_t i) const { return mV1[i] - mV2[i]; }
    size_t size() const { return mV1.size(); }

private:
    const V1& mV1;
    const V2& mV2;
};

//------------------------------------------------------------------------------

template <typename V1, typename V2>
VectorSum<V1, V2> operator+(const V1& v1, const V2& v2) { return {v1, v2}; }

template <typename V1, typename V2>
VectorDiff<V1, V2> operator-(const V1& v1, const V2& v2) { return {v1, v2}; }

//------------------------------------------------------------------------------

#endif // VECTOR_EXPRESSION_HAS_BEEN_INCLUDED

