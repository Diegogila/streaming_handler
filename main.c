/*
 * =============================================================================
 * PROJECT: Streaming Content Manager
 * =============================================================================
 * PURPOSE: 
 *   A command-line application to manage movies and TV shows in a watchlist.
 *   Users can add, modify, and delete items with their associated streaming
 *   platforms.
 * 
 * FEATURES:
 *   - Add movies or TV shows with their streaming platform
 *   - View lists of all movies and TV shows
 *   - Modify existing entries
 *   - Delete entries from the watchlist
 *   - Persistent menu-driven interface
 * 
 * AUTHOR: Diego Gilabert
 * DATE: 04/15/2026
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <regex.h>

/* ==================== GLOBAL VARIABLES ==================== */
bool is_on = true;                           /* Control flag for main program loop */
int movies_count = 0;                        /* Counter for number of movies added */
int tv_shows_count = 0;                      /* Counter for number of TV shows added */
char *movies[100], *tv_shows[100];          /* Arrays to store movie and TV show pointers (max 100 each) */

/* ==================== FUNCTION DECLARATIONS ==================== */

/**
 * show_items()
 * 
 * DESCRIPTION:
 *   Displays all items from a provided list to the console.
 *   If the list is empty, displays a message indicating no items are available.
 * 
 * PARAMETERS:
 *   list[in]  - Pointer to array of strings containing item names
 *   count[in] - Number of items in the list
 * 
 * RETURN: void
 */
void show_items(char **list, int count);

/**
 * movie_or_tv_show()
 * 
 * DESCRIPTION:
 *   Prompts user to choose between adding/modifying/deleting a movie or TV show.
 *   Displays selection menu and returns user's choice.
 * 
 * PARAMETERS: none
 * 
 * RETURN: int - 1 for movie, 2 for TV show
 */
int movie_or_tv_show();

/**
 * add_item()
 * 
 * DESCRIPTION:
 *   Prompts user to enter streaming platform and item name.
 *   Creates a new string combining both values and allocates memory for it.
 *   Format: "Platform: Item Name"
 * 
 * PARAMETERS:
 *   kind_item[in] - Type of item ("pelicula" for movie or "serie" for TV show)
 * 
 * RETURN: char* - Dynamically allocated string with the new item data
 */
char *add_item(char *kind_item);

/**
 * modify_item()
 * 
 * DESCRIPTION:
 *   Allows user to select and modify an existing item from the list.
 *   User selects by index and can change the item details.
 * 
 * PARAMETERS:
 *   list[in/out]     - Array of items to modify
 *   count[in/out]    - Pointer to the count of items in the list
 *   kind_item[in]    - Type of item being modified
 * 
 * RETURN: void
 */
void modify_item(char **list, int *count, char *kind_item);

/**
 * delete_item()
 * 
 * DESCRIPTION:
 *   Allows user to select and delete an item from the list by index.
 *   Removes the selected item and updates the item count.
 * 
 * PARAMETERS:
 *   list[in/out]     - Array of items to delete from
 *   count[in/out]    - Pointer to the count of items in the list
 *   kind_item[in]    - Type of item being deleted
 * 
 * RETURN: void
 */
void delete_item(char **list, int *count, char *kind_item);




/**
 * validate_format()
 * 
 * DESCRIPTION:
 *   Validates whether a given string follows the expected format.
 *   Typically checks that the string contains valid content such as
 *   "Platform: Item Name" and is not empty or malformed.
 * 
 * PARAMETERS:
 *   str[in] - String to validate
 * 
 * RETURN:
 *   int - Returns 1 if the format is valid, 0 otherwise
 */
int validate_format(char *str);

/**
 * get_data()
 * 
 * DESCRIPTION:
 *   Reads data from a file corresponding to the given item type and
 *   loads it into the provided list. Each valid line from the file
 *   is stored as a dynamically allocated string in the list.
 *   Updates the count of items loaded.
 * 
 * PARAMETERS:
 *   kind_items[in]   - Type of items (used to determine file name)
 *   list[in/out]     - Array of strings where data will be stored
 *   count[in/out]    - Pointer to the number of items in the list
 * 
 * RETURN: void
 */
void get_data(char *kind_items, char **list, int *count);

/**
 * save_data()
 * 
 * DESCRIPTION:
 *   Writes all items from the provided list into a file corresponding
 *   to the given item type. Each item is written as a new line in the file,
 *   ensuring proper formatting and persistence of data.
 * 
 * PARAMETERS:
 *   kind_items[in] - Type of items (used to determine file name)
 *   list[in]       - Array of strings containing the items to save
 *   count[in]      - Number of items in the list
 * 
 * RETURN: void
 */
