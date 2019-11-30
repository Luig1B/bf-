# BF++: Basically brainfuck with "functions".
## Addictions:
* `{` Starts a function;
* `}` Ends a function;
* `#` Call a function.
## Functionality
This doesn't make the language functional since there's no arguments, return, etc. It's just a subroutine for your code to follow.
## Making a function
Functions are identified with "IDs" which are the value of the current cell when a `{` is read. See the example:
```bf
++++ { >[>++++<-]< }
```
This function will multiply the next cell by 4 and will store the result 2 cells forward. Notice that it'll increment the starting cell four times. By doing this, 4 will be the "ID" for this function. A function can't have a null (zero) "ID".
## Calling a function
Calling a function is also easy, you just need to store the function's "ID" in the current cell and use the `#` to call it. See the example:
```bf
++++ Setting function's ID {
	>[ >++++<- ]<
} ---- Returning back to 0

> ++++ Selecting the function
> ++++ ++++ ++++ ++++ Using 16 as the "argument"
< # Calling the function
>> +. Incrementing 1 and printing the result (Expected: A)
```
Using the function we made earlier, we made a "multiply by four function". Recursion is allowed, you just need to keep control of it. Also, if the value in the current cell is 0, the call will be completely ignored. This can be an easier way of doing conditionals when necessary.
