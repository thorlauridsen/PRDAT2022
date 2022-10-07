# Assignment 5

## Exercise 5.1
F# implementation:
Can be found in `Exercises.fs`
```
let merge (lst1, lst2) = List.sort (lst1 @ lst2)
```

C# implementation:
Can be found in `Exercise5_1\Exercise5_1\Program.cs`
```
static int[] merge(int[] xs, int[] ys){
    int[] rs = new int[xs.Length+ys.Length];
    int ri = 0;
    int xi = 0;
    int yi = 0;

    while(xi < xs.Length || yi < ys.Length){
        if(xi < xs.Length && yi < ys.Length){
            if(xs[xi] < ys[yi]){
                rs[ri] = xs[xi];
                xi++;
            } else {
                rs[ri] = ys[yi];
                yi++;
            }
        } else if (xi < xs.Length) {
            rs[ri] = xs[xi];
            xi++;
        } else {
            rs[ri] = ys[yi];
            yi++;
        }
        ri++;
    }
    return rs;
}

public static void Main(string[] args){
    int[] xs = { 3, 5, 12 };
    int[] ys = { 2, 3, 4, 7 };
    Console.WriteLine(String.Join(", ", merge(xs,ys)));
}
```

## Exercise 5.7
Unfinished

## Exercise 6.1
```
let add x = let f y = x+y in f end
  in let addtwo = add 2
    in let x = 77 in addtwo 5 end
  end
end
```
Yes it is expeected
x is already defined in `addtwo = add 2`
So `let x = 77` has no effect

```
let add x = let f y = x+y in f end
in add 2 end
```
Since we only give the function one actual argument but expects 2, it returns a function.

![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec05/Images/Ex61.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec05/Images/Ex61b.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec05/Images/Ex61c.png?raw=true)

## Exercise 6.2
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec05/Images/Ex62.png?raw=true)

## Exercise 6.3
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec05/Images/Ex63.png?raw=true)

## Exercise 6.4

## Exercise 6.5
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec05/Images/Ex65a.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec05/Images/Ex65b.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec05/Images/Ex65c.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec05/Images/Ex65d.png?raw=true)
![](https://github.com/REXKrash/PRDAT2022/blob/main/Lectures/Lec05/Images/Ex65e.png?raw=true)
