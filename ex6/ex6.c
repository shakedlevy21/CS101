#include "ex6.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define INT_BUFFER 128

// ================================================
// Basic struct definitions from ex6.h assumed:
//   PokemonData { int id; char *name; PokemonType TYPE; int hp; int attack; EvolutionStatus CAN_EVOLVE; }
//   PokemonNode { PokemonData* data; PokemonNode* left, *right; }
//   OwnerNode   { char* ownerName; PokemonNode* pokedexRoot; OwnerNode *next, *prev; }
//   OwnerNode* ownerHead;
//   const PokemonData pokedex[];
// ================================================

// --------------------------------------------------------------
// 1) Safe integer reading
// --------------------------------------------------------------

void trimWhitespace(char *str)
{
    // Remove leading spaces/tabs/\r
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\r')
        start++;

    if (start > 0)
    {
        int idx = 0;
        while (str[start])
            str[idx++] = str[start++];
        str[idx] = '\0';
    }

    // Remove trailing spaces/tabs/\r
    int len = (int)strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\r'))
    {
        str[--len] = '\0';
    }
}

char *myStrdup(const char *src)
{
    if (!src)
        return NULL;
    size_t len = strlen(src);
    char *dest = (char *)malloc(len + 1);
    if (!dest)
    {
        printf("Memory allocation failed in myStrdup.\n");
        return NULL;
    }
    strcpy(dest, src);
    return dest;
}

int readIntSafe(const char *prompt)
{
    char buffer[INT_BUFFER];
    int value;
    int success = 0;

    while (!success)
    {
        printf("%s", prompt);

        // If we fail to read, treat it as invalid
        if (!fgets(buffer, sizeof(buffer), stdin))
        {
            printf("Invalid input.\n");
            clearerr(stdin);
            continue;
        }

        // 1) Strip any trailing \r or \n
        //    so "123\r\n" becomes "123"
        size_t len = strlen(buffer);
        if (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r'))
            buffer[--len] = '\0';
        if (len > 0 && (buffer[len - 1] == '\r' || buffer[len - 1] == '\n'))
            buffer[--len] = '\0';

        // 2) Check if empty after stripping
        if (len == 0)
        {
            printf("Invalid input.\n");
            continue;
        }

        // 3) Attempt to parse integer with strtol
        char *endptr;
        value = (int)strtol(buffer, &endptr, 10);

        // If endptr didn't point to the end => leftover chars => invalid
        // or if buffer was something non-numeric
        if (*endptr != '\0')
        {
            printf("Invalid input.\n");
        }
        else
        {
            // We got a valid integer
            success = 1;
        }
    }
    return value;
}

// --------------------------------------------------------------
// 2) Utility: Get type name from enum
// --------------------------------------------------------------
const char *getTypeName(PokemonType type)
{
    switch (type)
    {
    case GRASS:
        return "GRASS";
    case FIRE:
        return "FIRE";
    case WATER:
        return "WATER";
    case BUG:
        return "BUG";
    case NORMAL:
        return "NORMAL";
    case POISON:
        return "POISON";
    case ELECTRIC:
        return "ELECTRIC";
    case GROUND:
        return "GROUND";
    case FAIRY:
        return "FAIRY";
    case FIGHTING:
        return "FIGHTING";
    case PSYCHIC:
        return "PSYCHIC";
    case ROCK:
        return "ROCK";
    case GHOST:
        return "GHOST";
    case DRAGON:
        return "DRAGON";
    case ICE:
        return "ICE";
    default:
        return "UNKNOWN";
    }
}

// --------------------------------------------------------------
// Utility: getDynamicInput (for reading a line into malloc'd memory)
// --------------------------------------------------------------
char *getDynamicInput()
{
    // char ch;
    // int num = 0;
    // char *newstring = NULL, *temp = NULL;
    //
    // scanf(" ");
    // while ((ch = (char)getchar()) != '\n' && ch != '\r') {
    //     ++num;
    //     temp = (char*)realloc(newstring, (num + 1) * sizeof(char));
    //     if(temp == NULL) {
    //         free(newstring);
    //         printf("Memory allocation error\n");
    //         exit(1);
    //     }
    //     newstring = temp;
    //     newstring[num - 1] = ch;
    // }
    // if (num > 0) {
    //     newstring[num] = '\0';
    // } else {
    //     free(newstring);
    //     newstring = NULL;
    //     temp = NULL;
    // }
    // if (num == 0) {
    //     free(newstring);
    //     temp = NULL;
    // }
    //
    // return newstring;
    scanf(" ");
    char *input = NULL;
    size_t size = 0, capacity = 1;
    input = (char *)malloc(capacity);
    if (!input)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (size + 1 >= capacity)
        {
            capacity *= 2;
            char *temp = (char *)realloc(input, capacity);
            if (!temp)
            {
                printf("Memory reallocation failed.\n");
                free(input);
                return NULL;
            }
            input = temp;
        }
        input[size++] = (char)c;
    }
    input[size] = '\0';

    // Trim any leading/trailing whitespace or carriage returns
    trimWhitespace(input);

    return input;

}

