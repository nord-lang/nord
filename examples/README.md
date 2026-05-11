# Nord Language Examples

## Basic Stream Processing

```nord
# Process even numbers from 1-100
stream evens = range(1, 100)
    |> filter(|x| x % 2 == 0)
    |> map(|x| x * 2)
```

## Actor Example

```nord
actor Counter {
    let mut count: i64 = 0
    
    pub fn inc(&mut self) -> i64 {
        self.count += 1
        self.count
    }
}
```

## Channel Communication

```nord
chan<i32> numbers = chan::new()

actor worker {
    fn process(c: chan<i32>) {
        loop {
            let val = c.recv()
            print(val)
        }
    }
}
```