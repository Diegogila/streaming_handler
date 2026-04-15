#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// We're going to define the variables
bool is_on = true;
int movies_count = 0;
int series_count = 0;
char *movies[100], *series[100];

void show_items(char **list, int count);
char *add_item(char *kind_item);
void modify_item(char **list, int *count, char *kind_item);
void delete_item(char **list, int *count, char *kind_item);


int main(){
    while (is_on)
    {
        int user_choise;
        printf("***********************************\n"
            "Bienvenido a tu gestor de Streaming.\n"
            "------------------------------------\n"
            "Estas son las peliculas y series que tienes pendientes por ver:\n\n"
            "Peliculas:\n");
        show_items(movies,movies_count);
        printf("\nSeries:\n");
        show_items(series,series_count);
        printf("\n------------------------------------\n"
		    "Porfavor seleccione una opcion:\n\n"
		    "1.- Agregar pelicula o serie\n"
            "2.- Modificar pelicula o serie\n"
		    "3.- Eliminar pelicula o serie\n"
		    "0.- Cerrar programa\n\n");
        scanf("%d",&user_choise);
        printf("***********************************\n");
        switch (user_choise)
        {
            case 1:
                printf("***********************************\n"
                       "Agregar pelicula o serie\n"
                       "------------------------------------\n"
                       "¿Es una serie o pelicula?\n"
                       "1.- Pelicula\n"
                       "2.- Serie\n\n");
                scanf("%d", &user_choise);
                printf("***********************************\n");
                switch (user_choise){
                case 1:
                    movies[movies_count] = add_item("pelicula");
                    (movies_count)++;
                    break;
                case 2:
                    series[series_count] = add_item("serie");
                    (series_count)++;
                    break;
                default:
                    printf("Seleccion invalida\n");
                    break;
                }
            break;
            case 2:
                printf("***********************************\n"
                       "Modificar pelicula o serie\n"
                       "------------------------------------\n"
                       "¿Es una serie o pelicula?\n"
                       "1.- Pelicula\n"
                       "2.- Serie\n\n");
                scanf("%d", &user_choise);
                printf("***********************************\n");
                switch (user_choise){
                case 1:
                    modify_item(movies, &movies_count, "pelicula");
                    break;
                case 2:
                    modify_item(series, &series_count, "serie");
                    break;
                default:
                    printf("Seleccion invalida\n");
                    break;
                }
            break;
            case 3:
                printf("***********************************\n"
                       "Eliminar pelicula o serie\n"
                       "------------------------------------\n"
                       "¿Es una serie o pelicula?\n"
                       "1.- Pelicula\n"
                       "2.- Serie\n\n");
                scanf("%d", &user_choise);
                printf("***********************************\n");
                switch (user_choise)
                {
                case 1:
                    delete_item(movies, &movies_count, "peliculas");
                    break;
                case 2:
                    delete_item(series, &series_count, "series");
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
    return 0;
}

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
    while (getchar() != '\n');
    char buffer[203];
    char streaming_platform[100];
    char item[100];
    printf("------------------------------------\n"
    "¿En que plataforma esta?:\n");
    fgets(streaming_platform, sizeof(streaming_platform), stdin);
    streaming_platform[strcspn(streaming_platform, "\n")] = 0;
    printf("Nombre de la %s:\n", kind_item);
    fgets(item, sizeof(item), stdin);
    item[strcspn(item, "\n")] = 0;
    snprintf(buffer, sizeof(buffer), "%s: %s", streaming_platform, item);
    return strdup(buffer);
}

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
    list[index] = add_item(kind_item);
    return;
};

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
    if (user_choise > 0 && user_choise <= *count)
    {
        for (int i = index; i < *count - 1; i++)
        {
            list[i] = list[i + 1];
        }
        (*count)--;
        printf("Seleccion eliminada correctamente");
        getchar();
    }
    else
        printf("Seleccion invalida");
    return;
}