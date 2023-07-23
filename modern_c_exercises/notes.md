# Enumeration
## Ability to name small integers

```c
enum corvid { magpie, raven, jay, chough, corvid_num, };
char const*const bird[corvid_num] = {
    [chough] = "chough",
    [raven] = "raven",
    [magpie] = "magpie",
    [jay] = "jay",
};
```

Particularly useful for dealing with string literals.  
Anytime you need to deal with named things, putting them into an array and identifiying them with an enum is fantastic.  
A sort of side thing that is useful to note is that, when you enumerate them this way you do not have to keep track of the indices.  

# Compound Literals
## Use of macro to define a type

```c
# define CORVID_NAME /**/ \
(char const*const[corvid_num]){ \
[chough] = "chough", \
[raven] = "raven", \
[magpie] = "magpie", \
[jay] = "jay", \
}
```

**NO ; AFTER MACRO, ITS JUST TEXT REPLACEMENT**  

"There must be space between the macro name and the () of the compound literal, here indicated by the /**/ comment. Otherwise, this would be interpreted as the start of a definition of a function-like macro."  