// Function to print a single Pokemon node
void printPokemonNode(PokemonNode *node)
{
    if (!node)
        return;
    printf("ID: %d, Name: %s, Type: %s, HP: %d, Attack: %d, Can Evolve: %s\n",
           node->data->id,
           node->data->name,
           getTypeName(node->data->TYPE),
           node->data->hp,
           node->data->attack,
           (node->data->CAN_EVOLVE == CAN_EVOLVE) ? "Yes" : "No");
}

// --------------------------------------------------------------
// Display Menu
// --------------------------------------------------------------
void displayMenu(OwnerNode *owner)
{
    if (!owner->pokedexRoot)
    {
        printf("Pokedex is empty.\n");
        return;
    }

    printf("Display:\n");
    printf("1. BFS (Level-Order)\n");
    printf("2. Pre-Order\n");
    printf("3. In-Order\n");
    printf("4. Post-Order\n");
    printf("5. Alphabetical (by name)\n");

    int choice;
    printf("Your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        BFSGeneric(owner->pokedexRoot, displayBFS);
        break;
    case 2:
        preOrderGeneric(owner->pokedexRoot ,preOrderTraversal);
        break;
    case 3:
        inOrderGeneric(owner->pokedexRoot, inOrderTraversal);
        break;
    case 4:
        postOrderGeneric(owner->pokedexRoot, postOrderTraversal);
        break;
    case 5:
        alphabeticalGeneric(owner->pokedexRoot, printPokemonNode);
        break;
    default:
        printf("Invalid choice.\n");
    }
}

