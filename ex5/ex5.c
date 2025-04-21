/*******************
name: Shaked Levy
ID: 212730311
EX5
*******************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FALSE, TRUE } Bool;

typedef struct Song {
    char* title;
    char* artist;
    int year;
    char* lyrics;
    int streams;
} Song;

typedef int (*Comparator)(const Song*, const Song*);

typedef struct SongItem{
    Song* data;
    struct SongItem* next;
} SongItem;

typedef struct {
    SongItem *head, *last;
} SongList;

typedef struct Playlist {
    char* name;
    SongList* songs;
    int songsNum;
} Playlist;

typedef struct PlaylistItem {
    Playlist* data;
    struct PlaylistItem* next;
} PlaylistItem;

typedef struct {
    PlaylistItem *head, *last;
} PlaylistList;

PlaylistList* addPlaylistList();
SongList* addSongList(Playlist* list);
void addPlaylistItem(PlaylistList* list, Playlist* newPlaylist);
void addSongItem(SongList* list, Song* newSong);
Playlist* newPlaylist(const char* name);
Song* newSong(const char* title, const char* artist, int year, const char* lyrics);
void printPlaylist(Playlist* playlist);
void printSong(SongItem* song);
void freeSong(Song* song);
void freeSongItem(SongItem* item);
void freeSongList(SongList* list);
void freePlaylist(Playlist* playlist);
void freePlaylistItem(PlaylistItem* item);
void freePlaylistList(PlaylistList* list);
Bool equalPlaylist(Playlist* playlist1, Playlist* playlist2);
Bool equalSong(const Song* song1, const Song* song2);
void removePlaylist(PlaylistList* list, Playlist* playlist);
void removeSong(SongList* list, Song* song);
void printPlaylistsNames(PlaylistItem* playlist, int counter);
char* getStringInput();
PlaylistItem* getPlaylistItemInput(PlaylistItem* playlist ,int index);
SongItem* getSongItemInput(SongItem* song ,int index);
void printPlaylistsMenu();
void printSongs(SongItem* songlist, int counter);
void playSong(SongItem* song);
void playAllSongs(SongItem* list);
void switchSongs(SongItem* a, SongItem* b);
void printSongsMenu();
int yearCompare(const Song* song1, const Song* song2);
void sortPlaylistByYear(SongList* list);
int streamCompareAscending(const Song* song1, const Song* song2);
void sortPlaylistByStreamAscending(SongList* list);
int streamCompareDescending(const Song* song1, const Song* song2);
void sortPlaylistByStreamDescending(SongList* list);
int compareAlphabetical(const Song* song1, const Song* song2);
void sortPlaylistAlphabetical(SongList* list);


int main() {

    int task = -1;
    int numOfPlaylists = 0;
    PlaylistList* playlists = addPlaylistList();

    do {
        printPlaylistsMenu();
        scanf("%d", &task);

        switch (task)
        {
            case 1:
            {
                int playTask = -1;
                PlaylistItem* item;

                do {
                    printf("Choose a playlist:\n");
                    printPlaylistsNames(playlists->head, 1);
                    printf("%d. Back to main menu\n", numOfPlaylists+1);
                    scanf("%d", &playTask);
                    if (numOfPlaylists == 0) {
                        break;
                    }
                    if (playTask == numOfPlaylists+1) {
                        break;
                    }
                    if (playTask < numOfPlaylists || playTask > 0) {
                        //inside a playlist menu
                        item = getPlaylistItemInput(playlists->head, playTask);
                        printf("playlist %s:\n", item->data->name);
                        do {
                            printSongsMenu();
                            scanf("%d", &playTask);
                            switch (playTask)
                            {
                                case 1:
                                {
                                    //show playlist
                                    printSongs(item->data->songs->head, 1);
                                    do {
                                        int songNum;
                                        printf("choose a song to play, or 0 to quit:\n");
                                        scanf("%d", &songNum);
                                        if (songNum == 0) {
                                            break;
                                        }
                                        SongItem* currentsong = getSongItemInput(item->data->songs->head, songNum);
                                        if (currentsong == NULL) {
                                            freeSongItem(currentsong);
                                            exit(1);
                                        }
                                        playSong(currentsong);

                                    } while (TRUE);

                                    break;
                                }
                                case 2:
                                {
                                    //add song
                                    int year;
                                    printf("Enter song's details\n");
                                    printf("Title: \n");
                                    char* title = getStringInput();
                                    if (title == NULL) {
                                        free(title);
                                        exit(1);
                                    }
                                    printf("Artist:\n");
                                    char* artist = getStringInput();
                                    if (artist == NULL) {
                                        free(artist);
                                        exit(1);
                                    }
                                    printf("Year of release:\n");
                                    scanf("%d", &year);
                                    printf("Lyrics:\n");
                                    char* lyrics = getStringInput();
                                    if (lyrics == NULL) {
                                        free(lyrics);
                                        exit(1);
                                    }
                                    Song* newsong = newSong(title, artist, year, lyrics);
                                    free(title);
                                    free(artist);
                                    free(lyrics);
                                    addSongItem(item->data->songs, newsong);
                                    item->data->songsNum++;
                                    break;
                                }
                                case 3:
                                {
                                    //delete song
                                    int songTask;
                                    printSongs(item->data->songs->head,1);
                                    printf("choose a song to delete, or 0 to quit:\n");
                                    scanf("%d", &songTask);
                                    if (songTask == 0) {
                                        break;
                                    }
                                    SongItem* songToDelete = getSongItemInput(item->data->songs->head, songTask);
                                    removeSong(item->data->songs, songToDelete->data);
                                    printf("Song deleted successfully.\n");
                                    break;
                                }
                                case 4:
                                {
                                    //sort
                                    printf("choose:\n"
                                            "1. sort by year\n"
                                            "2. sort by streams - ascending order\n"
                                            "3. sort by streams - descending order\n"
                                            "4. sort alphabetically\n");
                                    scanf("%d", &playTask);
                                    switch (playTask) {
                                        case 1:
                                            sortPlaylistByYear(item->data->songs);
                                            break;
                                        case 2:
                                            sortPlaylistByStreamAscending(item->data->songs);
                                            break;
                                        case 3:
                                            sortPlaylistByStreamDescending(item->data->songs);
                                            break;
                                        default:
                                            sortPlaylistAlphabetical(item->data->songs);
                                            break;
                                    }
                                    break;
                                }
                                case 5:
                                {
                                    //play
                                    playAllSongs(item->data->songs->head);
                                    break;
                                }
                                default: playTask = 6; break;
                            }
                        } while (playTask != 6);
                    }

                } while (playTask != numOfPlaylists+1);

                break;
            }
            case 2:
            {
                //enter a playlist
                printf("Enter playlist's name:\n");
                char* ch = getStringInput();
                Playlist* list = newPlaylist(ch);
                addPlaylistItem(playlists, list);
                free(ch);
                numOfPlaylists++;
                break;
            }
            case 3:
            {
                //delete a playlist
                int playTask = -1;
                PlaylistItem* item;
                PlaylistList* listcase3 = playlists;
                printf("Choose a playlist:\n");
                printPlaylistsNames(playlists->head, 1);
                printf("%d. Back to main menu\n", numOfPlaylists+1);
                scanf("%d", &playTask);
                if (numOfPlaylists == 0) {
                    break;
                }
                if (playTask <= numOfPlaylists || playTask > 0) {
                    //inside a playlist menu
                    item = getPlaylistItemInput(playlists->head, playTask);
                    removePlaylist(listcase3, item->data);
                    numOfPlaylists--;
                    printf("Playlist deleted.\n");
                }
                break;
            }
            default:
                scanf("%d", &task);
        }
    } while (task != 4);
    freePlaylistList(playlists);
    printf("Goodbye!\n");  
}


PlaylistList* addPlaylistList() {
    PlaylistList* sl = (PlaylistList*)malloc(sizeof(PlaylistList));
    if(sl == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    sl->head = NULL;
    sl->last = NULL;
    return sl;
}

SongList* addSongList(Playlist* list) {
    SongList* sl = (SongList*)malloc(sizeof(SongList));
    if(sl == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    sl->head = NULL;
    sl->last = NULL;
    list->songs = sl;
    return sl;
}

void addPlaylistItem(PlaylistList* list, Playlist* newPlaylist) {
    PlaylistItem* item = (PlaylistItem*)malloc(sizeof(PlaylistItem));
    if(item == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    item->data = newPlaylist;
    item->next = NULL;
    if (list->head == NULL)
    {
        list->head = item;
        list->last = item;
    }
    else
    {
        list->last->next = item;
        list->last = item;
    }
}

void addSongItem(SongList* list, Song* newSong) {
    SongItem* item = (SongItem*)malloc(sizeof(SongItem));
    if(item == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    item->data = newSong;
    item->next = NULL;
    if (list->head == NULL)
    {
        list->head = item;
        list->last = item;
    }
    else
    {
        list->last->next = item;
        list->last = item;
    }
}

Playlist* newPlaylist(const char* name) {
    Playlist* playlist = (Playlist*) malloc(sizeof(Playlist));
    if(playlist == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    playlist->name = (char*) malloc(strlen(name) + 1);
    strcpy(playlist->name, name);
    playlist->songs = addSongList(playlist);
    playlist->songsNum = 0;
    return playlist;
}

Song* newSong(const char* title, const char* artist, int year, const char* lyrics) {
    Song* song = (Song*) malloc(sizeof(Song));
    if(song == NULL) {
        printf("Memory allocation error\n");
        free(song);
        exit(1);
    }
    song->title = (char*) malloc(strlen(title) + 1);
    if(song->title == NULL) {
        printf("Memory allocation error\n");
        free(song->title);
        exit(1);
    }
    strcpy(song->title, title);
    song->artist = (char*) malloc(strlen(artist) + 1);
    if(song->artist == NULL) {
        printf("Memory allocation error\n");
        free(song->title);
        exit(1);
    }
    strcpy(song->artist, artist);
    song->year = year;
    song->lyrics = (char*) malloc(strlen(lyrics) + 1);
    if(song->lyrics == NULL) {
        printf("Memory allocation error\n");
        free(song->lyrics);
        exit(1);
    }
    strcpy(song->lyrics, lyrics);
    song->streams = 0;
    return song;
}

void freeSong(Song* song) {
    if (song != NULL) {
        free(song->title);
        free(song->artist);
        free(song->lyrics);
        free(song);
    }
}


void freeSongItem(SongItem* item) {
    if (item != NULL) {
        freeSong(item->data);
        freeSongItem(item->next);
        free(item);
    }
}

void freeSongList(SongList* list) {
    freeSongItem(list->head);
    free(list);
}

void freePlaylist(Playlist* playlist) {
    freeSongList(playlist->songs);
    free(playlist->name);
    free(playlist);
}
void freePlaylistItem(PlaylistItem* item) {
    if (item != NULL) {
        freePlaylist(item->data);
        freePlaylistItem(item->next);
        free(item);
    }
}

void freePlaylistList(PlaylistList* list) {
    freePlaylistItem(list->head);
    free(list);
}

Bool equalPlaylist(Playlist* playlist1, Playlist* playlist2) {
    if (playlist1->songsNum == playlist2->songsNum && strcmp(playlist1->name, playlist2->name) == 0) {
        return TRUE;
    }
    return FALSE;
}

Bool equalSong(const Song* song1, const Song* song2) {
    if (song1->streams == song2->streams && song1->year == song2->year && strcmp(song1->title, song2->title) == 0) {
        return TRUE;
    }
    return FALSE;
}

void removePlaylist(PlaylistList* list, Playlist* playlist) {
    PlaylistItem* iterator = list->head;
    PlaylistItem* previous;
    if (list->head && equalPlaylist(list->head->data, playlist) == TRUE){
        list->head = iterator->next;
        if (list->head == NULL) list->last = NULL;
        iterator->next = NULL;
        freePlaylistItem(iterator);
        return;
    }
    while (iterator != NULL && equalPlaylist(iterator->data, playlist) == FALSE){
        previous = iterator;
        iterator = iterator->next;
    }
    if (iterator == NULL) return;
    else if (equalPlaylist(iterator->data, playlist) == TRUE) {
        previous->next = iterator->next;
        iterator->next = NULL;
        if (iterator == list->last)
            list->last = previous;
        freePlaylistItem(iterator);
    }
}

void removeSong(SongList* list, Song* song) {
    SongItem* iterator = list->head;
    SongItem* previous;
    if (list->head && equalSong(list->head->data, song) == TRUE){
        list->head = iterator->next;
        if (list->head == NULL) list->last = NULL;
        iterator->next = NULL;
        freeSongItem(iterator);
        return;
    }
    while (iterator != NULL && equalSong(iterator->data, song) == FALSE){
        previous = iterator;
        iterator = iterator->next;
    }
    if (iterator == NULL) return;
    else if (equalSong(iterator->data, song) == TRUE) {
        previous->next = iterator->next;
        iterator->next = NULL;
        if (iterator == list->last)
            list->last = previous;
        freeSongItem(iterator);
    }
}

void printPlaylistsNames(PlaylistItem* playlist, int counter) {
    PlaylistItem* item = playlist;
    if (item == NULL) {
        return;
    }
    if (item->next != NULL) {

        printf("%d. %s\n", counter, item->data->name);

        counter++;
        printPlaylistsNames(item->next, counter);
    }
    else {
        printf("%d. %s\n", counter, item->data->name);
    }

}

char* getStringInput() {
    char ch;
    int num = 0;
    char *newstring = NULL, *temp = NULL;

    scanf(" ");
    while ((ch = (char)getchar()) != '\n' && ch != '\r') {
        ++num;
        temp = (char*)realloc(newstring, (num + 1) * sizeof(char));
        if(temp == NULL) {
            free(newstring);
            printf("Memory allocation error\n");
            exit(1);
        }
        newstring = temp;
        newstring[num - 1] = ch;
    }
    if (num > 0) {
        newstring[num] = '\0';
    } else {
        free(newstring);
        newstring = NULL;
    }
    return newstring;
}

PlaylistItem* getPlaylistItemInput(PlaylistItem* playlist ,int index) {
    PlaylistItem* list = playlist;
    if (list == NULL) {
        return NULL;
    }
    if (list->next != NULL) {
        if (index == 1) {
            return list;
        }
        return getPlaylistItemInput(list->next, --index);
    }
    return list;
}

SongItem* getSongItemInput(SongItem* song ,int index) {
    SongItem* list = song;
    if (list == NULL) {
        return NULL;
    }
    if (list->next != NULL) {
        if (index == 1) {
            return list;
        }
        return getSongItemInput(list->next, --index);
    }
    return list;
}

void printSongs(SongItem* songlist, int counter) {
    SongItem* iterator = songlist;
    if (iterator != NULL) {
        printf("%d. Title: %s\n", counter, iterator->data->title);
        printf("\tArtist: %s\n" , iterator->data->artist);
        printf("\tReleased: %d\n", iterator->data->year);
        printf("\tStreams: %d\n\n", iterator->data->streams);
        counter++;
        printSongs(iterator->next, counter);
    }
}

void playSong(SongItem* song) {
    SongItem* iterator = song;
    if (iterator != NULL) {
        printf("Now playing %s:\n", iterator->data->title);
        printf("$ %s $\n\n", iterator->data->lyrics);
        iterator->data->streams++;
    }
}

void playAllSongs(SongItem* list) {
    SongItem* iterator = list;
    if (iterator->next != NULL) {
        playSong(iterator);
        playAllSongs(iterator->next);
    }
    if (iterator->next == NULL) {
        playSong(iterator);
    }
}

void switchSongs(SongItem* a, SongItem* b) {
    Song* temp = a->data;
    a->data = b->data;
    b->data = temp;
}

int yearCompare(const Song* song1, const Song* song2) {
    return song1->year - song2->year;
}

void sortPlaylistByYear(SongList* list){
    SongItem* i = NULL;
    Bool switched = TRUE;
    while (switched == TRUE){
        switched = FALSE;
        i = list->head;
        while (i->next != NULL){
            if (yearCompare(i->data, i->next->data)>0){
                switched = TRUE;
                switchSongs(i, i->next);
            }
            i = i->next;
        }
    }
    printf("sorted\n");
}

int streamCompareAscending(const Song* song1, const Song* song2) {
    return song1->streams - song2->streams;
}

void sortPlaylistByStreamAscending(SongList* list){
    SongItem* i = NULL;
    Bool switched = TRUE;
    while (switched == TRUE){
        switched = FALSE;
        i = list->head;
        while (i->next != NULL){
            if (streamCompareAscending(i->data, i->next->data)>0){
                switched = TRUE;
                switchSongs(i, i->next);
            }
            i = i->next;
        }
    }
    printf("sorted\n");
}

int streamCompareDescending( const Song* song1, const Song* song2) {
    return song2->streams - song1->streams;
}

void sortPlaylistByStreamDescending(SongList* list){
    SongItem* i = NULL;
    Bool switched = TRUE;
    while (switched == TRUE){
        switched = FALSE;
        i = list->head;
        while (i->next != NULL){
            if (streamCompareDescending(i->data, i->next->data)>0){
                switched = TRUE;
                switchSongs(i, i->next);
            }
            i = i->next;
        }
    }
    printf("sorted\n");
}

int compareAlphabetical(const Song* song1, const Song* song2) {
    return strcmp(song1->title, song2->title);
}

void sortPlaylistAlphabetical(SongList* list){
    SongItem* i = NULL;
    Bool switched = TRUE;
    while (switched == TRUE){
        switched = FALSE;
        i = list->head;
        while (i->next != NULL){
            if (compareAlphabetical(i->data, i->next->data)>0){
                switched = TRUE;
                switchSongs(i, i->next);
            }
            i = i->next;
        }
    }
    printf("sorted\n");
}

void printPlaylistsMenu() {
    printf("Please Choose:\n");
    printf("\t1. Watch playlists\n\t2. Add playlist\n\t3. Remove playlist\n\t4. exit\n");
}

void printSongsMenu() {
    printf("\t1. Show Playlist\n\t2. Add Song\n\t3. Delete Song\n\t4. Sort\n\t5. Play\n\t6. exit\n");
}