void save_data(char *kind_items, char **list, int count);

/**
 * main()
 * 
 * DESCRIPTION:
 *   Entry point of the application. Implements the main menu loop where users
 *   can navigate through options to add, modify, or delete movies and TV shows.
 *   The loop continues until the user chooses to exit (option 0).
 * 
 * LOGIC:
 *   1. Display current lists of movies and TV shows
 *   2. Show main menu with available options
 *   3. Process user selection (1=Add, 2=Modify, 3=Delete, 0=Exit)
 *   4. Execute corresponding operation
 *   5. Repeat until user exits
 * 
 * RETURN: int - Always returns 0 (success)
 */
int main(){
    get_data("movies", movies, &movies_count);
    get_data("tv_shows", tv_shows, &tv_shows_count);
    while (is_on) /* Main program loop - continues while is_on is true */
    {
        int user_choise;
        
        /* Display the main menu with current lists */
        printf("***********************************\n"
            "Bienvenido a tu gestor de Streaming.\n"
            "------------------------------------\n"
            "Estas son las peliculas y series que tienes pendientes por ver:\n\n"
            "Peliculas:\n");
        show_items(movies,movies_count);
        printf("\nSeries:\n");
        show_items(tv_shows,tv_shows_count);
        printf("\n\n------------------------------------\n"
		    "Porfavor seleccione una opcion:\n\n"
		    "1.- Agregar pelicula o serie\n"
            "2.- Modificar pelicula o serie\n"
		    "3.- Eliminar pelicula o serie\n"
		    "0.- Cerrar programa\n\n");
        scanf("%d",&user_choise);
        printf("***********************************\n");
        
        /* Process user choice */
        switch (user_choise)
        {
            case 1:
            /* OPERATION 1: Add a new movie or TV show */
                printf("***********************************\n"
                       "Agregar pelicula o serie\n"
                       "------------------------------------\n");
                user_choise = movie_or_tv_show();
                printf("***********************************\n");
                
                /* Sub-menu to select movie or TV show */
                switch (user_choise){
                case 1:
                    movies[movies_count] = add_item("pelicula");
                    (movies_count)++;
                    break;
                case 2:
                    tv_shows[tv_shows_count] = add_item("serie");
                    (tv_shows_count)++;
                    break;
                default:
                    printf("Seleccion invalida\n");
                    break;
                }
            break;
            case 2:
            /* OPERATION 2: Modify an existing movie or TV show */
                printf("***********************************\n"
                       "Modificar pelicula o serie\n"
                       "------------------------------------\n");
                user_choise = movie_or_tv_show();
                printf("***********************************\n");
                switch (user_choise){
                case 1:
                    modify_item(movies, &movies_count, "pelicula");
                    break;
                case 2:
                    modify_item(tv_shows, &tv_shows_count, "serie");
                    break;
                default:
                    printf("Seleccion invalida\n");
                    break;
                }
            break;
            case 3:
            /* OPERATION 3: Delete a movie or TV show from the lists */
                printf("***********************************\n"
                       "Eliminar pelicula o serie\n"
                       "------------------------------------\n");
                user_choise = movie_or_tv_show();
                printf("***********************************\n");
                switch (user_choise)
                {
                case 1:
                    delete_item(movies, &movies_count, "peliculas");
                    break;
                case 2:
                    delete_item(tv_shows, &tv_shows_count, "series");
                    break;
                default:
                    printf("Seleccion invalida\n");
                    break;
                }
            case 0:
                is_on = false;
                break;
            default:
                printf("No has seleccionado una opcion valida\n");
                break;
            }
    }
    save_data("movies", movies, movies_count);
    save_data("tv_shows", tv_shows, tv_shows_count);
    return 0;
}

/* ==================== FUNCTION IMPLEMENTATIONS ==================== */

/**
 * validate_format() [DECLARATION]
 * 
 * Validates whether a given string follows the expected format.
 * Ensures the string is not empty and matches the required structure.
 */
int validate_format(char *str){
    regex_t regex;
    int result;

    regcomp(&regex, "^[^:]+: [^:]+$", REG_EXTENDED);
    result = regexec(&regex, str, 0, NULL, 0);
    regfree(&regex);

    return result == 0;
}

/**
 * save_data() [DECLARATION]
 * 
 * Saves all items from the given list into a file corresponding to
 * the specified item type, writing each item on a new line.
 */
