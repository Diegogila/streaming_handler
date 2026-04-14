#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// We're going to define the variables
bool is_on = true;
int movies_count = 2;
int series_count = 2;
//char *movies[100], *series[100];
char *movies[100] = {"Pelicula1", "Pelicula2"};
char *series[100] = {"Serie1", "Serie2"};

void show_items(char **list, int count);
void add_item(char **list, int *count);
void delete_item(char **list, int *count, char *kind_item);


int main(){
    while (is_on)
    {
        int user_choise;
        printf("Bienvenido a tu gestor de Streaming.\n"
            "------------------------------------\n"
            "Estas son las peliculas y series que tienes pendientes por ver:\n\n"
            "Peliculas:\n");
        show_items(movies,movies_count);
        printf("\nSeries:\n");
        show_items(series,series_count);
        printf("\n------------------------------------\n"
		    "Porfavor seleccione una opcion:\n"
		    "1.- Agregar pelicula o serie\n"
		    "2.- Eliminar pelicula o serie\n"
		    "0.- Cerrar programa\n\n");
        scanf("%d",&user_choise);
        switch (user_choise)
        {
            case 1:
                printf("------------------------------------\n"
                       "¿Es una serie o pelicula?\n"
                       "1.- Pelicula\n"
                       "2.- Serie\n\n");
                scanf("%d", &user_choise);
                switch (user_choise){
                case 1:
                    add_item(movies, &movies_count);
                    break;
                case 2:
                    add_item(series, &series_count);
                    break;
                default:
                    break;
                }
            break;
            case 2:
                printf("------------------------------------\n"
                       "¿Es una serie o pelicula?\n"
                       "1.- Pelicula\n"
                       "2.- Serie\n\n");
                scanf("%d", &user_choise);
                switch (user_choise)
                {
                case 1:
                    delete_item(movies, &movies_count, "peliculas");
                    break;
                case 2:
                    delete_item(series, &series_count, "series");
                    break;
                default:
                    break;
                }
                /*printf("Elegiste eliminar pelicula");
                printf("------------------------------------\n"
                    "¿Es una serie o pelicula?\n"
                    "1.- Pelicula\n"
                    "2.- Serie\n\n");
                    scanf("%d",&user_choise);
                    switch (user_choise)
                    {
                        case 1:
                            printf("Digite el numero de pelicula que desea eliminar\n");
                            scanf("%d",&user_choise);
                            if(user_choise>0 && user_choise <= movies_count){
                                for (int i = user_choise; i < movies_count-1; i++)
                                {
                                    movies[i] = movies[i+1];
                                }
                                movies_count = movies_count-1;
                                printf("Pelicula eliminada correctamente");
                                getchar();
                            }
                            break;
                        case 2:
                            printf("Digite el numero de serie que desea eliminar\n");
                            scanf("%d",&user_choise);
                            if(user_choise>0 && user_choise <= series_count){
                                for (int i = user_choise; i < series_count-1; i++)
                                {
                                    series[i] = series[i+1];
                                }
                                series_count = series_count-1;
                                printf("Serie eliminada correctamente");
                                getchar();
                            }
                            break;
                        default:
                            printf("Opcion invalida!");
                            getchar();
                            break;
                    }*/
                break;
            case 0:
                is_on = false;
                break;
            default:
                printf("No has seleccionado una opcion valida");
                break;
            }
    }
    return 0;
}

void show_items(char **list, int count)
{
    if (count == 0)
    {
        printf("No hay elementos");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        printf("%i.- %s\n", i + 1, list[i]);
    }
}

void add_item(char **list,int *count){
    while (getchar() != '\n');
    char buffer[203];
    char streaming_platform[100];
    char item[100];
    printf("------------------------------------\n"
    "¿En que plataforma esta?:\n");
    fgets(streaming_platform, sizeof(streaming_platform), stdin);
    streaming_platform[strcspn(streaming_platform, "\n")] = 0;
    printf("Nombre:\n");
    fgets(item, sizeof(item), stdin);
    item[strcspn(item, "\n")] = 0;
    snprintf(buffer, sizeof(buffer), "%s: %s", streaming_platform, item);
    list[*count] = strdup(buffer);
    (*count)++;
    printf("Pelicula agregada correctamente");
    getchar();
}

void delete_item(char **list, int *count, char *kind_item)
{
    int user_choise;
    printf("Elegiste eliminar %s\n", kind_item);
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
            movies[i] = movies[i + 1];
        }
        (*count)--;
        printf("Seleccion eliminada correctamente");
        getchar();
    }
    else
        printf("Seleccion invalida");
    return;
}