// --------------------------------------------------------------
// Sub-menu for existing Pokedex
// --------------------------------------------------------------
void enterExistingPokedexMenu()
{
    if (ownerHead == NULL) {
        printf("No existing Pokedexes.\n");
        return;
    }
    // list owners
    printf("\nExisting Pokedexes:\n");
    printOwnerNames();

    //choosing an owner
    int choice;
    printf("Choose a Pokedex by number: ");
    scanf("%d", &choice);
    OwnerNode *current = findOwnerByIndex(choice);
    printf("\nEntering %s's Pokedex...\n", current->ownerName);

    int subChoice;
    do
    {
        printf("\n-- %s's Pokedex Menu --\n", current->ownerName);
        printf("1. Add Pokemon\n");
        printf("2. Display Pokedex\n");
        printf("3. Release Pokemon (by ID)\n");
        printf("4. Pokemon Fight!\n");
        printf("5. Evolve Pokemon\n");
        printf("6. Back to Main\n");

        printf("Your choice: ");
        scanf("%d", &subChoice);

        switch (subChoice) {
            case 1:
                addPokemon(current);
            break;
            case 2:
                displayMenu(current);
            break;
            case 3:
                {
                    if (current->pokedexRoot == NULL) {
                        printf("No Pokemon to release.\n");
                        break;
                    }
                    int id;
                    printf("Enter Pokemon ID to release: ");
                    scanf("%d", &id);
                    if (searchPokemonBFS(current->pokedexRoot, id)) {
                        printf("Removing Pokemon %s (ID %d).\n", pokedex[id-1].name, pokedex[id-1].id);
                        current->pokedexRoot = freePokemon(current->pokedexRoot, id);
                    } else {
                        printf("No Pokemon with ID %d found.\n", id);
                    }
                    break;
                }
        case 4:
            pokemonFight(current);
            break;
        case 5:
            evolvePokemon(current);
            break;
        case 6:
            printf("Back to Main Menu.\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (subChoice != 6);
}

// --------------------------------------------------------------
// Main Menu
// --------------------------------------------------------------
void mainMenu()
{
    int choice;
    do
    {
        printf("\n=== Main Menu ===\n");
        printf("1. New Pokedex\n");
        printf("2. Existing Pokedex\n");
        printf("3. Delete a Pokedex\n");
        printf("4. Merge Pokedexes\n");
        printf("5. Sort Owners by Name\n");
        printf("6. Print Owners in a direction X times\n");
        printf("7. Exit\n");

        printf("Your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            openPokedexMenu();
            break;
        case 2:
            enterExistingPokedexMenu();
            break;
        case 3:
            if (ownerHead == NULL) {
                printf("No existing Pokedexes to delete.\n");
                break;
            }
            printf("\n=== Delete a Pokedex ===\n");
            printOwnerNames();

            int id;
            printf("Choose a Pokedex to delete by number: ");
            scanf("%d", &id);
            OwnerNode* node = findOwnerByIndex(id);
            printf("Deleting %s's entire Pokedex...\n", node->ownerName);
            deletePokedex(node);
            printf("Pokedex deleted.\n");
            break;
        case 4:
            mergePokedexMenu();
            break;
        case 5:
            sortOwners();
            break;
        case 6:
            if (ownerHead == NULL) {
                printf("No owners.\n");
                break;
            }
            char direction;
            printf("Enter direction (F or B): ");
            scanf(" %c", &direction);
            int nums;
            printf("How many prints? ");
            scanf("%d", &nums);
            printOwnersCircular(nums, direction);
            break;
        case 7:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid.\n");
        }
    } while (choice != 7);
}

void openPokedexMenu() {
    printf("Your name: ");
    char *name = getDynamicInput();
    if (name == NULL) {
        exit(1);
    }
    //check for duplicates
    OwnerNode *temp = ownerHead;
    if (temp != NULL) {
        if (temp->next == NULL) {//if list has one owner
            if (strcmp(temp->ownerName, name) == 0) {
                printf("Owner '%s' already exists. Not creating a new Pokedex.", name);
                free(name);
                return;
            }
        } else {
            while (temp->next != ownerHead) {
                if (strcmp(temp->ownerName, name) == 0) {
                    printf("Owner '%s' already exists. Not creating a new Pokedex.", name);
                    free(name);
                    return;
                }
                temp = temp->next;
            }
        }
    }
    printf("Choose Starter:\n"
           "1. Bulbasaur\n"
           "2. Charmander\n"
           "3. Squirtle\n");
    int choice;
    printf("Your choice: ");
    scanf("%d", &choice);
    if (choice < 0 || choice > 151) {
        return;
    }
    const PokemonData *newPokemon;
    switch (choice) {
        case 1:
            //id 0 is Bulbasaur
            newPokemon = &pokedex[0];
        break;
        case 2:
            //id 3 is Charmander
            newPokemon = &pokedex[3];
        break;
        case 3:
            //id 6 is Squirtle
            newPokemon = &pokedex[6];
        break;
    default:
        newPokemon = &pokedex[0];
    }
    PokemonNode *newpokemonnode = createPokemonNode(newPokemon);
    OwnerNode *newOwner = createOwner(name, newpokemonnode);
    if (newOwner != NULL) {
        printf("New Pokedex created for %s with starter %s.\n"
        , newOwner->ownerName, newOwner->pokedexRoot->data->name);
    }
}


PokemonNode *createPokemonNode(const PokemonData *data) {
    PokemonNode *node = (PokemonNode *)malloc(sizeof(PokemonNode));
    if (node == NULL) {
        exit(1);
    }
    node->data = (PokemonData *)malloc(sizeof(PokemonData));
    if (node->data == NULL) {
        exit(1);
    }
    node->data->id = data->id;
    node->data->name = data->name;
    node->data->TYPE = data->TYPE;
    node->data->hp = data->hp;
    node->data->attack = data->attack;
    node->data->CAN_EVOLVE = data->CAN_EVOLVE;
    node->left = NULL;
    node->right = NULL;
    return node;
}

OwnerNode *createOwner(char *ownerName, PokemonNode *starter) {
    OwnerNode *owner = (OwnerNode *)malloc(sizeof(OwnerNode));
    if (owner == NULL) {
        printf("Memory allocation error.\n");
        exit(1);
    }

    //start making a new owner and place it
    owner->ownerName = ownerName;
    owner->pokedexRoot = starter;

    //if the list is empty
    if (ownerHead == NULL) {
        ownerHead = owner;
        owner->next = NULL;
        owner->prev = NULL;
        return owner;
    }

    //if the list has one owner
    if (ownerHead->next == NULL) {
        ownerHead->next = owner;
        owner->next = ownerHead;
        owner->prev = ownerHead;
        ownerHead->prev = owner;
        return owner;
    }
    OwnerNode *owneriterrator = ownerHead;
    while (owneriterrator->next != ownerHead) {
        owneriterrator = owneriterrator->next;
    }

    //emplement prev and next owner
    owneriterrator->next = owner;
    owner->next = ownerHead;
    owner->prev = owneriterrator;
    ownerHead->prev = owner;
    return owner;
}

void printOwnerNames() {
    OwnerNode *iterator = ownerHead;
    int counter = 1;
    if (ownerHead == NULL) {
        printf("No Pokedex found.\n");
        return;
    }
    if (ownerHead->next == NULL) {
        printf("%d. %s\n", counter, iterator->ownerName);
        return;
    }
    do {
        printf("%d. %s\n", counter, iterator->ownerName);
        iterator = iterator->next;
        counter++;
    } while (iterator != ownerHead);
}

OwnerNode *findOwnerByIndex(int index) {
    OwnerNode *iterator = ownerHead;
    int counter = 1;
    while (counter != index) {
        iterator = iterator->next;
        counter++;
    }
    return iterator;
}

//search for pokemon in pokedex by id
PokemonNode *searchPokemonBFS(PokemonNode *root, int id) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data->id > id) {
        return searchPokemonBFS(root->left, id);
    }
    if (root->data->id < id) {
        return searchPokemonBFS(root->right, id);
    }
    return root;
}

//insert node to BST by id
PokemonNode *insertPokemonNode(PokemonNode *root, PokemonNode *newNode) {
    if (root == NULL) {
        PokemonNode *newRoot = createPokemonNode(newNode->data);
        return newRoot;
    }
    if (root->data->id > newNode->data->id) {
        root->left = insertPokemonNode(root->left, newNode);
    }
    if (root->data->id < newNode->data->id) {
        root->right = insertPokemonNode(root->right, newNode);
    }
    if (root->data->id == newNode->data->id) {
        return NULL;
    }
    return root;
}

void addPokemon(OwnerNode *owner) {
    int index = -1;
    printf("Enter ID to add: ");
    scanf("%d", &index);
    if (searchPokemonBFS(owner->pokedexRoot, index) == NULL) {
        //create a new pokemon node and insert to BST
        const PokemonData *newPokemon = &pokedex[index-1];
        PokemonNode *newpokemonnode = createPokemonNode(newPokemon);
        owner->pokedexRoot = insertPokemonNode(owner->pokedexRoot, newpokemonnode);
        printf("Pokemon %s (ID %d) added.\n", newpokemonnode->data->name, newpokemonnode->data->id);
        free(newpokemonnode->data);
        free(newpokemonnode);
    } else {
        printf("Pokemon with ID %d is already in the Pokedex. No changes made.\n", index);
    }
}

void initNodeArray(NodeArray *na, int cap) {
    na->capacity = cap;
    na->size = 0;
    na->nodes = (PokemonNode **)malloc(cap * sizeof(PokemonNode *));
    if (na->nodes == NULL) {
        exit(1);  // Memory allocation failed
    }
}

void addNode(NodeArray *na, PokemonNode *node) {
    if (na->size == na->capacity) {
        //resize the array
        na->capacity++;//add to capacity
        PokemonNode **temp = realloc(na->nodes, na->capacity * sizeof(PokemonNode *));
        if (temp == NULL) {
            exit(1);
        }
        na->nodes = temp;
    }
    na->nodes[na->size] = node;//add new node
    na->size++;
}

void displayBFS(PokemonNode *root) {
    printPokemonNode(root);
}

void BFSGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        printf("Pokedex is empty.\n");
        return;
    }

    NodeArray nodeArray;
    initNodeArray(&nodeArray, 1);
    addNode(&nodeArray, root);

    int currentIndex = 0;
    while (currentIndex < nodeArray.size) {
        PokemonNode *current = nodeArray.nodes[currentIndex];
        visit(current);
        currentIndex++;
        if (current->left != NULL) {
            addNode(&nodeArray, current->left);
        }
        if (current->right != NULL) {
            addNode(&nodeArray, current->right);
        }
    }

    free(nodeArray.nodes);
}

