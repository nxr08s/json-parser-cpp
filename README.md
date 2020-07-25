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

Here is transition table:

| State                 |      { 	 |     } 	|      [  	 |    ]    |   ,  |   :  |      " 	  | letter | number + - . | ws char |       \ 	  |      t 		|      f 	  |      n 		|
| :-------------------- | :--------: | :------: | :--------: | :-----: | :--: | :--: | :--------: | :--:   | :----------: | :-----: | :---------: | :---------: | :---------: | :---------: |
| **Initial state**     | 3 #push(2) | #2 		| 4 #push(2) | #2 	   | #2   | #2 	 | #2 		  | #2 	   | #2 		  | 		| #2 		  | #2 			| #2 		  | #2 			|
| **in Object**			| #3         | #ret 	| #3 		 | #3      | 	  | #3 	 | 5 #push(3) | #3 	   | #3 		  | 		| #3 		  | #3 			| #3 		  | #3 			|
| **in Array**          | 3 #push(4) | #4 		| 4 #push(4) | #ret    | 	  | #4 	 | 9 #push(4) | #4 	   | 9 #push(4)   | 		| #4 		  | 12 #push(4) | 13 #push(4) | 14 #push(4) |
| **in Name**           | 5          | 5 		| 5 		 | 5 	   | 5    | 5 	 | 6 		  | 5 	   | 5 			  | 5 		| 11 #push(5) | 5 			| 5 		  | 5 			|
| **in After name**     | #6 		 | #6 		| #6 		 | #6 	   | #6   | 7 	 | #6 		  | #6 	   | #6 	 	  | 		| #6 		  | #6 			| #6 		  | #6 			|
| **in Before value**   | 3 		 | #7 		| 4 		 | #7 	   | #7   | #7 	 | 9 	      | #7 	   | 8 			  | 		| #7 		  | 12 			| 13 		  | 14 			|
| **in Number**         | #8 		 |	#ret x2 | #8 		 | #ret x2 | #ret | #8 	 | #8 		  | #8 	   | 8 			  | 10 		| #8 		  | #8 			| #8 		  | #8 			|
| **in String**         | 9 		 | 9 		| 9 		 | 9 	   | 9 	  | 9 	 | 10 	 	  | 9 	   | 9 			  | 9 		| 11 #push(9) | 9 		    | 9 		  | 9 			|
| **in After Value**    | #10		 | #ret x2	| #10		 | #ret x2 | #ret | #10	 | #10		  | #10	   | #10		  |			| #10		  | #10			| #10		  | #10 		|
| **in Char escape**    | #ret		 | #ret		| #ret		 | #ret	   | #ret | #ret | #ret		  | #ret   | #ret		  | #ret	| #ret		  | #ret		| #ret		  | #ret 		|
| **in True**           | #12		 | #12		| #12		 | #12	   | #12  | #12	 | #12		  | #12	   | #12		  | 		| #12		  | #12		    | #12		  | #12 		|
| **in False**          | #13		 | #13		| #13		 | #13	   | #13  | #13	 | #13 		  | #13	   | #13		  | 		| #13		  | #13		    | #13		  | #13 		|
| **in Null**           | #13		 | #13 		| #13		 | #13	   | #13  | #13	 | #13 	 	  | #13	   | #13		  | 		| #13		  | #13		    | #13		  | #13 		|


### Todo:
- [ ] Make valid only letters in name
