# Json parser
C++ JSON parser with simple test / example of it's work. To parse and verify JSON data, state machine (sort of) is using. Main idea pretty simple, but main problem here - state machine itself. 

Despite several moments, parser meets all (almost) requirements of [RFC JSON standart](https://tools.ietf.org/html/rfc7159).
Data stores in objects in form of strings with its type (to manually convert them to appropriate data type). Data hierarchy is saved.

Main reasons to create this parser is:
- Educational purpose
- Informative errors (if there any)
- To use it in desktop app to visulize process of parsing json strings
- Practice with state machines

### State machine and transition table
Parser parse each char one by one, and because of the type of input data (chars), its hard (and, probably, inefficient) to change states by simply get new state from matrix by index. Whole state machine based on many (realy many) switch-case statements.
This state machine have state stack to remember states (e.g. string in object, and this object in array - we need to remebet that we in array and etc.)

#### Here is transition table:

| id | State             |      {    |    }   |      [    |    ]   |   ,  |   :  |      " 	 | letter |  num +-.  | ws char |       \ 	 |      t  	  |       f    |      n 	|
| :- | :---------------- | :-------: | :----: | :-------: | :----: | :--: | :--: | :-------: | :--:   | :-------: | :-----: | :--------: | :--------: | :--------: | :--------: |
|  2 | **Initial**		 | 3#push(2) | #2 	  | 4#push(2) | #2 	   | #2   | #2 	 | #2 		 | #2 	  | #2 		  | ##		| #2 		 | #2 		  | #2 		   | #2 		|
|  3 | **Object**		 | #3        | #ret	  | #3 		  | #3     | 	  | #3 	 | 5#push(3) | #3 	  | #3 		  | ##		| #3 		 | #3 		  | #3 		   | #3 		|
|  4 | **Array**         | 3#push(4) | #4 	  | 4#push(4) | #ret   | 	  | #4 	 | 9#push(4) | #4 	  | 9#push(4) | ##		| #4 		 | 12#push(4) | 13#push(4) | 14#push(4) |
|  5 | **Name**          | 5         | 5 	  | 5 		  | 5 	   | 5    | 5 	 | 6 		 | 5 	  | 5		  | 5 		| 11#push(5) | 5 		  | 5 		   | 5 			|
|  6 | **After name**    | #6 		 | #6 	  | #6 		  | #6 	   | #6   | 7 	 | #6 		 | #6 	  | #6 	 	  | ##		| #6 		 | #6 		  | #6 		   | #6 		|
|  7 | **Before value**  | 3 		 | #7 	  | 4 		  | #7 	   | #7   | #7 	 | 9 	     | #7 	  | 8 		  | ##		| #7 		 | 12 		  | 13 		   | 14 		|
|  8 | **Number**        | #8 		 | 2x#ret | #8 		  | 2x#ret | #ret | #8 	 | #8 		 | #8 	  | 8 		  | 10 		| #8 		 | #8 		  | #8 		   | #8 		|
|  9 | **String**        | 9 		 | 9 	  | 9 		  | 9 	   | 9 	  | 9 	 | 10 	 	 | 9 	  | 9 		  | 9 		| 11#push(9) | 9 		  | 9 		   | 9 			|
| 10 | **After Value**   | #10		 | 2x#ret | #10		  | 2x#ret | #ret | #10	 | #10		 | #10	  | #10		  |	##		| #10		 | #10		  | #10		   | #10 		|
| 11 | **Char escape**   | #ret		 | #ret	  | #ret      | #ret   | #ret | #ret | #ret		 | #ret   | #ret	  | #ret	| #ret		 | #ret		  | #ret	   | #ret 		|
| 12 | **True**          | #12		 | #12	  | #12		  | #12	   | #12  | #12	 | #12		 | #12	  | #12		  | ##		| #12		 | #12		  | #12		   | #12 		|
| 13 | **False**         | #13		 | #13	  | #13		  | #13	   | #13  | #13	 | #13 		 | #13	  | #13		  | ##		| #13		 | #13		  | #13		   | #13 		|
| 14 | **Null**          | #13		 | #13 	  | #13		  | #13	   | #13  | #13	 | #13 	 	 | #13	  | #13		  | ##		| #13		 | #13		  | #13		   | #13 		|

#### And errors:

| Code | 			Error message 		  |
| :--- | :------------------------------- |
|  #2  | Array or object expected 		  |
|  #3  | Value's name expected 	  		  |
|  #4  | Value expected 		  		  |
|  #6  | `:` expected 			  		  |
|  #8  | Number, `}`, `]` or `,` expected |
| #12  | `True` expected  				  |
| #13  | `False` expected 				  |
| #14  | `Null` expected  				  |

#### Explanation of "WTF is this?"
Transitions between states implemented in `*State.cpp` files, where each file represents certain row from transition table.
Explanations of statements from table:
- `x#push(y)` - go to state `x` and push state `y` into state stack
- `x` - just go to state `x`
- `#ret` - pop state from state stack
- `2x#ret` - pop 2 states from state stack
- `#x` - error `x` (see error codes) occured
- `##` - ignore char

#### How to use it
To parse string, you need to create object `Parser` with pointer to `const char*` string and size of the string as arguments. If size of string is ommited, parser will stop on `\0` char. Then you can start parse string by call `parse()` method. If you pass `False` to this method, parser will parse only one char and paused. If argument is omitted, parser will parse string till the end (or first error). 

You can get error message by calling `getError()` method and error position in string by calling 'getPos()' method. 

Method `success()` return state of parser.

Extracted data can be accessed by calling `getData()` method. This method returns `DataTree*` pointer to root of data tree. Suposed, that you know hierachy of data and type of data, and can manualy convert extracted data to needed type.

### Todo:
- [ ] ADD COMMENTS ASAP !!!
- [ ] Make valid only letters in name
- [ ] Somehow make autotype to data (RTTI?)
- [ ] Add `E` notation to numbers
