# TypeTraits Implementation

This repository contains a custom implementation of various type traits in C++, mimicking the behavior of the standard type traits found in the `<type_traits>` header. The implementation covers fundamental type traits, type modifiers, and type utilities.

## Features

The following type traits are implemented:

- **Type Modifiers**
  - `remove_const`
  - `remove_volatile`
  - `add_cv`
  - `add_const`
  - `add_volatile`
  - `remove_reference`
  - `remove_pointer`
  - `add_pointer`

- **Type Queries**
  - `is_same`
  - `is_void`
  - `is_null_pointer`
  - `is_integral`
  - `is_floating_point`
  - `is_array`
  - `is_pointer`
  - `is_lvalue_reference`
  - `is_rvalue_reference`
  - `is_arithmetic`
  - `is_fundamental`
  - `is_compound`
  - `is_reference`
  - `is_const`
  - `is_volatile`
  - `is_standard_layout`
  - `is_pod`
  - `is_literal_type`

- **Conditional and Result Types**
  - `enable_if`
  - `conditional`
  - `remove_cvref`
  - `remove_extent`
  - `underlying_type`

## Example Output

The following output demonstrates the usage of the implemented type traits:

````cpp
integral_constant<int, 42>::value = 42 true_type value = 1 false_type value = 0 is_same<int, int> = 1 is_same<int, float> = 0 remove_cv<const int>::type is int = 1 remove_extent<int[5]>::type is int = 1 is_integral<int> = 1 is_integral<float> = 0 is_floating_point<double> = 1 is_floating_point<int> = 0 is_pointer<int*> = 1 is_pointer<int> = 0 remove_pointer<int*>::type is int = 1 integralVariable = 10 conditional<true, int, double> is int = 1 underlying_type<Color>::type is uint8_t = 1
````


## Usage

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/type_traits.git
2. Navigate to the project directory: <br>
  ```bash
  cd type_traits
  ````
3. Compile the code: <br>
    ```bash
    g++ main.cpp -o main
    ````
4. Run the compiled program: <br>
  ```` bash
    ./main
  ````

