# Streaming Handler

A simple command-line app to manage movies and TV shows you want to watch.

## Features

- Add movies or TV shows with the streaming platform
- View your watchlist
- Modify or delete entries

## Files

- **main.c** - Full version with add, view, modify, delete

## Compile & Run

```bash
gcc -o streaming_handler main.c
./streaming_handler
```

## How It Works

1. Choose from the menu (1=Add, 2=Modify/Delete, 0=Exit)
2. Select if it's a movie or TV show
3. Enter the streaming platform and item name
4. View your updated list

Each entry is stored as: `Platform: Item Name`

Example:
```
Netflix: Stranger Things
Disney+: The Mandalorian
HBO Max: Breaking Bad
```

## Author

Diego Gilabert