void preOrderTraversal(PokemonNode *root) {
    printPokemonNode(root);
}

void preOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        printf("Pokedex is empty.\n");
        return;
    }
    visit(root);
    if (root->left != NULL) {
        preOrderGeneric(root->left, visit);
    }
    if (root->right != NULL) {
        preOrderGeneric(root->right, visit);
    }
}

void inOrderTraversal(PokemonNode *root) {
    printPokemonNode(root);
}

void inOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        printf("Pokedex is empty.\n");
        return;
    }
    if (root->left != NULL) {
        inOrderGeneric(root->left, visit);
    }
    visit(root);
    if (root->right != NULL) {
        inOrderGeneric(root->right, visit);
    }
}

void postOrderTraversal(PokemonNode *root) {
    printPokemonNode(root);
}

void postOrderGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        printf("Pokedex is empty.\n");
        return;
    }
    if (root->left != NULL) {
        postOrderGeneric(root->left, visit);
    }
    if (root->right != NULL) {
        postOrderGeneric(root->right,visit);
    }
    visit(root);
}

void collectAll(PokemonNode *root, NodeArray *na) {

    if (root == NULL) {
        printf("Pokedex is empty.\n");
        return;
    }
    addNode(na, root);
    if (root->left != NULL) {
        collectAll(root->left, na);
    }
    if (root->right != NULL) {
        collectAll(root->right,na);
    }
}

