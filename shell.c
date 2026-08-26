#include<stdio.h>
#include<stdlib.h>

typedef struct directory directory;

struct directory{

	char name[100];
	char *data;
	directory *root_dir;
	directory *next_dir;
	directory *child_dir;
	directory *parent_dir;
	int is_file;
};

directory* create_directory() {

	directory *created_directory = malloc(sizeof(directory));
	created_directory -> root_dir   = NULL; /*  */
	created_directory -> next_dir   = NULL;
	created_directory -> child_dir  = NULL;
	created_directory -> parent_dir = NULL;
	created_directory -> is_file    = 0;
    return created_directory;
}

typedef enum{
    LS,
    PWD,
    WHOAMI,
    MKDIR,
    RM,
    TOUCH,
    MV,
    /* CLEAR, */
    CD,
    /* CP, */
    CAT,
    ERROR
} function_table;

void list_directory_contents(directory *dir);
void print_current_directory(directory *dir);
void who_am_i();
void make_directory(directory *dir, char *str);
void remove_file(directory *dir, char *str);
void touch_file(directory *dir, char *str);
void touch_with_data(directory *dir, char *str, char *input);
void move_or_rename(directory *dir, char *str);
void clear_screen();
directory* change_directory(directory *dir, char *str);
void copy();
void cat_file(directory *dir, char *file_name);

int compare(char *str_a,char *str_b);

void str_copy(char *str_a, char *str_b) {
	
	int i = 0;
	while(str_b[i] != '\0') {
		str_a[i] = str_b[i];
		i++;
	}
}

int str_contains(char *str, char target) {

	int i = 0;
	while(str[i] != '\0') {
		if(str[i] == target)
			return 1;
		i++;
	}
	return 0;
}

void cat_file(directory *dir, char *filename) {

	directory *temp = dir -> child_dir;
	if(temp == NULL) {
		printf("No file named %s is here.",filename);
		return;
	}
	while(compare(temp -> name, filename) != 1) {
		if(temp -> next_dir != NULL)
			temp = temp -> next_dir;
		else {
			printf("no file named %s exist", filename);
			return;
		}
	}
	printf("%s", temp -> data);
	return;
}

int get_length(char *str) {

	if(str == NULL)
		return 0;
	int i = 0;
	while(str[i] != '\0')
		i++;
	return i;
}

int compare(char* str_a, char* str_b) {

	int len_a = get_length(str_a);
	if(len_a != get_length(str_b))
		return 0;
	int i = 0;
	while(i < len_a) {
		if(str_a[i] != str_b[i]) 
			return 0;
		i++;
	}
	return 1;
}

char* nested_dir_changer(directory **dir, char *str) {

    char arr[100][100];
    int i = 0, j = 0,k = 0;
    while(str[0] != '\n' && str[0] != '\0') {
        if(!str_contains(str, '/'))
            break;
        while(str[0] != '/' && str[0] != '\n' && str[i] != '\0') {
            arr[k][j] = str[0];
            i++;
            j++;
            str++;
        }
        str++;
        *dir = change_directory(*dir, arr[k]);
        j = 0;
        k++;
        i++;
    }
    return str;
}

directory* change_directory(directory *dir, char *str) {

    if(str_contains(str, '/') && get_length(str) > 1) {
        str = nested_dir_changer(&dir, str);
    }
	if(compare(str, "/") == 1) {
		while(dir -> parent_dir != NULL) {
			dir = dir -> parent_dir;
		}
		return dir;
	}
	directory *temp = dir -> child_dir;
	while(compare(temp -> name, str) != 1) {
		if(temp -> next_dir != NULL) 
			temp = temp -> next_dir;
		else {
			printf("No directory named %s found.",str);
			return dir;
		}
	}
	dir = temp;
	return dir;
}

void list_directory_contents(directory *dir) {

	directory *temp = dir -> child_dir;
	if(temp == NULL) {
		printf("directory is Empty.\n");
		return;
	}
	printf("Name    |      Type\n");
	printf("--------------------\n");
	char c = 'D';
	while((temp -> next_dir) != NULL) {
		if(temp -> is_file == 1) {
			c = 'F';
		}
		printf("%-8s|%2c\n",temp -> name, c);
		temp = temp -> next_dir;
	}
	printf("%-8s|%2c\n",temp -> name, c);
}

void print_current_directory(directory *dir) {
	
	printf("\n%s\n", dir -> name);
}

void who_am_i() {
	
	printf("root\n");
}

