#include <cstdlib>
#include <tuple>
#include <algorithm>


template <std::size_t string_length>
struct FixedString {
  constexpr FixedString(const char(&input_str)[string_length + 1]) {
    std::copy_n(input_str, string_length + 1, string);
  }

  auto operator<=>(const FixedString&) const -> bool = default;

  char string[string_length + 1];
};


template <std::size_t string_length>
FixedString(const char(&str)[string_length]) -> FixedString<string_length - 1>;


template <FixedString FieldName, typename T>
struct FieldEntry {
  using element_type = T;

  constexpr static auto field_name() { return FieldName; }
  T value;
};


template <typename ... FieldEntries>
struct Fields: FieldEntries ... {};


template <FixedString FieldName, typename T>
decltype(auto) get_impl(FieldEntry<FieldName, T>& m) {
  return (m.value);
}


template <FixedString FieldName, typename FieldEntry>
decltype(auto) get(FieldEntry&& e) {
  return get_impl<FieldName>(std::forward<FieldEntry>(e));
}


template <FixedString FieldName, typename T>
struct FieldNameValuePair {
  T value;
};


template <FixedString FieldName>
struct FieldArgType {
  template <typename T>
  constexpr auto operator=(T t) const {
    return FieldNameValuePair<FieldName, T>{std::move(t)};
  }
};


template <FixedString FieldName>
inline constexpr auto FieldArg = FieldArgType<FieldName>{};

// template <typename ... FieldMembers>
// struct MetaFields: MetaFieldsImpl<FieldMembers...> {
//   using super = MetaFieldsImpl<FieldMembers...>;
//
//   template <typename ... FieldNameValuePair>
//   constexpr MetaFields(FieldNameValuePair... names_and_values)
//   : super(params(std::move(names_and_values)...)) {}
// };
//
//
