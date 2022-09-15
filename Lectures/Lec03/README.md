# Answers

## PLC 3.3

`let z = (17) in z + 2 * 3 end EOF`

`Let ("z", CstI 17, Prim ("+", Var "z", Prim ("*", CstI 2, CstI 3)))`


| Main                                                                     | Rule |
| ------------------------------------------------------------------------ | ---- |
| => Expr EOF                                                              | A    |
| => LET NAME EQ Expr IN Expr END EOF                                      | F    |
| => LET NAME EQ Expr IN Expr TIMES Expr END EOF                           | G    |
| => LET NAME EQ Expr IN Expr TIMES CSTINT END EOF                         | C    |
| => LET NAME EQ Expr IN Expr PLUS Expr TIMES CSTINT END EOF               | H    |
| => LET NAME EQ Expr IN Expr PLUS CSTINT TIMES CSTINT END EOF             | C    |
| => LET NAME EQ Expr IN NAME PLUS CSTINT TIMES CSTINT END EOF             | B    |
| => LET NAME EQ LPAR Expr RPAR IN NAME PLUS CSTINT TIMES CSTINT END EOF   | E    |
| => LET NAME EQ LPAR CSTINT RPAR IN NAME PLUS CSTINT TIMES CSTINT END EOF | C    |

## PLC 3.4
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Diagrams/Exercise3_4.jpg?raw=true)


## PLC 3.5
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Images/fromString1.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Images/fromString2.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Images/fromString3.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Images/fromString4.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Images/fromString5.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Images/fromString6.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Images/fromString7.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Images/fromString8.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Images/fromString9.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec03/Images/fromString10.png?raw=true)