void make_directory(directory *dir, char *Name) {

    directory *constant = dir;
    if(str_contains(Name, ' ')) {
        char arr[20][80];
        int i = 0;
        int j = 0;
        int x = 0;
        while(Name[i] != '\n' && Name[i] != '\0') {
            while(Name[i] != ' ' && Name[i] != '\n' && Name[i] != '\0') {
                arr[x][j] = Name[i];
                Name++;
                j++;
            }
            Name++;
            arr[x][j] = '\0';
            j++;
            if(str_contains(arr[x], '/')) {
                char *ab = nested_dir_changer(&dir, arr[x]);
                make_directory(dir, ab);
                dir = constant;
            }
            else {
                dir = constant;
                make_directory(dir, arr[x]);
            }
            x++;
        }
        return;
    }
    else if(str_contains(Name, '/')) {
        char *ab = nested_dir_changer(&dir, Name);
        make_directory(dir, ab);
        dir = constant;
        return;
    }
	if(dir -> child_dir == NULL) {
		dir -> child_dir               = create_directory();
		dir -> child_dir -> parent_dir = dir;
		str_copy(dir -> child_dir -> name, Name);
		return;
	}
	directory *temp = dir -> child_dir;
	while(temp -> next_dir != NULL) {
		temp = temp -> next_dir;
	}
	directory *created_dir    = create_directory();
	str_copy(created_dir -> name, Name);
	created_dir -> parent_dir = dir;
	temp -> next_dir          = created_dir;
	return;
}

void remove_file(directory *dir, char *str) {

    directory *constant = dir;
    if(str_contains(str, ' ')) {
        char arr[20][80];
        int i = 0;
        int j = 0;
        int x = 0;
        while(str[i] != '\n' && str[i] != '\0') {
            while(str[i] != ' ' && str[i] != '\n' && str[i] != '\0') {
                arr[x][j] = str[i];
                str++;
                j++;
            }
            str++;
            arr[x][j] = '\0';
            j++;
            if(str_contains(arr[x], '/')) {
                char *ab = nested_dir_changer(&dir, arr[x]);
                remove_file(dir, ab);
                dir = constant;
            }
            else {
                dir = constant;
                remove_file(dir, arr[x]);
            }
            x++;
        }
        return;
    }
    else if(str_contains(str, '/')) {
       char *ab = nested_dir_changer(&dir, str);
        remove_file(dir, ab);
        dir = constant;
        return;
    }
	directory *temp = dir -> child_dir;
	directory *prev = temp;
	while(compare(temp -> name, str) != 1) {
		if(temp != NULL) {
			prev = temp;
			temp = temp -> next_dir;
		}
		else {
			printf("No filed named %s exists\n",str);
			return;
		}
	}
	if(temp -> next_dir != NULL)
		prev -> next_dir = temp -> next_dir;
	else
		prev -> next_dir = NULL;
	if(temp == dir -> child_dir) {
		if(temp -> next_dir != NULL)
			dir -> child_dir = temp -> next_dir;
		else
			dir -> child_dir = NULL;
	}
	free(temp);
	return;
}

void touch_file(directory *dir, char *str) {
	
    directory *constant = dir;
    if(str_contains(str, ' ')) {
        char arr[20][80];
        int i = 0;
        int j = 0;
        int x = 0;
        while(str[i] != '\n' && str[i] != '\0') {
            while(str[i] != ' ' && str[i] != '\n' && str[i] != '\0') {
                arr[x][j] = str[i];
                str++;
                j++;
            }
            str++;
            arr[x][j] = '\0';
            j++;
            if(str_contains(arr[x], '/')) {
                char *ab = nested_dir_changer(&dir, arr[x]);
                touch_file(dir, ab);
                dir = constant;
            }
            else {
                dir = constant;
                touch_file(dir, arr[x]);
            }
            x++;
        }
        return;
    }
    else if(str_contains(str, '/')) {
        char *ab = nested_dir_changer(&dir, str);
        touch_file(dir, ab);
        dir = constant;
        return;
    }
	if(dir -> child_dir == NULL) {
		dir -> child_dir               = create_directory();
		dir -> child_dir -> parent_dir = dir;
		str_copy(dir -> child_dir -> name, str);
		return;
	}
	directory *temp = dir -> child_dir;
	while(temp -> next_dir != NULL)
		temp = temp -> next_dir;
	directory *created_dir    = create_directory();
	str_copy(created_dir -> name, str);
	created_dir -> parent_dir = dir;
	temp -> next_dir          = created_dir;
	return;
}

