/*! \file main.c
 *  \brief Definitions for main function.
 *
 */


#include <assert.h>
#include <termios.h>
#include <signal.h>
#include <errno.h>
#include <video.h>
   
typedef enum
{
    ADD=1,
    DISPLAY,
    FIND_BY_FILMNAME,
    EDIT,
    DELETE
} option_t;

struct termios saved_term;

static int login( void );
static void restore_terminal( void );
static void sigint_handler( int sig );

int main( int argc, char *argv[ ] )
{
    if( login( ) == 1 )
    {
        int option;

        do {
            printf( "\
            [1] Add new entry\n\
            [2] Display a list of all entries\n\
            [3] Find entries by film name\n\
            [4] Edit an entry\n\
            [5] Delete an entry\n\
            [0] Exit\n\
            --> " );
            scanf( "%d", &option );
            while( getchar( ) != '\n' );

            switch( option )
            {
                case ADD:
                {
                    video_t video;
                    unsigned int c;

                    printf("Please enter the film name: ");
                    scanf("%s", video.film_name);
        
                    printf("Please enter the production co: ");
                    scanf("%s", video.production_co);

                    printf("Please enter the director: ");
                    scanf("%s", video.director);
        
                    printf("Please enter the stars: ");
                    scanf("%s", video.stars);

                    printf("Please enter the language: ");
                    scanf("%s", video.language);
        
                    printf("Please enter the runtime: ");
                    scanf("%s", video.runtime);

                    printf("Please enter the country: ");
                    scanf("%s", video.country);
        
                    printf("Please enter the release date: ");
                    scanf("%s", video.release_date);

                    printf("Please enter the story_line: ");
                    scanf("%s", video.story_line);
        
                    if(!add_entry(db, &video)) 
                    {
                        perror ("Error on add entry\n");
                        printf( "Value of errno: %d\n", errno );           
                    }//End if
                    
                    c = display_entries(db);
                    if (c == 0)
                    {
                        printf( "There are no entries found\n" );
                        break; 
                    }else{
                        printf( "There are %d entries found\n", c );
                    }
                    putc('\n', stdout);

                    } break;//End add case
                case DISPLAY:
                    {
                    unsigned int c; 

                    c = display_entries(db);
                    if (c == 0)
                    {
                        printf( "There are no entries found\n" );
                        break; 
                    }else{
                        printf( "There are %d entries found\n", c );
                    }
                    putc('\n', stdout);

                    } break;//End display case
                case FIND_BY_FILMNAME:
                    {
                    char film_name[ MAXLENGTH ];
                    video_t video;
                    int next_option;
                    unsigned int c;

                    printf( "Enter film name: " );
                    scanf( "%[^\n]", film_name );
                    while( getchar( ) != '\n' );

                    c = find_entry(db, film_name);
                    if ( c == 0 )
                    {
                        printf( "There are no entries found\n" );
                        break; 
                    }else{
                        printf( "There are %d entries found\n", c );
                    }//End if

                    do 
                    {
                        printf( "\
                        [1] Edit entry\n\
                        [2] Delete entry\n\
                        [0] Exit\n\
                        --> " );
                        scanf( "%d", &next_option );
                        while( getchar( ) != '\n' );

                        switch( next_option )
                        {
                         case 1:
                             {
                              int field_option;
                              unsigned int index;

                              do 
                              {
                               printf( "Enter index from list: " );
                               scanf( "%d", &index );
                              } while( getchar( ) != '\n' );

                              do 
                              {
                               printf( "\
                               What field to wish to edit?\n\
                               [1] Film name\n\
                               [2] Production co\n\
                               [3] Director\n\
                               [4] Stars\n\
                               [5] Language\n\
                               [6] Runtime\n\
                               [7] Country\n\
                               [8] Release date\n\
                               [9] Story line\n\
                               [0] Exit\n\
                               --> " );
                               scanf( "%d", &field_option );
                               while( getchar( ) != '\n' );

                               switch( field_option )
                               {
                                case 1:
                                    {
                                     printf("Please enter the film name: ");
                                     scanf("%s", video.film_name);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit film name entry\n");
                                     }else{
                                         perror ("Error on edit film name entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 2:
                                    {
                                     printf("Please enter the production co: ");
                                     scanf("%s", video.production_co);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit production co entry\n");
                                     }else{
                                         perror ("Error on edit production co entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 3:
                                    {
                                     printf("Please enter the director: ");
                                     scanf("%s", video.director);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit director entry\n");
                                     }else{
                                         perror ("Error on edit director entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 4:
                                    {
                                     printf("Please enter the stars: ");
                                     scanf("%s", video.stars);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit stars entry\n");
                                     }else{
                                         perror ("Error on edit stars entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 5:
                                    {
                                     printf("Please enter the language: ");
                                     scanf("%s", video.language);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit language entry\n");
                                     }else{
                                         perror ("Error on edit language entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 6:
                                    {
                                     printf("Please enter the runtime: ");
                                     scanf("%s", video.runtime);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit runtime entry\n");
                                     }else{
                                         perror ("Error on edit runtime entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 7:
                                    {
                                     printf("Please enter the country: ");
                                     scanf("%s", video.country);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit country entry\n");
                                     }else{
                                         perror ("Error on edit country entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 8:
                                    {
                                     printf("Please enter the release date: ");
                                     scanf("%s", video.release_date);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit release date entry\n");
                                     }else{
                                         perror ("Error on edit release date entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 9:
                                    {
                                     printf("Please enter the story line: ");
                                     scanf("%s", video.story_line);
                                                                
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit story line entry\n");
                                     }else{
                                         perror ("Error on edit story line entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;                                                
                                }//End switch

                                } while( field_option != 0 );

                             } break;
                         case 2:
                             {
                              unsigned int index;

                              do {
                                  printf( "Enter index from list: " );
                                  scanf( "%d", &index );
                              } while( getchar( ) != '\n' );

                              if (delete_entry( index )){
                                  printf( "Entry %d deleted successfully\n", index );
                              }else{
                                  perror ("Error on delete entry\n");
                                  printf( "Value of errno: %d\n", errno );           
                              }//End if
                              
                             } break;
                         }//End switch
                         
                         } while( next_option != 0 );                        
                    } break; /* end case find */
                case EDIT: 
                    {
                     video_t video;
                     int next_option;
                     unsigned int c;

                    c = display_entries(db);
                    if (c == 0)
                    {
                        printf( "There are no entries found\n" );
                        break; 
                    }else{
                        printf( "There are %d entries found\n", c );
                    }//End if

                    do 
                    {
                        printf( "\
                        [1] Edit entry\n\
                        [2] Delete entry\n\
                        [0] Exit\n\
                        --> " );
                        scanf( "%d", &next_option );
                        while( getchar( ) != '\n' );

                        switch( next_option )
                        {
                         case 1:
                             {
                              int field_option;
                              unsigned int index;

                              do 
                              {
                               printf( "Enter index from list: " );
                               scanf( "%d", &index );
                              } while( getchar( ) != '\n' );

                              do 
                              {
                               printf( "\
                               What field to wish to edit?\n\
                               [1] Film name\n\
                               [2] Production co\n\
                               [3] Director\n\
                               [4] Stars\n\
                               [5] Language\n\
                               [6] Runtime\n\
                               [7] Country\n\
                               [8] Release date\n\
                               [9] Story line\n\
                               [0] Exit\n\
                               --> " );
                               scanf( "%d", &field_option );
                               while( getchar( ) != '\n' );

                               switch( field_option )
                               {
                                case 1:
                                    {
                                     printf("Please enter the film name: ");
                                     scanf("%s", video.film_name);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit film name entry\n");
                                     }else{
                                         perror ("Error on edit film name entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 2:
                                    {
                                     printf("Please enter the production co: ");
                                     scanf("%s", video.production_co);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit production co entry\n");
                                     }else{
                                         perror ("Error on edit production co entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 3:
                                    {
                                     printf("Please enter the director: ");
                                     scanf("%s", video.director);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit director entry\n");
                                     }else{
                                         perror ("Error on edit director entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 4:
                                    {
                                     printf("Please enter the stars: ");
                                     scanf("%s", video.stars);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit stars entry\n");
                                     }else{
                                         perror ("Error on edit stars entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 5:
                                    {
                                     printf("Please enter the language: ");
                                     scanf("%s", video.language);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit language entry\n");
                                     }else{
                                         perror ("Error on edit language entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 6:
                                    {
                                     printf("Please enter the runtime: ");
                                     scanf("%s", video.runtime);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit runtime entry\n");
                                     }else{
                                         perror ("Error on edit runtime entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 7:
                                    {
                                     printf("Please enter the country: ");
                                     scanf("%s", video.country);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit country entry\n");
                                     }else{
                                         perror ("Error on edit country entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 8:
                                    {
                                     printf("Please enter the release date: ");
                                     scanf("%s", video.release_date);
                                                              
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit release date entry\n");
                                     }else{
                                         perror ("Error on edit release date entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;
                                case 9:
                                    {
                                     printf("Please enter the story line: ");
                                     scanf("%s", video.story_line);
                                                                
                                     if (edit_entry( index, field_option, &video )){
                                         printf("successfully edit story line entry\n");
                                     }else{
                                         perror ("Error on edit story line entry\n");
                                         printf( "Value of errno: %d\n", errno );           
                                     }//End if
                                    } break;                                                
                                }//End switch

                                } while( field_option != 0 );

                             } break;
                         case 2:
                             {
                              unsigned int index;

                              do {
                                  printf( "Enter index from list: " );
                                  scanf( "%d", &index );
                              } while( getchar( ) != '\n' );

                              if (delete_entry( index )){
                                  printf( "Entry %d deleted successfully\n", index );
                              }else{
                                  perror ("Error on delete entry\n");
                                  printf( "Value of errno: %d\n", errno );           
                              }///End if
                              
                             } break;
                         }//End switch
                         
                         } while( next_option != 0 ); 
                    } break; /* end case edit */
                case DELETE:
                    {
                    video_t video;  
                    unsigned int c;
                    unsigned int index;
                        
                    c = display_entries(db);
                    if (c == 0)
                    {
                        printf( "There are no entries found\n" );
                        break; 
                    }else{
                        printf( "There are %d entries found\n", c );
                    }//End if

                    do {
                        printf( "Enter index from list: " );
                        scanf( "%d", &index );
                    } while( getchar( ) != '\n' );

                    if (delete_entry( index )){
                        printf( "Entry %d deleted successfully\n", index );
                    }else{
                        perror ("Error on delete entry\n");
                        printf( "Value of errno: %d\n", errno );           
                    }///End if
                        
                    } break; /* end case delete */
            }
        } while( option != 0 );

    }
    else 
    {
        printf( "Fail to login\n" );
    }//End if

    return 0;
}


int login( void )
{
    struct termios tmp_term;
    struct sigaction sa_sigint;
    char username[ MAXLENGTH ],
         password[ MAXLENGTH ];
         //scanned_line[ MAXLENGTH ],
         //scanned_username[ MAXLENGTH ],
         //scanned_password[ MAXLENGTH ];

    printf( "Enter username: " );
    scanf( "%s", username );

    if( tcgetattr( fileno( stdin ), &saved_term ) == -1 ) 
    {
        perror( "tcgetattr" );
        exit( EXIT_FAILURE );
    }//End if

    tmp_term = saved_term;

    memset( &sa_sigint, 0, sizeof( struct sigaction ) );
    sa_sigint.sa_handler = sigint_handler;
    sa_sigint.sa_flags = 0;

    if( sigaction( SIGINT, &sa_sigint, NULL ) < 0 )
    {
        perror( "sigaction" );
        exit( EXIT_FAILURE );
    }//End if

    tmp_term.c_lflag &= ~ECHO;
    if( tcsetattr( fileno( stdin ), TCSANOW, &tmp_term ) == -1 ) 
    {
        perror( "tcgetattr" );
        exit( EXIT_FAILURE );
    }//End if

    printf( "Enter password: " );
    scanf( "%s", password );

    restore_terminal( );

   return assert_credentials(db, username, password);
}//End login 


void restore_terminal( void )
{
    if( tcsetattr( fileno( stdin ), TCSANOW, &saved_term ) == -1 )
    {
        perror( "tcsetattr" );
        exit( EXIT_FAILURE );
    }//End if
}//End restore

void sigint_handler( int sig )
{
    if( SIGINT == sig )
   {
        restore_terminal( );
    }

    exit( EXIT_SUCCESS );
}// End sigint_handler

