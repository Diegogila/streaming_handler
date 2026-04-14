#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// We're going to define the variables
bool is_on = true;
int movies_count = 0;
int series_count = 0;
int movie_or_serie;
int record_index;
int list_index;
char *movies[100], *series[100];



int main(){
    while (is_on)
    {
        int user_choise;
        char *user_input;
        printf("Bienvenido a tu gestor de Streaming.\n"
            "------------------------------------\n"
            "Estas son las peliculas y series que tienes pendientes por ver:\n\n"
            "Peliculas:\n");
        for (int i = 0; i < movies_count; i++)
        {
            if (movies_count == 0)
            {
                printf(" ");
            } else
                printf("%i.- %s\n", i+1, movies[i]);
        }
        printf("\nSeries:\n");
        for (int i = 0; i < series_count; i++)
        {
            if (series_count == 0)
            {
                printf(" ");
            } else
                printf("%i.- %s\n", i+1, series[i]);
        }
        printf("\n------------------------------------\n"
		"Porfavor seleccione una opcion:\n"
		"1.- Agregar pelicula o serie\n"
		"2.- Eliminar pelicula o serie\n"
		"0.- Cerrar programa\n\n");
        scanf("%d",&user_choise);
        switch (user_choise)
        {
            case 1:
                while (getchar() != '\n');
                char buffer[203];
                char streaming_platform[100];
                printf("------------------------------------\n"
                "¿En que plataforma esta?\n");
                fgets(streaming_platform, sizeof(streaming_platform), stdin);
                streaming_platform[strcspn(streaming_platform, "\n")] = 0;
                printf("------------------------------------\n"
                "¿Es una serie o pelicula?\n"
                "1.- Pelicula\n"
                "2.- Serie\n\n");
                scanf("%d",&user_choise);
                switch (user_choise)
                {
                case 1:
                    char movie[100];
                    printf("¿Cual es el nombre de la pelicula?\n");
                    while (getchar() != '\n');
                    fgets(movie, sizeof(movie), stdin);
                    movie[strcspn(movie, "\n")] = 0;
                    snprintf(buffer,sizeof(buffer),"%s: %s",streaming_platform,movie);
                    movies[movies_count] = strdup(buffer);
                    movies_count = movies_count+1;
                    printf("Pelicula agregada correctamente");
                    getchar();
                    break;
                case 2:
                    char serie[100];
                    printf("¿Cual es el nombre de la serie?\n");
                    while (getchar() != '\n');
                    fgets(serie, sizeof(serie), stdin);
                    serie[strcspn(serie, "\n")] = 0;
                    snprintf(buffer,sizeof(buffer),"%s: %s",streaming_platform,serie);
                    series[series_count] = strdup(buffer);
                    series_count = series_count+1;
                    printf("Serie agregada correctamente");
                    getchar();
                    break;
                default:
                    printf("Opcion invalida!");
                    getchar();
                    break;
                }
            break;
        case 2:
            printf("Elegiste eliminar pelicula");
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
                }
            break;
        case 0:
            is_on = false;
        default:
            printf("No has seleccionado una opcion valida");
            break;
        }
    }
    return 0;
}