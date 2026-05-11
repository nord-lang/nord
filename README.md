# Nord Language (.no)

Compiled language for distributed systems and microservices.

## Features
- **No GC** - Arena allocation for zero-latency memory management
- **Actors** - Native actor model with typed channels
- **Streams** - Built-in reactive data processing
- **Static types** - Compile-time safety with type inference

## Language Elements

### Actors
```nord
actor Counter {
    let mut count: i64 = 0
    
    pub fn inc(&mut self) -> i64 {
        self.count += 1
        self.count
    }
}
```

### Streams
```nord
stream numbers = range(1, 100)
    |> filter(|x| x % 2 == 0)
    |> map(|x| x * 2)
```

### Channels
```nord
chan<String> messages = chan::new()
spawn worker(messages)
```

## Building
```
make
```

## Installation

### From Release (Recommended)
```bash
curl -fsSL https://raw.githubusercontent.com/nord-lang/nord/main/install.sh | bash
```

Or download from [Releases](https://github.com/nord-lang/nord/releases).

### Manual Build
```bash
git clone https://github.com/nord-lang/nord.git
cd nord
make
sudo cp nordvm /usr/local/bin/
```

## Usage

```bash
# Run a Nord file
nordvm script.no

# Start REPL
nordvm -repl
```

## Architecture
- Lexer → Parser → AST → LLVM IR → Native binary