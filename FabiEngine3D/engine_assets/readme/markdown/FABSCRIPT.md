# FabScript
- FabScript is a custom **interpreted** scripting language created for FabiEngine3D.
- Experience with coding is a prerequisite (Python, Java, C++, C#, Javascript, etc.).
- Scripts are run from the first line to the last line, from left to right.
### META
- Line 1 of every script file **must** specify its type: initialization, update, destruction.
- Line 2 of every script file **must** specify its execution state: entry or sleep.
- **Initialization** script: `META script_type_init`.
- **Update** script: `META script_type_update`.
- **Destruction** script: `META script_type_destroy`.
- **Entry** script: `META script_execution_entry`.
- **Waiting** script: `META script_execution_waiting`.
#### Example code
```
1. META script_type_init
2. META execution_entry
3. 
4. /// Your code <--- This is a comment by the way
```
### Variables & values
#### Creation syntax
- You can **create** a variable using: `<scope> <mutability> <type> <name> = <value>`.
#### Alteration syntax
- You can **edit** a variable using: `EDIT <name> = <value>`.
#### Scope
- A variable **scope** can be **global** (`GLOB` keyword) or **local** (no extra keyword).
- A local variable can only be accessed in the **same script** file.
- A global variable can be accessed by **ALL** script files.
- A local variable will be deleted after **the end** of a script file execution, once created.
- A global variable will **never** be deleted, once created.
#### Mutability
- A variable can be **immutable** (`CONST` keyword) or **mutable** (no extra keyword).
- If you try to change a CONST variable, you will get an error!
#### Naming conventions
- A variable name **must** be unique and not conflicting with FabScript keywords.
- A variable name **must** start with an alpha value (abc...).
- A global variable name **must** start with '_'
#### Basic values
- Types to choose from: `VEC3` (vector3), `STR` (string), `INT` (integer), `DEC` (decimal), `BOOL` (boolean).
- A boolean can only be true or false just like binary (example: `<true>` or `<false>`) (NOTE: the < and > are in this case **NOT** placeholders).
- A string can be any characters, as long as it's surrounded with " " (example: `"hello world"`).
- An integer is a whole number which can also be negative (example: `42`).
- A decimal is a floating point number which can also be negative (example: `42.536`).
#### Special values - VEC3
- A vec3 is composed of 3 individual **decimal** values (example: `[1.0 2.0 3.0]`).
- Usually a VEC3 is a position/direction or color.
- To **access/change** the individual components, add .x/.y/.z or .r/.g/.b after the variable name (example: `<name>.x`).
#### Special values - LIST
- A list is a special type of variable that holds 0 or more **individual values** (example: `{42, "test", <false>}`).
- A list **cannot** hold another list value/variable.
- You can **access** individual list components using: `<name>[<index>]`.
- You can **add** a new value to the list using: `PUSH <name> <value>`.
- You can **delete** an existing value from the list using: `PULL <name> <index>`.
- Remember: an index starts from **0**!
- You **cannot** access a VEC3 decimal from a list directly.
#### Type casting
- You can **cast** a variable to a different **type** using: `CAST <name> <type>`.
- You can cast from INT to DEC and vice versa.
- You can cast from INT to BOOL and vice versa.
- You can cast from BOOL to STR and vice versa (if possible).
- You can cast from INT to STR and vice versa (if possible).
- You can cast from DEC to STR and vice versa (if possible).
- You can cast from VEC3 to STR and vice versa (if possible).
- You **cannot** cast (an element of) a LIST variable.
#### Example code
```
/// Variable syntax for each type
BOOL myBoolean = <false>
STR myString = "hello world"
INT myInteger = 42
DEC myDecimal = 42.94858
VEC3 myVector = [1.0 2.0 3.0]
LIST myList = {42, myBoolean, [4 2 0]}

/// Constant variables
CONST STR immutableString = "i cannot be changed"
STR mutableString = "try to change me"
EDIT mutableString = "i changed you"

/// Global variables
GLOB INT _someInteger = 5
GLOB CONST INT _constInteger = 5

/// Casting variables
CAST myDecimal INT
STR intString = "123"
CAST intString INT

/// Vector3 variable
VEC3 redColor = [1.0 0.0 0.0]
DEC redValue = redColor.r

/// List variable
LIST myList = {"hello", 123, 45.0, redColor, redColor.x, <false>}
STR temp1 = myList[0]
PUSH temp1 "newValue"
PULL temp1 6
```
### Arithmetic operations
#### Arithmetic types
- There are 5 types of arithmetic: addition, subtraction, multiplication, division, negation.
- Addition syntax: `INCR <name> <value>`.
- Subtraction syntax: `DECR <name> <value>`.
- Multiplication syntax: `MUL <name> <value>`.
- Division syntax: `DIV <name> <value>`.
- Negation syntax: `NEG <name>`.
- The result of the arithmetic operation will be stored in the variable the operation was applied on.
- Arithmetic can be applied on individual list elements, but not the list itself!
#### Example code
```
INT myInteger = 40
DIV myInteger 5
NEG myInteger
/// Now myInteger will be -8
```
### Logic operations
#### Comparison operators
- To check if two values are **the same**: `<value> IS <value>`.
- To check if two values are **different**: `<value> NOT <value>`.
- To check if one value is **higher** than the other: `<value> MORE <value>` (only works for `INT` and `DEC` values).
- To check if one value is **lower** than the other: `<value> LESS <value>` (only works for `INT` and `DEC` values).
- You cannot use different comparison value types (example: `5 IS 5.0` will not work, but `5 IS 5` will do).
#### Logic operators
- To check if **all** the comparison statements are true: `<comparison> AND <comparison>`.
- To check if ***any** of the comparison statements are true: `<comparison> OR <comparison>`.
- You **cannot** combine the `AND` and `OR` keywords in one logic statement.
#### Logic statements
- There are 3 types: if-statement, elif-statement, else-statement.
- Every logic statement **must** end with a `:`.
- All code under a logic statement **must** must be indented with 4 spaces / 1 TAB.
- The order is: if - elif - else.
- These statements can be nested infinitely.
- Works the same as all other programming languages.
#### Example code
```
INT age = 41
IF age IS 41 AND "hello" IS "world":
    fe3d:print("You should not see this message!")
ELIF test IS 42:
    fe3d:print("I am 42!")
ELIF age LESS 42:
    fe3d:print("I am younger than 42!")
ELSE:
    fe3d:print("I am higher than 42!")
```
### Loops
- Use a `LOOP` statement if you want to run a block of code multiple times.
- Once a loop is started, you can only get out using the `BREAK` statement.
- You can use loops for iterating over a LIST for example.
#### Example code
```
LIST myList = {"hello","beautiful", "world"}
INT index = 0
LOOP:
    IF index IS 2:
        BREAK
    fe3d:print(myList[index])
    
/// Console output:
/// > hello
/// > beautiful
/// > world
```
### Executing other scripts
- For every script **type** (init, update, destroy) there is an `execution_entry` META defined.
- From there you can decide the **order of execution** yourself.
- You can **execute** another script file using: `EXEC <name>`.
- After the script is executed, the program will continue running the script **where it left off**.
- The script that is executed must have the **same type** as the caller script.
- This works the same way as **functions** in other programming languages.
#### Example code
```
/// Code in main_script.fe3d
EXEC print_script
fe3d:print("goodbye world")

/// Code in print_script.fe3d
fe3d:print("hello world")

/// Console output:
/// > hello world
/// > goodbye world
```
### Functions
- You can call functions that are built-in FabiEngine3D.
- There are 3 types of functions: `fe3d` functions, `math` functions, `misc` functions.
- Functions **can** return a value, which can be saved in a variable.
#### Example code
```
STR myString = "i am printed"
fe3d:camera_set_position(1.0, 2.0, 3.0)
VEC3 camPos = fe3d:camera_get_position()
fe3d:print(myString)
fe3d:print(camPos.x)

/// Console output:
/// > i am printed
/// > 1.0
```
### Tips & tricks
- You can set the value of a `BOOL` variable to the result of a condition using: `... <name> = (<condition>)`.
- You can use the `PASS` statement as an empty placeholder for a logical statement or loop.
- Be careful with loops as they can become indefinite. Luckily this will get detected eventually.
- Integer values are clamped between -999999999 and 999999999 to prevent overflow.
- Decimal values are clamped between -999999999.0 and 999999999.0 to prevent overflow.
- Decimal values have a precision of 5 decimals after the dot.
