### Miscellaneous functions
- `misc:list_concat`(`STR` firstName, `STR` secondName) ---> `LIST`  
  Returns the lists with **firstName** and **secondName** concatenated together. **firstName** and **secondName** must be put in string values.
- `misc:list_size`(`STR` name) ---> `INT`  
  Returns the counted total of list items and returns the amount. **name** must be put in a string value.
- `misc:string_concat`(`STR` first, `STR` second) ---> `STR`  
  Returns **first** and **second** concatenated together.
- `misc:string_size`(`STR` string) ---> `INT`  
  Returns the counted total of **string** characters and returns the amount.
- `misc:string_part`(`STR` string, `INT` index, `INT` count) ---> `STR`  
  Returns a part from **string**. Example: **string** = "test", **index** = 1, **count** = 2, returns: "est".
- `misc:string_contains`(`STR` string, `STR` subString) ---> `BOOL`  
  Returns true if **string** contains **subString**.
- `misc:string_split`(`STR` string, `STR` splitter) ---> `LIST`  
  Returns a list of strings splitted from **string** by **splitter** (must be single character).
- `misc:random_integer`(`INT` min, `INT` max) ---> `INT`  
  Returns a random integer between **min** and **max**.
- `misc:random_decimal`(`DEC` min, `DEC` max) ---> `DEC`  
  Returns a random decimal between **min** and **max**.
