#ifndef MPL_BITSETSIZE_HPP
#define MPL_BITSETSIZE_HPP

#include <bitset>

namespace MPL{
	template<typename T> using BitsetSize = std::integral_constant<std::size_t, T{}.size()>;
}
#endif //MPL_BITSETSIZE_HPP