void save_data(char *kind_item, char **list, int count){
    char filename[100];
    sprintf(filename, "%s.txt", kind_item);
    FILE *file = fopen(filename, "w");

    if(file == NULL){
        printf("No se pudo leer el archivo\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if(validate_format(list[i])){
            fprintf(file, "%s\n", list[i]);
        } else printf("Formato incorrecto, no se puede guardar");
    }

    fclose(file);
    return;
}

/**
 * get_data() [DECLARATION]
 * 
 * Reads data from a file based on the item type and loads it into
 * the provided list, updating the item count.
 */
void get_data(char *kind_item, char **list, int *count){
    char filename[100];
    sprintf(filename, "%s.txt", kind_item);
    FILE *file = fopen(filename, "r");

    if(file == NULL){
        return ;
    }

    char line[100];

    while(fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = 0;
        list[*count] = malloc(strlen(line) + 1);
        strcpy(list[*count], line);
        (*count)++;
    }

    fclose(file);
    return;


}

/**
 * movie_or_tv_show() [IMPLEMENTATION]
 * 
 * Displays a menu asking the user to choose between a movie or TV show,
 * captures input, and returns the selection.
 */
int movie_or_tv_show()
{
    int user_choise;
    printf("¿Es una serie o pelicula?\n"
           "1.- Pelicula\n"
           "2.- Serie\n\n");
    scanf("%d", &user_choise);
    return user_choise;
};

/**
 * show_items() [IMPLEMENTATION]
 * 
 * Iterates through the provided list and prints each item with its index.
 * If the list is empty, displays a message indicating no items are available.
 */
void show_items(char **list, int count)
{
    if (count == 0)
    {
        printf("(No hay elementos disponibles)");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        printf("%i.- %s\n", i + 1, list[i]);
    }
    return;
}

char *add_item(char *kind_item){
    while (getchar() != '\n');  /* Clear input buffer of leftover characters */
    char buffer[203];           /* Temporary buffer to store the combined string */
    char streaming_platform[100];  /* Buffer to store streaming platform name */
    char item[100];             /* Buffer to store item name */
    
    /* Prompt and collect streaming platform information */
    printf("------------------------------------\n"
    "¿En que plataforma esta?:\n");
    fgets(streaming_platform, sizeof(streaming_platform), stdin);
    streaming_platform[strcspn(streaming_platform, "\n")] = 0;  /* Remove trailing newline */
    
    /* Prompt and collect item name */
    printf("Nombre de la %s:\n", kind_item);
    fgets(item, sizeof(item), stdin);
    item[strcspn(item, "\n")] = 0;  /* Remove trailing newline */
    
    /* Create the combined string in format "Platform: Item" */
    snprintf(buffer, sizeof(buffer), "%s: %s", streaming_platform, item);
    
    /* Return dynamically allocated copy of the buffer */
    return strdup(buffer);
}

/**
 * modify_item() [IMPLEMENTATION]
 * 
 * Displays the list of items and allows user to select one to modify.
 * Prompts for new information and updates the selected item.
 */
void modify_item(char **list, int *count,char *kind_item){
    int user_choise;
    printf("------------------------------------\n");
    printf("Estas son las %ss disponibles:\n", kind_item);
    show_items(list, *count);
    printf("------------------------------------\n"
           "Digite el numero que desea modificar\n");
    scanf("%d", &user_choise);
    int index = user_choise - 1;
    printf("Ha seleccionado %s\n", list[index]);
    list[index] = add_item(kind_item);  /* Replace with new item information */
    return;
};

/**
 * delete_item() [IMPLEMENTATION]
 * 
 * Displays the list of items and allows user to select one to delete.
 * Removes the selected item from the list by shifting remaining items
 * and decrements the count. Validates user input before deletion.
 */
void delete_item(char **list, int *count, char *kind_item)
{
    int user_choise;
    printf("------------------------------------\n");
    printf("Estas son las %s disponibles:\n", kind_item);
    show_items(list, *count);
    printf("------------------------------------\n"
           "Digite el numero que desea eliminar\n");
    scanf("%d", &user_choise);
    int index = user_choise - 1;
    /* Validate that the selected index is within valid range */
    if (user_choise > 0 && user_choise <= *count)
    {
        /* Shift all items after the deleted item one position to the left */
        for (int i = index; i < *count - 1; i++)
        {
            list[i] = list[i + 1];
        }
        (*count)--;  /* Decrement the item count */
        printf("Seleccion eliminada correctamente");
        getchar();
    }
    else
        printf("Seleccion invalida");
    return;
}