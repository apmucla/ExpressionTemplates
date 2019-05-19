#ifndef VECTOR_HAS_BEEN_INCLUDED
#define VECTOR_HAS_BEEN_INCLUDED

#include "VectorExpression.h"

#include <vector>

#ifdef MY_DEBUG
#include <cassert>
#endif

//------------------------------------------------------------------------------

template <typename T>
class Vector : public VectorExpression<Vector<T>, T>
{
public:
    using MyBaseType = VectorExpression<Vector<T>, T>;

    // Analogous alias to that of the standard library containers.
    using value_type = T;

    /// Construct an empty vector of size n.
    explicit Vector(size_t n) : mElems(n)
    {
        // empty
    }

    /// @brief Construct a Vector from any VectorExpression.
    /// @note This acts as a copy constructor for this class.
    template <typename D, typename U>
    Vector(const VectorExpression<D, U>& exp) : mElems(exp.size())
    {
        for (size_t i = 0, iMax = exp.size(); i < iMax; ++i) {
            mElems[i] = static_cast<T>(exp[i]);
        }
    }

    template <typename D, typename U>
    Vector& operator+=(const VectorExpression<D, U>& exp)
    {
#ifdef MY_DEBUG
        assert(mElems.size() == exp.size());
#endif
        for (size_t i = 0, iMax = mElems.size(); i < iMax; ++i) {
            mElems[i] += static_cast<T>(exp[i]);
        }
        return *this;
    }

    template <typename D, typename U>
    Vector& operator-=(const VectorExpression<D, U>& exp)
    {
#ifdef MY_DEBUG
        assert(mElems.size() == exp.size());
#endif
        for (size_t i = 0, iMax = mElems.size(); i < iMax; ++i) {
            mElems[i] -= static_cast<T>(exp[i]);
        }
        return *this;
    }

    const T& operator[](size_t i) const { return mElems[i]; }
    T& operator[](size_t i) { return mElems[i]; }

    size_t size() const { return mElems.size(); }

private:
    std::vector<T> mElems;
};

//------------------------------------------------------------------------------

#endif // VECTOR_HAS_BEEN_INCLUDED