int compareByNameNode(const void *a, const void *b) {
    PokemonNode *nodeA = *(PokemonNode **)a;
    PokemonNode *nodeB = *(PokemonNode **)b;
    int result = strcmp(nodeA->data->name, nodeB->data->name);
    return result;
}

void alphabeticalGeneric(PokemonNode *root, VisitNodeFunc visit) {
    if (root == NULL) {
        printf("Pokedex is empty.\n");
        return;
    }
    NodeArray *nodeArr = (NodeArray *)malloc(sizeof(NodeArray));
    initNodeArray(nodeArr, 1);
    //initializing the array with all the nodes in the tree
    collectAll(root, nodeArr);

    qsort(nodeArr->nodes, nodeArr->size, sizeof(PokemonNode*), compareByNameNode);
    for (int i = 0; i < nodeArr->size; i++) {
        visit(nodeArr->nodes[i]);
    }
    free(nodeArr->nodes);
    free(nodeArr);
}

PokemonNode* freePokemon(PokemonNode* root, int id) {
    if (root == NULL)
        return NULL;

    if (id > root->data->id) {
        root->right = freePokemon(root->right, id);
    }
    else if (id < root->data->id) {
        root->left = freePokemon(root->left, id);
    }
    else {
        if (root->left == NULL && root->right == NULL) {
            free(root->data);
            free(root);
            return NULL;
        }
        else if (root->left == NULL
                 || root->right == NULL) {
            PokemonNode* temp;
            if (root->left == NULL) {
                temp = root->right;
            }
            else {
                temp = root->left;
            }
            free(root->data);
            free(root);
            return temp;
                 }
        else {
            PokemonNode* temp = root->left;
            while (temp && temp->right) {
                temp = temp->right;
            }
            root->data = temp->data;
            root->right = freePokemon(root->right, temp->data->id);
        }
    }
    return root;
}

