# Project Overview
In this project, I built a program that gets four input file names. The first file will be the function definition file, 
the second will be the input values for which the function and its derivative is to be calculated. I calculated function and
partial derivatives for given input values and print the results to two output files one for a value of a function (third input) and one for partial derivatives(fourth input).


## File Formats
  ### Function Definition File
  The function definition file has the following format:
  ```
  <input>
  <input>
  ...
  <input>
  <output>
  <assignment>
  <assignment>
  ...
  <assignment>
  
  Context free grammar of the <input> ,<output> and <assignment> will be following:
  
  <input> -> input <var>
  <output> -> output <var>
  <assignment> -> <var> = <function> <var> <var> (designed for functions with two parameters)
  <assignment> -> <var> = <function> <var>       (designed for functions with one parameter)
  <assignment> -> <var> = <var>                  (designed for assignments)
  where <var> is variable name and <function> is function name.
  ```
  Functions:

- cos
- sin
- tan
- acos
- asin
- atan
- exp
- log
- sqrt
- add
- mult
- subs
- divide
- pow

  ### Input Values File
  The input values file has the following format:
  ```
  <input 1> <input 2> ... <input n> (names of input paramaters)
  <value 1> <value 2> ... <value n> (values of corresponding paramaters)
  <value 1> <value 2> ... <value n>
  ```
  For each line, I calculated the output of the described function and partial derivatives with respect to  each input variable.
  
  ### Output Values File
  The output values file has the following format:
  ```
  <output>
  <value 1>
  <value 2>
  <value 3>
  ...
  where <output> is the name of output variable and <value> is the value of 
  function with the corresponding input values given in the input values file.
  ```
  
  ### Derivative Values File
  The derivative values file has the following format:
  ```
  <deriv 1> <deriv 2> ... <deriv n>
  <value 1> <value 2> ... <value n>
  <value 1> <value 2> ... <value n>
  <value 1> <value 2> ... <value n>
  where  <deriv 1> <deriv 2> ... <deriv n>'s are the names of derivatives
  and <value 1> <value 2> ... <value n>'s are the values of derivatives with
  respected to corresponding variable and with the corresponding input values
  given in the input values file.
  ```
  
    
    
