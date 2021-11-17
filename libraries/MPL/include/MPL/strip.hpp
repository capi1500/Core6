#pragma once

namespace helper{
	template<class T>
	struct strip{
		using type = T;
	};
	
	template<class T, template<class> class X>
	struct strip<X<T>>{
		using type = T;
	};
}

template<class T>
using strip = helper::strip<T>::type;