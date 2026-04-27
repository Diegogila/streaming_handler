# Streaming Manager

A command-line application written in C to manage movies and TV shows in a personal watchlist with file persistence.

---

## Features

- Add movies or TV shows with their streaming platform  
- View your watchlist (movies and series separately)  
- Modify existing entries  
- Delete entries  
- Data persistence using text files (`.txt`)  
- Input validation to ensure consistent format  
- Automatic loading of saved data on startup  

---

## Project Structure

- **main.c** — Main application with all features implemented  
- **movies.txt** — Stores saved movies  
- **tv_shows.txt** — Stores saved TV shows  

---

## Compile & Run

gcc -o streaming_manager main.c
./streaming_manager

---

## How It Works

1. When the program starts, it loads saved data from files  
2. The main menu is displayed:
   - `1` → Add item  
   - `2` → Modify item  
   - `3` → Delete item  
   - `0` → Exit  
3. Choose whether the item is a movie or TV show  
4. Enter:
   - Streaming platform  
   - Item name  
5. The item is stored in memory and saved to file  

---

## Data Format

Each entry is stored as: `Platform: Item Name`

Example:
```
Netflix: Stranger Things
Disney+: The Mandalorian
HBO Max: Breaking Bad
```


---

## Data Persistence

- Data is stored in plain text files:
  - `movies.txt`
  - `tv_shows.txt`
- Each item is saved on a new line  
- Empty lines are ignored when reading  
- Data is automatically saved when the program exits  

---

## Input Validation
 
- Ensures correct format (`Platform: Item Name`)  
- Avoids corrupted or malformed data  

---

## Author

Diego Gilabert  


## Author

Diego Gilabert