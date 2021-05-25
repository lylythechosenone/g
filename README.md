# g
## A programming language

g is a compiled language that has gone through various stages of completeness over the year of 2020. It started as an interpreted language called `EEE` (which was completed, but it was very slow), then as a theoretical compiled language called `EEEEE`. g is the implementation of `EEEEE`.

| NOTE: if you're wondering why I stopped using meme names, I didn't; g compiles to an assembly subset called gasm. |
| --- |

The idea of g is it's a very simple, easy-to-learn language that is also very fast. It has only 3 builtin primitive types, `string` (which has subtype `char`), `number` and `nothing`. Each type has a shortened version (`str`, `num`, `none`). `number` can hold any signed or unsigned number from 1 byte to 8 bytes. The size and signedness are automatically decided at compile-time. `string` is a pointer to an array of `char`s (stack-allocated for constants, heap- or stack-allocated for variables). `nothing` is the same as C/C++ `void`.

## What makes g unique
Unlike most compiled languages, g doesn't have pointers. It handles memory things for you, under the hood. There are also a lot of other unique things about g. For example, a function can return multiple values, as long as they can all be shoved into `rax`.

| NOTE: even though g doesn't have pointers, there is a `System.Memory` namespace that provides functions for setting specific locations in memory. |
| --- |

#### Custom subtypes
In g, you can create custom subtypes for built-in types using `type(allowedValues)` where `type` is the type and `allowedValues` is a comma-separated list of acceptible values. Attempting to set the variable to a value not in `allowedValues` will result in a compile-time error.

#### Multiple return values
g functions can return an infinite number of values, as long as they can all be packed into the `a` register (64-bit on `x86_64`, 32-bit on `x86`). For example, on an `x86_64` system, you can `return 255, 255, 255, 255, 65536, 65536`, because `255` takes up exactly 1 byte, and `65536` takes up 2. All together, that adds up to 8 bytes, or 64 bits.

#### Smallest-possible numbers
g uses the smallest possible type to store number values, and saves memory.

#### Speed over size
All functions under 10 lines are copied as normal code, rather than invoked, to save in runtime. This adds a bit to file size, and can be configured using command-line arguments.

## Status
g is currently in development, and so far it has a fully functional lexer, a partially functional parser and a small library of classes.

## Getting started
Just because the compiler isn't done doesn't mean you shouldn't start learning now! To get started, check out the docs below. I'll post a "Hello, world!" example here soon.

# Docs

## Keywords

#### Types

* `char`: a single character, one byte.<br>
* `string`: a pointer to a list of characters, 64-bit on `x86_64`, 32-bit on `x86`<br>
    * `str`
* `number`: a single number. Can be either one byte, 2 bytes, 4 bytes or 8 bytes. Can also be either signed or unsigned, and decimal or non-decimal.<br>
    * `num`
* `nothing`: nothing. Equal to C `void`.<br>
    * `none`

#### Control flow
* `if`: basic if statement.
    * `else`
* `while`: a while loop.
    * `do`
    * `break`
    * `continue
* `for`: a for loop.
    * `break`
    * `continue`
* `switch`: a switch statement.
    * `case`
    * `break`

#### Functions
* `return`: return a value, or multiple.

#### Variables
* `const`: a read-only variable.
* `compiletime`: a variable which has a value known at compile-time. All uses of it will be substituted with its value.

#### Preprocessor
* `pre if`: check if a preprocessor statement is true, or if a macro is defined
    * `pre else`
    * `pre else if`
    * `pre end`

| NOTE: running `pre if` on a boolean macro will return based on if the macro is defined, not based on the value. if you want to base off of value, use `pre if MACRO == true` |
| --- |

* `pre define`: define a macro
    * `pre end` (when multi-line)

* `pre loop`: duplicate a code fragment *n* times, to make sure that your loops are unwrapped.

## Syntax

### Functions
A function is declared like this:
```
Name(type parameter, ...): type, ... {
    // Your code
}
```
* `Name`: the name of the function
* `type parameter`: a parameter to the function. `type` is the type of the parameter, `parameter` is the name. replace `...` with more of these to add more parameters
* `type`: a return type, replace `...` with more types to add more return values (but remember, they all have to fit into the `a` register)