void pokemonFight(OwnerNode *owner) {
    if (owner->pokedexRoot == NULL) {
        printf("Pokedex is empty.\n");
        return;
    }
    int id1;
    int id2;
    printf("Enter ID of the first Pokemon: ");
    scanf("%d", &id1);
    printf("Enter ID of the second Pokemon: ");
    scanf("%d", &id2);
    PokemonNode* temp1 = searchPokemonBFS(owner->pokedexRoot, id1);
    PokemonNode* temp2 = searchPokemonBFS(owner->pokedexRoot, id2);
    if (!temp1 || !temp2) {
        printf("One or both Pokemon IDs not found.\n");
        return;
    }
    double score1 = ((temp1->data->attack) * 1.5) + ((temp1->data->hp) * 1.2);
    double score2 = ((temp2->data->attack) * 1.5) + ((temp2->data->hp) * 1.2);
    printf("Pokemon 1: %s (Score = %.2f)\n", temp1->data->name, score1);
    printf("Pokemon 2: %s (Score = %.2f)\n", temp2->data->name, score2);
    if (score1 > score2) {
        printf("%s wins!\n", temp1->data->name);
    } else if (score1 < score2) {
        printf("%s wins!\n", temp2->data->name);
    } else { //tie
        printf("It’s a tie!\n");
    }
}

