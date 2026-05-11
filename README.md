# Nord Language

Compiled language for distributed systems and microservices.

## Goals
- No GC, use arena allocation for minimum latency
- Actor model for distributed concurrency
- Native reactive streams for data processing
- Compile to native code via LLVM

## Example

```nord
actor Counter {
    let mut count: i64 = 0
    
    pub fn inc(&mut self) -> i64 {
        self.count += 1
        self.count
    }
}

stream numbers = range(1, 100)
    |> filter(|x| x % 2 == 0)
    |> map(|x| x * 2)
```

## Building
```
make
```