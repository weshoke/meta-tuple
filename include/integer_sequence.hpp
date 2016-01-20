#ifndef INTEGER_SEQUENCE_HPP
#define INTEGER_SEQUENCE_HPP


// Based on code from Atria
// sequence of integers of type T
// T: integer type
// ...Ints: the Parameter Pack of integers that is the actual sequence
// http://en.cppreference.com/w/cpp/language/parameter_pack
template <typename T, T ...Ints>
struct integer_sequence {
	// type of integer
	using value_type = T;
	
	// The size of the sequence
	static constexpr std::size_t size() {
		return sizeof...(Ints);
	}
};

namespace detail {

	// Declare the recursive template structure
	template <typename T, T Curr, T Limit, typename Accum>
	struct make_integer_sequence;

	// Sequence generator
	// T: integer type
	// Limit: sequence limit
	// ...Ns: the sequence
	template <typename T, T Limit, T ...Ns>
	// Partial template specialization of above declaration ( http://en.cppreference.com/w/cpp/language/partial_specialization )
	// where the current point in sequence generation is Limit
	// This is the terminating node of template recursion
	// The partial specialization encodes a class of patterns for generating
	// instances of the above declaration
	struct make_integer_sequence<T, Limit, Limit, integer_sequence<T, Ns...> > {
		// The sequence represented by this instance of the recursion
		// http://en.cppreference.com/w/cpp/language/type_alias
		// The type is exposed to the initiator of the recursive process through inheritance
		using type = integer_sequence<T, Ns...>;
	};

	// Recursive sequence generation template
	// Once Curr == Limit, the sequnece will terminate
	// This is the first template instantiated since it's a partial specialization
	// on Accum = integer_sequence<...>
	template <typename T, T Curr, T Limit, T ...Ns>
	struct make_integer_sequence<T, Curr, Limit, integer_sequence<T, Ns...> >
		: make_integer_sequence<
			T, (Curr + 1), Limit, integer_sequence<T, Ns..., Curr>
		>
	{};

}


// Template Aliases
// https://isocpp.org/wiki/faq/cpp11-language-templates#template-alias
template<class T, T N>
using make_integer_sequence = typename detail::make_integer_sequence<
  T, 0, N, integer_sequence<T> >::type;


/*
	Calling make_integer_sequence2<int, 3>() will derive the type from the following constructions:
		+ make_integer_sequence<int, 0, 3, integer_sequence<int> >::make_integer_sequence() [T = int, Curr = 0, Limit = 3, Accum = integer_sequence<int>]
		+ make_integer_sequence<int, 1, 3, integer_sequence<int, 0> >::make_integer_sequence() [T = int, Curr = 1, Limit = 3, Accum = integer_sequence<int, 0>]
		+ make_integer_sequence<int, 2, 3, integer_sequence<int, 0, 1> >::make_integer_sequence() [T = int, Curr = 2, Limit = 3, Accum = integer_sequence<int, 0, 1>]
		+ make_integer_sequence<int, 3, 3, integer_sequence<int, 0, 1, 2> >::make_integer_sequence() [T = int, Curr = 3, Limit = 3, Accum = integer_sequence<int, 0, 1, 2>]
*/

#endif
