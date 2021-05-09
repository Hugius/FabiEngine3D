### Miscellaneous functions
- `misc:concat_strings`(`STR` first, `STR` second) ---> `STR`  
  Returns **first** and **second** concatenated together.
- `misc:concat_lists`(`STR` firstName, `STR` secondName) ---> `LIST`  
  Returns the lists with **firstName** and **secondName** concatenated together. **firstName** and **secondName** must be put in string values.
- `misc:get_list_size`(`STR` name) ---> `INT`  
  Returns the counted total of list items and returns the amount. **name** must be put in a string value.
- `misc:get_string_size`(`STR` value) ---> `INT`  
  Returns the counted total of **value** characters and returns the amount.
- `misc:get_string_part`(`STR` value, `INT` index, `INT` count) ---> `STR`  
  Returns a part from **value**. Example: **value** = "test", **index** = 1, **count** = 2, returns: "est".
- `misc:get_random_integer`(`INT` min, `INT` max) ---> `INT`  
  Returns a random integer between **min** and **max**.
- `misc:get_random_decimal`(`DEC` min, `DEC` max) ---> `DEC`  
  Returns a random decimal between **min** and **max**.
- `misc:time_interval`(`INT` frames) ---> `BOOL`  
  Returns true every time **frames** has passed.
