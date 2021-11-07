# Miscellaneous functions
### Getters
- `misc:list_concat`(`STR` firstName, `STR` secondName) ---> `LIST`  
  Returns the lists with **firstName** and **secondName** concatenated together. **firstName** and **secondName** must be put in string values.
- `misc:list_get_size`(`STR` name) ---> `INT`  
  Returns the total amount of items in list with **name**. **name** must be put in a string value.
- `misc:list_contains`(`STR` name, `VEC3/STR/DEC/INT/BOOL` value) ---> `BOOL`  
  Returns true if list with **name** contains **value**. **name** must be put in a string value.
- `misc:list_reverse`(`STR` name) ---> `LIST`  
  Returns the list with **name** in reverse. **name** must be put in a string value.
- `misc:string_concat`(`STR` first, `STR` second) ---> `STR`  
  Returns **first** and **second** concatenated together.
- `misc:string_get_size`(`STR` string) ---> `INT`  
  Returns the total amount of characters **string**.
- `misc:string_get_part`(`STR` string, `INT` index, `INT` count) ---> `STR`  
  Returns a part from **string**. Example: **string** = "test", **index** = 1, **count** = 2, returns: "est".
- `misc:string_contains`(`STR` string, `STR` subString) ---> `BOOL`  
  Returns true if **string** contains **subString**.
- `misc:string_split`(`STR` string, `STR` splitter) ---> `LIST`  
  Returns a list of strings splitted from **string** by **splitter** (must be single character).
- `misc:string_reverse`(`STR` string) ---> `STR`  
  Returns the **string** in reverse.
- `misc:random_integer`(`INT` min, `INT` max) ---> `INT`  
  Returns a random integer between **min** and **max**.
- `misc:random_decimal`(`DEC` min, `DEC` max) ---> `DEC`  
  Returns a random decimal between **min** and **max**.
