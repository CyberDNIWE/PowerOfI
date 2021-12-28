#pragma once

// Usage: 
//	float myval = power_of_I::powOfI<3>(2.0f);
//	>> myval is 2.0f * 2.0f * 2.0f = 2.0f ^ 3 = 8.0f

namespace power_of_I
{
	namespace _inner
	{
		// Function-like power of INT calculations, that when unrolled looks like:
		// x ^ 3 = x * x * x; and has the same performance

		template<unsigned int N, typename VT>
		struct _PowOfI
		{
			constexpr VT operator()(VT x) const noexcept
			{
				return x * power_of_I::_inner::_PowOfI<N - 1, VT>()(x);
			}
		};

		template<typename VT>
		struct _PowOfI<1, VT>
		{
			constexpr VT operator()(VT x) const noexcept
			{
				return x;
			}
		};

		template<typename VT>
		struct _PowOfI<0, VT>
		{
			constexpr VT operator()(VT x) const noexcept
			{
				return 1;
			}
		};
	};

	template<unsigned int N, typename V>
	constexpr V powOfI(V value) noexcept
	{
		return power_of_I::_inner::_PowOfI<N, V>()(value);
	}
	
	// For c++17 and up use this instead
	// Holy shit that's way easier now and is possibly more efficent (~19 lines of -o0 assembly less)
	/*
	template<unsigned int N, typename VT>
	constexpr VT powOfI(VT x) noexcept
	{
    		if constexpr(N == 0)
        		return 1;
    		else if constexpr(N == 1)
        		return x;
    		else
        		return x * powOfI<N-1>(x);
	}
	//*/
};