void evolvePokemon(OwnerNode *owner) {
    if (owner->pokedexRoot == NULL) {
        printf("Cannot evolve. Pokedex empty.\n");
        return;
    }
    int id = readIntSafe("Enter ID of Pokemon to evolve: ");
    PokemonNode* node = searchPokemonBFS(owner->pokedexRoot, id);
    if (node == NULL) {
        printf("No Pokemon with ID %d found.\n", id);
        return;
    }
    int evolvedId = id;
    PokemonNode* evolvedPokemon = (PokemonNode *)malloc(sizeof(PokemonNode));
    evolvedPokemon->data->id = pokedex[evolvedId].id;
    evolvedPokemon->data->hp = pokedex[evolvedId].hp;
    evolvedPokemon->data->attack = pokedex[evolvedId].attack;
    evolvedPokemon->data->name = node->data->name;
    evolvedPokemon->data->TYPE = pokedex[evolvedId].TYPE;
    evolvedPokemon->data->CAN_EVOLVE = pokedex[evolvedId].CAN_EVOLVE;
    if (node->data->CAN_EVOLVE == CAN_EVOLVE) {
        PokemonNode* checkFor = searchPokemonBFS(owner->pokedexRoot, evolvedId+1);
        if (checkFor != NULL) {//returned not null then we have the evolved version
            printf("Removing Pokemon %s (ID %d).\n", pokedex[id-1].name, pokedex[id-1].id);
            //delete original and add evolved
            owner->pokedexRoot = freePokemon(owner->pokedexRoot ,id);//returns the new root of the pokedex after free
            insertPokemonNode(owner->pokedexRoot, evolvedPokemon);
            printf("Pokemon evolved from %s (ID %d) to %s (ID %d).\n",
                pokedex[id-1].name, pokedex[id-1].id, pokedex[evolvedId].name, pokedex[evolvedId].id);
        }//then we have is so we will delete this pokemon
        else {
            node->data->id = pokedex[evolvedId].id;
            node->data->hp = pokedex[evolvedId].hp;
            node->data->attack = pokedex[evolvedId].attack;
            node->data->name = node->data->name;
            node->data->TYPE = pokedex[evolvedId].TYPE;
            node->data->CAN_EVOLVE = pokedex[evolvedId].CAN_EVOLVE;
            printf("Pokemon evolved from %s (ID %d) to %s (ID %d).\n",
                pokedex[id-1].name, pokedex[id-1].id, pokedex[evolvedId].name, pokedex[evolvedId].id);
            return;
        }
    } else {
        printf("Cannot evolve.\n");
    }
}
void freePokemonNode(PokemonNode *node) {
    if (node == NULL) {
        return;
    }
    free(node->data);
    free(node);
}
void freePokemonTree(PokemonNode *root) {
    if (root == NULL) {
        return;
    }
    postOrderGeneric(root, freePokemonNode);
    root = NULL;
}
void freeOwnerNode(OwnerNode *owner) {
    freePokemonTree(owner->pokedexRoot);
    free(owner->ownerName);
    free(owner);
}


void deletePokedex(OwnerNode* node) {
    if (node == NULL) {
        return;
    }

    if (node == ownerHead) {//node is head
        if (node->next == NULL) {//one owner in the list
            freeOwnerNode(node);
            ownerHead = NULL;
            return;
        }

        //more than one owner in the list
        OwnerNode *tempForHead = node->next;
        OwnerNode *tempForTail = ownerHead;

        //go to the last node
        while (tempForTail->next != ownerHead) {
            tempForTail = tempForTail->next;
        }

        ownerHead = tempForHead;
        ownerHead->prev = tempForTail;
        tempForTail->next = ownerHead;

        freeOwnerNode(node);
        return;
    }

    //node is not the head
    if (node->next == ownerHead) { //last node
        node->prev->next = ownerHead;
        ownerHead->prev = node->prev;
        freeOwnerNode(node);
    } else { //in the middle
        node->prev->next = node->next;
        node->next->prev = node->prev;
        freeOwnerNode(node);
    }
}

OwnerNode *findOwnerByName(const char *name) {
    OwnerNode *iterator = ownerHead;
    if (ownerHead == NULL) {
        return NULL;
    }
    do {
        if (strcmp(iterator->ownerName, name) == 0) {
            return iterator;
        }
        iterator = iterator->next;
    } while (iterator != ownerHead);
    return NULL;
}

