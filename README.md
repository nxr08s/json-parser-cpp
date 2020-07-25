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

| State | { |