void touch_with_data(directory *dir, char *str, char *input) {
	
	if(dir -> child_dir == NULL) {
		dir -> child_dir               = create_directory();
		dir -> child_dir -> parent_dir = dir;
		dir -> child_dir -> data       = malloc(sizeof(input));
		dir -> child_dir -> is_file    = 1;
		str_copy(dir -> child_dir -> name, str);
		str_copy(dir -> child_dir -> data, input);
		return;
	}
	directory *temp = dir -> child_dir;
	while(temp -> next_dir != NULL)
		temp = temp -> next_dir;
	directory *created_dir    = create_directory();
	created_dir -> data       = malloc(sizeof(input));
	str_copy(created_dir -> data, input);
	str_copy(created_dir -> name, str);
	created_dir -> is_file    = 1;
	created_dir -> parent_dir = dir;
	temp -> next_dir          = created_dir;
	return;
}

void move_or_rename(directory *dir, char *str) {

}

void test();

int main() {

	directory *dir          = create_directory();
    function_table commands;
	str_copy(dir -> name, "root");
	char input[500];
    char function_name[20];
    char arguments[100];
	while(1) {
		printf("%s $ ",dir -> name);
		fgets(input, sizeof(input), stdin);
		int i = 0;
        int j = 0;
        while(input[i] != ' ' && input[i] != '\n' && input[i] != '\0') {
            function_name[i] = input[i];
            i++;
        }
        function_name[i] = '\0';
        i++;
        while(input[i] != '\n' && input[i] != '\0') {
            arguments[j] = input[i];
            j++;
            i++;
        }
        arguments[j] = '\0';
        j++;

		i = 0;
        if(compare(function_name, "ls"))
            commands = LS;
        else if(compare(function_name, "pwd"))
            commands = PWD;
        else if(compare(function_name, "whoami"))
            commands = WHOAMI;
        else if(compare(function_name, "mkdir"))
            commands = MKDIR;
        else if(compare(function_name, "rm"))
            commands = RM;
        else if(compare(function_name, "touch"))
            commands = TOUCH;
        else if(compare(function_name, "mv"))
            commands = MV;
        /* else if(compare(function_name, "clear")) */
        /*     commands = CLEAR; */
        else if(compare(function_name, "cd"))
            commands = CD;
        /* else if(compare(function_name, "cp")) */
        /*     commands = CP; */
        else if(compare(function_name, "cat"))
            commands = CAT;
        else if(compare(function_name, "exit"))
            commands = ERROR;

        switch(commands) {
            case LS:
                list_directory_contents(dir);
                break;
            case PWD:
                print_current_directory(dir);
                break;
            case WHOAMI:
                who_am_i();
                break;
            case MKDIR:
                make_directory(dir, arguments);
                break;
            case RM:
                remove_file(dir, arguments);
                break;
            case TOUCH:
                touch_file(dir, arguments);
                break;
            case MV:
                move_or_rename(dir, arguments);
                break;
            /* case CLEAR: */
            /*     clear_screen(); */
            /*     break; */
            case CD:
                dir = change_directory(dir, arguments);
                break;
            /* case CP: */
            /*     copy(); */
            /*     break; */
            case CAT:
                cat_file(dir, arguments);
                break;
            case ERROR:
                exit(1);
                break;
            default:
                printf("Enter valid Command:");
                break;
        }
    }
	test();
	return 0;
}

void test() {

	directory *dir = create_directory();
	make_directory(dir, "Dummy_folder");
	if(compare(dir -> child_dir -> name, "Dummy_folder") != 1) {
		printf("Make directory test 1 failed\n");
		exit(1);
	}	else {
		printf("Make directory test 1 passed\n");
	}
	make_directory(dir, "Dummy_folder_b");
	if(compare(dir -> child_dir -> next_dir -> name, "Dummy_folder_b") != 1) {
		printf("Make directory test 2 failed\n");
		exit(1);
	}	else {
		printf("Make directory test 2 passed\n");
	}
	remove_file(dir, "Dummy_folder_b");
	if(dir -> child_dir -> next_dir != NULL) {
		printf("remove test 1 failed\n");
		exit(1);
	}	else {
		printf("remove test 1 passed\n");
	}
	remove_file(dir, "Dummy_folder");
	if(dir -> child_dir != NULL) {
		printf("remove test 2 failed\n");
		exit(1);
	}	else {
		printf("remove test 2 passed\n");
	}
	touch_file(dir, "Anything_file");
	if(dir -> child_dir == NULL) {
		printf("touch test 1 failed\n");
		exit(1);
	}	else {
		printf("touch test 1 passed\n");
	}
	move_or_rename(dir, "Anything_file Renamed_file");
	if(compare(dir -> child_dir -> name, "Renamed_file") != 1) {
		printf("Rename test 1 failed\n");
		exit(1);
	}	else {
		printf("Renme test 1 passed\n");
	}
}
