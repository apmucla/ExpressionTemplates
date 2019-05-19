# Expression Templates
A brief exploration into expression templates. Please note that the code provided here is only a partial implementation of what would be needed for a minimially-complete library for vector arithemtic. I do not provide the code I wrote to generate the comparison timings between using expression templates and not. 

## Summary

The slides I created for presenting this topic can be found [here](https://docs.google.com/presentation/d/1WG5CnyspITbZEYCSgYHYMcLHg37DWYNNGgHdPCDOCLI/edit?usp=sharing).

The motivation for the use of expression templates is to write code in such a way so that the compiler can understand expressions, e.g. mathematical vector expressions, at compile time to achieve efficient evaluation. The example I gave in the presentation is as follows. Consider the following snippet of code 

```c++
int main() {
    // Vectors are size 10^7
    Vector<double> y = a1 + a2 + a3 + a4 + a5;
}
```

In a naive implementation of the `Vector<T>` class, evaluating that line would call the copy constructor of `Vector<double>` five times, along with looping through the length of a vector five times. If move semantics are used correctly, then only one copy needs to be made, but four loops are still required to perform the vector additions. However, we know that only one loop is needed, like so:

```c++
int main() {
    constexpr size_t N = 10000000;    // size = 10^7
    Vector<double> y(N);
    for (size_t i = 0; i < N; ++i) {
        y[i] = a1[i] + a2[i] + a3[i] + a4[i] + a5[i];
    }
}
```

Using expression templates, this is achievable without complicating client code! In other words, with the structure of expression templates, the compiler will be able to evaluate 

```c++
Vector<double> y = a1 + a2 + a3 + a4 + a5;
```

exactly like the code snippet above with one for loop. I forgot to report on this in my presentation, but based on my timing results, ***the performance of vector arithmetic using expression templates is exactly on par with writing out the for loop ourselves***.

## Files in this repo

| File | Description |
|------|-------------|
| `Stopwatch.h` | Class I used to time all of my code |
| `Types.h` | Provides auxiliary functionality |
| `Vector.h` | Self-contained vector class (one only needs to include this file) |
| `VectorExpression.h` | Implementation of the vector expression templates |


