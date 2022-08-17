# Scripting

## 1. General

- FabScript is an interpreted scripting language specifically created for the engine.
- Experience with coding is a prerequisite (such as: Python, Java, C++, C#, Javascript, et cetera).
- Scripts are run from the first line to the last line, from left to right.

## 2. Comments

Comments are pieces of text that do not get executed by the FabScript interpreter as code. They are very useful for explaining code or to bring more structure in the codebase. You can write comments in the code like this:

```text
1. /// This is a comment
```

## 3. META

### 3.1 General

Line 1 of every script file must specify its type: initialization, update, destruction.

- Initialize script: `META script_type_initialize`.
- Update script: `META script_type_update`.
- Terminate script: `META script_type_terminate`.

Line 2 of every script file must specify its state: entry or wait.

- Entry script: `META script_state_entry`.
- Wait script: `META script_state_wait`.

### 3.2 Example Code

```text
1. META script_type_initialize
2. META script_execution_entry
3. 
4. /// Your code goes here
```

## 4. Variables & Values

### 4.1 Creation Syntax

- You can create a variable using `<scope> <mutability> <type> <name> = <value>`.

### 4.2 Alteration Syntax

- You can edit a variable using `EDIT <name> = <value>`.

### 4.3 Scope

- A variable scope can be global (`GLOB` keyword) or local (no extra keyword).
- A local variable can only be accessed in the same script file.
- A global variable can be accessed by ALL script files.
- A local variable will be deleted at the end of a script file execution.
- A global variable will never be deleted.

### 4.4 Mutability

- A variable can be immutable (`CNST` keyword) or mutable (no extra keyword).
- If you try to change an immutable variable, you will get an error!

### 4.5 Naming Conventions

- A variable name must be unique and not conflict with FabScript keywords.
- A variable name must start with an alphabetic character (abc...).
- A global variable name must start with `_`

### 4.6 Basic Values

- Types to choose from: `STR` (string), `INT` (integer), `DEC` (decimal), `BOL` (boolean).
- A string is a concatenation of any characters, as long as they are surrounded with `"` `"`. Example: `"hello world"`.
- A decimal is a floating point number which can also be negative. Example: `-42.536`.
- An integer is a whole number which can also be negative. Example: `-42`.
- A boolean can only be true or false. Example: `<true>` or `<false>` (NOTE: the `<` and `>` are not placeholders).

### 4.7 Special Value

- A list is a special type of value that holds 0 or more individual values. Example: `{42, "test", <false>}`.
- A list cannot hold another list value/variable.
- You can access individual list components using `<name>[<index>]`.
- You can add a new value to the list using `PUSH <name> <value>`.
- You can delete an existing value from the list using `PULL <name> <index>`.
- Remember: an index starts from 0!

### 4.8 Type Casting

- You can cast a variable to a different type using: `CAST <name> <type>`.
- You can cast from `INT` to `DEC` and vice versa.
- You can cast from `INT` to `BOL` and vice versa.
- You can cast from `BOL` to `STR` and vice versa (if possible).
- You can cast from `INT` to `STR` and vice versa (if possible).
- You can cast from `DEC` to `STR` and vice versa (if possible).
- You cannot cast (an element of) a `LST` variable.

### 4.9 Example Code

```text
1.  /// String variable
2.  STR myString = "hello world"
3.
4.  /// Decimal variable
5.  DEC myDecimal = 42.94858
6.
7.  /// Integer variable
8.  INT myInteger = 42
9.
10. /// Boolean variable
11. BOL myBoolean = <false>
12.
13. /// List variable
14. LST myList = {42, myBoolean, "test123", 45.0}
15. STR firstElement = myList[0]
16. PUSH myList "newValue"
17. PULL myList 2
18.
19. /// Immutable variable
20. CNST STR immutableString = "i cannot be changed"
21. STR mutableString = "try to change me"
22. EDIT mutableString = "i changed you"
23.
24. /// Global variable
25. GLOB INT _someInteger = 5
26. GLOB CNST INT _anotherInteger = 5
27.
28. /// Variable casting
29. CAST myDecimal INT
30. STR intString = "123"
31. CAST intString INT
```

## 5. Arithmetic Operations

### General

- There are 5 types of arithmetic: addition, subtraction, multiplication, division, modulus, negation.
- Addition syntax: `ADD <name> <value>`.
- Subtraction syntax: `SUB <name> <value>`.
- Multiplication syntax: `MUL <name> <value>`.
- Division syntax: `DIV <name> <value>`.
- Modulus syntax: `MOD <name> <value>`.
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
- You can set the value of a `BOL` variable to the result of a condition using: `... <name> = (<condition>)`.

### 6.2 Example Code

```text
1. INT age = 12
2. BOL isUnderAge = (age LESS 18)
3. fe3d:print(isUnderAge)
4.
5. /// Console output:
6. /// > true
```

## 7. Logic Operations

### 7.1 General

- To check if all the comparison operations are true: `<comparison> AND <comparison>`.
- To check if any of the comparison operations are true: `<comparison> OR <comparison>`.
- You cannot use both the `AND` and `OR` keywords in one logic operation.

### 7.2 Example Code

```text
1. INT age = 999
2. BOL isValidAge = (age MORE 0 AND age LESS 100)
3. fe3d:print(isValidAge)
4.
5. /// Console output:
6. /// > false
```

## 8. Condition Operations

### 8.1 General

- There are 3 types: `IF`, `ELIF`, `ELSE`.
- All code under a condition operation must must be indented with 4 spaces / 1 tab.
- You can chain these condition operations, in the described order.
- Condition operations can be nested infinitely.
- Works the same as in other programming languages.

### 8.2 Example Code

```text
1.  INT age = 41
2.  IF age IS 100
3.      fe3d:print("I am dead!")
6.  ELIF age LESS 42
7.      fe3d:print("I am younger than 42!")
8.  ELSE
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
1.  LST myList = {"hello", "beautiful", "world"}
2.  INT index = 0
3.  LOOP
4.      IF index IS 2
5.          BREAK
6.      fe3d:print(myList[index])
7.      ADD index 1
8.  
9.  /// Console output:
10. /// > hello
11. /// > beautiful
```

## 10. Executing Other Scripts

### 10.1 General

- The scripts that have the `execution_entry` META defined run first.
- From there you can decide the order of execution yourself.
- You can execute another script file using `EXECUTE <name>`.
- After the script is executed, the program will continue running the script where it left off.
- The script that is executed must have the same type as the calling script.
- This works the same as in other programming languages.
- The maximum execution depth is 10.
- You can exit the execution of a script file using `EXIT`.

### 10.2 Example Code

```text
1.  /// Code in main_script.fe3d
2.  EXECUTE print_script
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
- Functions can have "parameters", which are values expected to be passed to the function.
- Actual values that are passed to functions are called "arguments".
- List values cannot be used as parameters/arguments.

### 11.2 Example Code

```text
1. fe3d:camera_set_position(1.0, 2.0, 3.0)
2. DEC z = fe3d:camera_get_position_z()
3. fe3d:print(z)
4.
5. /// Console output:
6. /// > 3.0
```

### 11.3 Types

- [Engine Functions](SCRIPT_FE3D.md)
- [Mathematics Functions](SCRIPT_MATH.md)
- [Miscellaneous Functions](SCRIPT_MISC.md)

## 12. Tips & Tricks

- You can use the `PASS` statement as an empty placeholder.
- Be careful with loops as they can become infinite. Luckily this will get detected by the interpreter.
- Integer values are clamped between `-999999999` and `999999999` to prevent overflow.
- Decimal values are clamped between `-999999999.0` and `999999999.0` to prevent overflow.
- Decimal values have a fixed precision of 5 decimals after the dot.
