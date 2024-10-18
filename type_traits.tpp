#include <iostream>

namespace TypeTraits {

// integral_constant    
template <typename T, T val>
struct integral_constant
{
    static constexpr T value = val;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

// bool_constant, true_type, false_type
template <bool val>
using bool_constant = integral_constant<bool, val>;
using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

// is_same
template <typename T, typename U>
struct is_same : false_type {};

template <typename T>
struct is_same<T, T> : true_type {};

// is_same_v
template <typename T, typename U>
inline constexpr bool is_same_v = is_same<T, U>::value;

// remove_cv
template <typename T>
struct remove_cv {
    using type = T;
};

template <typename T>
struct remove_cv<const T> {
    using type = T;
};

template <typename T>
struct remove_cv<volatile T> {
    using type = T;
};

template <typename T>
struct remove_cv<const volatile T> {
    using type = T;
};

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

// remove_const
template <typename T>
struct remove_const {
    using type = T;
};

template <typename T>
struct remove_const<const T> {
    using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

// remove_volatile
template <typename T>
struct remove_volatile {
    using type = T;
};

template <typename T> 
struct remove_volatile<volatile T> {
    using type = T;
};

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

// is_void
template <typename T>
struct is_void : false_type {};

template <>
struct is_void<void> : true_type {};

template <typename T>
inline constexpr bool is_void_v = is_void<T>::value;

// is_null_pointer
template <typename T>
struct is_null_pointer : false_type {};

template <>
struct is_null_pointer<std::nullptr_t> : true_type {};

template <typename T>
inline constexpr bool is_null_pointer_v = is_null_pointer<T>::value;

// is_integral
template <typename T>
struct is_integral : false_type {};

template <> struct is_integral<bool> : true_type {};
template <> struct is_integral<char> : true_type {};
template <> struct is_integral<signed char> : true_type {};
template <> struct is_integral<unsigned char> : true_type {};
template <> struct is_integral<short> : true_type {};
template <> struct is_integral<unsigned short> : true_type {};
template <> struct is_integral<int> : true_type {};
template <> struct is_integral<unsigned int> : true_type {};
template <> struct is_integral<long> : true_type {};
template <> struct is_integral<unsigned long> : true_type {};
template <> struct is_integral<long long> : true_type {};
template <> struct is_integral<unsigned long long> : true_type {};

template <typename T>
inline constexpr bool is_integral_v = is_integral<T>::value;

// is_floating_point
template <typename T>
struct is_floating_point : false_type {};

template <>
struct is_floating_point<float> : true_type {};

template <>
struct is_floating_point<double> : true_type {};

template <>
struct is_floating_point<long double> : true_type {};

template <typename T>
inline constexpr bool is_floating_point_v = is_floating_point<T>::value;

// is_array
template <typename T>
struct is_array : false_type {};

template <typename T>
struct is_array<T[]> : true_type {};

template <typename T, std::size_t N> 
struct is_array<T[N]> : true_type {};

template <typename T>
inline constexpr bool is_class_v = is_class<T>::value;

template <typename T>
inline constexpr bool is_enum_v = is_enum<T>::value;

// is_pointer
template <typename T>
struct is_pointer : false_type {};

template <typename T>
struct is_pointer<T*> : true_type {};

template <typename T>
struct is_pointer<T* const> : true_type {};

template <typename T>
struct is_pointer<T* volatile> : true_type {};

template <typename T>
struct is_pointer<T* const volatile> : true_type {};

template <typename T>
inline constexpr bool is_pointer_v = is_pointer<T>::value;

// is_lvalue_reference
template <typename T>
struct is_lvalue_reference : false_type {};

template <typename T>
struct is_lvalue_reference<T&> : true_type {};

template <typename T>
inline constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;

// is_rvalue_reference
template <typename T>
struct is_rvalue_reference : false_type {};

template <typename T>
struct is_rvalue_reference<T&&> : true_type {};

template <typename T>
inline constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;

// is_arithmetic
template <typename T>
struct is_arithmetic : bool_constant<is_integral_v<T> || is_floating_point_v<T>> {};

template <typename T>
inline constexpr bool is_arithmetic_v = is_arithmetic<T>::value;

// is_fundamental
template <typename T>
struct is_fundamental : bool_constant<is_arithmetic_v<T> || is_void_v<T> || is_null_pointer_v<T>> {};

template <typename T>
inline constexpr bool is_fundamental_v = is_fundamental<T>::value;

// is_scalar
template <typename T>
struct is_scalar : bool_constant<is_arithmetic_v<T> || is_enum_v<T> || is_pointer_v<T>> {};

// is_object
template<class T>
struct is_object : bool_constant<is_scalar_v<T> || is_array_v<T> || is_union_v<T> || is_class_v<T>> {};

// is_compound
template<class T>
struct is_compound : bool_constant<!is_fundamental_v<T>> {};

template <typename T>
inline constexpr bool is_compound_v = is_compound<T>::value;

// is_reference
template <typename T>
struct is_reference : false_type {};

template <typename T>
struct is_reference<T&> : true_type {};

template <typename T>
struct is_reference<T&&> : true_type {};

template <typename T>
inline constexpr bool is_reference_v = is_reference<T>::value;

// is_const
template <typename T>
struct is_const : false_type {};

template <typename T>
struct is_const<const T> : true_type {}; 

template <typename T>
inline constexpr bool is_const_v = is_const<T>::value;

// is_volatile
template <typename T>
struct is_volatile : false_type {};

template <typename T>
struct is_volatile<volatile T> : true_type {};

// is_trivial
template <typename T>
struct is_trivial {
    static constexpr bool value = __has_trivial_constructor(T) && __has_trivial_copy(T) && __has_trivial_assign(T) && __has_trivial_destructor(T);
};

template <typename T>
inline constexpr bool is_trivial_v = is_trivial<T>::value;

// is_trivially_copyable
template <typename T>
struct is_trivially_copyable {
    static constexpr bool value = __has_trivial_copy(T);
};

template <typename T>
inline constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;

// is_standard_layout
template <typename T>
struct is_standard_layout {
    static constexpr bool value = __is_standard_layout(T);
};

template <typename T>
inline constexpr bool is_standard_layout_v = is_standard_layout<T>::value;

// is_pod
template <typename T>
struct is_pod {
    static constexpr bool value = __is_pod(T);
};

template <typename T>
inline constexpr bool is_pod_v = is_pod<T>::value;

// is_literal_type
template <typename T>
struct is_literal_type : bool_constant <__is_literal_type(T)>
{};

//remove_const
template <typename T>
struct remove_const {
    using type = T;
};

template <typename T>
struct remove_const<const T> {
    using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

//remove_volatile
template <typename T>
struct remove_volatile {
    using type = T;
};

template <typename T> 
struct remove_volatile<volatile T> {
    using type = T;
};

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

//add_cv
template <typename T>
struct add_cv {
    using type = const volatile T;
};

template <typename T>
using add_cv_t = typename add_cv<T>::type;

//add_const
template <typename T>
struct add_const {
    using type = const T;
};

template <typename T>
using add_const_t = typename add_const<T>::type;

//add_volatile
template <typename T>
struct add_volatile {
    using type = volatile T;
};

template <typename T>
using add_volatile_t = typename add_volatile<T>::type;


//remove_reference
template <typename T>
struct remove_reference {
    using type = T;
};

template <typename T>
struct remove_reference<T&> {
    using type = T;
};

template <typename T>
struct remove_reference<T&&> {
    using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

//add_lvalue_reference
template <typename T>
struct add_lvalue_reference {
    using type = T&;
};

template <typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

//add_rvalue_reference
template <typename T>
struct add_rvalue_reference {
    using type = T&&;
};

template <typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

//remove_pointer
template <typename T> 
struct remove_pointer { 
    using type = T; 
};

template <typename T> 
struct remove_pointer<T*> { 
    using type = T; 
};

template <typename T> 
struct remove_pointer<T* const> { 
    using type = T; 
};

template <typename T> 
struct remove_pointer<T* volatile> { 
    using type = T; 
};

template <typename T> 
struct remove_pointer<T* const volatile> { 
    using type = T; 
};

template <typename T>
using remove_pointer_t = typename remove_pointer<T>::type;


//add_pointer
template <typename T>
struct add_pointer {
    using type = T*;
};

template <typename T>
struct add_pointer<T*> {
    using type = T*;
};

template <typename T>
struct add_pointer<const T> {
    using type = const T*;
};

template <typename T>
struct add_pointer<volatile T> {
    using type = volatile T*;
};

template <typename T>
struct add_pointer<const volatile T> {
    using type = const volatile T*;
};

template <typename T>
using add_pointer_t = typename add_pointer<T>::type;

//enable_if
template <bool B, typename T = void>
struct enable_if
{};

template <typename T>
struct enable_if<true, T> {
    using type = T;
};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

//conditional
template <bool B, typename T, typename F>
struct conditional {
    using type = T; 
};

template<typename T, typename F>
struct conditional<false, T, F> {
    using type = F; 
};

template<bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

//remove_cvref
template <typename T>
struct remove_cvref {
    using type = typename remove_cv<typename remove_reference<T>::type>::type;
};

template <typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

//remove_extent
template <typename T>
struct remove_extent {
    using type = T;
};

template <typename T>
struct remove_extent<T[]> {
    using type = T;
};

template <typename T, std::size_t N>
struct remove_extent<T[N]> {
    using type = T;
};

template <typename T>
using remove_extent_t = typename remove_extent<T>::type;


//underlying_type
template <typename T>
struct underlying_type {
    using type = __underlying_type(T);
};

template <typename T>
using underlying_type_t = typename underlying_type<T>::type;
};