void mergePokedexMenu() {
    //check if there is at list 2 owners
    if (ownerHead == NULL || ownerHead->next == NULL) {
        printf("Not enough owners to merge.\n");
        return;
    }
    //menu for displaying
    printf("\n=== Merge Pokedexes ===\n");
    printf("Enter name of first owner: ");
    char* name1 = getDynamicInput();
    printf("Enter name of second owner: ");
    char* name2 = getDynamicInput();
    if (name1 == NULL || name2 == NULL) {
        exit(1);
    }
    OwnerNode* firstOwner = findOwnerByName(name1);
    OwnerNode* secondOwner = findOwnerByName(name2);
    if (firstOwner == NULL || secondOwner == NULL) {
        printf("One or both Owners not found.\n");
        return;
    }
    printf("Merging %s and %s...\n",firstOwner->ownerName, secondOwner->ownerName);

    //bfs search and add node to tree
    //insertPokemonNode() for each node in the second owner
    PokemonNode* root = secondOwner->pokedexRoot;
    if (root == NULL) {
        printf("Pokedex is empty.\n");
        return;
    }

    NodeArray nodeArray;
    initNodeArray(&nodeArray, 1);
    addNode(&nodeArray, root);

    int currentIndex = 0;
    while (currentIndex < nodeArray.size) {
        PokemonNode *current = nodeArray.nodes[currentIndex];
        insertPokemonNode(firstOwner->pokedexRoot, current);
        currentIndex++;
        if (current->left != NULL) {
            addNode(&nodeArray, current->left);
        }
        if (current->right != NULL) {
            addNode(&nodeArray, current->right);
        }
    }
    free(nodeArray.nodes);
    printf("Merge completed.\n");
    deletePokedex(secondOwner);
    printf("Owner '%s' has been removed after merging.\n", name2);

    free(name1);
    free(name2);
}

void swapOwnerData(OwnerNode *a, OwnerNode *b) {
    //setting a temp for switching
    PokemonNode *tempRoot = a->pokedexRoot;
    char *tempName = a->ownerName;

    // //setting a as b
    a->pokedexRoot = b->pokedexRoot;
    a->ownerName = b->ownerName;

    // //setting b as temp
    b->pokedexRoot = tempRoot;
    b->ownerName = tempName;
}

void sortOwners() {
    if (ownerHead == NULL || ownerHead->next == NULL || ownerHead->next == ownerHead) {//not enough for sorting
        printf("0 or 1 owners only => no need to sort.\n");
        return;
    }
    //because we have a circular list we can just go through it until all the list is sorted
    //first counting how much nodes we have
    int counter = 0;
    OwnerNode *iterator = ownerHead;
    do {
        counter++;
        iterator = iterator->next;
    } while (iterator != ownerHead);
    //go through the list until all of it is sorted (using a index integer to check if all of the list is sorted)
    int index = 0;
    while (index < counter-1) {
        index = 0;
        iterator = ownerHead;
        for (int i = 0; i < counter; i++) {
            if (strcmp(iterator->ownerName, iterator->next->ownerName) > 0) {
                swapOwnerData(iterator, iterator->next);
            } else {
                index++;
                iterator = iterator->next;
            }
        }
    }
    printf("Owners sorted by name.\n");
}

void printOwnersCircular(int nums, char direction) {
    if (ownerHead == NULL) {//it will break before but just in case :)
        return;
    }
    if (ownerHead->next == NULL) {
        if (direction == 'f' || direction == 'F') {
            for (int i = 1; i <= nums; i++) {
                printf("[%d] %s\n", i, ownerHead->ownerName);
            }
        }
        if (direction == 'b' || direction == 'B') {
            for (int i = 1; i <= nums; i++) {
                printf("[%d] %s\n", i, ownerHead->ownerName);
            }
        }
    }
    OwnerNode *iterator = ownerHead;
    if (direction == 'f' || direction == 'F') {
        for (int i = 1; i <= nums; i++) {
            printf("[%d] %s\n", i, iterator->ownerName);
            iterator = iterator->next;
        }
    }
    if (direction == 'b' || direction == 'B') {
        for (int i = 1; i <= nums; i++) {
            printf("[%d] %s\n", i, iterator->ownerName);
            iterator = iterator->prev;
        }
    }
}

void freeAllOwners() {
    if (ownerHead == NULL) {
        return;
    }
    if (ownerHead->next == NULL) {
        deletePokedex(ownerHead);
        return;
    }
    while (ownerHead->next != ownerHead) {
        deletePokedex(ownerHead->next);
    }
    deletePokedex(ownerHead);
}

int main()
{
    mainMenu();
    freeAllOwners();

    return 0;
}
