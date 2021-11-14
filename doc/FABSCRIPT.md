# FabScript

## 1. General

- FabScript is a custom interpreted scripting language created for FabiEngine3D.
- Experience with coding is a prerequisite (such as: Python, Java, C++, C#, Javascript, etc.).
- Scripts are run from the first line to the last line, from left to right.

## 2. Comments

Comments are pieces of text that do not get executed by the FabScript interpreter as code. They are very useful for explaining code or to bring more structure in the codebase. You can write comments in the code like this:

```text
1. /// This is a comment
```

## 3. META

### 3.1 General

Line 1 of every script file must specify its type: initialization, update, destruction.

- Initialization script: `META script_type_init`.
- Update script: `META script_type_update`.
- Destruction script: `META script_type_destroy`.

Line 2 of every script file must specify its execution state: entry or waiting.

- Entry script: `META script_execution_entry`.
- Waiting script: `META script_execution_waiting`.

### 3.2 Example Code

```text
1. META script_type_init
2. META script_execution_entry
3. 
4. /// Your code goes here
```

## 4. Variables & Values

### 4.1 Creation Syntax

- You can create a variable using: `<scope> <mutability> <type> <name> = <value>`.

### 4.2 Alteration Syntax

- You can edit a variable using: `EDIT <name> = <value>`.

### 4.3 Scope

- A variable scope can be global (`GLOB` keyword) or local (no extra keyword).
- A local variable can only be accessed in the same script file.
- A global variable can be accessed by ALL script files.
- A local variable will be deleted at the end of a script file execution.
- A global variable will never be deleted.

### 4.4 Mutability

- A variable can be immutable (`CONST` keyword) or mutable (no extra keyword).
- If you try to change a `CONST` variable, you will get an error!

### 4.5 Naming Conventions

- A variable name must be unique and not conflict with FabScript keywords.
- A variable name must start with an alphabetic character (abc...).
- A global variable name must start with '_'

### 4.6 Basic Values

- Types to choose from: `VEC3` (vector3), `STR` (string), `INT` (integer), `DEC` (decimal), `BOOL` (boolean).
- A boolean can only be true or false just like binary (example: `<true>` or `<false>`) (NOTE: the < and > are in this case NOT placeholders).
- A string can be any characters, as long as it's surrounded with " " (example: `"hello world"`).
- An integer is a whole number which can also be negative (example: `42`).
- A decimal is a floating point number which can also be negative (example: `42.536`).

### 4.7 Special Values - VEC3

- A vec3 is composed of 3 individual decimal values (example: `[1.0 2.0 3.0]`).
- Usually a VEC3 is a position/direction or color.
- To access/change the individual components, add .x/.y/.z or .r/.g/.b after the variable name (example: `<name>.x`).

### 4.8 Special Values - LIST

- A list is a special type of variable that holds 0 or more individual values (example: `{42, "test", <false>}`).
- A list cannot hold another list value/variable.
- You can access individual list components using: `<name>[<index>]`.
- You can add a new value to the list using: `PUSH <name> <value>`.
- You can delete an existing value from the list using: `PULL <name> <index>`.
- Remember: an index starts from 0!
- You cannot access a VEC3 decimal from a list directly.

### 4.9 Type Casting

- You can cast a variable to a different type using: `CAST <name> <type>`.
- You can cast from INT to DEC and vice versa.
- You can cast from INT to BOOL and vice versa.
- You can cast from BOOL to STR and vice versa (if possible).
- You can cast from INT to STR and vice versa (if possible).
- You can cast from DEC to STR and vice versa (if possible).
- You can cast from VEC3 to STR and vice versa (if possible).
- You cannot cast (an element of) a LIST variable.

### 4.10 Example Code

```text
1.  /// Variable syntax for each type
2.  BOOL myBoolean = <false>
3.  STR myString = "hello world"
4.  INT myInteger = 42
5.  DEC myDecimal = 42.94858
6.  VEC3 myVector = [1.0 2.0 3.0]
7.  LIST myList = {42, myBoolean, [4 2 0]}
8. 
9.  /// Constant variables
10. CONST STR immutableString = "i cannot be changed"
11. STR mutableString = "try to change me"
12. EDIT mutableString = "i changed you"
13. 
14. /// Global variables
15. GLOB INT _someInteger = 5
16. GLOB CONST INT _constInteger = 5
17. 
18. /// Casting variables
19. CAST myDecimal INT
20. STR intString = "123"
21. CAST intString INT
22. 
23. /// Vector3 variable
24. VEC3 redColor = [1.0 0.0 0.0]
25. DEC redValue = redColor.r
26. 
27. /// List variable
28. LIST myList = {"hello", 123, 45.0, redColor, redColor.x, <false>}
29. STR temp1 = myList[0]
30. PUSH temp1 "newValue"
31. PULL temp1 6
```

## 5. Arithmetic Operations

### General

- There are 5 types of arithmetic: addition, subtraction, multiplication, division, negation.
- Addition syntax: `INCR <name> <value>`.
- Subtraction syntax: `DECR <name> <value>`.
- Multiplication syntax: `MUL <name> <value>`.
- Division syntax: `DIV <name> <value>`.
- Negation syntax: `NEG <name>`.
- The result of the arithmetic operation will be stored in the variable the operation was applied on.
- Arithmetic can be applied on individual list elements, but not the list itself!

### 5.2 Example Code

```text
1. INT myInteger = 40
2. DIV myInteger 5
3. NEG myInteger
4.
5. /// Now myInteger will be -8
```

## 6. Comparison Operations

### 6.1 General

- To check if two values are the same: `<value> IS <value>`.
- To check if two values are different: `<value> NOT <value>`.
- To check if one value is higher than the other: `<value> MORE <value>` (only works for `INT` and `DEC` values).
- To check if one value is lower than the other: `<value> LESS <value>` (only works for `INT` and `DEC` values).
- You cannot use different comparison value types (example: `5 IS 5.0` will not work, but `5 IS 5` will).
- You can set the value of a `BOOL` variable to the result of a condition using: `... <name> = (<condition>)`.

### 6.2 Example Code

```text
1. INT age = 12
2. BOOL isUnderAge = (age LESS 18)
3. fe3d:print(isUnderAge)
4.
5. /// Console output:
6. /// > true
```

## 7. Logical Operations

### 7.1 General

- To check if all the comparison statements are true: `<comparison> AND <comparison>`.
- To check if any of the comparison statements are true: `<comparison> OR <comparison>`.
- You cannot combine the `AND` and `OR` keywords in one logical statement.

### 7.2 Example Code

```text
1. INT age = 999
2. BOOL isValidAge = (age MORE 0 AND age LESS 100)
3. fe3d:print(isValidAge)
4.
5. /// Console output:
6. /// > false
```

## 8. Conditional Operations

### 8.1 General

- There are 3 types: `IF`, `ELIF`, `ELSE`.
- Every logical statement must end with a `:`.
- All code under a logical statement must must be indented with 4 spaces / 1 tab.
- You can chain these conditional operations, in the described order.
- Conditional statements can be nested infinitely.
- Works the same as in other programming languages.

### 8.2 Example Code

```text
1.  INT age = 41
2.  IF age IS 100:
3.      fe3d:print("I am dead!")
6.  ELIF age LESS 42:
7.      fe3d:print("I am younger than 42!")
8.  ELSE:
9.      fe3d:print("I am older than 42!")
10.
11. /// Console output:
12. /// > I am younger than 42!
```

## 9. Loops

### 9.1 General

- Use a `LOOP` statement if you want to run a block of code multiple times.
- You can exit a loop using the `BREAK` statement.
- You can skip a loop iteration by using the `CONTINUE` statement.
- the maximum iterations per loop is 1000.

### 9.2 Example Code

```text
1.  LIST myList = {"hello", "beautiful", "world"}
2.  INT index = 0
3.  LOOP:
4.      IF index IS 2:
5.          BREAK
6.      fe3d:print(myList[index])
7.  
8.  /// Console output:
9.  /// > hello
10. /// > beautiful
11. /// > world
```

## 10. Executing Other Scripts

### 10.1 General

- The scripts that have the `execution_entry` META defined run first.
- From there you can decide the order of execution yourself.
- You can execute another script file using: `EXEC <name>`.
- After the script is executed, the program will continue running the script where it left off.
- The script that is executed must have the same type as the calling script.
- This works the same as in other programming languages.
- The maximum execution depth is 10.

### 10.2 Example Code

```text
1.  /// Code in main_script.fe3d
2.  EXEC print_script
3.  fe3d:print("goodbye world!")
4.
5.  /// Code in print_script.fe3d
6.  fe3d:print("hello world!")
7.
8.  /// Console output:
9.  /// > hello world!
10. /// > goodbye world!
```

## 11. Functions

### 11.1 General

- You can call functions defined by the engine.
- There are 3 types of functions: `fe3d` functions, `math` functions, `misc` functions.
- Functions can return a value, which can be saved in a variable.

### 11.2 Example Code

```text
1. STR myString = "i am printed"
2. fe3d:camera_set_position(1.0, 2.0, 3.0)
3. VEC3 camPos = fe3d:camera_get_position()
4. fe3d:print(myString)
5. fe3d:print(camPos)
6.
7. /// Console output:
8. /// > i am printed
9. /// > 1.0 2.0 3.0
```

## 12. Tips & Tricks

- You can use the `PASS` statement as an empty placeholder for conditional statements or loops.
- Be careful with loops as they can become infinite. Luckily this will get detected by the interpreter.
- Integer values are clamped between -999999999 and 999999999 to prevent overflow.
- Decimal values are clamped between -999999999.0 and 999999999.0 to prevent overflow.
- Decimal values have a fixed precision of 5 decimals after the dot.
